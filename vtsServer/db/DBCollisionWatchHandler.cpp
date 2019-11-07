
#include "StdAfx.h"
#include "DBCollisionWatchHandler.h"

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
#include "message/hgCollisionWatch.pb.h"

DBCollisionWatchHandler::DBCollisionWatchHandler(void)
{
}


DBCollisionWatchHandler::~DBCollisionWatchHandler(void)
{
}

void DBCollisionWatchHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    QMap<QString,CollisionWatch>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.find(MMSI);
    if (l_it != hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.end())
    {
        Updatehandle(s, sqlOperator);
    }
    else
    {
        Addhandle(s, sqlOperator);
    }
}


void DBCollisionWatchHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("collision_watch_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_CollisionWatch",b_CollisionWatch);
    l_data.insert("DCPA",DCPA);
    l_data.insert("TCPA",TCPA);
    if (Type == Custom)
    {
        l_data.insert("CustomDCPA",DCPA);
        l_data.insert("CustomTCPA",TCPA);
    }
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("MMSI = '%1'").arg(MMSI));
    Result = "Update  collision_watch_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(collision_watch_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    Result = "Update collision_watch_table true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }


}

void DBCollisionWatchHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("collision_watch_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_CollisionWatch",b_CollisionWatch);
    l_data.insert("DCPA",DCPA);
    l_data.insert("TCPA",TCPA);
    if (Type == Custom)
    {
        l_data.insert("CustomDCPA",DCPA);
        l_data.insert("CustomTCPA",TCPA);
    }
    else
    {
        l_data.insert("CustomDCPA",0);
        l_data.insert("CustomTCPA",0);
    }
    l_pSqlInsertCmd->SetData(l_data);
    Result = "Add collision_watch_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(collision_watch_table Add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Add collision_watch_table true";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

