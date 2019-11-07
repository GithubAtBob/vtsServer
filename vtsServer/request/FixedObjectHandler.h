#pragma once

#include "frame/vtsRequestHandler.h"

class DBFixedObjectHandler;
class FixedObjectRequest;
class FixedObjectHandler :
    public vtsRequestHandler
{
public:
    FixedObjectHandler();
    ~FixedObjectHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBFixedObjectHandler* db);

    void UpdateFunction(FixedObjectRequest msg);

    void RemoveFunction(FixedObjectRequest msg);

    void AllFunction(FixedObjectRequest msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("fixedobject", FixedObjectHandler);