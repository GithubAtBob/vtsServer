#pragma once

#include "frame/vtsTimerHandler.h"

class hgGroundWatchTimerHandler : public vtsTimerHandler
{
public:
    hgGroundWatchTimerHandler(const std::string& name);
    ~hgGroundWatchTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
