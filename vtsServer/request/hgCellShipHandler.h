#pragma once

#include "frame/vtsRequestHandler.h"


class hgCellShipHandler :
    public vtsRequestHandler
{
public:
    hgCellShipHandler();
    ~hgCellShipHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

protected:
};

vtsDECLARE_REQUEST_HANDLER("CellularShip", hgCellShipHandler);