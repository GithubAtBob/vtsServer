
#include "StdAfx.h"
#include "DBSectorHandler.h"

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


DBSectorHandler::DBSectorHandler(void)
{
}


DBSectorHandler::~DBSectorHandler(void)
{
}

void DBSectorHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (Type)
    {
    case DBSectorHandlerType::Add:
        Addhandle(s, sqlOperator);
        break;
    case DBSectorHandlerType::Update:
        Updatehandle(s, sqlOperator);
        break;
    case DBSectorHandlerType::Remove:
        Removehandle(s, sqlOperator);
        break;
    }
}

void DBSectorHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("sector_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("lat",Lat);
    l_data.insert("lon",Lon);
    l_data.insert("radius",Radius);
    l_data.insert("beginangle",BeginAngle);
    l_data.insert("endangle",EndAngle);
    l_data.insert("linestyle",LineStyle);
    l_data.insert("fullstyle",FullStyle);
    l_data.insert("linewidth",LineWidth);
    QByteArray mesID;
    QDataStream outID(&mesID,QIODevice::WriteOnly);
    outID.setVersion(QDataStream::Qt_5_2);
    outID << WaringID;
    l_data.insert("waringID",QVariant(mesID));
    l_data.insert("waringtype",WaringType);
    l_data.insert("drawman",DrawMan);
    l_data.insert("isshare",IsShare);
    l_data.insert("linecolor",LineColor);
    l_data.insert("fullcolor",FullColor);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "add false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(sector_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBSectorHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("sector_table");
    QMap<QString, QVariant> l_data;
    //l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("lat",Lat);
    l_data.insert("lon",Lon);
    l_data.insert("radius",Radius);
    l_data.insert("beginangle",BeginAngle);
    l_data.insert("endangle",EndAngle);
    l_data.insert("linestyle",LineStyle);
    l_data.insert("fullstyle",FullStyle);
    l_data.insert("linewidth",LineWidth);
    QByteArray mesID;
    QDataStream outID(&mesID,QIODevice::WriteOnly);
    outID.setVersion(QDataStream::Qt_5_2);
    outID << WaringID;
    l_data.insert("waringID",QVariant(mesID));
    l_data.insert("waringtype",WaringType);
    l_data.insert("drawman",DrawMan);
    //l_data.insert("isshare",IsShare);
    l_data.insert("linecolor",LineColor);
    l_data.insert("fullcolor",FullColor);

    WaringInfo l_info = Info.Get(0);
    if (Info.size() > 0)
    {
        l_data.insert("enter_time",l_info.enter_time());
        l_data.insert("enter_speed",l_info.enter_speed());
        l_data.insert("enter_acceleration",l_info.enter_acceleration());
        l_data.insert("leave_time",l_info.leave_time());
        l_data.insert("leave_speed",l_info.leave_speed());
        l_data.insert("leave_acceleration",l_info.leave_acceleration());
        l_data.insert("inside_time",l_info.inside_time());
        l_data.insert("inside_speed",l_info.inside_speed());
        l_data.insert("inside_acceleration",l_info.inside_acceleration());
        l_data.insert("outside_time",l_info.outside_time());
        l_data.insert("outside_speed",l_info.outside_speed());
        l_data.insert("outside_acceleration",l_info.outside_acceleration());
        l_data.insert("app_time",l_info.app_time());
        l_data.insert("high_duration",l_info.high_duration());
        l_data.insert("high_speed",l_info.high_speed());
        l_data.insert("low_duration",l_info.low_duration());
        l_data.insert("low_speed",l_info.low_speed());
        l_data.insert("pro_duration",l_info.pro_duration());
        l_data.insert("pro_lat",l_info.pro_lat());
        l_data.insert("pro_lon",l_info.pro_lon());
        l_data.insert("add_max",l_info.add_max());
        l_data.insert("add_min",l_info.add_min());
        l_data.insert("add_duration",l_info.add_duration());
        l_data.insert("col_cpa",l_info.col_cpa());
        l_data.insert("col_tcpa",l_info.col_tcpa());
        l_data.insert("col_dcpa",l_info.col_dcpa());
        l_data.insert("col_dist",l_info.col_dist());
        l_data.insert("con_time",l_info.con_time());
        l_data.insert("con_total",l_info.con_total());
        l_data.insert("gro_depth",l_info.gro_depth());
        l_data.insert("gro_time",l_info.gro_time());
        l_data.insert("cou_change",l_info.cou_change());
        l_data.insert("cou_time",l_info.cou_time());
        l_data.insert("fog_begin_time",l_info.fog_begin_time());
        l_data.insert("fog_end_time",l_info.fog_end_time());
        l_data.insert("fog_time",l_info.fog_time());
        QByteArray anc;
        QDataStream outanc(&anc,QIODevice::WriteOnly);
        outanc.setVersion(QDataStream::Qt_5_2);
        auto l_anc = l_info.anc_type();
        outanc << l_anc;
        l_data.insert("anc_type",QVariant(anc));
        QByteArray l_fogMMSI;
        QDataStream outfog(&l_fogMMSI,QIODevice::WriteOnly);
        outfog.setVersion(QDataStream::Qt_5_2);
        auto l_fog = l_info.fog_mmsi();
        outfog << l_fog;
        l_data.insert("fog_mmsi",QVariant(l_fogMMSI));
    }
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));

//     l_pSqlUpdateCmd->SetData("lon",10);          ///更新具体某项
    //     l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));
    Result = "OK";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(sector_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBSectorHandler::Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
    l_pSqlRemoveCmd->SetTableName("sector_table");

    l_pSqlRemoveCmd->SetFilter(QString("ID = '%1'").arg(ID));

    Result = "Remove false";
    if (!sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
    {
		std::cout << "Open datatabase error(sector_table Remove):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    if (l_pSqlRemoveCmd)
    {
        delete l_pSqlRemoveCmd;
        l_pSqlRemoveCmd = NULL;
    }
}
// 
// void DBSectorHandler::Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
// {
//     hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
//     l_pSqlSelectCmd->SetTableName("sector_table");
// 
//     //l_pSqlSelectCmd->SetFilter(QString("drawman = '%1' or isshare = '1'").arg(DrawMan));
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
//     Respon.clear_sectors();
//     for (int i = 0; i < l_pSqlRecord->count(); i++)
//     {
//         QSqlRecord l_record = l_pSqlRecord->at(i);
//         SectorRequest* l_requst = Respon.add_sectors();
//         std::string l_ID = l_record.value("ID").toString().toStdString();
//         std::string l_name = l_record.value("name").toString().toStdString();
//         double l_lat = l_record.value("lat").toDouble();
//         double l_lon = l_record.value("lon").toDouble();
//         double l_radius = l_record.value("radius").toDouble();
//         double l_beginangle = l_record.value("beginangle").toDouble();
//         double l_endangle = l_record.value("endangle").toDouble();
//         int l_linestyle = l_record.value("linestyle").toInt();
//         int l_fullstyle = l_record.value("fullstyle").toInt();
//         int l_linewidth = l_record.value("linewidth").toInt();
//         QByteArray l_waringID = l_record.value("waringID").toByteArray();
//         std::string l_waringtype = l_record.value("waringtype").toString().toStdString();
//         std::string l_drawman = l_record.value("drawman").toString().toStdString();
//         bool l_isshare = l_record.value("isshare").toBool();
//         std::string l_linecolor = l_record.value("linecolor").toString().toStdString();
//         std::string l_fullcolor = l_record.value("fullcolor").toString().toStdString();
//         int enter_time = l_record.value("enter_time").toInt();
//         double enter_speed = l_record.value("enter_speed").toDouble();
//         double enter_acceleration = l_record.value("enter_acceleration").toDouble();
//         int leave_time = l_record.value("leave_time").toInt();
//         double leave_speed = l_record.value("leave_speed").toDouble();
//         double leave_acceleration = l_record.value("leave_acceleration").toDouble();
//         int inside_time = l_record.value("inside_time").toInt();
//         double inside_speed = l_record.value("inside_speed").toDouble();
//         double inside_acceleration = l_record.value("inside_acceleration").toDouble();
//         int outside_time = l_record.value("outside_time").toInt();
//         double outside_speed = l_record.value("outside_speed").toDouble();
//         double outside_acceleration = l_record.value("outside_acceleration").toDouble();
//         int high_duration = l_record.value("high_duration").toInt();
//         double high_speed = l_record.value("high_speed").toDouble();
//         int low_duration = l_record.value("low_duration").toInt();
//         double low_speed = l_record.value("low_speed").toDouble();
//         int pro_duration = l_record.value("pro_duration").toInt();
//         double pro_lat = l_record.value("pro_lat").toDouble();
//         double pro_lon = l_record.value("pro_lon").toDouble();
//         double add_max = l_record.value("add_max").toDouble();
//         double add_min = l_record.value("add_min").toDouble();
//         double add_duration = l_record.value("add_duration").toDouble();
//         double col_cpa = l_record.value("col_cpa").toDouble();
//         double col_tcpa = l_record.value("col_tcpa").toDouble();
//         double col_dcpa = l_record.value("col_dcpa").toDouble();
//         double col_dist = l_record.value("col_dist").toDouble();
//         int con_time = l_record.value("con_time").toInt();
//         int con_total = l_record.value("con_total").toInt();
//         double gro_depth = l_record.value("gro_depth").toDouble();
//         int gro_time = l_record.value("gro_time").toInt();
//         QByteArray l_anc_type = l_record.value("anc_type").toByteArray();
//         int app_time = l_record.value("app_time").toInt();
//         double cou_change = l_record.value("cou_change").toDouble();
//         int cou_time = l_record.value("cou_time").toInt();
//         time_t fog_begin_time = l_record.value("fog_begin_time").toInt();
//         time_t fog_end_time = l_record.value("fog_end_time").toInt();
//         int fog_time = l_record.value("fog_time").toInt();
//         QByteArray fog_mmsi = l_record.value("fog_mmsi").toByteArray();
//         l_requst->set_type(Type);
//         l_requst->set_id(l_ID);
//         l_requst->set_name(l_name);
//         l_requst->set_lat(l_lat);
//         l_requst->set_lon(l_lon);
//         l_requst->set_radius(l_radius);
//         l_requst->set_beginangle(l_beginangle);
//         l_requst->set_endangle(l_endangle);
//         l_requst->set_linestyle(l_linestyle);
//         l_requst->set_fullstyle(l_fullstyle);
//         l_requst->set_linewidth(l_linewidth);
//         google::protobuf::RepeatedPtrField<google::protobuf::string> l_proID;
//         QDataStream inID(&l_waringID,QIODevice::ReadOnly);
//         inID.setVersion(QDataStream::Qt_5_2);
//         inID >> l_proID;
//         for (int i = 0; i < l_proID.size(); i++)
//         {
//             l_requst->add_waringid(l_proID.Get(i));
//         }
//         l_requst->set_waringtype(l_waringtype);
//         l_requst->set_drawman(l_drawman);
//         l_requst->set_isshare(l_isshare);
//         l_requst->set_linecolor(l_linecolor);
//         l_requst->set_fullcolor(l_fullcolor);
//         WaringInfo* l_Info = l_requst->add_info();
//         l_Info->set_enter_time(enter_time);
//         l_Info->set_enter_speed(enter_speed);
//         l_Info->set_enter_acceleration(enter_acceleration);
//         l_Info->set_leave_time(leave_time);
//         l_Info->set_leave_speed(leave_speed);
//         l_Info->set_leave_acceleration(leave_acceleration);
//         l_Info->set_inside_time(inside_time);
//         l_Info->set_inside_speed(inside_speed);
//         l_Info->set_inside_acceleration(inside_acceleration);
//         l_Info->set_outside_time(outside_time);
//         l_Info->set_outside_speed(outside_speed);
//         l_Info->set_outside_acceleration(outside_acceleration);
//         l_Info->set_high_duration(high_duration);
//         l_Info->set_high_speed(high_speed);
//         l_Info->set_low_duration(low_duration);
//         l_Info->set_low_speed(low_speed);
//         l_Info->set_pro_duration(pro_duration);
//         l_Info->set_pro_lat(pro_lat);
//         l_Info->set_pro_lon(pro_lon);
//         l_Info->set_add_max(add_max);
//         l_Info->set_add_min(add_min);
//         l_Info->set_add_duration(add_duration);
//         l_Info->set_col_cpa(col_cpa);
//         l_Info->set_col_tcpa(col_tcpa);
//         l_Info->set_col_dcpa(col_dcpa);
//         l_Info->set_con_time(con_time);
//         l_Info->set_con_total(con_total);
//         l_Info->set_gro_depth(gro_depth);
//         l_Info->set_gro_time(gro_time);
//         l_Info->set_app_time(app_time);
//         l_Info->set_cou_change(cou_change);
//         l_Info->set_cou_time(cou_time);
//         l_Info->set_fog_begin_time(fog_begin_time);
//         l_Info->set_fog_end_time(fog_end_time);
//         l_Info->set_fog_time(fog_time);
//         google::protobuf::RepeatedPtrField<std::string> l_Anc;
//         QDataStream inAnc(&l_anc_type,QIODevice::ReadOnly);
//         inAnc.setVersion(QDataStream::Qt_5_2);
//         inAnc >> l_Anc;
//         for (int i = 0; i < l_Anc.size(); i++)
//         {
//             l_Info->add_anc_type(l_Anc.Get(i));
//         }
//         google::protobuf::RepeatedPtrField<std::string> l_fog;
//         QDataStream inFog(&fog_mmsi,QIODevice::ReadOnly);
//         inFog.setVersion(QDataStream::Qt_5_2);
//         inFog >> l_fog;
//         for (int i = 0; i < l_fog.size(); i++)
//         {
//             l_Info->add_fog_mmsi(l_fog.Get(i));
//         }
//     }
//     if (l_pSqlSelectCmd)
//     {
//         delete l_pSqlSelectCmd;
//         l_pSqlSelectCmd = NULL;
//     }
// }
