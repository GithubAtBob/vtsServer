#pragma once

#include "frame/vtsRequestHandler.h"

class DBCricleHandler;
class CricleRequest;
class CricleHandler :
    public vtsRequestHandler
{
public:
    CricleHandler();
    ~CricleHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBCricleHandler* db);

    void UpdateCricle(CricleRequest msg);

    void RemoveCricle(CricleRequest msg);

    void AllCricle(CricleRequest msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};