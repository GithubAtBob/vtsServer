#pragma once

#include <string>
#include <map>
#include <boost/asio.hpp>

class vtsServer;
class vtsRequestHandler;

/*!
 * ��ʱ������
 * @note ʹ��vtsSETUP_HANDLER���õĶ�ʱ���ڳ�������ʱ�Զ�����,�����������ɳ����й�
 * @note �������к����õĶ�ʱ��,�������ڿ�����Ա�Լ�����@see cancel
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
         * ���߳�ִ�ж�ʱ��
         */
        WorkMode_main = 0,

        /*!
         * ���߳�ִ�ж�ʱ��
         */
        WorkMode_thread = 1,

        /*!
         * �̶���ʱ�������������߳�ִ��
         */
         // WorkMode_persistant_main = 2,

        /*!
         * �̶���ʱ�������������߳�ִ��
         */
         // WorkMode_persistant_thread = 3,
    };

    /*!
     * ָ������ģʽ
     * @see vtsTimerHanlder::WorkMode
     */
    virtual WorkMode workMode() = 0;

    virtual void handle(const boost::system::error_code& e) = 0;

    /*!
     * ȡ����ʱ��
     * @param autoDelete �Ƿ��Զ�ɾ��;trueʱ,�ڴ�����ʱ���¼���,timer��delete�Լ�
     * @note ��autoDelete����Ϊfalse,��Ҫ�ֶ�ɾ��
     */
    bool cancel(bool autoDelete);

    /*!
     * ���ö�ʱ����ʱʱ��
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