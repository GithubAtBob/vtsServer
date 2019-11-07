#pragma once

#include "frame/vtsRequestHandler.h"

class DBBerthWatchHandler;

class hgBerthWatchHandler :
    public vtsRequestHandler
{
public:
    hgBerthWatchHandler();
    ~hgBerthWatchHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBBerthWatchHandler* db);

protected:

};

vtsDECLARE_REQUEST_HANDLER("BerthWatch", hgBerthWatchHandler);