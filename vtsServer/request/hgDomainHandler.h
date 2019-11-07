#pragma once

#include "frame/vtsRequestHandler.h"

class DBDomainHandler;

class hgDomainHandler :
    public vtsRequestHandler
{
public:
    hgDomainHandler();
    ~hgDomainHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBDomainHandler* db);

protected:
   
};

vtsDECLARE_REQUEST_HANDLER("Domain", hgDomainHandler);