#pragma once

#include "frame/vtsRequestHandler.h"

class DBAlgorTextHandler;
class hgAlgorTextHandler :
    public vtsRequestHandler
{
public:
    hgAlgorTextHandler();
    ~hgAlgorTextHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBAlgorTextHandler* db);
// 
// protected:
//     void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("AlgorText", hgAlgorTextHandler);