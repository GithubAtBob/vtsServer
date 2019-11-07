
#include "StdAfx.h"
#include "DBHabitDangerHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"

DBHabitDangerHandler::DBHabitDangerHandler(void)
{
}


DBHabitDangerHandler::~DBHabitDangerHandler(void)
{
}

void DBHabitDangerHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (m_DangerCard.type())
    {
    case CardMesType::CMTSend:
        Savehandle(s, sqlOperator);
        break;
    case CardMesType::CMTRead:
        Readhandle(s, sqlOperator);
        break;
    }
}

void DBHabitDangerHandler::Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("danger_target_card_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(m_DangerCard.userid().c_str()));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(danger_target_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    QMap<QString, QVariant> l_data;
    l_data.insert("userid",m_DangerCard.userid().c_str());
    l_data.insert("target",m_DangerCard.target());
    l_data.insert("dist",m_DangerCard.dist());
    l_data.insert("MaxCPA",m_DangerCard.maxcpa());
    l_data.insert("MaxTCPA",m_DangerCard.maxtcpa().c_str());
    l_data.insert("radiotype",m_DangerCard.radiotype());
    l_data.insert("MinSpeed",m_DangerCard.minspeed());
    l_data.insert("pre_time",m_DangerCard.pre_time());
    l_data.insert("pre_starTime",m_DangerCard.pre_startime());
    l_data.insert("pre_endTime",m_DangerCard.pre_endtime());
    l_data.insert("pre_check",m_DangerCard.pre_check());
    if (l_pSqlRecord->size() == 0)
    {
        hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
        l_pSqlInsertCmd->SetTableName("danger_target_card_table");
        l_pSqlInsertCmd->SetData(l_data);
        if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
        {
            std::cout << "Open datatabase error(danger_target_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
        l_pSqlUpdateCmd->SetTableName("danger_target_card_table");
        l_pSqlUpdateCmd->SetData(l_data);
        l_pSqlUpdateCmd->SetFilter(QString("userid = '%1'").arg(m_DangerCard.userid().c_str()));
        if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
        {
            std::cout << "Open datatabase error(danger_target_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBHabitDangerHandler::Readhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("danger_target_card_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(m_DangerCard.userid().c_str()));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(danger_target_card_table Read):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
        m_DangerCard.set_target(l_record.value("target").toInt());
        m_DangerCard.set_dist(l_record.value("dist").toDouble());
        m_DangerCard.set_maxcpa(l_record.value("MaxCPA").toDouble());
        m_DangerCard.set_maxtcpa(l_record.value("MaxTCPA").toString().toStdString());
        m_DangerCard.set_radiotype(l_record.value("radiotype").toInt());
        m_DangerCard.set_minspeed(l_record.value("MinSpeed").toDouble());
        m_DangerCard.set_pre_time(l_record.value("pre_time").toInt());
        m_DangerCard.set_pre_startime(l_record.value("pre_starTime").toUInt());
        m_DangerCard.set_pre_endtime(l_record.value("pre_endTime").toUInt());
        m_DangerCard.set_pre_check((PreRadioType)l_record.value("pre_check").toInt());
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}
