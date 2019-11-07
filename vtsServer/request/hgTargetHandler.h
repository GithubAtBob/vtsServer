#pragma once

#include "frame/vtsRequestHandler.h"

class DBLoginHandler;

class hgTargetHandler :
    public vtsRequestHandler
{
public:
    hgTargetHandler();
    ~hgTargetHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);



protected:
};

vtsDECLARE_REQUEST_HANDLER("AisMessage", hgTargetHandler);