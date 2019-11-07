#include "StdAfx.h"
#include "hgLostTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgComManager.h"
#include "Managers/hgConfigManager.h"
#include "Managers/hgTargetManager.h"
#include "hgAisDecoder.h"
#include "message/hgAisMessage.pb.h"
#include "message/hgWarningMes.pb.h"

vtsSETUP_TIMER("lost", 1, hgLostTimerHandler);

hgLostTimerHandler::hgLostTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
    
}

hgLostTimerHandler::~hgLostTimerHandler(void)
{
   
}

vtsTimerHandler::WorkMode hgLostTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_main;
}

void hgLostTimerHandler::handle(const boost::system::error_code& e)
{
	  double start = GetTickCount();
    //return;
    //mymap<QString,hgTarget>::iterator l_itTarget = hgTargetManager::m_mapTarget.begin();
    //mymap<QString,hgTarget>::iterator l_itAis = hgTargetManager::m_mapAis.begin();
    //mymap<QString,hgTarget>::iterator l_itRadar = hgTargetManager::m_mapRadar.begin();
    QList <QString> l_TargetMissList;//ID 
    QList <QString> l_TargetDeleteList;//ID
    QList <QString> l_RadarMissList;//ID 
    QList <QString> l_RadarDeleteList;//ID
    l_TargetMissList.clear();
    l_TargetDeleteList.clear();
    l_RadarMissList.clear();
    l_RadarDeleteList.clear();
    {
        mymap<QString,hgTarget>::iterator l_itTarget = hgTargetManager::m_mapTarget.begin();
        while (l_itTarget != hgTargetManager::m_mapTarget.end())
        {
            l_itTarget->ReportInterval++;
            l_itTarget->RadarInterval++;
            if (l_itTarget->ReportInterval >= hgConfigManager::m_sSysConfig->m_iLostTime*Min_TO_SEC && l_itTarget->ReportInterval < hgConfigManager::m_sSysConfig->m_iDeleteTime*Min_TO_SEC)
            {
                l_itTarget->Missing = true;
                l_TargetMissList.push_back(l_itTarget->MMSI);
            }
            else if (l_itTarget->ReportInterval >= hgConfigManager::m_sSysConfig->m_iDeleteTime*Min_TO_SEC)
            {
                l_TargetDeleteList.push_back(l_itTarget->MMSI);
                if (l_itTarget->Result == AIS_FUSE)
                {
                    l_itTarget = hgTargetManager::m_mapTarget.erase(l_itTarget);
                    continue;
                }
            }

            if (l_itTarget->RadarInterval >= hgConfigManager::m_sSysConfig->m_iRadarLost*Min_TO_SEC && l_itTarget->RadarInterval < hgConfigManager::m_sSysConfig->m_iRadarDelete*Min_TO_SEC)
            {
                l_itTarget->RadarMissing = true;
                l_RadarMissList.push_back(l_itTarget->MMSI);
            }
            else if (l_itTarget->ReportInterval >= hgConfigManager::m_sSysConfig->m_iRadarDelete*Min_TO_SEC)
            {
                l_RadarDeleteList.push_back(l_itTarget->MMSI);
                if (l_itTarget->Result == RADAR_FUSE)
                {
                    l_itTarget = hgTargetManager::m_mapTarget.erase(l_itTarget);
                    continue;
                }
                else if (l_itTarget->Result == AIS_RADAR_FUSE && l_itTarget->ReportInterval >= hgConfigManager::m_sSysConfig->m_iDeleteTime*Min_TO_SEC)
                {
                    QMap<QString,hgResult>::iterator l_ResultIt = hgTargetManager::m_mapResult.find(l_itTarget->ID);
                    if (l_ResultIt != hgTargetManager::m_mapResult.end())
                    {
                        if (hgTargetManager::m_AlgorOwnMMSI.contains(l_ResultIt->MMSI))
                        {
                            qDebug () << "<<<<  2";
                        }
                        //qDebug () << "<<<<  2";
                        hgTargetManager::m_mapResult.erase(l_ResultIt);
                    }
                    l_itTarget = hgTargetManager::m_mapTarget.erase(l_itTarget);
                    continue;
                }
            }

            l_itTarget++;
        }
    }

    //{
    //    auto lockerTarget = hgTargetManager::getMapTargetLocker();
    //    auto &mapTarget = lockerTarget->raw();
    //    for (int i = 0; i < l_MissList.size(); i++)
    //    {
    //        l_itTarget = mapTarget.find(l_MissList.at(i));
    //        if (l_itTarget != mapTarget.end())
    //        {
    //            l_itTarget->Missing = true;
    //        }
    //    }
    //}

    //{
    //    auto lockerTarget = hgTargetManager::getMapTargetLocker();
    //    auto &mapTarget = lockerTarget->raw();
    //    for (int i = 0; i < l_EraseList.size(); i++)
    //    {
    //        l_itTarget = mapTarget.find(l_EraseList.at(i));
    //        if (l_itTarget != mapTarget.end())
    //        {
    //            mapTarget.erase(l_itTarget);
    //        }
    //    }
    //}



           /* hgWarningMes l_mes;
            l_mes.set_warningid(555);
            l_mes.set_warningguid(hgWaringTypeGuid[LOSTTRACK]);
            l_mes.set_warningpriority(0);
            l_mes.set_warningname(l_itAis->MMSI.toStdString());
            l_mes.set_mmsi(l_itAis->MMSI.toStdString());
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            this->server()->connectionManager().for_each
                ([&](ConnectionPtr p){
                    boost::system::error_code error;
                    p->write("hgWarningMes",l_mes,error);
                    });*/
    hgTargetManager::m_mapTarget.UnLockAll();
    hgTargetManager::m_mapAis.UnLockAll();
    hgTargetManager::m_mapRadar.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgLostTimerHandler TimeDiff: " << diff;
		}
}
