#pragma once

#include "frame/vtsRequestHandler.h"

class hgHeartBeatHandler :
    public vtsRequestHandler
{
public:
    hgHeartBeatHandler();
    ~hgHeartBeatHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

protected:
};

vtsDECLARE_REQUEST_HANDLER("HeartBeat", hgHeartBeatHandler);