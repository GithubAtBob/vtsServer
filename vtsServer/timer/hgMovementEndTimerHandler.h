#pragma once

#include "frame/vtsTimerHandler.h"
#define MoveDistance 50.0  //�ƶ�100��   

class hgMovementEndTimerHandler : public vtsTimerHandler
{
public:
    hgMovementEndTimerHandler(const std::string& name);
    ~hgMovementEndTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

};
