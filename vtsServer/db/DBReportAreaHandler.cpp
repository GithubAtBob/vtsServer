
#include "StdAfx.h"
#include "DBReportAreaHandler.h"

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

DBReportAreaHandler::DBReportAreaHandler(void)
{
}


DBReportAreaHandler::~DBReportAreaHandler(void)
{
}

void DBReportAreaHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    QMap<QString,ReportArea>::iterator l_it = hgAlarmManager::m_WarningSetManager.m_mapReportArea.find(MMSI);
    if (l_it != hgAlarmManager::m_WarningSetManager.m_mapReportArea.end())
    {
        Updatehandle(s, sqlOperator);
    }
    else
    {
        Addhandle(s, sqlOperator);
    }
}


void DBReportAreaHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("report_area_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_ReportArea",b_ReportArea);
    l_data.insert("b_Pattern",b_Pattern);

    QMap<QString,AreaData>::iterator it = mapAreaData.begin();
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    for (it; it != mapAreaData.begin(); ++it)
    {
        out << it->ID << it->type;
    }
    l_data.insert("AreaData",QVariant(mes));

    l_data.insert("EarilestTime",EarilestTime);
    l_data.insert("LatestTime",LatestTime);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("MMSI = '%1'").arg(MMSI));
    Result = "Update  report_area_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(report_area_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update report_area_table true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }


}

void DBReportAreaHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("report_area_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("MMSI",MMSI);
    l_data.insert("b_ReportArea",b_ReportArea);
    l_data.insert("b_Pattern",b_Pattern);


    QMap<QString,AreaData>::iterator it = mapAreaData.begin();
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    for (it; it != mapAreaData.begin(); ++it)
    {
        out << it->ID << it->type;
    }
    l_data.insert("AreaData",QVariant(mes));

    l_data.insert("EarilestTime",EarilestTime);
    l_data.insert("LatestTime",LatestTime);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "Add report_area_table false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(report_area_table Add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Add report_area_table true";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

