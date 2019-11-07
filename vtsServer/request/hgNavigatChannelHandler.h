#pragma once

#include "frame/vtsRequestHandler.h"

class DBNavigatChannelHandler;

class hgNavigatChannelHandler :
    public vtsRequestHandler
{
public:
    hgNavigatChannelHandler();
    ~hgNavigatChannelHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);


    void afterDb(DBNavigatChannelHandler* db);

protected:
};

vtsDECLARE_REQUEST_HANDLER("NavigatChannel", hgNavigatChannelHandler);