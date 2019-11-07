#pragma once

#include "frame/vtsTimerHandler.h"

class hgAnchorAreaTimerHandler : public vtsTimerHandler
{
public:
    hgAnchorAreaTimerHandler(const std::string& name);
    ~hgAnchorAreaTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
