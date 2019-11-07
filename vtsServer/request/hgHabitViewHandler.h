#pragma once

#include "frame/vtsRequestHandler.h"

class DBHabitViewHandler;

class hgHabitViewHandler :
    public vtsRequestHandler
{
public:
    hgHabitViewHandler();
    ~hgHabitViewHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBHabitViewHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("ViewCard", hgHabitViewHandler);