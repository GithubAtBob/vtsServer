#pragma once

#include "frame/vtsRequestHandler.h"

class DBSpeedWatchHandler;

class hgSpeedWatchHandler :
    public vtsRequestHandler
{
public:
    hgSpeedWatchHandler();
    ~hgSpeedWatchHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBSpeedWatchHandler* db);

protected:
};

vtsDECLARE_REQUEST_HANDLER("SpeedWatch", hgSpeedWatchHandler);