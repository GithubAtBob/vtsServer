#pragma once

#include "frame/vtsTimerHandler.h"

class hgEllipseTimerHandler : public vtsTimerHandler
{
public:
    hgEllipseTimerHandler(const std::string& name);
    ~hgEllipseTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
