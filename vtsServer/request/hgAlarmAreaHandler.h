#pragma once

#include "frame/vtsRequestHandler.h"

class DBAlarmAreaHandler;

class hgAlarmAreaHandler :
    public vtsRequestHandler
{
public:
    hgAlarmAreaHandler();
    ~hgAlarmAreaHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBAlarmAreaHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("AlarmArea", hgAlarmAreaHandler);