#pragma once

#include "frame/vtsTimerHandler.h"


class hgSimulationTimerHandler : public vtsTimerHandler
{
public:
    hgSimulationTimerHandler(const std::string& name);
    ~hgSimulationTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
