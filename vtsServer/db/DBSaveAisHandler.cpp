
#include "StdAfx.h"
#include "DBSaveAisHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "Managers/hgTargetManager.h"


DBSaveAisHandler::DBSaveAisHandler(void)
{
}


DBSaveAisHandler::~DBSaveAisHandler(void)
{
}

void DBSaveAisHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("target_dynamic_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",QString::fromStdString(AISMessage.id()));
    l_data.insert("MMSI",QString::fromStdString(AISMessage.mmsi()));
    l_data.insert("RadarID",QString::fromStdString(AISMessage.radarid()));
    l_data.insert("Source",AISMessage.source());
    l_data.insert("Result",AISMessage.result());
    l_data.insert("Reserved",AISMessage.reserved());
    l_data.insert("Rng",AISMessage.rng());
    l_data.insert("Spd",AISMessage.spd());
    l_data.insert("Crs",AISMessage.crs());
    l_data.insert("Scans",AISMessage.scans());
    l_data.insert("Flags",AISMessage.flags());
    l_data.insert("MID",AISMessage.mid());
    l_data.insert("ROTAIS",AISMessage.rotais());
    l_data.insert("SOG",AISMessage.sog());
    l_data.insert("Lon",AISMessage.lon());
    l_data.insert("Lat",AISMessage.lat());
    l_data.insert("COG",AISMessage.cog());
    l_data.insert("HDG",AISMessage.hdg());
    l_data.insert("SyncState",AISMessage.syncstate());
    l_data.insert("SlotTO",AISMessage.slotto());
    l_data.insert("ReportTicks",AISMessage.reportticks());
    l_data.insert("RecentPeriod",AISMessage.recentperiod());
    l_data.insert("PosAccuracy",AISMessage.posaccuracy());
    l_data.insert("m_utc_hour",AISMessage.m_utc_hour());
    l_data.insert("m_utc_min",AISMessage.m_utc_min());
    l_data.insert("m_utc_sec",AISMessage.m_utc_sec());
    l_data.insert("Range_NM",AISMessage.range_nm());
    l_data.insert("Brg",AISMessage.brg());
    l_data.insert("b_active",0);
    l_data.insert("n_alarm_state",0);
    l_data.insert("b_suppress_audio",0);
    l_data.insert("b_positionValid",0);
    l_data.insert("b_nameValid",0);
    l_data.insert("SyncState",0);
    l_data.insert("bCPA_Valid",AISMessage.bcpa_valid());
    l_data.insert("TCPA",AISMessage.tcpa());
    l_data.insert("CPA",AISMessage.cpa());
    l_pSqlInsertCmd->SetData(l_data);
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(target_dynamic_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}