#pragma once

#include "frame/vtsRequestHandler.h"

class hgGPSDataHandler :
    public vtsRequestHandler
{
public:
    hgGPSDataHandler();
    ~hgGPSDataHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    //void afterDb(DBArpaTargetHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("hgGPSData", hgGPSDataHandler);