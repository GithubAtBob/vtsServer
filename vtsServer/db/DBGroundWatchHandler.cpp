
#include "StdAfx.h"
#include "DBGroundWatchHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

DBGroundWatchHandler::DBGroundWatchHandler(void)
{
}


DBGroundWatchHandler::~DBGroundWatchHandler(void)
{
}

void DBGroundWatchHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    QMap<QString,GroundWatch>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapGroundWatch.find(MMSI);
    if (l_it != hgAlarmManager::m_WarningSetManager.m_mapGroundWatch.end())
    {
        Updatehandle(s, sqlOperator);
    }
    else
    {
        Addhandle(s, sqlOperator);
    }
}


void DBGroundWatchHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("ground_watch_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_GroundWatch",b_GroundWatch);
    l_data.insert("GroundDraught",GroundDraught);
    l_data.insert("KeelClearance",KeelClearance);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("MMSI = '%1'").arg(MMSI));
    Result = "Update  ground_watch_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(ground_watch_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update ground_watch_table true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }


}

void DBGroundWatchHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("ground_watch_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_GroundWatch",b_GroundWatch);
    l_data.insert("GroundDraught",GroundDraught);
    l_data.insert("KeelClearance",KeelClearance);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "Add ground_watch_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(ground_watch_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Add ground_watch_table true";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

