#pragma once

#include "frame/vtsRequestHandler.h"

//class DBWaringHandler;

class hgRadarAskHandler :
    public vtsRequestHandler
{
public:
    hgRadarAskHandler();
    ~hgRadarAskHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    //void afterDb(DBWaringHandler* db);
// 
// protected:
//     void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("RadarAsk", hgRadarAskHandler);