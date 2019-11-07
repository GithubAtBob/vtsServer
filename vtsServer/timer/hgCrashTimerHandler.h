#pragma once

#include "frame/vtsTimerHandler.h"

class hgCrashTimerHandler : public vtsTimerHandler
{
public:
    hgCrashTimerHandler(const std::string& name);
    ~hgCrashTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

protected:
};
