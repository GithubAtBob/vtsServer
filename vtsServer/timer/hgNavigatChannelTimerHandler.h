#pragma once

#include "frame/vtsTimerHandler.h"

class hgNavigatChannelTimerHandler : public vtsTimerHandler
{
public:
    hgNavigatChannelTimerHandler(const std::string& name);
    ~hgNavigatChannelTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
