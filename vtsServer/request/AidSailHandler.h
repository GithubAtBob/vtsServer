#pragma once

#include "frame/vtsRequestHandler.h"

class DBAidSailHandler;
class AidSailRequest;
class AidSailHandler :
    public vtsRequestHandler
{
public:
    AidSailHandler();
    ~AidSailHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBAidSailHandler* db);

    void UpdateFunction(AidSailRequest msg);

    void RemoveFunction(AidSailRequest msg);

    void AllFunction(AidSailRequest msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};
