#pragma once

#include "frame/vtsRequestHandler.h"

class DBHabitTarSetHandler;

class hgHabitTarSetHandler :
    public vtsRequestHandler
{
public:
    hgHabitTarSetHandler();
    ~hgHabitTarSetHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBHabitTarSetHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("HabitTarSet", hgHabitTarSetHandler);