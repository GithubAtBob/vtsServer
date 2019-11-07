#pragma once

#include "frame/vtsRequestHandler.h"

class DBEllipseHandler;

class EllipseHandler :
    public vtsRequestHandler
{
public:
    EllipseHandler();
    ~EllipseHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBEllipseHandler* db);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("ellipse", EllipseHandler);