#pragma once

#include <string>
#include <map>
#include <boost/asio.hpp>

class vtsServer;
class vtsRequestHandler;

/*!
 * 定时器处理
 * @note 使用vtsSETUP_HANDLER设置的定时器在程序启动时自动启用,其生命周期由程序托管
 * @note 程序运行后设置的定时器,生命周期开发人员自己管理@see cancel
 */
class vtsTimerHandler :
    private boost::noncopyable
{
public:
    explicit vtsTimerHandler(const std::string& name);
    ~vtsTimerHandler(void);

    enum WorkMode
    {
        /*!
         * 主线程执行定时器
         */
        WorkMode_main = 0,

        /*!
         * 子线程执行定时器
         */
        WorkMode_thread = 1,

        /*!
         * 固定定时器触发，在主线程执行
         */
         // WorkMode_persistant_main = 2,

        /*!
         * 固定定时器触发，在子线程执行
         */
         // WorkMode_persistant_thread = 3,
    };

    /*!
     * 指定工作模式
     * @see vtsTimerHanlder::WorkMode
     */
    virtual WorkMode workMode() = 0;

    virtual void handle(const boost::system::error_code& e) = 0;

    /*!
     * 取消定时器
     * @param autoDelete 是否自动删除;true时,在触发定时器事件后,timer会delete自己
     * @note 如autoDelete设置为false,需要手动删除
     */
    bool cancel(bool autoDelete);

    /*!
     * 设置定时器超时时间
     */
    void setDuration(double sec);

    double duration()
    {
        return _durationSec;
    }

    const std::string &name()
    {
        return _name;
    }

    bool canceled()
    {
        return _canceled;
    }

    bool start(vtsServer* server);

    static std::map<std::string, vtsTimerHandler*>& handlerMap();

    static vtsTimerHandler* getTimer(const std::string& name);

    static bool clearTimer(const std::string& name);

    vtsServer *server();

protected:

    void init(vtsServer* server);

    bool run();

private:

    void whenExpired(const boost::system::error_code& e);

    boost::asio::deadline_timer *_timer;

    vtsServer *_server;

    std::string _name;

    double _durationSec;

    bool _canceled;

    bool _autoDelete;

    friend class vtsRequestHandler;
    friend class vtsServer;
};

#define vtsSETUP_TIMER(_name, _sec, _handler) \
namespace _internal_\
{ \
    class _internal##_handler##Creator \
    { \
    public: \
        _internal##_handler##Creator() \
        { \
            assert(vtsTimerHandler::handlerMap().find(_name) ==  \
            vtsTimerHandler::handlerMap().end()); \
            _handler *p = new _handler(_name); \
            p->setDuration(_sec); \
            vtsTimerHandler::handlerMap()[_name] = p; \
        } \
    }; \
    static _internal##_handler##Creator s_##_handler##CreatorInst; \
}