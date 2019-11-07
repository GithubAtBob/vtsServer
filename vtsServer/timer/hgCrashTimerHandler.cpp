#include "StdAfx.h"
#include "hgCrashTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgTargetManager.h"
#include "hgutils/NavUtil.h"
#include <QDebug>
#include "message/hgCPAWarning.pb.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgConfigManager.h"

#include "Managers/hgSendManager.h"
extern const char* hgWaringTypeGuid[];
vtsSETUP_TIMER("CarshCPA", 1, hgCrashTimerHandler);

hgCrashTimerHandler::hgCrashTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{

}

hgCrashTimerHandler::~hgCrashTimerHandler(void)
{
}

vtsTimerHandler::WorkMode hgCrashTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_main;
}

void hgCrashTimerHandler::handle(const boost::system::error_code& e)
{

    return;
    mymap<QString,hgTarget>::iterator l_itOuter;
    mymap<QString,hgTarget>::iterator l_itInner;
    for (l_itOuter = hgTargetManager::m_mapTarget.begin(); l_itOuter != hgTargetManager::m_mapTarget.end(); ++l_itOuter)
    {
        for (l_itInner = hgTargetManager::m_mapTarget.begin(); l_itInner != hgTargetManager::m_mapTarget.end(); ++l_itInner)
        {
            if (l_itOuter->MMSI == l_itInner->MMSI)
            {
                continue;
            }
            hg::utils::PointLL l_pointLLOwn,l_pointLLTarget,l_pointLLEnd;
            double l_dTCPA,l_dDCPA;
            l_pointLLOwn.setLat(l_itOuter->Lat);
            l_pointLLOwn.setLon(l_itOuter->Lon);
            l_pointLLTarget.setLat(l_itInner->Lat);
            l_pointLLTarget.setLon(l_itInner->Lon);
            hg::utils::navutil::getTCPADCPA(l_pointLLOwn,l_itOuter->SOG,l_itOuter->COG,l_pointLLTarget,l_itInner->SOG,l_itInner->COG,&l_dTCPA,&l_dDCPA);
            if ((l_dDCPA <= hgConfigManager::m_sSysConfig->m_dayCPA || l_dDCPA <= hgConfigManager::m_sSysConfig->m_nightCPA || l_dDCPA <= hgConfigManager::m_sSysConfig->m_customCPA)
                && (abs(l_dTCPA) <= hgConfigManager::m_sSysConfig->m_dayTCPA || abs(l_dTCPA) <= hgConfigManager::m_sSysConfig->m_nightTCPA || abs(l_dTCPA) <= hgConfigManager::m_sSysConfig->m_customTCPA))
            {
                QMap<QString,QStringList>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapCollisionWarn.find(l_itInner->MMSI);
                if (l_it != hgAlarmManager::m_WarningSetManager.m_mapCollisionWarn.end())
                {
                    if (l_it.value().indexOf(l_itInner->MMSI) != -1)
                    {
                        continue;
                    }
                    
                }
                double l_dDistance,l_Bearing,l_ReciprocalBear;
                hg::utils::navutil::getDistanceBearing(l_pointLLOwn,l_pointLLTarget,&l_dDistance,&l_Bearing);
                hg::utils::navutil::getDistanceBearing(l_pointLLTarget,l_pointLLOwn,&l_dDistance,&l_ReciprocalBear);

                hgCPAWarning l_CPAWarning;
                l_CPAWarning.set_warningid(hgWaringTypeGuid[COLLISIONWATCH]);
                l_CPAWarning.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_CPAWarning.set_warningpriority(0);
                l_CPAWarning.set_warningname(l_itInner->MMSI.toStdString());
                l_CPAWarning.set_targetmmsi(l_itOuter->MMSI.toStdString());
                l_CPAWarning.set_mmsi(l_itInner->MMSI.toStdString());
                l_CPAWarning.set_warningtime(hgTargetManager::GetWarnTime());
                l_CPAWarning.set_shipname(l_itInner->ShipName.toStdString());
                l_CPAWarning.set_callsign(l_itInner->CallSign.toStdString());
                l_CPAWarning.set_shiptype(l_itInner->ShipType.toStdString());
                l_CPAWarning.set_sog(l_itOuter->SOG);
                l_CPAWarning.set_cpa(l_dDCPA);
                l_CPAWarning.set_tcpa(l_dTCPA);
                l_CPAWarning.set_relativebear(l_Bearing);
                l_CPAWarning.set_distance(l_dDistance);
                l_CPAWarning.set_reciprocalbear(l_ReciprocalBear);

                hgSendManager::SendClientMessage("CPAWarning",l_CPAWarning,this->server());
//                 this->server()->connectionManager().for_each
//                     ([&](ConnectionPtr p){
//                         p->write("CPAWarning",l_CPAWarning);
//                 });

                hgAlarmManager::m_WarningSetManager.SaveCollisionWarn(l_itInner->MMSI,l_itOuter->MMSI);
                
            }
            else
            {
                QMap<QString,QStringList>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapCollisionWarn.find(l_itInner->MMSI);
                if (l_it != hgAlarmManager::m_WarningSetManager.m_mapCollisionWarn.end())
                {
                    if (l_it.value().indexOf(l_itInner->MMSI) != -1)
                    {
                        continue;
                    }
                    for (int i = 0; i < l_it.value().size(); i++)
                    {
                        if(l_it.value()[i] == l_itOuter->MMSI)
                        {
                            hgCPAWarning l_CPAWarning;

                            hgSendManager::SendClientMessage("CPAWarning",l_CPAWarning,this->server());
//                             this->server()->connectionManager().for_each
//                                 ([&](ConnectionPtr p){
//                                     p->write("CPAWarning",l_CPAWarning);
//                              });

                            l_it.value().erase(l_it.value().begin()+i);
                            break;
                        }
                    }
                }  
            }
        }
    }

    hgTargetManager::m_mapTarget.UnLockAll();
}
