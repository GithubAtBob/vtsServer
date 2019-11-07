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
     * vtsRequestHandler������ʽ.
     */
    enum WorkMode
    {

        /*!
         * �Զ�ɾ��,�ڵ���handle����������delete
         * @note Handler�е���responseAsync,callLater,postToDB;����ʹ�ø÷�ʽ
         * @see vtsRequsetHandler::responseAsync vtsRequestHanlder::callLater vtsRequestHandler::postToDB
         */
        Work_Delete_Auto = 0,

        /*!
         * �ֶ�ɾ��,һ��������Ҫ�����첽����ʱ����Ҫָ���ֶ�ɾ��
         * @see vtsRequsetHandler::responseAsync vtsRequestHanlder::callLater vtsRequestHandler::postToDB
         */
        Work_Delete_Manual = 1,

        /*!
         * ��ӽ�����
         * ָ�����ַ�ʽ��,����������ͬ������ʹ��ͬһ��ʵ��������.
         * @note ָ���÷�ʽ,reset������״̬���þ���Ϊ��Ҫ
         * @see vtsRequestHandler::reset
         */
        Work_Cached = 2,
    };

    vtsRequestHandler();

    virtual ~vtsRequestHandler(void);

    /*!
     * ��ʼ������,�ɿ�ܵ���;
     */
    void init(const std::string& msgType, ConnectionPtr connection)
    {
        _msgType = msgType;
        _connection = connection;
    }

    /*!
     * ����״̬
     * ����handleǰ�������
     * @note reset������Work_Cached��ʽ�µ�Ӧ��.
     */
    virtual void reset() {}

    /*!
     * ָ������ģʽ
     * @see vtsRequestHandler::WorkMode
     */
    virtual WorkMode workMode() = 0;

    /*!
     * �������¼�.ҵ���������.
     * @see ָ��ΪWork_Delete_Auto,���øú�������Զ�ɾ��
     */
    virtual void handle(boost::asio::const_buffer& data) = 0;

    /*!
     * ������Ӧ��Ϣ
     * @param[in] handler �ص�����
     *  ����ǩ�� void func(const boost::system::error_code &e)
     *  ����ʹ��boost::bind
     * @note ��response�����Ĳ��:�첽����,���ú����Ϸ���.
     */
    template <typename CompletionHandler>
    inline void response(google::protobuf::Message& msg, BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        assert(workMode() != Work_Delete_Auto);
        _connection->write(_msgType, msg, handler);
    }

    /*!
     * ������Ӧ��Ϣ
     * @note ��responseAsync�����Ĳ��:��������,ֱ�����ݷ��ͳɹ��ŷ���
     */
    void response(google::protobuf::Message& msg)
    {
        _connection->write(_msgType, msg);
    }

    /*!
     * Ͷ���첽����
     * @pararm[in] handler �ص�����
     *  ����ǩ��: void func() ���� boost::bind
     * @note �����߳�ִ��
     */
    template <typename CompletionHandler>
    inline void post(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        assert(workMode() != Work_Delete_Auto);
        _connection->mainService().post(handler);
    }

    /*!
     * Ͷ���첽����
     * @pararm[in] handler �ص�����
     *  ����ǩ��: void func() ���� boost::bind
     * @note ��ҵ���߳�ִ��,��post��һ�¡�
     */
    template <typename CompletionHandler>
    inline void postToThread(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        assert(workMode() != Work_Delete_Auto);
        _connection->threadService().post(handler);
    }

    /*!
     * ���ö�ʱ��
     * @param[in] handler �ص�����
     *  ����ǩ��: void function(const boost::system::error_code& e)����boost::bind
     * @note ��ʱ��ֻ��һ����,��Ҫ����ѭ����,�ڻص������м�������callLater,���Ƽ�ʹ��setTimer���� 
     * @note �ص�����handler��error_code���ͺ���Ҫ,���������ǳ�ʱִ�л��Ǳ�cancelִ��
     *       �жϷ���: e == boost::asio::error::operation_aborted��cancel
     *       ���� if (!e) ��ʱִ��
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
     * ����һ����ʱ��
     * @param handler ��ʱ������������
     * @note ��ʱ����name�����ظ�
     * @note �ö�ʱ��������������Ҫ�Լ�����
     * @note handler����cancelʱ��Ҫָ�����Զ�ɾ�����Ƿ��Զ�ɾ��@see vtsTimerHandler::cancel
     */
    bool setTimer(vtsTimerHandler *handler);

    vtsTimerHandler *getTimer(const std::string& name);

    bool clearTimer(const std::string& name);

    /*!
     * �첽�������ݿ�ҵ��
     * @param[in] dbhandler ���ݿ�ҵ������,@see vtsDatabaseHandler
     * @param[in] handler �ص�����
     *  ����ǩ��: void func() ���� boost::bind
     * @note ��dispatchToDB�Ĳ��:�첽����,���ú����Ϸ���
     * @note dbhandler�������߳��д���,ע���߳�ͬ������
     */
    template <typename CompletionHandler>
    inline void postToDB(vtsDatabaseHandler* dbhandler, BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        _connection->postToDB(dbhandler, handler);
    }

    /*!
     * ͬ���������ݿ�ҵ��
     * @param[in] dbhandler ���ݿ�ҵ������,@see vtsDatabaseHandler
     * @note ��postToDB�Ĳ��:ͬ������,����ֱ�����ݿ�ҵ������ϲŷ���
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