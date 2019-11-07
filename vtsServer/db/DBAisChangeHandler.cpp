
#include "StdAfx.h"
#include "DBAisChangeHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"


DBAisChangeHandler::DBAisChangeHandler(void)
{
}


DBAisChangeHandler::~DBAisChangeHandler(void)
{
}

void DBAisChangeHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",m_MMSI);
    l_data.insert("MMSI",m_MMSI);
    l_data.insert("ShipName",m_ShipNameEN);
    l_data.insert("ChShipName",m_ShipNameCH);
    l_data.insert("CallSign",m_Callsign);
    l_data.insert("Nationality",m_Nationality);
    l_data.insert("IMO",m_IMO);
    l_data.insert("Class",m_Class);
    l_data.insert("ShipType",m_ShipType);
    l_data.insert("DimA",m_DimA);
    l_data.insert("DimB",m_DimB);
    l_data.insert("DimC",m_DimC);
	l_data.insert("DimD",m_DimD);
	l_data.insert("Length",m_DimA+m_DimB);
	l_data.insert("Width",m_DimD+m_DimD);
    l_data.insert("Note",m_Note);
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("target_static_table");
    l_pSqlInsertCmd->SetData(l_data);
    Result = "Update false";
    if (sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
        Result = "OK";
		qDebug() << "Insert " << m_MMSI << "target_static_table";
        if (l_pSqlInsertCmd)
        {
            delete l_pSqlInsertCmd;
            l_pSqlInsertCmd = NULL;
        }
        return ;
    }
	else
	{
		std::cout << "Insert datatabase error(target_static_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		if (l_pSqlInsertCmd)
		{
			delete l_pSqlInsertCmd;
			l_pSqlInsertCmd = NULL;
		}
	}


    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("target_static_table");
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("MMSI = '%1'").arg(m_MMSI));

    //     l_pSqlUpdateCmd->SetData("lon",10);          ///更新具体某项
    //     l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(target_static_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

	qDebug() << "Update " << m_MMSI << "target_static_table";
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }
}

