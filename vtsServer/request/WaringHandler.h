#pragma once

#include "frame/vtsRequestHandler.h"

class DBWaringHandler;

class WaringHandler :
    public vtsRequestHandler
{
public:
    WaringHandler();
    ~WaringHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBWaringHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("waring", WaringHandler);