#pragma once

#include "frame/vtsRequestHandler.h"
using namespace std;

class DBLoginHandler;
class LoginHandler :
    public vtsRequestHandler
{
public:
    LoginHandler();
    ~LoginHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBLoginHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);

    std::clock_t t1;
    std::clock_t t2;
};

vtsDECLARE_REQUEST_HANDLER("login", LoginHandler);