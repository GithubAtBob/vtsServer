
#include "StdAfx.h"
#include "DBSpeedWatchHandler.h"

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

DBSpeedWatchHandler::DBSpeedWatchHandler(void)
{
}


DBSpeedWatchHandler::~DBSpeedWatchHandler(void)
{
}

void DBSpeedWatchHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    QMap<QString,SpeedWatch>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapSpeedWatch.find(MMSI);
    if (l_it != hgAlarmManager::m_WarningSetManager.m_mapSpeedWatch.end())
    {
        Updatehandle(s, sqlOperator);
    }
    else
    {
        Addhandle(s, sqlOperator);
    }
}


void DBSpeedWatchHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("speed_watch_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_SpeedWatch",b_SpeedWatch);
    l_data.insert("MinSpeed",MinSpeed);
    l_data.insert("MinDuration",MinDuration);
    l_data.insert("MaxSpeed",MaxSpeed);
    l_data.insert("MaxDuration",MaxDuration);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("MMSI = '%1'").arg(MMSI));
    Result = "Update  speed_watch_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(speed_watch_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update speed_watch_table true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }


}

void DBSpeedWatchHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("speed_watch_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_SpeedWatch",b_SpeedWatch);
    l_data.insert("MinSpeed",MinSpeed);
    l_data.insert("MinDuration",MinDuration);
    l_data.insert("MaxSpeed",MaxSpeed);
    l_data.insert("MaxDuration",MaxDuration);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "Add speed_watch_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(speed_watch_table Add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Add speed_watch_table true";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

