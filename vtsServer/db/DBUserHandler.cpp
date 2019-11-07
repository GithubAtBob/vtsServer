
#include "StdAfx.h"
#include "DBUserHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlOperator.h"


DBUserHandler::DBUserHandler(void)
{

}


DBUserHandler::~DBUserHandler(void)
{
}

void DBUserHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (Type)
    {
    case Update:
        UpdateHandle(s, sqlOperator);
        break;
    case Remove:
        DeleHandle(s, sqlOperator);
        break;
    }
}

void DBUserHandler::DeleHandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
    l_pSqlRemoveCmd->SetTableName("user_table");

    l_pSqlRemoveCmd->SetFilter(QString("loginname = '%1'").arg(LoginName));

    Result = "Remove false";
    if (!sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
    {
		std::cout << "Open datatabase error(user_table Remove):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBUserHandler::UpdateHandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("user_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("userid",UserID);
    l_data.insert("loginname",LoginName);
    l_data.insert("username",UserName);
    l_data.insert("password",Password);
    l_data.insert("phone",Phone);
    l_data.insert("avatar",avatar);
    l_data.insert("groupID",UserGroup);
    l_pSqlUpdateCmd->SetData(l_data);


    l_pSqlUpdateCmd->SetFilter(QString("loginname = '%1'").arg(OldName));
    Result = "Update false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(user_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
