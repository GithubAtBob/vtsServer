#pragma once

#include "frame/vtsRequestHandler.h"

class hgAisTextHandler :
    public vtsRequestHandler
{
public:
    hgAisTextHandler();
    ~hgAisTextHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void aisTextReceive(boost::asio::const_buffer& data);


protected:

};

vtsDECLARE_REQUEST_HANDLER("AisText", hgAisTextHandler);