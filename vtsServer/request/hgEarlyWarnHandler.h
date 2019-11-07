#pragma once

#include "frame/vtsRequestHandler.h"


class hgEarlyWarnHandler :
    public vtsRequestHandler
{
public:
    hgEarlyWarnHandler();
    ~hgEarlyWarnHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);


    //void afterDb(DBWaringHandler* db);
// 
protected:

};

vtsDECLARE_REQUEST_HANDLER("EarlyWarn", hgEarlyWarnHandler);