#include "StdAfx.h"
#include "LayerData/hgCricleLayer.h"

hgCricleLayer::hgCricleLayer(void)
    :m_CongesTime(-1),m_IsSendCongestion(false)
{

}

hgCricleLayer::~hgCricleLayer(void)
{

}

void hgCricleLayer::GetWarningData(hgCricleLayer &cricle)
{
    cricle.m_Info = m_Info;
    cricle.m_InsideMMSI = m_InsideMMSI;
    cricle.m_IsSendCongestion = m_IsSendCongestion;
    cricle.m_CongesTime = m_CongesTime;
}
