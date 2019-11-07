#pragma once

#include "frame/vtsRequestHandler.h"

class DBArpaTargetHandler;
class ArpaTargetPack;
class hgArpaTargetHandler :
    public vtsRequestHandler
{
public:
    hgArpaTargetHandler();
    ~hgArpaTargetHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBArpaTargetHandler* db);
    
    void WriteToFile(ArpaTargetPack& msg);

    void RadarFuseType(ArpaTargetPack& msg);

    void OwnFuseType(ArpaTargetPack& msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("ArpaTargetPack", hgArpaTargetHandler);