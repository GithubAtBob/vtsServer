#pragma once

#include "frame/vtsTimerHandler.h"

#define Min_TO_SEC 60  
class hgFuseTimerHandler : public vtsTimerHandler
{
public:
    hgFuseTimerHandler(const std::string& name);
    ~hgFuseTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);



protected:

};
