#pragma once

#include "frame/vtsRequestHandler.h"

class DBHabitDangerHandler;

class hgHabitDangerHandler :
    public vtsRequestHandler
{
public:
    hgHabitDangerHandler();
    ~hgHabitDangerHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBHabitDangerHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("DangerCard", hgHabitDangerHandler);