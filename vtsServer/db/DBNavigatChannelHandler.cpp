
#include "StdAfx.h"
#include "DBNavigatChannelHandler.h"

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

DBNavigatChannelHandler::DBNavigatChannelHandler(void)
{
}


DBNavigatChannelHandler::~DBNavigatChannelHandler(void)
{
}

void DBNavigatChannelHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    QMap<QString,NavigatChannel>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapNavigatChannel.find(MMSI);
    if (l_it != hgAlarmManager::m_WarningSetManager.m_mapNavigatChannel.end())
    {
        Updatehandle(s, sqlOperator);
    }
    else
    {
        Addhandle(s, sqlOperator);
    }
}


void DBNavigatChannelHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("navigat_channel_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_NavigatChannel",b_NavigatChannel);
    l_data.insert("ID",ID);
    l_data.insert("Type",Type);
    //l_data.insert("Name",Name);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(MMSI));
    Result = "Update  navigat_channel_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(navigat_channel_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update navigat_channel_table true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }


}

void DBNavigatChannelHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("navigat_channel_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_NavigatChannel",b_NavigatChannel);
    l_data.insert("ID",ID);
    l_data.insert("Type",Type);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "Add navigat_channel_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(navigat_channel_table Add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Add navigat_channel_table true";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

