#pragma once

#include "frame/vtsRequestHandler.h"

class DBAuthorizedHandler;

class hgAuthorizedHandler :
    public vtsRequestHandler
{
public:
    hgAuthorizedHandler();
    ~hgAuthorizedHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBAuthorizedHandler* db);

protected:

};

vtsDECLARE_REQUEST_HANDLER("Authorized", hgAuthorizedHandler);