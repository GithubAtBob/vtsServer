#pragma once

#include "frame/vtsRequestHandler.h"

class hgServerModeHandler :
    public vtsRequestHandler
{
public:
    hgServerModeHandler();
    ~hgServerModeHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

protected:
};

vtsDECLARE_REQUEST_HANDLER("hgServerMode", hgServerModeHandler);