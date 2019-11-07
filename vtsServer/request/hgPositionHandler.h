#pragma once

#include "frame/vtsRequestHandler.h"

class DBCPAHandler;

class hgPositionHandler :
    public vtsRequestHandler
{
public:
    hgPositionHandler();
    ~hgPositionHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);


protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("PositionPredict", hgPositionHandler);