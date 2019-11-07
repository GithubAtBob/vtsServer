#pragma once

#include "frame/vtsRequestHandler.h"

class DBAlgorBackHandler;
class hgAlgorBackHandler :
    public vtsRequestHandler
{
public:
    hgAlgorBackHandler();
    ~hgAlgorBackHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBAlgorBackHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("hgAlgorBack", hgAlgorBackHandler);