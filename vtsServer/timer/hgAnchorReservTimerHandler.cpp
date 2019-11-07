#include "StdAfx.h"
#include "hgAnchorReservTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgTargetManager.h"
#include "hgutils/NavUtil.h"
#include "Managers/hgAlarmManager.h"
//vtsSETUP_TIMER("Domain", 1, hgDomainTimerHandler);

extern const char* hgWaringTypeGuid[];
hgAnchorReservTimerHandler::hgAnchorReservTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgAnchorReservTimerHandler::~hgAnchorReservTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgAnchorReservTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgAnchorReservTimerHandler::handle(const boost::system::error_code& e)
{
	  double start = GetTickCount();
    QMap<QString,AnchorReserv>::iterator l_itAnchor;
    for (l_itAnchor = hgAlarmManager::m_WarningSetManager.m_mapAnchorReserv.begin(); l_itAnchor != hgAlarmManager::m_WarningSetManager.m_mapAnchorReserv.end(); l_itAnchor++)
    {
        if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itAnchor->TargetID) != hgAlarmManager::m_WarningSetManager.m_mapAuthorized.end())
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itAnchor->TargetID)->Authorize == true)
            {
                continue;
            }   
        }
        if (l_itAnchor->b_AnchorReserv == false)
        {
            continue;
        }

        int l_type;
        QString l_GUID;
        if (hgAlarmManager::FindTarget(l_itAnchor->ID,l_itAnchor->TargetID,l_type,l_GUID))
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAnchor->TargetID)->m_bIsAnchorArea == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[ANCHORAGE]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itAnchor->TargetID.toStdString());
                l_mes.set_mmsi(l_itAnchor->TargetID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                l_mes.set_userlayguid(l_GUID.toStdString());
                l_mes.set_userlayid((UserLayerType)l_type);
                l_mes.set_warningtype(AnchorReservWarn);
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                }
                this->server()->closeDBConnection(database);
            } 
            hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAnchor->TargetID)->m_bIsAnchorReserv = true;
        }
        else
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAnchor->TargetID)->m_bIsAnchorReserv == true)
            {
                //´¬Àë¿ªÅ×ÃªÇø
                hgWarningMes l_WarningMes;
                l_WarningMes.set_warningid(hgWaringTypeGuid[ANCHORAGE]);
                l_WarningMes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_WarningMes.set_warningpriority(NoRisk);
                l_WarningMes.set_warningname(l_itAnchor->TargetID.toStdString());
                l_WarningMes.set_mmsi(l_itAnchor->TargetID.toStdString());
                l_WarningMes.set_userlayguid("");
                l_WarningMes.set_userlayid(UNotes);
                l_WarningMes.set_warningtime(hgTargetManager::GetWarnTime());
                l_WarningMes.set_warningtype(AnchorReservWarn);
                l_WarningMes.set_targetmmsi("");
                hgAlarmManager::SendMessage(l_WarningMes,"hgWarningMes",this);
            }
            hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAnchor->TargetID)->m_bIsAnchorReserv = false;
        }

    }
    hgTargetManager::m_mapTarget.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgAnchorReservTimerHandler TimeDiff: " << diff;
		}
}
