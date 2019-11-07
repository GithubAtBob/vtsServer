#pragma once

#include "frame/vtsTimerHandler.h"

#define Min_TO_SEC 60  
class hgLostTimerHandler : public vtsTimerHandler
{
public:
    hgLostTimerHandler(const std::string& name);
    ~hgLostTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);



protected:

};
