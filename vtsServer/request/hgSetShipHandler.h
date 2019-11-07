#pragma once

#include "frame/vtsRequestHandler.h"

class DBSetShipHandler;

class hgSetShipHandler :
    public vtsRequestHandler
{
public:
    hgSetShipHandler();
    ~hgSetShipHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBSetShipHandler* db);

protected:
};

vtsDECLARE_REQUEST_HANDLER("SetShip", hgSetShipHandler);