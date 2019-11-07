#pragma once

#include "frame/vtsRequestHandler.h"

class DBGroupHandler;

class GroupHandler :
    public vtsRequestHandler
{
public:
    GroupHandler();
    ~GroupHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBGroupHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("group", GroupHandler);