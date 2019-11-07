#pragma once

#include "frame/vtsRequestHandler.h"

class hgRadarAISStateHandler :
    public vtsRequestHandler
{
public:
    hgRadarAISStateHandler();
    ~hgRadarAISStateHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

protected:
    //void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("RadarAISState", hgRadarAISStateHandler);