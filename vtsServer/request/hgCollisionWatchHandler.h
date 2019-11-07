#pragma once

#include "frame/vtsRequestHandler.h"

class DBCollisionWatchHandler;

class hgCollisionWatchHandler :
    public vtsRequestHandler
{
public:
    hgCollisionWatchHandler();
    ~hgCollisionWatchHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBCollisionWatchHandler* db);

    void afterResponse(const boost::system::error_code& e);

protected:

};

vtsDECLARE_REQUEST_HANDLER("CollisionWatch", hgCollisionWatchHandler);