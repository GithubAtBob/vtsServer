#pragma once

#include "frame/vtsTimerHandler.h"

class hgDomainTimerHandler : public vtsTimerHandler
{
public:
    hgDomainTimerHandler(const std::string& name);
    ~hgDomainTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

private:
    QMap <double,QString> m_mapDomain;
};
