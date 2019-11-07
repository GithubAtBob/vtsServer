#pragma once

#include "frame/vtsRequestHandler.h"

class DBUserHandler;

class UserHandler :
    public vtsRequestHandler
{
public:
    UserHandler();
    ~UserHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBUserHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("user", UserHandler);