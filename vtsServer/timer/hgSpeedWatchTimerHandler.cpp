#include "StdAfx.h"
#include "hgSpeedWatchTimerHandler.h"

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
hgSpeedWatchTimerHandler::hgSpeedWatchTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgSpeedWatchTimerHandler::~hgSpeedWatchTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgSpeedWatchTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgSpeedWatchTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    QMap<QString,SpeedWatch>::iterator l_itSpeedWatch;
    for (l_itSpeedWatch = hgAlarmManager::m_WarningSetManager.m_mapSpeedWatch.begin(); l_itSpeedWatch != hgAlarmManager::m_WarningSetManager.m_mapSpeedWatch.end(); l_itSpeedWatch++)
    {

        if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itSpeedWatch->TargetID) != hgAlarmManager::m_WarningSetManager.m_mapAuthorized.end())
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itSpeedWatch->TargetID)->Authorize == true)
            {
                continue;
            }   
        }
        if (l_itSpeedWatch->b_SpeedWatch == false)
        {
            continue;
        }
        int l_iType = hgAlarmManager::SpeedWatching(l_itSpeedWatch.value());

        if (l_iType == MinSpeed)
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itSpeedWatch->TargetID)->m_bIsMinSpeed == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[LOWSPEEDWATCH]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itSpeedWatch->TargetID.toStdString());
                l_mes.set_mmsi(l_itSpeedWatch->TargetID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itSpeedWatch->TargetID)->m_bIsMinSpeed = true;

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                }
                this->server()->closeDBConnection(database);
            }
        }
        else if (l_iType == MaxSpeed)
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itSpeedWatch->TargetID)->m_bIsMaxSpeed == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[HIGHSPEEDWATCH]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itSpeedWatch->TargetID.toStdString());
                l_mes.set_mmsi(l_itSpeedWatch->TargetID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itSpeedWatch->TargetID)->m_bIsMaxSpeed = true;

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
			vtsInfo << "hgSpeedWatchTimerHandler TimeDiff: " << diff;
		}
}
