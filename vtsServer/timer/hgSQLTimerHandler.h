#pragma once

#include "frame/vtsTimerHandler.h"

class hgSQLTimerHandler : public vtsTimerHandler
{
public:
    hgSQLTimerHandler(const std::string& name);
    ~hgSQLTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);
};
