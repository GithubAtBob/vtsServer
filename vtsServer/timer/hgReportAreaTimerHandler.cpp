#include "StdAfx.h"
#include "hgReportAreaTimerHandler.h"

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
hgReportAreaTimerHandler::hgReportAreaTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgReportAreaTimerHandler::~hgReportAreaTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgReportAreaTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgReportAreaTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    QMap<QString,ReportArea>::iterator l_itArea;
    for (l_itArea = hgAlarmManager::m_WarningSetManager.m_mapReportArea.begin(); l_itArea != hgAlarmManager::m_WarningSetManager.m_mapReportArea.end(); l_itArea++)
    {

        if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itArea->TargetID) != hgAlarmManager::m_WarningSetManager.m_mapAuthorized.end())
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itArea->TargetID)->Authorize == true)
            {
                continue;
            }   
        }
        if (l_itArea->b_ReportArea == false)
        {
            continue;
        }

        if (l_itArea->b_Pattern == false)
        {
            if (hgAlarmManager::ReportEnter(l_itArea->TargetID))
            {
                if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsReportArea == false)
                {
                    hgWarningMes l_mes;
                    l_mes.set_warningid(hgWaringTypeGuid[REPORTINGAREA]);
                    l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                    l_mes.set_warningpriority(PriorityRed);
                    l_mes.set_warningname(l_itArea->TargetID.toStdString());
                    l_mes.set_mmsi(l_itArea->TargetID.toStdString());
                    l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                    hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                    QSqlDatabase database = this->server()->openDBConnection();
                    hgSqlOperator l_sqlOperator(database);
                    {
                        hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                    }
                    this->server()->closeDBConnection(database);
                } 
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsReportArea = true;
            }
            else
            {
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsReportArea = false;
            }
        } 
        else if (l_itArea->b_Pattern == true)
        {
            int l_iType = hgAlarmManager::ReportNoEnter(l_itArea->mapAreaData,l_itArea->TargetID);
            if (l_iType == Yes)//进入其它报告区
            {
                if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsReportArea == false)
                {
                    hgWarningMes l_mes;
                    l_mes.set_warningid(hgWaringTypeGuid[REPORTINGAREA]);
                    l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                    l_mes.set_warningpriority(PriorityRed);
                    l_mes.set_warningname(l_itArea->TargetID.toStdString());
                    l_mes.set_mmsi(l_itArea->TargetID.toStdString());
                    l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                    hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                    QSqlDatabase database = this->server()->openDBConnection();
                    hgSqlOperator l_sqlOperator(database);
                    {
                        hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                    }
                    this->server()->closeDBConnection(database);
                } 
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsReportArea = true;
            }
            else if (l_iType == No) //没有进入其它报告区
            {
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsReportArea = false;
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsReportTime = false;
            }
            else //进入相应报告区的时间
            {
                if (hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsReportTime == false)
                {
                    if (l_iType < l_itArea->EarilestTime)
                    {
                        hgWarningMes l_mes;
                        l_mes.set_warningid(hgWaringTypeGuid[REPORTINGAREA]);
                        l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                        l_mes.set_warningpriority(PriorityRed);
                        l_mes.set_warningname(l_itArea->TargetID.toStdString());
                        l_mes.set_mmsi(l_itArea->TargetID.toStdString());
                        l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                        hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                        QSqlDatabase database = this->server()->openDBConnection();
                        hgSqlOperator l_sqlOperator(database);
                        {
                            hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                        }
                        this->server()->closeDBConnection(database);
                    }
                    if (l_iType > l_itArea->LatestTime)
                    {
                        hgWarningMes l_mes;
                        l_mes.set_warningid(hgWaringTypeGuid[REPORTINGAREA]);
                        l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                        l_mes.set_warningpriority(PriorityRed);
                        l_mes.set_warningname(l_itArea->TargetID.toStdString());
                        l_mes.set_mmsi(l_itArea->TargetID.toStdString());
                        l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                        hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                        QSqlDatabase database = this->server()->openDBConnection();
                        hgSqlOperator l_sqlOperator(database);
                        {
                            hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                        }
                        this->server()->closeDBConnection(database);
                    }
                } 
                hgAlarmManager::m_WarningSetManager.m_mapWarnInfo.find(l_itArea->TargetID)->m_bIsReportTime = true;
                l_itArea->enter = true;
            }

            //超时未进入报告区
            if (time(NULL) >= l_itArea->LatestTime && l_itArea->enter == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[REPORTINGAREA]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname(l_itArea->TargetID.toStdString());
                l_mes.set_mmsi(l_itArea->TargetID.toStdString());
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgAlarmManager::SaveWarnData(l_sqlOperator,l_mes);
                }
                this->server()->closeDBConnection(database);

                l_itArea->enter = true;
            }
        }

    }

    hgTargetManager::m_mapTarget.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgReportAreaTimerHandler TimeDiff: " << diff;
		}
}
