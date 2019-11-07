#pragma once

#include "frame/vtsTimerHandler.h"
namespace hg
{
    namespace utils
    {
        class PolygonLL;
        class LineLL;
    }
}

class hgReportTimerHandler : public vtsTimerHandler
{
public:
    hgReportTimerHandler(const std::string& name);
    ~hgReportTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

    bool ThroughReport(hg::utils::PolygonLL ploygon, hg::utils::LineLL line);

};
