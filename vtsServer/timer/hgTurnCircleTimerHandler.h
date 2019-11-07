#pragma once

#include "frame/vtsTimerHandler.h"

class hgTurnCircleTimerHandler : public vtsTimerHandler
{
public:
    hgTurnCircleTimerHandler(const std::string& name);
    ~hgTurnCircleTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
