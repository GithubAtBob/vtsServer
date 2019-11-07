#pragma once

#include "frame/vtsRequestHandler.h"

class DBTurnCircleHandler;

class hgTurnCircleHandler :
    public vtsRequestHandler
{
public:
    hgTurnCircleHandler();
    ~hgTurnCircleHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBTurnCircleHandler* db);

protected:
    
};

vtsDECLARE_REQUEST_HANDLER("TurnCircle", hgTurnCircleHandler);