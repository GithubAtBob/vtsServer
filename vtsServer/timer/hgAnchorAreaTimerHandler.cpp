#include "StdAfx.h"
#include "hgAnchorAreaTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgTargetManager.h"
#include "hgutils/NavUtil.h"
#include "Managers/hgAlarmManager.h"
//vtsSETUP_TIMER("Domain", 1, hgDomainTimerHandler);

extern const char* hgWaringTypeGuid[];
hgAnchorAreaTimerHandler::hgAnchorAreaTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgAnchorAreaTimerHandler::~hgAnchorAreaTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgAnchorAreaTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgAnchorAreaTimerHandler::handle(const boost::system::error_code& e)
{
	  double start = GetTickCount();
    QMap<QString,AnchorArea>::iterator l_itArea;
    for (l_itArea = hgAlarmManager::m_WarningSetManager.m_mapAnchorArea.begin(); l_itArea != hgAlarmManager::m_WarningSetManager.m_mapAnchorArea.end(); ++l_itArea)
    {
        if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itArea->TargetID) != hgAlarmManager::m_WarningSetManager.m_mapAuthorized.end())
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itArea->TargetID)->Authorize == true)
            {
                continue;
            }  
        }
        if (l_itArea->b_AnchorArea == false)
        {
            continue;
        }
        int l_type;
        QString l_GUID;
        if (hgAlarmManager::FindTarget(l_itArea->ID,l_itArea->TargetID,l_type,l_GUID)) 
        {
            //船进入非授权抛锚区
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsAnchorArea == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[ANCHORAGE]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itArea->TargetID.toStdString());
                l_mes.set_mmsi(l_itArea->TargetID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                l_mes.set_userlayguid(l_GUID.toStdString());
                l_mes.set_userlayid((UserLayerType)l_type);
                l_mes.set_warningtype(AnchorAreaWarn);
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                }
                this->server()->closeDBConnection(database);
            } 
            hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsAnchorArea = true;
        }
        else
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsAnchorArea == true)
            {
                //船离开抛锚区
                hgWarningMes l_WarningMes;
                l_WarningMes.set_warningid(hgWaringTypeGuid[ANCHORAGE]);
                l_WarningMes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_WarningMes.set_warningpriority(NoRisk);
                l_WarningMes.set_warningname(l_itArea->TargetID.toStdString());
                l_WarningMes.set_mmsi(l_itArea->TargetID.toStdString());
                l_WarningMes.set_userlayguid("");
                l_WarningMes.set_userlayid(UNotes);
                l_WarningMes.set_warningtime(hgTargetManager::GetWarnTime());
                l_WarningMes.set_warningtype(AnchorAreaWarn);
                l_WarningMes.set_targetmmsi("");
                hgAlarmManager::SendMessage(l_WarningMes,"hgWarningMes",this);
            }
            hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsAnchorArea = false;
        }      
    }
    hgTargetManager::m_mapTarget.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo <<"hgAnchorAreaTimerHandler TimeDiff: " << diff;
		}
}
