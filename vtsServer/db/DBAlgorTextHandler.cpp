
#include "StdAfx.h"
#include "DBAlgorTextHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "Managers/hgTargetManager.h"


DBAlgorTextHandler::DBAlgorTextHandler(void)
{
}


DBAlgorTextHandler::~DBAlgorTextHandler(void)
{
}

void DBAlgorTextHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
	if ( _isnan(msg.tcpa()) != 0 )
	{
		std::cout << "tcpa data error:" << msg.tcpa() << endl;
		return ;
	}
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("alagortext_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("warningtime",hgTargetManager::GetWarnTime());
    l_data.insert("rv",msg.rv());
    l_data.insert("rc",msg.rc());
    l_data.insert("dis",msg.dis());
    l_data.insert("tcpa",msg.tcpa());
    l_data.insert("sda",/*msg.sda()*/0);
    l_data.insert("sdam",/*msg.sdam()*/0);
    l_data.insert("tarlat",msg.tarlat());
    l_data.insert("tarlon",msg.tarlon());
    l_data.insert("tarcoure",msg.tarcoure());
    l_data.insert("tarspd",msg.tarspd());
    l_data.insert("tarmmsi",msg.tarmmsi().c_str());
    l_data.insert("bown",msg.bown());
    l_data.insert("ownmmsi",msg.ownmmsi().c_str());
    l_pSqlInsertCmd->SetData(l_data);
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(alagortext_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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