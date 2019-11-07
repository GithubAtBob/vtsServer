
#include "StdAfx.h"
#include "DBAlgorWarMesHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"


DBAlgorWarMesHandler::DBAlgorWarMesHandler(void)
{
}


DBAlgorWarMesHandler::~DBAlgorWarMesHandler(void)
{
}

void DBAlgorWarMesHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    Savehandle(s, sqlOperator);
}

void DBAlgorWarMesHandler::Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("algorwar_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("WarnID",AlgorWarMes.warningid().c_str());
    l_data.insert("WarnDUID",AlgorWarMes.warningguid().c_str());
    l_data.insert("WarningPriority",AlgorWarMes.warningpriority());
    l_data.insert("WarningName",AlgorWarMes.warningname().c_str());
    l_data.insert("MMSI",AlgorWarMes.mmsi().c_str());
    l_data.insert("otherMMSI",AlgorWarMes.othermmsi().c_str());
    l_data.insert("WarningTime",AlgorWarMes.warningtime());
    l_data.insert("WarMes",AlgorWarMes.warmes());
    l_data.insert("level",AlgorWarMes.level());
    l_data.insert("blink",AlgorWarMes.blink());
    l_data.insert("vector_min",AlgorWarMes.vector_min());
    l_data.insert("sound",AlgorWarMes.sound());
    l_pSqlInsertCmd->SetData(l_data);
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(algorwar_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }  
}