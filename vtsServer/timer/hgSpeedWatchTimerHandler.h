#pragma once

#include "frame/vtsTimerHandler.h"


class hgSpeedWatchTimerHandler : public vtsTimerHandler
{
public:
    hgSpeedWatchTimerHandler(const std::string& name);
    ~hgSpeedWatchTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

private:

};
