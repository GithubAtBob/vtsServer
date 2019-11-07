#pragma once

#include "frame/vtsRequestHandler.h"

class DBRegisterHandler;

class RegisterHandler :
    public vtsRequestHandler
{
public:
    RegisterHandler();
    ~RegisterHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBRegisterHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);

    std::clock_t t1;
    std::clock_t t2;
};

vtsDECLARE_REQUEST_HANDLER("register", RegisterHandler);