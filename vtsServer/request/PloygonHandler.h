#pragma once

#include "frame/vtsRequestHandler.h"

class DBPloygonHandler;
class PloygonRequest;

class PloygonHandler :
    public vtsRequestHandler
{
public:
    PloygonHandler();
    ~PloygonHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBPloygonHandler* db);

    void UpdatePolygon(PloygonRequest msg);

    void RemovePolygon(PloygonRequest msg);

    void AllPolygon(PloygonRequest msg);

    void SendChangeToAlgor();

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("ploygon", PloygonHandler);