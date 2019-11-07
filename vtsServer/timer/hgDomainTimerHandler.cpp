#include "StdAfx.h"
#include "hgDomainTimerHandler.h"

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
hgDomainTimerHandler::hgDomainTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgDomainTimerHandler::~hgDomainTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgDomainTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgDomainTimerHandler::handle(const boost::system::error_code& e)
{
	  double start = GetTickCount();
    QMap<QString,Domain>::iterator l_itDomain;
    QMap<QString,hgTarget>::iterator l_itAisMsg;
    for (l_itDomain = hgAlarmManager::m_WarningSetManager.m_mapDomain.begin(); l_itDomain != hgAlarmManager::m_WarningSetManager.m_mapDomain.end(); l_itDomain++)
    {

        if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itDomain->TargetID) != hgAlarmManager::m_WarningSetManager.m_mapAuthorized.end())
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itDomain->TargetID)->Authorize == true)
            {
                continue;
            }   
        }
        if (l_itDomain->DomainWatch == false)
        {
            continue;
        }
        {
            l_itAisMsg = hgTargetManager::m_mapTarget.find(l_itDomain->TargetID);
            if ( l_itAisMsg == hgTargetManager::m_mapTarget.end() )
            {
                continue ;
            }
        }
        if (hgAlarmManager::DomainWatchMsg(l_itAisMsg->ID,l_itAisMsg->Lat,l_itAisMsg->Lon,l_itDomain->DomainRadius))
        {
            QMap<double,hgTarget>::iterator l_itDomainWatch = hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAisMsg->ID)->m_mapDomainWatch.begin();
            for (l_itDomainWatch; l_itDomainWatch != hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAisMsg->ID)->m_mapDomainWatch.end(); ++l_itDomainWatch)
            {
                if (l_itDomainWatch->DomainWatch == false)
                {
                    hgWarningMes l_mes;
                    l_mes.set_warningid(hgWaringTypeGuid[DOMAINWATCH]);
                    l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                    l_mes.set_warningpriority(PriorityRed);
                    l_mes.set_warningname("DomainWatch");
                    l_mes.set_mmsi(l_itDomain->TargetID.toStdString());
                    l_mes.set_targetmmsi(l_itDomainWatch->ID.toStdString());
                    l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                    l_mes.set_warningtype(DomainWatchWarn);
                    hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);
                    l_itDomainWatch->DomainWatch = true;

                    QSqlDatabase database = this->server()->openDBConnection();
                    hgSqlOperator l_sqlOperator(database);
                    {
                        hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                    }
                    this->server()->closeDBConnection(database);
                }
            }
        }

        if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAisMsg->MMSI) != hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.end())
        {
            for (int i = 0; i < hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAisMsg->ID)->m_listDomainCancel.size(); i++)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[DOMAINWATCH]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(NoRisk);
                l_mes.set_warningname("DomainWatch");
                l_mes.set_mmsi(l_itDomain->TargetID.toStdString());
                l_mes.set_targetmmsi(hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itAisMsg->ID)->m_listDomainCancel[i].toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                l_mes.set_warningtype(DomainWatchWarn);
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);
            }
        }
    }
    hgTargetManager::m_mapTarget.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgDomainTimerHandler TimeDiff: " << diff;
		}
}
