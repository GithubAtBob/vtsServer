#pragma once

#include "frame/vtsRequestHandler.h"

class DBAnchorAreaHandler;

class hgAnchorAreaHandler :
    public vtsRequestHandler
{
public:
    hgAnchorAreaHandler();
    ~hgAnchorAreaHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void afterDb(DBAnchorAreaHandler* db);

protected:
};

vtsDECLARE_REQUEST_HANDLER("AnchorArea", hgAnchorAreaHandler);