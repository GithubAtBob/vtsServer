#pragma once

#include "frame/vtsRequestHandler.h"

class DBHabitSystemHandler;

class hgHabitSystemHandler :
    public vtsRequestHandler
{
public:
    hgHabitSystemHandler();
    ~hgHabitSystemHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBHabitSystemHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("SystemCard", hgHabitSystemHandler);