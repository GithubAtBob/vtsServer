#pragma once

#include "frame/vtsTimerHandler.h"

class hgAnchorReservTimerHandler : public vtsTimerHandler
{
public:
    hgAnchorReservTimerHandler(const std::string& name);
    ~hgAnchorReservTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
