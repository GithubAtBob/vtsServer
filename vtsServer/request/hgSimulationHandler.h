#pragma once

#include "frame/vtsRequestHandler.h"

class DBBerthWatchHandler;

class hgSimulationHandler :
    public vtsRequestHandler
{
public:
    hgSimulationHandler();
    ~hgSimulationHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBBerthWatchHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("Simulation", hgSimulationHandler);