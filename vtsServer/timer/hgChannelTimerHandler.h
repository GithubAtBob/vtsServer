#pragma once

#include "frame/vtsTimerHandler.h"

class hgChannelTimerHandler : public vtsTimerHandler
{
public:
    hgChannelTimerHandler(const std::string& name);
    ~hgChannelTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
