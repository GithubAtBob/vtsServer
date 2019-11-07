#pragma once

#include "frame/vtsRequestHandler.h"

class DBMovementEndHandler;

class hgMovementEndHandler :
    public vtsRequestHandler
{
public:
    hgMovementEndHandler();
    ~hgMovementEndHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBMovementEndHandler* db);

protected:
};

vtsDECLARE_REQUEST_HANDLER("MovementEnd", hgMovementEndHandler);