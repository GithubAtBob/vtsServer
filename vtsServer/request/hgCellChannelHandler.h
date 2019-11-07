#pragma once

#include "frame/vtsRequestHandler.h"


class hgCellChannelHandler :
    public vtsRequestHandler
{
public:
    hgCellChannelHandler();
    ~hgCellChannelHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);


};

vtsDECLARE_REQUEST_HANDLER("CellChannel", hgCellChannelHandler);