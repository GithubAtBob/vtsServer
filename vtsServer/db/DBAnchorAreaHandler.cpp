
#include "StdAfx.h"
#include "DBAnchorAreaHandler.h"

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

DBAnchorAreaHandler::DBAnchorAreaHandler(void)
{
}


DBAnchorAreaHandler::~DBAnchorAreaHandler(void)
{
}

void DBAnchorAreaHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    QMap<QString,AnchorArea>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapAnchorArea.find(MMSI);
    if (l_it != hgAlarmManager::m_WarningSetManager.m_mapAnchorArea.end())
    {
        Updatehandle(s, sqlOperator);
    }
    else
    {
        Addhandle(s, sqlOperator);
    }
}


void DBAnchorAreaHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    return;
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("anchor_area_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_AnchorArea",b_AnchorArea);
    l_data.insert("ID",ID);
    l_data.insert("Type",Type);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("MMSI = '%1'").arg(MMSI));
    Result = "Update  anchor_area_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(anchor_area_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update anchor_area_table true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }


}

void DBAnchorAreaHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("anchor_area_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_AnchorArea",b_AnchorArea);
    l_data.insert("ID",ID);
    l_data.insert("Type",Type);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "Add anchor_area_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(anchor_area_table Add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Add anchor_area_table true";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

