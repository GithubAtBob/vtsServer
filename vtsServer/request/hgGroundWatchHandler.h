#pragma once

#include "frame/vtsRequestHandler.h"

class DBGroundWatchHandler;

class hgGroundWatchHandler :
    public vtsRequestHandler
{
public:
    hgGroundWatchHandler();
    ~hgGroundWatchHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBGroundWatchHandler* db);

protected:
};

vtsDECLARE_REQUEST_HANDLER("GroundWatch", hgGroundWatchHandler);