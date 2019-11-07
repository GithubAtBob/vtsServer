#pragma once

#include "frame/vtsRequestHandler.h"
#include "message/hgAisMessage.pb.h"
class DBArpaAllHandler;
class ArpaTargetPack;
class hgArpaAllHandler :
    public vtsRequestHandler
{
public:
    hgArpaAllHandler();
    ~hgArpaAllHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBArpaAllHandler* db);
    
    void WriteToFile(ArpaTargetPack msg);

    void RadarFuseType(ArpaTargetPack msg);

    void OwnFuseType(ArpaTargetPack msg);

	bool OwnShipTurnDir(hgAisMessage msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("hgArpaAll", hgArpaAllHandler);