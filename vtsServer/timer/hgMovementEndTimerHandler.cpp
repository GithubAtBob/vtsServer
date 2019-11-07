#include "StdAfx.h"
#include "hgMovementEndTimerHandler.h"

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
hgMovementEndTimerHandler::hgMovementEndTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgMovementEndTimerHandler::~hgMovementEndTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgMovementEndTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgMovementEndTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    QMap<QString,MovementEnd>::iterator l_itMovementEnd;
    QMap<QString,hgTarget>::iterator l_itAis;
    for (l_itMovementEnd = hgAlarmManager::m_WarningSetManager.m_mapMovementEnd.begin(); l_itMovementEnd != hgAlarmManager::m_WarningSetManager.m_mapMovementEnd.end(); l_itMovementEnd++)
    {
        if (l_itMovementEnd->b_MovementEnd == false)
        {
            continue;
        }
        l_itAis = hgTargetManager::m_mapTarget.find(l_itMovementEnd->TargetID);
        if (l_itAis == hgTargetManager::m_mapTarget.end())
        {
            return;
        }
        hg::utils::PointLL l_pointLLOwn,l_pointLLTarget,l_pointLLEnd;
        double l_dDistance;
        l_pointLLOwn.setLat(l_itAis->Lat);
        l_pointLLOwn.setLon(l_itAis->Lon);
        l_pointLLTarget.setLat(l_itMovementEnd->EndLat);
        l_pointLLTarget.setLon(l_itMovementEnd->EndLon);
        l_dDistance = hg::utils::navutil::getDistance(l_pointLLOwn,l_pointLLTarget)*NM2M;  //º£Àï->Ã×
        if (l_dDistance > MoveDistance)
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itMovementEnd->TargetID)->m_bIsMovementEnd == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[MOVEMENTEND]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itAis->ID.toStdString());
                l_mes.set_mmsi(l_itAis->ID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                }
                this->server()->closeDBConnection(database);
            }
            hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itMovementEnd->TargetID)->m_bIsMovementEnd = true;
        }
    }
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgMovementEndTimerHandler TimeDiff: " << diff;
		}
}
