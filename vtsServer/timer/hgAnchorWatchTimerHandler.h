#pragma once

#include "frame/vtsTimerHandler.h"

class hgAnchorWatchTimerHandler : public vtsTimerHandler
{
public:
    hgAnchorWatchTimerHandler(const std::string& name);
    ~hgAnchorWatchTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
