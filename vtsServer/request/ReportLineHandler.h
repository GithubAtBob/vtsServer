#pragma once

#include "frame/vtsRequestHandler.h"

class DBReportLineHandler;
class ReportLineRequest;
class ReportLineHandler :
    public vtsRequestHandler
{
public:
    ReportLineHandler();
    ~ReportLineHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBReportLineHandler* db);

    void UpdateFunction(ReportLineRequest msg);

    void RemoveFunction(ReportLineRequest msg);

    void AllFunction(ReportLineRequest msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("reportline", ReportLineHandler);