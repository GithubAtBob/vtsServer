#include "StdAfx.h"

#include "vtsTimerHandler.h"

#include "vtsLog.h"
#include "vtsServer.h"


vtsTimerHandler::vtsTimerHandler(const std::string& name)
    : _name(name),
    _server(nullptr),
    _durationSec(0.0),
    _timer(nullptr),
    _autoDelete(false),
    _canceled(false)
{
}

vtsTimerHandler::~vtsTimerHandler(void)
{
    delete _timer;
    _timer = nullptr;
}

std::map<std::string, vtsTimerHandler*>& vtsTimerHandler::handlerMap()
{
    static std::map<std::string, vtsTimerHandler*> s_inst;
    return s_inst;
}

void vtsTimerHandler::init(vtsServer* server)
{
    _server = server;
    if (workMode() == WorkMode_main)
        _timer = new boost::asio::deadline_timer(_server->mainService());
    else
        _timer = new boost::asio::deadline_timer(_server->threadService());
}

bool vtsTimerHandler::run()
{
    if (!_timer)
    {
        vtsWarning << "timer do not init: " << _name;
        return false;
    }

    if (_durationSec <= 0.0)
    {
        vtsWarning << "timer duration sec error: " << _name << " duration: " << _durationSec;
        return false;
    }

    _timer->expires_from_now(boost::posix_time::millisec(_durationSec*1000));
    _timer->async_wait(boost::bind(&vtsTimerHandler::whenExpired, this, boost::asio::placeholders::error));
    return true;
}

void vtsTimerHandler::whenExpired(const boost::system::error_code& e)
{
    handle(e);
    if (!e && !_canceled)
    {
        _timer->expires_from_now(boost::posix_time::millisec(_durationSec*1000));
        _timer->async_wait(boost::bind(&vtsTimerHandler::whenExpired, this, boost::asio::placeholders::error));
    }
    else
    {
        if (_autoDelete)
        {
            auto &handlerMap = vtsTimerHandler::handlerMap();
            if (handlerMap.find(_name) != handlerMap.end())
            {
                handlerMap.erase(_name);
            }
            delete this;
        }
    }
}

bool vtsTimerHandler::cancel(bool autoDelete)
{
    if (!_timer)
    {
        vtsWarning << "timer do not init: " << _name;
        return false;
    }

    _autoDelete = autoDelete;

    _timer->cancel();
    _canceled = true;
    return true;
}

void vtsTimerHandler::setDuration(double sec)
{
    _durationSec = sec;
}

vtsServer * vtsTimerHandler::server()
{
    return _server;
}

bool vtsTimerHandler::start(vtsServer* server)
{
    assert(_durationSec > 0.0);

    auto &handlerMap = vtsTimerHandler::handlerMap();
    if (handlerMap.find(_name) != handlerMap.end())
    {
        vtsWarning << "timer handler exits. name: " << _name;
        return false;
    }
    handlerMap[_name] = this;

    this->init(server);

    return this->run();
}

vtsTimerHandler* vtsTimerHandler::getTimer(const std::string& name)
{
    auto &handlerMap = vtsTimerHandler::handlerMap();
    auto found = handlerMap.find(name);
    if (found == handlerMap.end())
        return nullptr;

    return found->second;
}

bool vtsTimerHandler::clearTimer(const std::string& name)
{
    auto &handlerMap = vtsTimerHandler::handlerMap();
    auto found = handlerMap.find(name);
    if (found == handlerMap.end())
        return false;

    return found->second->cancel(true);
}
