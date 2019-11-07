#include "StdAfx.h"
#include "LayerData/hgSectorLayer.h"

hgSectorLayer::hgSectorLayer(void)
    :m_CongesTime(-1),m_IsSendCongestion(false)
{

}

hgSectorLayer::~hgSectorLayer(void)
{

}

void hgSectorLayer::GetWarningData(hgSectorLayer &sector)
{
    sector.m_Info = m_Info;
    sector.m_InsideMMSI = m_InsideMMSI;
    sector.m_IsSendCongestion = m_IsSendCongestion;
    sector.m_CongesTime = m_CongesTime;
}
