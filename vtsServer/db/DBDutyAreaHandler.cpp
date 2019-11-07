
#include "StdAfx.h"
#include "DBDutyAreaHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"


DBDutyAreaHandler::DBDutyAreaHandler(void)
{
}


DBDutyAreaHandler::~DBDutyAreaHandler(void)
{
}

void DBDutyAreaHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (Type)
    {
    case DBDutyAreaHandlerType::Add:
        Addhandle(s, sqlOperator);
        break;
    case DBDutyAreaHandlerType::Update:
        Updatehandle(s, sqlOperator);
        break;
    case DBDutyAreaHandlerType::Remove:
        Removehandle(s, sqlOperator);
        break;
    }
}

void DBDutyAreaHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("dutyarea_table");
    QMap<QString, QVariant> l_data;
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << Point;
    l_data.insert("point",QVariant(mes));
    l_data.insert("ID",ID);
    l_data.insert("name",Name);
    //l_data.insert("point",Point);
    l_data.insert("linestyle",LineStyle);
    l_data.insert("fullstyle",FullStyle);
    l_data.insert("linewidth",LineWidth);
    l_data.insert("dutyman",DutyMan);
    l_data.insert("drawman",DrawMan);
    l_data.insert("isshare",IsShare);
    l_data.insert("linecolor",LineColor);
    l_data.insert("fullcolor",FullColor);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "add false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(dutyarea_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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
}

void DBDutyAreaHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("dutyarea_table");
    QMap<QString, QVariant> l_data;
    //l_data.insert("ID",ID);
    l_data.insert("name",Name);
    QByteArray mes;
    QDataStream out(&mes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << Point;
    l_data.insert("point",QVariant(mes));
    //l_data.insert("point",Point);
    l_data.insert("linestyle",LineStyle);
    l_data.insert("fullstyle",FullStyle);
    l_data.insert("linewidth",LineWidth);
    l_data.insert("dutyman",DutyMan);
    l_data.insert("drawman",DrawMan);
//    l_data.insert("isshare",IsShare);
    l_data.insert("linecolor",LineColor);
    l_data.insert("fullcolor",FullColor);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));

    Result = "Update false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(dutyarea_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }
}

void DBDutyAreaHandler::Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
    l_pSqlRemoveCmd->SetTableName("dutyarea_table");

    l_pSqlRemoveCmd->SetFilter(QString("ID = '%1'").arg(ID));

    Result = "Remove false";
    if (!sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
    {
		std::cout << "Open datatabase error(dutyarea_table Remove):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    std::cout << Result.toStdString();
    if (l_pSqlRemoveCmd)
    {
        delete l_pSqlRemoveCmd;
        l_pSqlRemoveCmd = NULL;
    }
}

// void DBDutyAreaHandler::Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
// {
//     hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
//     l_pSqlSelectCmd->SetTableName("dutyarea_table");
// 
//     //l_pSqlSelectCmd->SetFilter(QString("drawman = '%1' or isshare = '1'").arg(Name));
//     if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
//     {
//         std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
//         if (l_pSqlSelectCmd)
//         {
//             delete l_pSqlSelectCmd;
//             l_pSqlSelectCmd = NULL;
//         }
//         return;
//     }
//     Respon.set_type(Type); 
//     QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
//     Respon.clear_dutyareas();
//     for (int i = 0; i < l_pSqlRecord->count(); i++)
//     {
//         QSqlRecord l_record = l_pSqlRecord->at(i);
//         DutyAreaRequest* l_requst = Respon.add_dutyareas();
//         std::string l_ID = l_record.value("ID").toString().toStdString();
//         std::string l_name = l_record.value("name").toString().toStdString();
//         QByteArray l_points = l_record.value("point").toByteArray();
//         int l_linestyle = l_record.value("linestyle").toInt();
//         int l_fullstyle = l_record.value("fullstyle").toInt();
//         int l_linewidth = l_record.value("linewidth").toInt();
//         std::string l_dutyman = l_record.value("dutyman").toString().toStdString();
//         std::string l_drawman = l_record.value("drawman").toString().toStdString();
//         bool l_isshare = l_record.value("isshare").toBool();
//         std::string l_linecolor = l_record.value("linecolor").toString().toStdString();
//         std::string l_fullcolor = l_record.value("fullcolor").toString().toStdString();
//         l_requst->set_type(Type);
//         l_requst->set_id(l_ID);
//         l_requst->set_name(l_name);
//         google::protobuf::RepeatedPtrField<PointMes> l_Point;
//         QDataStream in(&l_points,QIODevice::ReadOnly);
//         in.setVersion(QDataStream::Qt_5_2);
//         in >> l_Point;
//         for (int i = 0; i < l_Point.size(); i++)
//         {
//             PointMes* l_mes = l_requst->add_point();
//             l_mes->set_lat(l_Point.Get(i).lat());
//             l_mes->set_lon(l_Point.Get(i).lon());
//         }
//         l_requst->set_linestyle(l_linestyle);
//         l_requst->set_fullstyle(l_fullstyle);
//         l_requst->set_linewidth(l_linewidth);
//         l_requst->set_dutyman(l_dutyman);
//         l_requst->set_drawman(l_drawman);
//         l_requst->set_isshare(l_isshare);
//         l_requst->set_linecolor(l_linecolor);
//         l_requst->set_fullcolor(l_fullcolor);
//     }
//     if (l_pSqlSelectCmd)
//     {
//         delete l_pSqlSelectCmd;
//         l_pSqlSelectCmd = NULL;
//     }
// }
