#pragma once

#include "frame/vtsRequestHandler.h"
using namespace std;

class DBWaringHandler;

class hgAlgorithmModeHandler :
    public vtsRequestHandler
{
public:
    hgAlgorithmModeHandler();
    ~hgAlgorithmModeHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    //std::vector<std::string> m_restServer;

    //void afterDb(DBWaringHandler* db);
// 
// protected:
//     void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("AlgorithmMode", hgAlgorithmModeHandler);