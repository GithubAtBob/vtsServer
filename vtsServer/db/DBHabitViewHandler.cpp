
#include "StdAfx.h"
#include "DBHabitViewHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"

DBHabitViewHandler::DBHabitViewHandler(void)
{
}


DBHabitViewHandler::~DBHabitViewHandler(void)
{
}

void DBHabitViewHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (Type)
    {
    case CardMesType::CMTSend:
        Savehandle(s, sqlOperator);
        break;
    case CardMesType::CMTRead:
        Readhandle(s, sqlOperator);
        break;
    }
}

void DBHabitViewHandler::Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("view_card_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(UserID));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(view_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    QMap<QString, QVariant> l_data;
    l_data.insert("userid",UserID);
    l_data.insert("lat",Lat);
    l_data.insert("lon",Lon);
    l_data.insert("vrange",Range);
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << Quick;
    l_data.insert("quickdata",QVariant(mes));
    if (l_pSqlRecord->size() == 0)
    {
        hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
        l_pSqlInsertCmd->SetTableName("view_card_table");
        l_pSqlInsertCmd->SetData(l_data);
        if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
        {
            std::cout << "Open datatabase error(view_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
            if (l_pSqlInsertCmd)
            {
                delete l_pSqlInsertCmd;
                l_pSqlInsertCmd = NULL;
            }
            return;
        }
    }
    else
    {
        hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
        l_pSqlUpdateCmd->SetTableName("view_card_table");
        l_pSqlUpdateCmd->SetData(l_data);
        l_pSqlUpdateCmd->SetFilter(QString("userid = '%1'").arg(UserID));
        if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
        {
            std::cout << "Open datatabase error(view_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
            if (l_pSqlUpdateCmd)
            {
                delete l_pSqlUpdateCmd;
                l_pSqlUpdateCmd = NULL;
            }
            return;
        }
    }
    //////////////////
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void DBHabitViewHandler::Readhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("view_card_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(UserID));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(view_card_table Read):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (l_pSqlRecord->size() == 0)
    {
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return ;
    }
    else
    {
        QSqlRecord l_record = l_pSqlRecord->at(0);
        Lat = l_record.value("lat").toDouble();
        Lon = l_record.value("lon").toDouble();
        Range = l_record.value("vrange").toInt();
        QByteArray l_quickdata = l_record.value("quickdata").toByteArray();
        QDataStream in(&l_quickdata,QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_2);
        in >> Quick;//l_QuickData;
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}
