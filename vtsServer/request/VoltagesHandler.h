#pragma once

#include "frame/vtsRequestHandler.h"
using namespace std;

class VoltagesHandler :
    public vtsRequestHandler
{
public:
    VoltagesHandler();
    ~VoltagesHandler(void);

    WorkMode workMode();

    void handle(boost::asio::const_buffer& data);

    void timeout(time_t last);

protected:

    std::clock_t t1;
    std::clock_t t2;
};

vtsDECLARE_REQUEST_HANDLER("Voltages", VoltagesHandler);