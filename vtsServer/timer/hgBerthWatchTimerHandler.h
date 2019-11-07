#pragma once

#include "frame/vtsTimerHandler.h"

class hgBerthWatchTimerHandler : public vtsTimerHandler
{
public:
    hgBerthWatchTimerHandler(const std::string& name);
    ~hgBerthWatchTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
