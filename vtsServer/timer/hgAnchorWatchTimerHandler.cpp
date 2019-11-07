#include "StdAfx.h"
#include "hgAnchorWatchTimerHandler.h"

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
hgAnchorWatchTimerHandler::hgAnchorWatchTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgAnchorWatchTimerHandler::~hgAnchorWatchTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgAnchorWatchTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgAnchorWatchTimerHandler::handle(const boost::system::error_code& e)
{
	  double start = GetTickCount();
    QMap<QString,AnchorWatch>::iterator l_itAnchorWatch;
    mymap<QString,hgTarget>::iterator l_itAis;
    for (l_itAnchorWatch = hgAlarmManager::m_WarningSetManager.m_mapAnchorWatch.begin(); l_itAnchorWatch != hgAlarmManager::m_WarningSetManager.m_mapAnchorWatch.end(); l_itAnchorWatch++)
    {

        if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itAnchorWatch->TargetID) != hgAlarmManager::m_WarningSetManager.m_mapAuthorized.end())
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itAnchorWatch->TargetID)->Authorize == true)
            {
                continue;
            }   
        }
        if (l_itAnchorWatch->b_AnchorWatch == false)
        {
            continue;
        }

        l_itAis = hgTargetManager::m_mapTarget.find(l_itAnchorWatch->TargetID);
        hg::utils::PointLL l_pointLLOwn,l_pointLLTarget,l_pointLLEnd;
        double l_dDistance;
        l_pointLLOwn.setLat(l_itAis->Lat);
        l_pointLLOwn.setLon(l_itAis->Lon);
        l_pointLLTarget.setLat(l_itAnchorWatch->AnchorLat);
        l_pointLLTarget.setLon(l_itAnchorWatch->AnchorLon);
        l_dDistance = hg::utils::navutil::getDistance(l_pointLLOwn,l_pointLLTarget)*NM2M;  //海里->米
        if (l_dDistance >= l_itAnchorWatch->Clubbing && l_dDistance < l_itAnchorWatch->Dragging)//拖锚
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAnchorWatch->TargetID)->m_bIsClubbing == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[ANCHORWATCH]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itAis->ID.toStdString());
                l_mes.set_mmsi(l_itAis->ID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                l_mes.set_warningtype(ClubbingWarn);
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAnchorWatch->TargetID)->m_bIsClubbing = true;

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                }
                this->server()->closeDBConnection(database);
            } 
        } 
        else if (l_dDistance >= l_itAnchorWatch->Dragging)//走锚
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAnchorWatch->TargetID)->m_bIsDragging == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[ANCHORWATCH]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itAis->ID.toStdString());
                l_mes.set_mmsi(l_itAis->ID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                l_mes.set_warningtype(DraggingWarn);
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAnchorWatch->TargetID)->m_bIsDragging = true;

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                }
                this->server()->closeDBConnection(database);
            }
        }
    }
    hgTargetManager::m_mapTarget.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgAnchorWatchTimerHandler TimeDiff: " << diff;
		}
}
