#pragma once

#include "frame/vtsRequestHandler.h"

class DBWaringHandler;

class hgCPAWarningHandler :
    public vtsRequestHandler
{
public:
    hgCPAWarningHandler();
    ~hgCPAWarningHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);


    //void afterDb(DBWaringHandler* db);
// 
// protected:
//     void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("CPAWarning", hgCPAWarningHandler);