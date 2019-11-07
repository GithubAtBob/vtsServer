#pragma once

#include "frame/vtsRequestHandler.h"

class DBReportAreaHandler;

class hgReportAreaHandler :
    public vtsRequestHandler
{
public:
    hgReportAreaHandler();
    ~hgReportAreaHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBReportAreaHandler* db);

protected:
};

vtsDECLARE_REQUEST_HANDLER("ReportArea", hgReportAreaHandler);