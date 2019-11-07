#pragma once

#include "frame/vtsRequestHandler.h"

class DBAnchorReservHandler;

class hgAnchorReservHandler :
    public vtsRequestHandler
{
public:
    hgAnchorReservHandler();
    ~hgAnchorReservHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBAnchorReservHandler* db);

protected:

};

vtsDECLARE_REQUEST_HANDLER("AnchorReserv", hgAnchorReservHandler);