#pragma once

#include "frame/vtsRequestHandler.h"
using namespace std;

class hgShipAreaHandler :
    public vtsRequestHandler
{
public:
    hgShipAreaHandler();
    ~hgShipAreaHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    //std::vector<std::string> m_restServer;

    //void afterDb(DBWaringHandler* db);
// 
// protected:
//     void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("ShipArea", hgShipAreaHandler);