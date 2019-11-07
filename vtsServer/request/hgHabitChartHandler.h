#pragma once

#include "frame/vtsRequestHandler.h"

class DBHabitChartHandler;

class hgHabitChartHandler :
    public vtsRequestHandler
{
public:
    hgHabitChartHandler();
    ~hgHabitChartHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBHabitChartHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("ChartCard", hgHabitChartHandler);