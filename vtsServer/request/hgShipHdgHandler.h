#pragma once

#include "frame/vtsRequestHandler.h"

class hgShipHdgHandler :
    public vtsRequestHandler
{
public:
    hgShipHdgHandler();
    ~hgShipHdgHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

protected:
};
