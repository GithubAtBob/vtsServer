
#include "StdAfx.h"
#include "DBAnchorReservHandler.h"

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

DBAnchorReservHandler::DBAnchorReservHandler(void)
{
}


DBAnchorReservHandler::~DBAnchorReservHandler(void)
{
}

void DBAnchorReservHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    QMap<QString,AnchorReserv>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapAnchorReserv.find(MMSI);
    if (l_it != hgAlarmManager::m_WarningSetManager.m_mapAnchorReserv.end())
    {
        Updatehandle(s, sqlOperator);
    }
    else
    {
        Addhandle(s, sqlOperator);
    }
}


void DBAnchorReservHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("anchor_reserv_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_AnchorReserv",b_AnchorReserv);
    l_data.insert("ID",ID);
    l_data.insert("Type",Type);
    //l_data.insert("Name",Name);
    l_data.insert("ETA",ETA);
    l_data.insert("ETD",ETD);
    l_data.insert("Tracks",Tracks);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("MMSI = '%1'").arg(MMSI));
    Result = "Update  anchor_reserv_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(anchor_reserv_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update anchor_reserv_table true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }


}

void DBAnchorReservHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("anchor_reserv_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_AnchorReserv",b_AnchorReserv);
    l_data.insert("ID",ID);
    l_data.insert("Type",Type);
    //l_data.insert("Name",Name);
    l_data.insert("ETA",ETA);
    l_data.insert("ETD",ETD);
    l_data.insert("Tracks",Tracks);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "Add anchor_reserv_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(anchor_reserv_table Add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Add anchor_reserv_table true";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

