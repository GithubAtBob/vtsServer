#include "StdAfx.h"
#include "LayerData/hgPolygonLayer.h"

hgPolygonLayer::hgPolygonLayer(void)
    :m_CongesTime(-1),m_IsSendCongestion(false)
{

}

hgPolygonLayer::~hgPolygonLayer(void)
{

}

void hgPolygonLayer::GetWarningData(hgPolygonLayer &polygon)
{
    polygon.m_Info = m_Info;
    polygon.m_InsideMMSI = m_InsideMMSI;
    polygon.m_IsSendCongestion = m_IsSendCongestion;
    polygon.m_CongesTime = m_CongesTime;
}
