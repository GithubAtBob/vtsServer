#pragma once

#include "frame/vtsRequestHandler.h"


class hgDeleteTargetHandler :
    public vtsRequestHandler
{
public:
    hgDeleteTargetHandler();
    ~hgDeleteTargetHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);



protected:
 
};

vtsDECLARE_REQUEST_HANDLER("DeleteTarget", hgDeleteTargetHandler);