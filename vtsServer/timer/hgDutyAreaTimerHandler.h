#pragma once

#include "frame/vtsTimerHandler.h"

class hgDutyAreaTimerHandler : public vtsTimerHandler
{
public:
    hgDutyAreaTimerHandler(const std::string& name);
    ~hgDutyAreaTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
