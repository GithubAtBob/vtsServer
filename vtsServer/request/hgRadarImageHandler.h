#pragma once

#include "frame/vtsRequestHandler.h"

class DBRadarImageHandler;
class RadarImagePack;
class hgRadarImageHandler :
    public vtsRequestHandler
{
public:
    hgRadarImageHandler();
    ~hgRadarImageHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBRadarImageHandler* db);

    void SaveFile(RadarImagePack msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("RadarImage", hgRadarImageHandler);