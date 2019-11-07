#pragma once

#include "frame/vtsRequestHandler.h"

class DBDutyAreaHandler;
class DutyAreaRequest;
class DutyAreaHandler :
    public vtsRequestHandler
{
public:
    DutyAreaHandler();
    ~DutyAreaHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBDutyAreaHandler* db);

    void UpdateFunction(DutyAreaRequest msg);

    void RemoveFunction(DutyAreaRequest msg);

    void AllFunction(DutyAreaRequest msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};
