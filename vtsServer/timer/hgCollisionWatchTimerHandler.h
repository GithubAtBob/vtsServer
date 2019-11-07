#pragma once

#include "frame/vtsTimerHandler.h"

class hgCollisionWatchTimerHandler : public vtsTimerHandler
{
public:
    hgCollisionWatchTimerHandler(const std::string& name);
    ~hgCollisionWatchTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
