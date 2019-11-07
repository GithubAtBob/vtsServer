#pragma once

#include "frame/vtsTimerHandler.h"

class TestTimerHandler : public vtsTimerHandler
{
public:
    TestTimerHandler(const std::string& name);
    ~TestTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

    int m_count;
};
