#pragma once

#include "frame/vtsTimerHandler.h"

class hgReportAreaTimerHandler : public vtsTimerHandler
{
public:
    hgReportAreaTimerHandler(const std::string& name);
    ~hgReportAreaTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
