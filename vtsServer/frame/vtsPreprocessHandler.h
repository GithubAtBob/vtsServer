#pragma once

#include <list>
#include <boost/noncopyable.hpp>

#include "vtsConnection.h"

class vtsPreprocessHandler :
    private boost::noncopyable
{
public:
    virtual void whenConnectionConnected(ConnectionPtr c) { }

    virtual void whenConnectionDisconnected(ConnectionPtr c) { }

    virtual void beforeServerListen(vtsServer *s, const std::string& address, const std::string& port) { }

    virtual void beforeServerRun(vtsServer *s) { }

    virtual void afterServerRun(vtsServer *s) { }

    virtual void beforeServerStop(vtsServer *s) { } 

    virtual void afterServerStop(vtsServer *s) { }

    static std::list<vtsPreprocessHandler*> &handlerList();
};

#define vtsSETUP_PREPROCESS_HANDLER(_handler) \
namespace _internal_\
{ \
    class _internal##_handler##Creator \
    { \
    public: \
        _internal##_handler##Creator() \
        { \
            _handler *p = new _handler(); \
            vtsPreprocessHandler::handlerList().push_back(p); \
        } \
    }; \
    static _internal##_handler##Creator s_##_handler##CreatorInst; \
}