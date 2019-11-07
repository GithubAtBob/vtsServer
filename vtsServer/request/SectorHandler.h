#pragma once

#include "frame/vtsRequestHandler.h"

class DBSectorHandler;
class SectorRequest;
class SectorHandler :
    public vtsRequestHandler
{
public:
    SectorHandler();
    ~SectorHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

    void afterDb(DBSectorHandler* db);

    void UpdateSector(SectorRequest msg);

    void RemoveSector(SectorRequest msg);

    void AllSector(SectorRequest msg);

protected:
    void afterResponse(const boost::system::error_code& e);
};

vtsDECLARE_REQUEST_HANDLER("sector", SectorHandler);