#include "StdAfx.h"
#include "LayerData/hgChannelLayer.h"

hgChannelLayer::hgChannelLayer(void)
{

}

hgChannelLayer::~hgChannelLayer(void)
{

}

int hgChannelLayer::containsPoint(hg::utils::PointLL pointLL)
{
    for ( int i = 0; i < m_AllPoint.size(); i++ )
    {
        hg::utils::PolygonLL l_PolygonLL;
        l_PolygonLL.push_back(m_AllPoint.at(i).at(ChannelLeftBegin));
        l_PolygonLL.push_back(m_AllPoint.at(i).at(ChannelLeftEnd));
        l_PolygonLL.push_back(m_AllPoint.at(i).at(ChannelMidEnd));
        l_PolygonLL.push_back(m_AllPoint.at(i).at(ChannelRightEnd));
        l_PolygonLL.push_back(m_AllPoint.at(i).at(ChannelRightBegin));
        l_PolygonLL.push_back(m_AllPoint.at(i).at(ChannelMidBegin));
        if (l_PolygonLL.containsPoint(pointLL,Qt::WindingFill))
        {
            return i;
        }
    }
    return -1;
}
