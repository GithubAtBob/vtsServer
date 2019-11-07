
#include "StdAfx.h"
#include "DBArpaTargetHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"


DBArpaTargetHandler::DBArpaTargetHandler(void)
{
}


DBArpaTargetHandler::~DBArpaTargetHandler(void)
{
}

void DBArpaTargetHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    Savehandle(s, sqlOperator);
}

void DBArpaTargetHandler::Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("arpa_target_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",QString::fromStdString(ArpaTarget.id()));
    l_data.insert("number",QString::fromStdString(ArpaTarget.radarid()).toInt());
    l_data.insert("reserved",ArpaTarget.reserved());
    l_data.insert("rng",ArpaTarget.rng());
    l_data.insert("brg",ArpaTarget.brg());
    l_data.insert("spd",ArpaTarget.spd());
    l_data.insert("crs",ArpaTarget.crs());
    l_data.insert("sog",ArpaTarget.cog());
    l_data.insert("cog",ArpaTarget.cog());
    l_data.insert("scans",ArpaTarget.scans());
    l_data.insert("flags",ArpaTarget.flags());
    l_data.insert("longitude",ArpaTarget.lon());
    l_data.insert("latitude",ArpaTarget.lat());
    l_data.insert("time",ArpaTarget.reportticks());
    l_pSqlInsertCmd->SetData(l_data);
    
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(arpa_target_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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