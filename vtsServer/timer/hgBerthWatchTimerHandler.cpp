#include "StdAfx.h"
#include "hgBerthWatchTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgTargetManager.h"
#include "hgutils/NavUtil.h"
#include "hgutils/MathUtil.h"
#include "message/hgWarningMes.pb.h"
#include "Managers/hgAlarmManager.h"
//vtsSETUP_TIMER("Domain", 1, hgDomainTimerHandler);

extern const char* hgWaringTypeGuid[];
hgBerthWatchTimerHandler::hgBerthWatchTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgBerthWatchTimerHandler::~hgBerthWatchTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgBerthWatchTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgBerthWatchTimerHandler::handle(const boost::system::error_code& e)
{
	  double start = GetTickCount();
    QMap<QString,BerthWatch>::iterator l_itBerthWatch;
    QMap<QString,hgTarget>::iterator l_itAis;
    for (l_itBerthWatch = hgAlarmManager::m_WarningSetManager.m_mapBerthWatch.begin(); l_itBerthWatch != hgAlarmManager::m_WarningSetManager.m_mapBerthWatch.end(); l_itBerthWatch++)
    {

        if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itBerthWatch->TargetID) != hgAlarmManager::m_WarningSetManager.m_mapAuthorized.end())
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itBerthWatch->TargetID)->Authorize == true)
            {
                continue;
            }   
        }
        if (l_itBerthWatch->b_BerthWatch == false)
        {
            continue;
        }
        l_itAis = hgTargetManager::m_mapTarget.find(l_itBerthWatch->TargetID);
        hg::utils::PointLL l_pointLLOwn,l_pointLLTarget,l_pointLLEnd;
        double l_dDistance;
        l_pointLLOwn.setLat(l_itAis->Lat);
        l_pointLLOwn.setLon(l_itAis->Lon);
        l_pointLLTarget.setLat(l_itBerthWatch->BerthLat);
        l_pointLLTarget.setLon(l_itBerthWatch->BerthLon);
        l_dDistance = hg::utils::navutil::getDistance(l_pointLLOwn,l_pointLLTarget)*NM2M;  //º£Àï->Ã×
        if (l_dDistance >= l_itBerthWatch->Distance)
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itBerthWatch->TargetID)->m_bIsBerthWatch == false)
            {

                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[BERTHINGWATCH]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itAis->ID.toStdString());
                l_mes.set_mmsi(l_itAis->ID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                l_mes.set_warningtype(BerthWatchWarn);
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itBerthWatch->TargetID)->m_bIsBerthWatch = true;

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                }
                this->server()->closeDBConnection(database);
            }
        } 
        else
        {
            hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itBerthWatch->TargetID)->m_bIsBerthWatch = false;
        }
    }
    hgTargetManager::m_mapTarget.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgBerthWatchTimerHandler TimeDiff: " << diff;
		}
}
