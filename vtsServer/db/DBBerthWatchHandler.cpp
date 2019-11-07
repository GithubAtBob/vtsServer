
#include "StdAfx.h"
#include "DBBerthWatchHandler.h"

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

DBBerthWatchHandler::DBBerthWatchHandler(void)
{
}


DBBerthWatchHandler::~DBBerthWatchHandler(void)
{
}

void DBBerthWatchHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    QMap<QString,BerthWatch>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapBerthWatch.find(MMSI);
    if (l_it != hgAlarmManager::m_WarningSetManager.m_mapBerthWatch.end())
    {
        Updatehandle(s, sqlOperator);
    }
    else
    {
        Addhandle(s, sqlOperator);
    }
}


void DBBerthWatchHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("berth_watch_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_BerthWatch",b_BerthWatch);
    l_data.insert("Distance",Distance);
    l_data.insert("BerthLat",BerthLat);
    l_data.insert("BerthLon",BerthLon);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("MMSI = '%1'").arg(MMSI));
    Result = "Update  berth_watch_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(berth_watch_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update berth_watch_table true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }


}

void DBBerthWatchHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("berth_watch_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_BerthWatch",b_BerthWatch);
    l_data.insert("Distance",Distance);
    l_data.insert("BerthLat",BerthLat);
    l_data.insert("BerthLon",BerthLon);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "Add berth_watch_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(berth_watch_table Add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Add berth_watch_table true";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

