#pragma once

#include "frame/vtsTimerHandler.h"


#define ClassSmallSOG 2
#define ClassMediumSOG 14
#define ClassBigSOG 23

class hgTrackPredictTimerHandler : public vtsTimerHandler
{
public:
    hgTrackPredictTimerHandler(const std::string& name);
    ~hgTrackPredictTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);
    void SimHandle(const boost::system::error_code& e);

};
