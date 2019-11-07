
#include "StdAfx.h"
#include "DBHabitChartHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"

DBHabitChartHandler::DBHabitChartHandler(void)
{
}


DBHabitChartHandler::~DBHabitChartHandler(void)
{
}

void DBHabitChartHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (m_ChartCard.type())
    {
    case CardMesType::CMTSend:
        Savehandle(s, sqlOperator);
        break;
    case CardMesType::CMTRead:
        Readhandle(s, sqlOperator);
        break;
    }
}

void DBHabitChartHandler::Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("chart_card_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(m_ChartCard.userid().c_str()));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(chart_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    QMap<QString, QVariant> l_data;
    l_data.insert("userid",m_ChartCard.userid().c_str());
    l_data.insert("color",m_ChartCard.color());
    l_data.insert("areastyle",m_ChartCard.areastyle());
    l_data.insert("pointstyle",m_ChartCard.pointstyle());
    l_data.insert("shallow",m_ChartCard.shallow());
    l_data.insert("safety",m_ChartCard.safety());
    l_data.insert("depth",m_ChartCard.depth());
    l_data.insert("safetydepth",m_ChartCard.safetydepth());
    l_data.insert("choicetype",m_ChartCard.choicetype());
    //l_data.insert("customdata",m_ChartCard.customdata().c_str());
    l_data.insert("safeset",m_ChartCard.safeset());
    l_data.insert("isFourshades",m_ChartCard.isfourshades());
    l_data.insert("isUseSCAMIN",m_ChartCard.isusescamin());
    l_data.insert("isMquality",m_ChartCard.ismquality());
    l_data.insert("isLocalLanguage",m_ChartCard.islocallanguage());
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    auto l_customdata = m_ChartCard.customdata();
    out << l_customdata;
    l_data.insert("customdata",QVariant(mes));
    if (l_pSqlRecord->size() == 0)
    {
        hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
        l_pSqlInsertCmd->SetTableName("chart_card_table");
        l_pSqlInsertCmd->SetData(l_data);
        if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
        {
            std::cout << "Open datatabase error(chart_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
        l_pSqlUpdateCmd->SetTableName("chart_card_table");
        l_pSqlUpdateCmd->SetData(l_data);
        l_pSqlUpdateCmd->SetFilter(QString("userid = '%1'").arg(m_ChartCard.userid().c_str()));
        if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
        {
            std::cout << "Open datatabase error(chart_card_table save):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBHabitChartHandler::Readhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("chart_card_table");
    l_pSqlSelectCmd->SetFilter(QString("userid = '%1'").arg(m_ChartCard.userid().c_str()));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(chart_card_table Read):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
        m_ChartCard.set_type(CardMesType::CMTNone);
        return ;
    }
    else
    {
        QSqlRecord l_record = l_pSqlRecord->at(0);
        m_ChartCard.set_color(l_record.value("color").toInt());
        m_ChartCard.set_areastyle(l_record.value("areastyle").toInt());
        m_ChartCard.set_pointstyle(l_record.value("pointstyle").toInt());
        m_ChartCard.set_shallow(l_record.value("shallow").toDouble());
        m_ChartCard.set_safety(l_record.value("safety").toDouble());
        m_ChartCard.set_depth(l_record.value("depth").toDouble());
        m_ChartCard.set_safetydepth(l_record.value("safetydepth").toDouble());
        m_ChartCard.set_choicetype(l_record.value("choicetype").toInt());
        //l_data.insert("customdata",m_ChartCard.customdata().c_str());
        m_ChartCard.set_safeset(l_record.value("safeset").toDouble());
        m_ChartCard.set_isfourshades(l_record.value("isFourshades").toBool());
        m_ChartCard.set_isusescamin(l_record.value("isUseSCAMIN").toBool());
        m_ChartCard.set_ismquality(l_record.value("isMquality").toBool());
        m_ChartCard.set_islocallanguage(l_record.value("isLocalLanguage").toBool());
        QByteArray l_customdata = l_record.value("customdata").toByteArray();
        google::protobuf::RepeatedField <google::protobuf::int32> l_Custom;
        QDataStream in(&l_customdata,QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_2);
        in >> l_Custom;
        for (int i = 0; i < l_Custom.size(); i++)
        {
            m_ChartCard.add_customdata(l_Custom.Get(i));
        }
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}
