
#include "stdafx.h"

#include "vtsRequestHandler.h"

#include "vtsServer.h"
#include "vtsTimerHandler.h"

vtsRequestHandler::vtsRequestHandler()
{
}

vtsRequestHandler::~vtsRequestHandler(void)
{
}

/*static*/
std::map<std::string, fnRequestHandlerCreator>& vtsRequestHandler::requestHandlerMap()
{
    static std::map<std::string, fnRequestHandlerCreator> s_requestHandlerMap;
    return s_requestHandlerMap;
}

bool vtsRequestHandler::setTimer(vtsTimerHandler *handler)
{
    assert(handler != nullptr);
    return handler->start(&_connection->server());
}

vtsTimerHandler * vtsRequestHandler::getTimer(const std::string& name)
{
    return vtsTimerHandler::getTimer(name);
}

bool vtsRequestHandler::clearTimer(const std::string& name)
{
    return vtsTimerHandler::clearTimer(name);
}