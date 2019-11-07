
#include "StdAfx.h"
#include "DBGroupHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"


DBGroupHandler::DBGroupHandler(void)
{
}


DBGroupHandler::~DBGroupHandler(void)
{
}

void DBGroupHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (Type)
    {
    case /*DBGroupHandlerType::*/Add:
        Addhandle(s, sqlOperator);
        break;
    case /*DBGroupHandlerType::*/Update:
        Updatehandle(s, sqlOperator);
        break;
    case /*DBGroupHandlerType::*/Remove:
        Removehandle(s, sqlOperator);
        break;
    }
}

void DBGroupHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("group_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("power",Power);
    l_data.insert("type",GroupType);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "add false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(group_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "add true";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

void DBGroupHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("group_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("name",Name);
    l_data.insert("power",Power);
    l_pSqlUpdateCmd->SetData(l_data);


    l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));
    Result = "Update false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(group_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Update true";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }
}

void DBGroupHandler::Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
    l_pSqlRemoveCmd->SetTableName("group_table");

    l_pSqlRemoveCmd->SetFilter(QString("ID = '%1'").arg(ID));

    Result = "Remove false";
    if (!sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
    {
		std::cout << "Open datatabase error(group_table Remove):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "Remove true";
    std::cout << Result.toStdString();
    if (l_pSqlRemoveCmd)
    {
        delete l_pSqlRemoveCmd;
        l_pSqlRemoveCmd = NULL;
    }
}
