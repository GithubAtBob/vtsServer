#pragma once

#include "frame/vtsRequestHandler.h"

class DBAnchorWatchHandler;

class hgAnchorWatchHandler :
    public vtsRequestHandler
{
public:
    hgAnchorWatchHandler();
    ~hgAnchorWatchHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBAnchorWatchHandler* db);

protected:
   
};

vtsDECLARE_REQUEST_HANDLER("AnchorWatch", hgAnchorWatchHandler);