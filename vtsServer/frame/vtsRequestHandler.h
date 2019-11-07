#pragma once

#include <string>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>

#include <QVariant>

#include "google/protobuf/message.h"

#include "vtsLog.h"
#include "vtsConnection.h"


class vtsRequestHandler;
class vtsDatabaseHandler;
class vtsTimerHandler;

typedef vtsRequestHandler* (*fnRequestHandlerCreator)(const std::string&, ConnectionPtr);

class vtsRequestHandler :
    private boost::noncopyable
{
public:

    /*!
     * vtsRequestHandler工作方式.
     */
    enum WorkMode
    {

        /*!
         * 自动删除,在调用handle函数后马上delete
         * @note Handler有调用responseAsync,callLater,postToDB;不能使用该方式
         * @see vtsRequsetHandler::responseAsync vtsRequestHanlder::callLater vtsRequestHandler::postToDB
         */
        Work_Delete_Auto = 0,

        /*!
         * 手动删除,一般是在需要调用异步函数时才需要指定手动删除
         * @see vtsRequsetHandler::responseAsync vtsRequestHanlder::callLater vtsRequestHandler::postToDB
         */
        Work_Delete_Manual = 1,

        /*!
         * 添加进缓冲
         * 指定这种方式后,后续所有相同的请求都使用同一个实例来处理.
         * @note 指定该方式,reset函数的状态重置就尤为重要
         * @see vtsRequestHandler::reset
         */
        Work_Cached = 2,
    };

    vtsRequestHandler();

    virtual ~vtsRequestHandler(void);

    /*!
     * 初始化函数,由框架调用;
     */
    void init(const std::string& msgType, ConnectionPtr connection)
    {
        _msgType = msgType;
        _connection = connection;
    }

    /*!
     * 重置状态
     * 调用handle前均会调用
     * @note reset函数在Work_Cached方式下的应用.
     */
    virtual void reset() {}

    /*!
     * 指定工作模式
     * @see vtsRequestHandler::WorkMode
     */
    virtual WorkMode workMode() = 0;

    /*!
     * 请求处理事件.业务代码的入口.
     * @see 指定为Work_Delete_Auto,调用该函数后会自动删除
     */
    virtual void handle(boost::asio::const_buffer& data) = 0;

    /*!
     * 发送响应消息
     * @param[in] handler 回调函数
     *  函数签名 void func(const boost::system::error_code &e)
     *  或者使用boost::bind
     * @note 与response函数的差别:异步函数,调用后马上返回.
     */
    template <typename CompletionHandler>
    inline void response(google::protobuf::Message& msg, BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        assert(workMode() != Work_Delete_Auto);
        _connection->write(_msgType, msg, handler);
    }

    /*!
     * 发送响应消息
     * @note 与responseAsync函数的差别:阻塞函数,直到数据发送成功才返回
     */
    void response(google::protobuf::Message& msg)
    {
        _connection->write(_msgType, msg);
    }

    /*!
     * 投递异步函数
     * @pararm[in] handler 回调函数
     *  函数签名: void func() 或者 boost::bind
     * @note 在主线程执行
     */
    template <typename CompletionHandler>
    inline void post(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        assert(workMode() != Work_Delete_Auto);
        _connection->mainService().post(handler);
    }

    /*!
     * 投递异步函数
     * @pararm[in] handler 回调函数
     *  函数签名: void func() 或者 boost::bind
     * @note 在业务线程执行,和post不一致。
     */
    template <typename CompletionHandler>
    inline void postToThread(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        assert(workMode() != Work_Delete_Auto);
        _connection->threadService().post(handler);
    }

    /*!
     * 设置定时器
     * @param[in] handler 回调函数
     *  函数签名: void function(const boost::system::error_code& e)或者boost::bind
     * @note 定时器只有一次性,如要设置循环的,在回调函数中继续调用callLater,但推荐使用setTimer函数 
     * @note 回调函数handler的error_code类型很重要,可以区分是超时执行还是被cancel执行
     *       判断方法: e == boost::asio::error::operation_aborted被cancel
     *       或者 if (!e) 超时执行
     */
    template <typename TimerHandler>
    inline boost::asio::deadline_timer& callLater(double sec, BOOST_ASIO_MOVE_ARG(TimerHandler) handler)
    {
        assert(workMode() != Work_Delete_Auto);
        boost::asio::deadline_timer *timer = new boost::asio::deadline_timer(_connection->mainService());
        timer->expires_from_now(boost::posix_time::millisec(sec*1000));
        timer->async_wait([handler, timer](const boost::system::error_code& e)
        {
            handler(e);
            delete timer;
        });
        return *timer;
    }

    /*!
     * 设置一个定时器
     * @param handler 定时器处理函数主体
     * @note 定时器的name可以重复
     * @note 该定时器的生命周期需要自己管理
     * @note handler调用cancel时需要指定是自动删除还是非自动删除@see vtsTimerHandler::cancel
     */
    bool setTimer(vtsTimerHandler *handler);

    vtsTimerHandler *getTimer(const std::string& name);

    bool clearTimer(const std::string& name);

    /*!
     * 异步处理数据库业务
     * @param[in] dbhandler 数据库业务处理类,@see vtsDatabaseHandler
     * @param[in] handler 回调函数
     *  函数签名: void func() 或者 boost::bind
     * @note 与dispatchToDB的差别:异步函数,调用后马上返回
     * @note dbhandler会在子线程中处理,注意线程同步问题
     */
    template <typename CompletionHandler>
    inline void postToDB(vtsDatabaseHandler* dbhandler, BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        _connection->postToDB(dbhandler, handler);
    }

    /*!
     * 同步处理数据库业务
     * @param[in] dbhandler 数据库业务处理类,@see vtsDatabaseHandler
     * @note 与postToDB的差别:同步函数,调用直到数据库业务处理完毕才返回
     */
    void dispatchToDB(vtsDatabaseHandler* dbhandler)
    {
        _connection->dispatchToDB(dbhandler);
    }

    static std::map<std::string, fnRequestHandlerCreator>& requestHandlerMap();

    ConnectionPtr connection()
    {
        return _connection;
    }

    const std::string msgType()
    {
        return _msgType;
    }

private:

    ConnectionPtr _connection;

    std::string _msgType;
};

#define vtsDECLARE_REQUEST_HANDLER(_name, _handler) \
    namespace _internal_\
    { \
        vtsRequestHandler* create##_handler (const std::string& msgType, ConnectionPtr connection) \
        { \
            _handler *p = new _handler(); \
            p->init(msgType, connection); \
            return p; \
        } \
        class _internal##_handler##Creator \
        { \
        public: \
            _internal##_handler##Creator() \
            { \
                assert(vtsRequestHandler::requestHandlerMap().find(_name) ==  \
                    vtsRequestHandler::requestHandlerMap().end()); \
                vtsRequestHandler::requestHandlerMap()[_name] = create##_handler; \
            } \
        }; \
        static _internal##_handler##Creator s_##_handler##CreatorInst; \
    } 