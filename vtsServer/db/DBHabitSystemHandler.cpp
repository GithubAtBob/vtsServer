
#include "StdAfx.h"
#include "DBHabitSystemHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"

DBHabitSystemHandler::DBHabitSystemHandler(void)
{
}


DBHabitSystemHandler::~DBHabitSystemHandler(void)
{
}

void DBHabitSystemHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (m_SystemCard.type())
    {
    case CardMesType::CMTSend:
        Savehandle(s, sqlOperator);
        break;
    case CardMesType::CMTRead:
        Readhandle(s, sqlOperator);
        break;
    }
}

void DBHabitSystemHandler::Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("system_card_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(m_SystemCard.userid().c_str()));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(system_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    QMap<QString, QVariant> l_data;
    l_data.insert("userid",m_SystemCard.userid().c_str());
    l_data.insert("isGrid",m_SystemCard.isgrid());
    l_data.insert("isFlower",m_SystemCard.isflower());
    l_data.insert("isDimensional",m_SystemCard.isdimensional());
    l_data.insert("isHOG",m_SystemCard.ishog());
    l_data.insert("isTurnRate",m_SystemCard.isturnrate());
    l_data.insert("radiotype",m_SystemCard.radiotype());
    l_data.insert("voyage",m_SystemCard.voyage());
    l_data.insert("time",m_SystemCard.time());
    l_data.insert("latlon",m_SystemCard.latlon());
    l_data.insert("speed",m_SystemCard.speed());
    l_data.insert("dist",m_SystemCard.dist());
    l_data.insert("depth",m_SystemCard.depth());
    google::protobuf::RepeatedPtrField<std::string> l_displayset = m_SystemCard.displayset();
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << l_displayset;
    l_data.insert("displayset",QVariant(mes));
    if (l_pSqlRecord->size() == 0)
    {
        hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
        l_pSqlInsertCmd->SetTableName("System_card_table");
        l_pSqlInsertCmd->SetData(l_data);
        if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
        {
            std::cout << "Open datatabase error(system_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
        l_pSqlUpdateCmd->SetTableName("system_card_table");
        l_pSqlUpdateCmd->SetData(l_data);
        l_pSqlUpdateCmd->SetFilter(QString("userid = '%1'").arg(m_SystemCard.userid().c_str()));
        if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
        {
            std::cout << "Open datatabase error(system_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBHabitSystemHandler::Readhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("system_card_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(m_SystemCard.userid().c_str()));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(system_card_table Read):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
        m_SystemCard.set_type(CardMesType::CMTNone);
        return ;
    }
    else
    {
        QSqlRecord l_record = l_pSqlRecord->at(0);
        m_SystemCard.set_isgrid(l_record.value("isGrid").toBool());
        m_SystemCard.set_isflower(l_record.value("isFlower").toBool());
        m_SystemCard.set_isdimensional(l_record.value("isDimensional").toBool());
        m_SystemCard.set_ishog(l_record.value("isHOG").toBool());
        m_SystemCard.set_isturnrate(l_record.value("isTurnRate").toBool());
        m_SystemCard.set_radiotype(l_record.value("radiotype").toInt());
        m_SystemCard.set_voyage(l_record.value("voyage").toDouble());
        m_SystemCard.set_time(l_record.value("time").toDouble());
        m_SystemCard.set_latlon(l_record.value("latlon").toInt());
        m_SystemCard.set_speed(l_record.value("speed").toInt());
        m_SystemCard.set_dist(l_record.value("dist").toInt());
        m_SystemCard.set_depth(l_record.value("depth").toInt());
        QByteArray l_DisPlay = l_record.value("displayset").toByteArray();
        google::protobuf::RepeatedPtrField<std::string> l_displayset;
        QDataStream inID(&l_DisPlay,QIODevice::ReadOnly);
        inID.setVersion(QDataStream::Qt_5_2);
        inID >> l_displayset;
        for (int i = 0; i < l_displayset.size(); i++)
        {
            m_SystemCard.add_displayset(l_displayset.Get(i));
        }
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}
