#include "StdAfx.h"
#include "hgNavigatChannelTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgTargetManager.h"
#include "hgutils/NavUtil.h"

//vtsSETUP_TIMER("Domain", 1, hgDomainTimerHandler);

hgNavigatChannelTimerHandler::hgNavigatChannelTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgNavigatChannelTimerHandler::~hgNavigatChannelTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgNavigatChannelTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgNavigatChannelTimerHandler::handle(const boost::system::error_code& e)
{
    //QMap<QString,Domain>::iterator l_itOuter;
    //QMap<QString,Domain>::iterator l_itInner;
    //for (l_itOuter = hgTargetManager::m_mapDomain.begin(); l_itOuter != hgTargetManager::m_mapDomain.end(); l_itOuter++)
    //{
    //    if (l_itOuter->DomainWatch == false)
    //    {
    //        continue;
    //    }
    //    for (l_itInner = l_itOuter + 1; l_itInner != hgTargetManager::m_mapDomain.end(); l_itInner++)
    //    {
    //        /*hg::utils::PointLL l_pointLLOwn,l_pointLLTarget,l_pointLLEnd;
    //        double l_dTCPA,l_dDCPA,l_dDistance;
    //        l_pointLLOwn.setLat(l_itOuter->Lat);
    //        l_pointLLOwn.setLon(l_itOuter->Lon);
    //        l_pointLLTarget.setLat(l_itInner->Lat);
    //        l_pointLLTarget.setLon(l_itInner->Lon);
    //        l_dDistance = hg::utils::navutil::getDistance(l_pointLLOwn,l_pointLLTarget);
    //        if (l_dDistance > RANGE)
    //        {
    //            return;
    //        }
    //        hg::utils::navutil::getTCPADCPA(l_pointLLOwn,l_itOuter->SOG,l_itOuter->COG,l_pointLLTarget,l_itInner->SOG,l_itInner->COG,&l_dTCPA,&l_dDCPA);
    //        if (l_dDCPA <= DCPAMAX && abs(l_dTCPA) <= TCPAMAX)
    //        {
    //            hgCPAWarning l_CPAWarning;
    //            l_CPAWarning.set_ownmmsi(l_itInner->MMSI.toStdString());
    //            l_CPAWarning.set_targetmmsi(l_itOuter->MMSI.toStdString());
    //            l_CPAWarning.set_dcpa(l_dDCPA);
    //            l_CPAWarning.set_tcpa(l_dTCPA);
    //            this->server()->connectionManager().for_each
    //                ([&](ConnectionPtr p){
    //                    boost::system::error_code error;
    //                    p->write("CPAWarning",l_CPAWarning,error);
    //            });
    //        }*/
    //    }
    //}
}
