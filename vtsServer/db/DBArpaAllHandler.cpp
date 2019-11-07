
#include "StdAfx.h"
#include "DBArpaAllHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"


DBArpaAllHandler::DBArpaAllHandler(void)
{
}


DBArpaAllHandler::~DBArpaAllHandler(void)
{
}

void DBArpaAllHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
	Savehandle(s, sqlOperator);
	Savehandle2(s, sqlOperator);
}

void DBArpaAllHandler::Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("arpaall_target_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("alldata",QByteArray::fromStdString(pack.arpadata()));
    l_data.insert("time",time(NULL));
    l_pSqlInsertCmd->SetData(l_data);
     
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(arpaall_target_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBArpaAllHandler::Savehandle2(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
	hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
	l_pSqlInsertCmd->SetTableName("arpaall_target_table_min");
	QMap<QString, QVariant> l_data;
	l_data.insert("alldata",QByteArray::fromStdString(pack.arpadata()));
	l_data.insert("time",time(NULL));
	l_pSqlInsertCmd->SetData(l_data);

	if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
	{
		std::cout << "Open datatabase error(arpaall_target_table_min):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
