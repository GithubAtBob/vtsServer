
#include "StdAfx.h"
#include "DBAlgorOwnShipHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"
#include "Managers/hgTargetManager.h"

DBAlgorOwnShipHandler::DBAlgorOwnShipHandler(void)
{
}


DBAlgorOwnShipHandler::~DBAlgorOwnShipHandler(void)
{
}

void DBAlgorOwnShipHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("ownshiplist_table");
    QMap<QString, QVariant> l_data;
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << m_List;
    l_data.insert("ownlist",QVariant(mes));
    l_data.insert("time",hgTargetManager::GetWarnTime());
    l_pSqlInsertCmd->SetData(l_data);
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(ownshiplist_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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