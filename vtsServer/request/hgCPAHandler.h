#pragma once

#include "frame/vtsRequestHandler.h"

class DBCPAHandler;

class hgCPAHandler :
    public vtsRequestHandler
{
public:
    hgCPAHandler();
    ~hgCPAHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBCPAHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("AddCPA", hgCPAHandler);