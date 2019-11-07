#pragma once

#include "frame/vtsRequestHandler.h"
class DBAisChangeHandler;

class hgAisChangeHandler :
    public vtsRequestHandler
{
public:
    hgAisChangeHandler();
    ~hgAisChangeHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBAisChangeHandler* db);


protected:
};

vtsDECLARE_REQUEST_HANDLER("AisChange", hgAisChangeHandler);