#pragma once

#include "frame/vtsTimerHandler.h"

class ReadElementTimerHandler : public vtsTimerHandler
{
public:
    ReadElementTimerHandler(const std::string& name);
    ~ReadElementTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

    int m_count;
};
