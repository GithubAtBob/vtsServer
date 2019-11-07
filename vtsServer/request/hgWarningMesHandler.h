#pragma once

#include "frame/vtsRequestHandler.h"

class DBWaringHandler;
class DBWarnHistoryHandler;

class hgWarningMesHandler :
    public vtsRequestHandler
{
public:
    hgWarningMesHandler();
    ~hgWarningMesHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBWarnHistoryHandler* db); 

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("hgWarningMes", hgWarningMesHandler);