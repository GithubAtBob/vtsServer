
#include "StdAfx.h"
#include "DBRegisterHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"


DBRegisterHandler::DBRegisterHandler(void)
{
}


DBRegisterHandler::~DBRegisterHandler(void)
{
}

void DBRegisterHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{

    clock_t t1 = clock();
     //*
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("user_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("loginname",LoginName);
    l_data.insert("userid",UserID);
    l_data.insert("username",UserName);
    l_data.insert("password",Password);
    l_data.insert("phone",Phone);
    l_data.insert("groupID",UserGroup);
    l_data.insert("avatar",avatar);
    l_data.insert("groupType",GroupType);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "false";

    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
        Message = sqlOperator.LastError().text().toLatin1().data();
		std::cout << "Open datatabase error(user_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }


    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();

    Result = "OK";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
    //*/
    

    /*
    hgSqlSelectCmd* cmd = new hgSqlSelectCmd();
    cmd->SetTableName("user_table");
    cmd->SetFilter("loginname='root'");
    if (!sqlOperator.ImplementCmd(cmd))
    {
        Message = sqlOperator.LastError().text().toLatin1().data();
        std::cout << "Open datatabase error(user_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    if (cmd)
    {
        delete cmd;
        cmd = NULL;
    }
    */

    clock_t t5 = clock();
    //qDebug() << "DBTime" << t5-t1;
}
