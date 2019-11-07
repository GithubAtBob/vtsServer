#pragma once

#include "frame/vtsRequestHandler.h"

class DBCPAHandler;

class hgFuseSetHandler :
    public vtsRequestHandler
{
public:
    hgFuseSetHandler();
    ~hgFuseSetHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);


protected:
};

vtsDECLARE_REQUEST_HANDLER("FuseSet", hgFuseSetHandler);