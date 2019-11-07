
#include "StdAfx.h"
#include "DBHabitTarSetHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"

DBHabitTarSetHandler::DBHabitTarSetHandler(void)
{
}


DBHabitTarSetHandler::~DBHabitTarSetHandler(void)
{
}

void DBHabitTarSetHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (m_TargetInfoCard.type())
    {
    case CardMesType::CMTSend:
        Savehandle(s, sqlOperator);
        break;
    case CardMesType::CMTRead:
        Readhandle(s, sqlOperator);
        break;
    }
}

void DBHabitTarSetHandler::Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("habit_target_set_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(m_TargetInfoCard.userid().c_str()));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(habit_target_set_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    QMap<QString, QVariant> l_data;
    l_data.insert("userid",m_TargetInfoCard.userid().c_str());
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    auto l_TarData = m_TargetInfoCard.tardata();
    out << l_TarData;
    l_data.insert("tardata",QVariant(mes));
    l_data.insert("showHistor",m_TargetInfoCard.showhistor());
    l_data.insert("trackgap",m_TargetInfoCard.trackgap());
    l_data.insert("trackgappoint",m_TargetInfoCard.trackgappoint());
    l_data.insert("trackspeed",m_TargetInfoCard.trackspeed());
    l_data.insert("showship",m_TargetInfoCard.showship());
    l_data.insert("showLigature",m_TargetInfoCard.showligature());
    l_data.insert("count_time",m_TargetInfoCard.count_time());
    l_data.insert("pointcount",m_TargetInfoCard.pointcount());
    if (l_pSqlRecord->size() == 0)
    {
        hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
        l_pSqlInsertCmd->SetTableName("habit_target_set_table");
        l_pSqlInsertCmd->SetData(l_data);
        if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
        {
            std::cout << "Open datatabase error(habit_target_set_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
        l_pSqlUpdateCmd->SetTableName("habit_target_set_table");
        l_pSqlUpdateCmd->SetData(l_data);
        l_pSqlUpdateCmd->SetFilter(QString("userid = '%1'").arg(m_TargetInfoCard.userid().c_str()));
        if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
        {
            std::cout << "Open datatabase error(habit_target_set_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBHabitTarSetHandler::Readhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("habit_target_set_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(m_TargetInfoCard.userid().c_str()));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(habit_target_set_table Read):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
        QByteArray l_tardata = l_record.value("tardata").toByteArray();
        google::protobuf::RepeatedPtrField <TargetInfoData> l_Tar;
        QDataStream in(&l_tardata,QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_2);
        in >> l_Tar;
        for (int i = 0; i < l_Tar.size(); i++)
        {
            TargetInfoData l_TarInfoData = l_Tar.Get(i);
            auto l_Mdata = m_TargetInfoCard.add_tardata();
            l_Mdata->set_index(l_TarInfoData.index());
            l_Mdata->set_checked(l_TarInfoData.checked());
        }
        m_TargetInfoCard.set_showhistor(l_record.value("showHistor").toBool());
        m_TargetInfoCard.set_trackgap(l_record.value("trackgap").toInt());
        m_TargetInfoCard.set_trackgappoint(l_record.value("trackgappoint").toDouble());
        m_TargetInfoCard.set_trackspeed(l_record.value("trackspeed").toDouble());
        m_TargetInfoCard.set_showship(l_record.value("showship").toBool());
        m_TargetInfoCard.set_showligature(l_record.value("showLigature").toBool());
        m_TargetInfoCard.set_count_time(l_record.value("count_time").toBool());
        m_TargetInfoCard.set_pointcount(l_record.value("pointcount").toInt());
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}
