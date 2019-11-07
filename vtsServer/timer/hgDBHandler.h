#pragma once

#include "frame/vtsTimerHandler.h"

class hgDBHandler : public vtsTimerHandler
{
public:
    hgDBHandler(const std::string& name);
    ~hgDBHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

	void ClearMax();

	void ClearMin();

	void ClearFusedTarget();

    int m_count;
};
