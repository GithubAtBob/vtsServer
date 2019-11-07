#pragma once

#include "frame/vtsRequestHandler.h"

class DBAlgorWarMesHandler;

class hgAlgorWarMesHandler :
    public vtsRequestHandler
{
public:
    hgAlgorWarMesHandler();
    ~hgAlgorWarMesHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);


    void afterDb(DBAlgorWarMesHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("hgAlgorWarMes", hgAlgorWarMesHandler);