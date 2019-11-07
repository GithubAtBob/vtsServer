#include "StdAfx.h"
#include "hgTurnCircleTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgTargetManager.h"
#include "hgutils/NavUtil.h"
#include "Managers/hgAlarmManager.h"

//vtsSETUP_TIMER("Domain", 1, hgDomainTimerHandler);

extern const char* hgWaringTypeGuid[];
hgTurnCircleTimerHandler::hgTurnCircleTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgTurnCircleTimerHandler::~hgTurnCircleTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgTurnCircleTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgTurnCircleTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    QMap<QString,TurnCircle>::iterator l_itTurn;
    for (l_itTurn = hgAlarmManager::m_WarningSetManager.m_mapTurnCircle.begin(); l_itTurn != hgAlarmManager::m_WarningSetManager.m_mapTurnCircle.end(); l_itTurn++)
    {

        if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itTurn->TargetID) != hgAlarmManager::m_WarningSetManager.m_mapAuthorized.end())
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itTurn->TargetID)->Authorize == true)
            {
                continue;
            }   
        }
        if (l_itTurn->b_TurnCircle == false)
        {
            continue;
        }

        if (hgAlarmManager::TurnOver(l_itTurn.value()))
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itTurn->TargetID)->m_bIsTurnCircle == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[TURNINGCIRCLE]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itTurn->TargetID.toStdString());
                l_mes.set_mmsi(l_itTurn->TargetID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                }
                this->server()->closeDBConnection(database);
            } 
            hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itTurn->TargetID)->m_bIsTurnCircle = true;
        } 
        else
        {
            hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itTurn->TargetID)->m_bIsTurnCircle = false;
        }
    }
    hgTargetManager::m_mapTarget.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgTurnCircleTimerHandler TimeDiff: " << diff;
		}
}
