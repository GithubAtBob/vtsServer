#pragma once

#include "frame/vtsRequestHandler.h"

class DBChannelHandler;
class ChannelRequest;
class ChannelHandler :
    public vtsRequestHandler
{
public:
    ChannelHandler();
    ~ChannelHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBChannelHandler* db);

    void UpdateFunction(ChannelRequest msg);

    void RemoveFunction(ChannelRequest msg);

    void AllFunction(ChannelRequest msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};
