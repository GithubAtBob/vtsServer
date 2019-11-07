#pragma once

#include "frame/vtsRequestHandler.h"

class DBAlgorOwnShipHandler;
class hgAlgorOwnShipHandler :
    public vtsRequestHandler
{
public:
    hgAlgorOwnShipHandler();
    ~hgAlgorOwnShipHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBAlgorOwnShipHandler* db);

protected:
};

vtsDECLARE_REQUEST_HANDLER("AlgorOwnShip", hgAlgorOwnShipHandler);