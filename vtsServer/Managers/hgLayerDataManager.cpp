#include "StdAfx.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"

#include "Managers/hgConfigManager.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlInsertCmd.h"
#include "OverLoad.h"
#include "message/PointMes.pb.h"
#include "message/channel.pb.h"
#include "hgutils/NavUtil.h"

#include "LayerData/hgUserLayWarning.h"


const char* hgWaringTypeGuid[] = 
{
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{F6942406-A72C-4FC7-9716-8569BB65BBED}"),//0
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{441FD237-BA9F-434E-89AF-096B90F7DD11}"),//1
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{88BFF8AF-5584-4468-8DAA-DFF017989846}"),//2
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{77571618-9F6D-4B9D-BCA8-A9B036381D2A}"),//3
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{D21BDC6B-06F2-4F15-97A6-0AAAD921F733}"),//4
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{1121800C-D7DC-417D-BB7C-E538D9CDE8F3}"),//5
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{52E756A9-59A1-473F-BD5B-3DE395C76138}"),//6
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{385E5F05-5196-45C1-9FAB-3E0D308B26E3}"),//7
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{89D1A229-E3B7-475E-BBCA-2E1E3012CA55}"),//8
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{B91DB7D6-D57C-43C5-A84B-07FA9405B6C3}"),//9
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{DCA0A575-067E-4ACA-8F0B-8B6A2E12617B}"),//10
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{B8826C19-0FD7-4930-AB4E-B45A66638CE2}"),//11
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{7059F7FD-8338-4A4F-AEDB-0BD8CC9F0B6B}"),//12
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{882F1339-F482-4E84-A165-3A4BA05B78C6}"),//13
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{93126741-BB98-4B44-83EC-D432B78E154A}"),//14
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{75FD3A0E-7EA3-443F-96B1-B8B4C3009CB3}"),//15
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{C9122543-06B8-467E-ACC9-EBE72A5778ED}"),//16
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{72479640-7602-45C2-9D17-1D8A4DB193FB}"),//17
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{A49599DB-6AEA-4536-BB73-24F5082FBCB4}"),//18
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{BB9275D9-9FE7-4B16-AC16-19001C9B7B34}"),//19
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{BC293AD8-70A4-4972-883F-E7C8CAAEEA79}"),//20
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{88FCBCE7-DDF2-4E58-A40B-94C0AFD1384D}"),//21
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{AAB4D96C-B16F-44DF-90E4-4D7EC540E725}"),//22
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{5DD9E1C6-0F95-419B-9528-42197A0C21C1}"),//23
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{367F84DF-811E-4AD7-B18E-B2DB7D8CB721}"),//24
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{AEB16960-71C5-45B5-B2E8-150059B06FDC}"),//25
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{22A1894C-7641-4446-A06F-203916A53D3D}"),//26
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{A2D4E789-8955-4848-A4E0-94BD9FD50DA3}"),//27
    QT_TRANSLATE_NOOP("hgWaringTypeGuid", "{329C3CB7-AF1D-47CE-8F61-2AE9D830135D}"),//28
};
extern const char* hgAnchorageTypeGuid[];
extern const char* hgAnchorageTypeName[];

hgLayerDataManager::hgLayerDataManager(void)
{
}


hgLayerDataManager::~hgLayerDataManager(void)
{
}

void hgLayerDataManager::ReadAll(hgSqlOperator& sqlOperator)
{
    for (int i = 0; i < 13; i++)
    {
        m_ShipMap.insert(hgAnchorageTypeName[i],hgAnchorageTypeGuid[i]);
    }
    ReadPloygon(sqlOperator);
    ReadEllipse(sqlOperator);
    ReadCricle(sqlOperator);
    ReadSector(sqlOperator);
    ReadDutyArea(sqlOperator);
    ReadReportLine(sqlOperator);
    ReadChannel(sqlOperator);
}

void hgLayerDataManager::ReadPloygon(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("ploygon_table");
 
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        //vtsPloygon l_ploygon;
        hgPolygonLayer l_ploygon;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        QByteArray l_points = l_record.value("point").toByteArray();
        int l_linestyle = l_record.value("linestyle").toInt();
        int l_fullstyle = l_record.value("fullstyle").toInt();
        int l_linewidth = l_record.value("linewidth").toInt();
        QByteArray l_waringID = l_record.value("waringID").toByteArray();
        QString l_waringtype = l_record.value("waringtype").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        QString l_linecolor = l_record.value("linecolor").toString();
        QString l_fullcolor = l_record.value("fullcolor").toString();
        ///////
        int enter_time = l_record.value("enter_time").toInt();
        double enter_speed = l_record.value("enter_speed").toDouble();
        double enter_acceleration = l_record.value("enter_acceleration").toDouble();
        int leave_time = l_record.value("leave_time").toInt();
        double leave_speed = l_record.value("leave_speed").toDouble();
        double leave_acceleration = l_record.value("leave_acceleration").toDouble();
        int inside_time = l_record.value("inside_time").toInt();
        double inside_speed = l_record.value("inside_speed").toDouble();
        double inside_acceleration = l_record.value("inside_acceleration").toDouble();
        int outside_time = l_record.value("outside_time").toInt();
        double outside_speed = l_record.value("outside_speed").toDouble();
        double outside_acceleration = l_record.value("outside_acceleration").toDouble();
        int high_duration = l_record.value("high_duration").toInt();
        double high_speed = l_record.value("high_speed").toDouble();
        int low_duration = l_record.value("low_duration").toInt();
        double low_speed = l_record.value("low_speed").toDouble();
        int pro_duration = l_record.value("pro_duration").toInt();
        double pro_lat = l_record.value("pro_lat").toDouble();
        double pro_lon = l_record.value("pro_lon").toDouble();
        double add_max = l_record.value("add_max").toDouble();
        double add_min = l_record.value("add_min").toDouble();
        double add_duration = l_record.value("add_duration").toDouble();
        double col_cpa = l_record.value("col_cpa").toDouble();
        double col_tcpa = l_record.value("col_tcpa").toDouble();
        double col_dcpa = l_record.value("col_dcpa").toDouble();
        double col_dist = l_record.value("col_dist").toDouble();
        int con_time = l_record.value("con_time").toInt();
        int con_total = l_record.value("con_total").toInt();
        double gro_depth = l_record.value("gro_depth").toDouble();
        int gro_time = l_record.value("gro_time").toInt();
        QByteArray anc_type = l_record.value("anc_type").toByteArray();
        int app_time = l_record.value("app_time").toInt();
        double cou_change = l_record.value("cou_change").toDouble();
        int cou_time = l_record.value("cou_time").toInt();
        time_t fog_begin_time = l_record.value("fog_begin_time").toInt();
        time_t fog_end_time = l_record.value("fog_end_time").toInt();
        int fog_time = l_record.value("fog_time").toInt();
        QByteArray fog_mmsi = l_record.value("fog_mmsi").toByteArray();
        ///////
        //ploygon.ID = l_ID;
        l_ploygon.m_Name = l_name;
        google::protobuf::RepeatedPtrField<PointMes> l_Point;
        QDataStream in(&l_points,QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_2);
        in >> l_Point;
        for (int i = 0; i < l_Point.size(); i++)
        {
            hg::utils::PointLL l_pointLL;
            l_pointLL.setLat(l_Point.Get(i).lat());
            l_pointLL.setLon(l_Point.Get(i).lon());
            l_ploygon.m_Polygon.push_back(l_pointLL);
        }
        google::protobuf::RepeatedPtrField<std::string> l_proID;
        QDataStream inID(&l_waringID,QIODevice::ReadOnly);
        inID.setVersion(QDataStream::Qt_5_2);
        inID >> l_proID;
        for (int i = 0; i < l_proID.size(); i++)
        {
            l_ploygon.m_WaringID.push_back(l_proID.Get(i).c_str());
        }
        l_ploygon.m_LineStyle = l_linestyle;
        l_ploygon.m_FullStyle = l_fullstyle;
        l_ploygon.m_LineWidth = l_linewidth; 
        l_ploygon.m_DrawMan = l_drawman;
        l_ploygon.m_IsNew = l_isshare;
        l_ploygon.m_LineColor = l_linecolor;
        l_ploygon.m_FullColor = l_fullcolor;
        ///
//         vtsULWaring l_ULWaring;
//         l_ULWaring.enter_time = enter_time;
//         l_ULWaring.enter_speed = enter_speed;
//         l_ULWaring.leave_time = leave_time;
//         l_ULWaring.leave_speed = leave_speed;
//         l_ULWaring.inside_time = inside_time;
//         l_ULWaring.inside_speed = inside_speed;
//         l_ULWaring.outside_time = outside_time;
//         l_ULWaring.outside_speed = outside_speed;
//         l_ULWaring.app_time = app_time;

        //l_ploygon.ULWaring = l_ULWaring;
        hgUserLayWarning l_ULWaring;
        l_ULWaring.enter_time = enter_time;
        l_ULWaring.enter_speed = enter_speed;
        l_ULWaring.leave_time = leave_time;
        l_ULWaring.leave_speed = leave_speed;
        l_ULWaring.inside_time = inside_time;
        l_ULWaring.inside_speed = inside_speed;
        l_ULWaring.outside_time = outside_time;
        l_ULWaring.outside_speed = outside_speed;
        l_ULWaring.app_time = app_time;//////////////////////////////
        l_ULWaring.high_duration = high_duration;//¸ßËÙ
        l_ULWaring.high_speed = high_speed;
        l_ULWaring.low_duration = low_duration;//µÍËÙ
        l_ULWaring.low_speed = low_speed;
        l_ULWaring.pro_duration = pro_duration;//½ûÃª
        l_ULWaring.pro_lat = pro_lat;
        l_ULWaring.pro_lon = pro_lon;
        //QList<QString>  anc_type;//Å×Ãª
        google::protobuf::RepeatedPtrField<std::string> l_Anc;
        QDataStream inAnc(&anc_type,QIODevice::ReadOnly);
        inAnc.setVersion(QDataStream::Qt_5_2);
        inAnc >> l_Anc;
        for (int i = 0; i < l_Anc.size(); i++)
        {
            l_ULWaring.anc_type.push_back(l_Anc.Get(i).c_str());
        }
        l_ULWaring.add_max = add_max;//¼ÓËÙ
        l_ULWaring.add_min = add_min;
        l_ULWaring.add_duration = add_duration;
        l_ULWaring.col_cpa = col_cpa;//Åö×²
        l_ULWaring.col_tcpa = col_tcpa;
        l_ULWaring.col_dcpa = col_dcpa;
        l_ULWaring.col_dist = col_dist;
        l_ULWaring.con_time = con_time;//Óµ¼·
        l_ULWaring.con_total = con_total;
        l_ULWaring.gro_depth = gro_depth;//¸éÇ³
        l_ULWaring.gro_time = gro_time;
        l_ULWaring.app_time = app_time;//½Ó½ü
        l_ULWaring.cou_change = cou_change;
        l_ULWaring.cou_time = cou_time;
        l_ULWaring.m_FogBeginTime = fog_begin_time;
        l_ULWaring.m_FogEndTime = fog_end_time;
        l_ULWaring.m_FogTime = fog_time;
        google::protobuf::RepeatedPtrField<std::string> l_Fog;
        QDataStream inFog(&fog_mmsi,QIODevice::ReadOnly);
        inFog.setVersion(QDataStream::Qt_5_2);
        inFog >> l_Fog;
        for (int i = 0; i < l_Fog.size(); i++)
        {
            l_ULWaring.m_FogMMSI.push_back(l_Fog.Get(i).c_str());
        }
        l_ploygon.m_ULWaring = l_ULWaring;
        m_pPloygonMap.insert(l_ID,l_ploygon);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
    CreateArea(sqlOperator);
}

void hgLayerDataManager::CreateArea(hgSqlOperator& sqlOperator)
{
    if ( !m_pPloygonMap.contains("{637F13FE-2E48-40B6-8327-68583E209BFE}") )//North
    {
        hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
        l_pSqlInsertCmd->SetTableName("ploygon_table");
        google::protobuf::RepeatedPtrField<PointMes> l_Point;
		PointMes* l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.230430);
		l_pointMes->set_lon(119.365110);
		l_pointMes = l_Point.Add();
        l_pointMes->set_lat(32.230321);
        l_pointMes->set_lon(119.366207);
        l_pointMes = l_Point.Add();
        l_pointMes->set_lat(32.230225);
        l_pointMes->set_lon(119.367013);
        l_pointMes = l_Point.Add();
        l_pointMes->set_lat(32.230075);
        l_pointMes->set_lon(119.367546);
        l_pointMes = l_Point.Add();
        l_pointMes->set_lat(32.229816);
		l_pointMes->set_lon(119.368255);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.229625);
		l_pointMes->set_lon(119.369433);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.229365);
		l_pointMes->set_lon(119.371804);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.229243);
		l_pointMes->set_lon(119.373998);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.229065);
		l_pointMes->set_lon(119.375643);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.229106);
		l_pointMes->set_lon(119.376450);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.229284);
		l_pointMes->set_lon(119.377337);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.229618);
		l_pointMes->set_lon(119.378176);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.230430);
		l_pointMes->set_lon(119.379709);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.231235);
		l_pointMes->set_lon(119.382241);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.231515);
		l_pointMes->set_lon(119.382636);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.231897);
		l_pointMes->set_lon(119.383024);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.232443);
		l_pointMes->set_lon(119.383999);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.232777);
		l_pointMes->set_lon(119.384467);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.233193);
		l_pointMes->set_lon(119.384895);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.233439);
		l_pointMes->set_lon(119.385088);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.234005);
		l_pointMes->set_lon(119.385701);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.234264);
		l_pointMes->set_lon(119.386105);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.234817);
		l_pointMes->set_lon(119.386693);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.235090);
		l_pointMes->set_lon(119.386822);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.235342);
		l_pointMes->set_lon(119.386871);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.236018);
		l_pointMes->set_lon(119.387371);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.237880);
		l_pointMes->set_lon(119.389242);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.239299);
		l_pointMes->set_lon(119.386839);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.233466);
		l_pointMes->set_lon(119.367481);
        google::protobuf::RepeatedPtrField<std::string> WaringID;
        auto l_warning = WaringID.Add();
        l_warning->append("{0A234218-3B1B-4B27-97C1-0E39F8294640}");//(±¨¾¯ÒÖÖÆ¾¯±¨)
        QMap<QString, QVariant> l_data;
        QByteArray mes;
        QDataStream out(&mes,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_2);
        out << l_Point;
        l_data.insert("point",QVariant(mes));
        QByteArray mesID;
        QDataStream outID(&mesID,QIODevice::WriteOnly);
        outID.setVersion(QDataStream::Qt_5_2);
        outID << WaringID;
        l_data.insert("waringID",QVariant(mesID));
        l_data.insert("ID","{637F13FE-2E48-40B6-8327-68583E209BFE}");
        l_data.insert("name","NorthArea");
        l_data.insert("linestyle",0);
        l_data.insert("fullstyle",0);
        l_data.insert("linewidth",1);
        l_pSqlInsertCmd->SetData(l_data);
        if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
        {
			std::cout << "Open datatabase error(ploygon_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
			delete l_pSqlInsertCmd;
			l_pSqlInsertCmd = NULL;
            return;
        }

        QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
        if (l_pSqlInsertCmd)
        {
            delete l_pSqlInsertCmd;
            l_pSqlInsertCmd = NULL;
        }
        hgPolygonLayer l_ploygon;
        l_ploygon.m_Name = "NorthArea";
        l_ploygon.m_LineStyle = 0;
        l_ploygon.m_FullStyle = 0;
        l_ploygon.m_LineWidth = 1;
        l_ploygon.m_WaringID.append("{0A234218-3B1B-4B27-97C1-0E39F8294640}");
        for (int i = 0; i < l_Point.size(); i++)
        {
            PointMes l_mes = l_Point.Get(i);
            l_ploygon.m_Polygon.push_back(hg::utils::PointLL(l_mes.lon(),l_mes.lat()));
        }
        m_pPloygonMap.insert("{637F13FE-2E48-40B6-8327-68583E209BFE}",l_ploygon);
    }
    if ( !m_pPloygonMap.contains("{5F81AA11-DA37-450C-A1FB-C0B52D5AE632}") )//South
    {
        hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
        l_pSqlInsertCmd->SetTableName("ploygon_table");
        google::protobuf::RepeatedPtrField<PointMes> l_Point;
        PointMes* l_pointMes = l_Point.Add();
        l_pointMes->set_lat(32.217039);
		l_pointMes->set_lon(119.380451);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.218297);
		l_pointMes->set_lon(119.381765);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.218974);
		l_pointMes->set_lon(119.382273);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.219335);
		l_pointMes->set_lon(119.382741);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.219670);
		l_pointMes->set_lon(119.383572);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.219867);
		l_pointMes->set_lon(119.383887);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.220093);
		l_pointMes->set_lon(119.384032);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.220734);
		l_pointMes->set_lon(119.384241);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.221225);
		l_pointMes->set_lon(119.384524);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.221723);
		l_pointMes->set_lon(119.384975);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.222549);
		l_pointMes->set_lon(119.385855);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.223047);
		l_pointMes->set_lon(119.386322);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.224405);
		l_pointMes->set_lon(119.387952);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.225415);
		l_pointMes->set_lon(119.389186);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.225797);
		l_pointMes->set_lon(119.389484);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.226977);
		l_pointMes->set_lon(119.390597);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.227578);
		l_pointMes->set_lon(119.391742);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.229659);
		l_pointMes->set_lon(119.393073);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.226036);
		l_pointMes->set_lon(119.398824);
		l_pointMes = l_Point.Add();
		l_pointMes->set_lat(32.215118);
		l_pointMes->set_lon(119.384500);
        google::protobuf::RepeatedPtrField<std::string> WaringID;
        auto l_warning = WaringID.Add();
        l_warning->append("{0A234218-3B1B-4B27-97C1-0E39F8294640}");//(±¨¾¯ÒÖÖÆ¾¯±¨)
        QMap<QString, QVariant> l_data;
        QByteArray mes;
        QDataStream out(&mes,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_2);
        out << l_Point;
        l_data.insert("point",QVariant(mes));
        QByteArray mesID;
        QDataStream outID(&mesID,QIODevice::WriteOnly);
        outID.setVersion(QDataStream::Qt_5_2);
        outID << WaringID;
        l_data.insert("waringID",QVariant(mesID));
        l_data.insert("ID","{5F81AA11-DA37-450C-A1FB-C0B52D5AE632}");
        l_data.insert("name","SouthArea");
        l_data.insert("linestyle",0);
        l_data.insert("fullstyle",0);
        l_data.insert("linewidth",1);
        l_pSqlInsertCmd->SetData(l_data);
        if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
        {
			std::cout << "Open datatabase error(ploygon_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
			delete l_pSqlInsertCmd;
			l_pSqlInsertCmd = NULL;
            return;
        }

        QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
        if (l_pSqlInsertCmd)
        {
            delete l_pSqlInsertCmd;
            l_pSqlInsertCmd = NULL;
        }
        hgPolygonLayer l_ploygon;
        l_ploygon.m_Name = "SouthArea";
        l_ploygon.m_LineStyle = 0;
        l_ploygon.m_FullStyle = 0;
        l_ploygon.m_LineWidth = 1;
        l_ploygon.m_WaringID.append("{0A234218-3B1B-4B27-97C1-0E39F8294640}");
        for (int i = 0; i < l_Point.size(); i++)
        {
            PointMes l_mes = l_Point.Get(i);
            l_ploygon.m_Polygon.push_back(hg::utils::PointLL(l_mes.lon(),l_mes.lat()));
        }
        m_pPloygonMap.insert("{5F81AA11-DA37-450C-A1FB-C0B52D5AE632}",l_ploygon);
    }
}

void hgLayerDataManager::ReadEllipse(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("ellipse_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        vtsEllipse l_ellipse;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        double l_lat = l_record.value("lat").toDouble();
        double l_lon = l_record.value("lon").toDouble();
        double l_longaxis = l_record.value("longaxis").toDouble();
        double l_shortaxis = l_record.value("shortaxis").toDouble();
        int l_linestyle = l_record.value("linestyle").toInt();
        int l_fullstyle = l_record.value("fullstyle").toInt();
        int l_linewidth = l_record.value("linewidth").toInt();
        QByteArray l_waringID = l_record.value("waringID").toByteArray();
        QString l_waringtype = l_record.value("waringtype").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        QString l_linecolor = l_record.value("linecolor").toString();
        QString l_fullcolor = l_record.value("fullcolor").toString();
        l_ellipse.Name = l_name;
        l_ellipse.Lat = l_lat;
        l_ellipse.Lon = l_lon;
        l_ellipse.LongAxis = l_longaxis;
        l_ellipse.ShortAxis = l_shortaxis;
        l_ellipse.LineStyle = l_linestyle;
        l_ellipse.FullStyle = l_fullstyle;
        l_ellipse.LineWidth = l_linewidth;
        google::protobuf::RepeatedField<google::protobuf::int32> l_proID;
        QDataStream inID(&l_waringID,QIODevice::ReadOnly);
        inID.setVersion(QDataStream::Qt_5_2);
        inID >> l_proID;
        for (int i = 0; i < l_proID.size(); i++)
        {
            l_ellipse.WaringID.push_back(l_proID.Get(i));
        }
        l_ellipse.DrawMan = l_drawman;
        l_ellipse.IsNew = l_isshare;
        l_ellipse.LineColor = l_linecolor;
        l_ellipse.FullColor = l_fullcolor;
        m_pEllipseMap.insert(l_ID, l_ellipse);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgLayerDataManager::ReadCricle(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("cricle_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgCricleLayer l_cricle;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        double l_lat = l_record.value("lat").toDouble();
        double l_lon = l_record.value("lon").toDouble();
        double l_radius = l_record.value("radius").toDouble();
        int l_linestyle = l_record.value("linestyle").toInt();
        int l_fullstyle = l_record.value("fullstyle").toInt();
        int l_linewidth = l_record.value("linewidth").toInt();
        QByteArray l_waringID = l_record.value("waringID").toByteArray();
        QString l_waringtype = l_record.value("waringtype").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        QString l_linecolor = l_record.value("linecolor").toString();
        QString l_fullcolor = l_record.value("fullcolor").toString();
        int enter_time = l_record.value("enter_time").toInt();
        double enter_speed = l_record.value("enter_speed").toDouble();
        double enter_acceleration = l_record.value("enter_acceleration").toDouble();
        int leave_time = l_record.value("leave_time").toInt();
        double leave_speed = l_record.value("leave_speed").toDouble();
        double leave_acceleration = l_record.value("leave_acceleration").toDouble();
        int inside_time = l_record.value("inside_time").toInt();
        double inside_speed = l_record.value("inside_speed").toDouble();
        double inside_acceleration = l_record.value("inside_acceleration").toDouble();
        int outside_time = l_record.value("outside_time").toInt();
        double outside_speed = l_record.value("outside_speed").toDouble();
        double outside_acceleration = l_record.value("outside_acceleration").toDouble();
        int high_duration = l_record.value("high_duration").toInt();
        double high_speed = l_record.value("high_speed").toDouble();
        int low_duration = l_record.value("low_duration").toInt();
        double low_speed = l_record.value("low_speed").toDouble();
        int pro_duration = l_record.value("pro_duration").toInt();
        double pro_lat = l_record.value("pro_lat").toDouble();
        double pro_lon = l_record.value("pro_lon").toDouble();
        double add_max = l_record.value("add_max").toDouble();
        double add_min = l_record.value("add_min").toDouble();
        double add_duration = l_record.value("add_duration").toDouble();
        double col_cpa = l_record.value("col_cpa").toDouble();
        double col_tcpa = l_record.value("col_tcpa").toDouble();
        double col_dcpa = l_record.value("col_dcpa").toDouble();
        double col_dist = l_record.value("col_dist").toDouble();
        int con_time = l_record.value("con_time").toInt();
        int con_total = l_record.value("con_total").toInt();
        double gro_depth = l_record.value("gro_depth").toDouble();
        int gro_time = l_record.value("gro_time").toInt();
        QByteArray anc_type = l_record.value("anc_type").toByteArray();
        int app_time = l_record.value("app_time").toInt();
        double cou_change = l_record.value("cou_change").toDouble();
        int cou_time = l_record.value("cou_time").toInt();
        time_t fog_begin_time = l_record.value("fog_begin_time").toInt();
        time_t fog_end_time = l_record.value("fog_end_time").toInt();
        int fog_time = l_record.value("fog_time").toInt();
        QByteArray fog_mmsi = l_record.value("fog_mmsi").toByteArray();
        l_cricle.m_Name = l_name;
        l_cricle.m_Lat = l_lat;
        l_cricle.m_Lon = l_lon;
        l_cricle.m_Radius = l_radius;
        l_cricle.m_LineStyle = l_linestyle;
        l_cricle.m_FullStyle = l_fullstyle;
        l_cricle.m_LineWidth = l_linewidth;
        google::protobuf::RepeatedPtrField<google::protobuf::string> l_proID;
        QDataStream inID(&l_waringID,QIODevice::ReadOnly);
        inID.setVersion(QDataStream::Qt_5_2);
        inID >> l_proID;
        for (int i = 0; i < l_proID.size(); i++)
        {
            l_cricle.m_WaringID.push_back(l_proID.Get(i).c_str());
        }
        l_cricle.m_DrawMan = l_drawman;
        l_cricle.m_IsNew = l_isshare;
        l_cricle.m_LineColor = l_linecolor;
        l_cricle.m_FullColor = l_fullcolor;
        ////
        hgUserLayWarning l_ULWaring;
        l_ULWaring.enter_time = enter_time;
        l_ULWaring.enter_speed = enter_speed;
        l_ULWaring.leave_time = leave_time;
        l_ULWaring.leave_speed = leave_speed;
        l_ULWaring.inside_time = inside_time;
        l_ULWaring.inside_speed = inside_speed;
        l_ULWaring.outside_time = outside_time;
        l_ULWaring.outside_speed = outside_speed;
        l_ULWaring.app_time = app_time;//////////////////////////////
        l_ULWaring.high_duration = high_duration;//¸ßËÙ
        l_ULWaring.high_speed = high_speed;
        l_ULWaring.low_duration = low_duration;//µÍËÙ
        l_ULWaring.low_speed = low_speed;
        l_ULWaring.pro_duration = pro_duration;//½ûÃª
        l_ULWaring.pro_lat = pro_lat;
        l_ULWaring.pro_lon = pro_lon;
        //QList<QString>  anc_type;//Å×Ãª
        google::protobuf::RepeatedPtrField<std::string> l_Anc;
        QDataStream inAnc(&anc_type,QIODevice::ReadOnly);
        inAnc.setVersion(QDataStream::Qt_5_2);
        inAnc >> l_Anc;
        for (int i = 0; i < l_Anc.size(); i++)
        {
            l_ULWaring.anc_type.push_back(l_Anc.Get(i).c_str());
        }
        l_ULWaring.add_max = add_max;//¼ÓËÙ
        l_ULWaring.add_min = add_min;
        l_ULWaring.add_duration = add_duration;
        l_ULWaring.col_cpa = col_cpa;//Åö×²
        l_ULWaring.col_tcpa = col_tcpa;
        l_ULWaring.col_dcpa = col_dcpa;
        l_ULWaring.col_dist = col_dist;
        l_ULWaring.con_time = con_time;//Óµ¼·
        l_ULWaring.con_total = con_total;
        l_ULWaring.gro_depth = gro_depth;//¸éÇ³
        l_ULWaring.gro_time = gro_time;
        l_ULWaring.cou_change = cou_change;
        l_ULWaring.cou_time = cou_time;
        l_ULWaring.m_FogBeginTime = fog_begin_time;
        l_ULWaring.m_FogEndTime = fog_end_time;
        l_ULWaring.m_FogTime = fog_time;
        google::protobuf::RepeatedPtrField<std::string> l_Fog;
        QDataStream inFog(&fog_mmsi,QIODevice::ReadOnly);
        inFog.setVersion(QDataStream::Qt_5_2);
        inFog >> l_Fog;
        for (int i = 0; i < l_Fog.size(); i++)
        {
            l_ULWaring.m_FogMMSI.push_back(l_Fog.Get(i).c_str());
        }
        l_cricle.m_ULWaring = l_ULWaring;
        m_pCricleMap.insert(l_ID,l_cricle);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgLayerDataManager::ReadSector(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("sector_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgSectorLayer l_sector;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        double l_lat = l_record.value("lat").toDouble();
        double l_lon = l_record.value("lon").toDouble();
        double l_radius = l_record.value("radius").toDouble();
        double l_beginangle = l_record.value("beginangle").toDouble();
        double l_endangle = l_record.value("endangle").toDouble();
        int l_linestyle = l_record.value("linestyle").toInt();
        int l_fullstyle = l_record.value("fullstyle").toInt();
        int l_linewidth = l_record.value("linewidth").toInt();
        QByteArray l_waringID = l_record.value("waringID").toByteArray();
        QString l_waringtype = l_record.value("waringtype").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        QString l_linecolor = l_record.value("linecolor").toString();
        QString l_fullcolor = l_record.value("fullcolor").toString();
        int enter_time = l_record.value("enter_time").toInt();
        double enter_speed = l_record.value("enter_speed").toDouble();
        double enter_acceleration = l_record.value("enter_acceleration").toDouble();
        int leave_time = l_record.value("leave_time").toInt();
        double leave_speed = l_record.value("leave_speed").toDouble();
        double leave_acceleration = l_record.value("leave_acceleration").toDouble();
        int inside_time = l_record.value("inside_time").toInt();
        double inside_speed = l_record.value("inside_speed").toDouble();
        double inside_acceleration = l_record.value("inside_acceleration").toDouble();
        int outside_time = l_record.value("outside_time").toInt();
        double outside_speed = l_record.value("outside_speed").toDouble();
        double outside_acceleration = l_record.value("outside_acceleration").toDouble();
        int high_duration = l_record.value("high_duration").toInt();
        double high_speed = l_record.value("high_speed").toDouble();
        int low_duration = l_record.value("low_duration").toInt();
        double low_speed = l_record.value("low_speed").toDouble();
        int pro_duration = l_record.value("pro_duration").toInt();
        double pro_lat = l_record.value("pro_lat").toDouble();
        double pro_lon = l_record.value("pro_lon").toDouble();
        double add_max = l_record.value("add_max").toDouble();
        double add_min = l_record.value("add_min").toDouble();
        double add_duration = l_record.value("add_duration").toDouble();
        double col_cpa = l_record.value("col_cpa").toDouble();
        double col_tcpa = l_record.value("col_tcpa").toDouble();
        double col_dcpa = l_record.value("col_dcpa").toDouble();
        double col_dist = l_record.value("col_dist").toDouble();
        int con_time = l_record.value("con_time").toInt();
        int con_total = l_record.value("con_total").toInt();
        double gro_depth = l_record.value("gro_depth").toDouble();
        int gro_time = l_record.value("gro_time").toInt();
        QByteArray anc_type = l_record.value("anc_type").toByteArray();
        int app_time = l_record.value("app_time").toInt();
        double cou_change = l_record.value("cou_change").toDouble();
        int cou_time = l_record.value("cou_time").toInt();
        time_t fog_begin_time = l_record.value("fog_begin_time").toInt();
        time_t fog_end_time = l_record.value("fog_end_time").toInt();
        int fog_time = l_record.value("fog_time").toInt();
        QByteArray fog_mmsi = l_record.value("fog_mmsi").toByteArray();
        l_sector.m_Name = l_name;
        l_sector.m_Lat = l_lat;
        l_sector.m_Lon = l_lon;
        l_sector.m_Radius = l_radius;
        l_sector.m_BeginAngle = l_beginangle;
        l_sector.m_EndAngle = l_endangle;
        l_sector.m_LineStyle = l_linestyle;
        l_sector.m_FullStyle = l_fullstyle;
        l_sector.m_LineWidth = l_linewidth;
        google::protobuf::RepeatedPtrField<google::protobuf::string> l_proID;
        QDataStream inID(&l_waringID,QIODevice::ReadOnly);
        inID.setVersion(QDataStream::Qt_5_2);
        inID >> l_proID;
        for (int i = 0; i < l_proID.size(); i++)
        {
            l_sector.m_WaringID.push_back(l_proID.Get(i).c_str());
        }
        l_sector.m_DrawMan = l_drawman;
        l_sector.m_IsNew = l_isshare;
        l_sector.m_LineColor = l_linecolor;
        l_sector.m_FullColor = l_fullcolor;
        ////
        hgUserLayWarning l_ULWaring;
        l_ULWaring.enter_time = enter_time;
        l_ULWaring.enter_speed = enter_speed;
        l_ULWaring.leave_time = leave_time;
        l_ULWaring.leave_speed = leave_speed;
        l_ULWaring.inside_time = inside_time;
        l_ULWaring.inside_speed = inside_speed;
        l_ULWaring.outside_time = outside_time;
        l_ULWaring.outside_speed = outside_speed;
        l_ULWaring.app_time = app_time;
        l_ULWaring.high_duration = high_duration;//¸ßËÙ
        l_ULWaring.high_speed = high_speed;
        l_ULWaring.low_duration = low_duration;//µÍËÙ
        l_ULWaring.low_speed = low_speed;
        l_ULWaring.pro_duration = pro_duration;//½ûÃª
        l_ULWaring.pro_lat = pro_lat;
        l_ULWaring.pro_lon = pro_lon;
        //QList<QString>  anc_type;//Å×Ãª
        google::protobuf::RepeatedPtrField<std::string> l_Anc;
        QDataStream inAnc(&anc_type,QIODevice::ReadOnly);
        inAnc.setVersion(QDataStream::Qt_5_2);
        inAnc >> l_Anc;
        for (int i = 0; i < l_Anc.size(); i++)
        {
            l_ULWaring.anc_type.push_back(l_Anc.Get(i).c_str());
        }
        l_ULWaring.add_max = add_max;//¼ÓËÙ
        l_ULWaring.add_min = add_min;
        l_ULWaring.add_duration = add_duration;
        l_ULWaring.col_cpa = col_cpa;//Åö×²
        l_ULWaring.col_tcpa = col_tcpa;
        l_ULWaring.col_dcpa = col_dcpa;
        l_ULWaring.col_dist = col_dist;
        l_ULWaring.con_time = con_time;//Óµ¼·
        l_ULWaring.con_total = con_total;
        l_ULWaring.gro_depth = gro_depth;//¸éÇ³
        l_ULWaring.gro_time = gro_time;
        l_ULWaring.cou_change = cou_change;
        l_ULWaring.cou_time = cou_time;
        l_ULWaring.m_FogBeginTime = fog_begin_time;
        l_ULWaring.m_FogEndTime = fog_end_time;
        l_ULWaring.m_FogTime = fog_time;
        google::protobuf::RepeatedPtrField<std::string> l_Fog;
        QDataStream inFog(&fog_mmsi,QIODevice::ReadOnly);
        inFog.setVersion(QDataStream::Qt_5_2);
        inFog >> l_Fog;
        for (int i = 0; i < l_Fog.size(); i++)
        {
            l_ULWaring.m_FogMMSI.push_back(l_Fog.Get(i).c_str());
        }
        l_sector.m_ULWaring = l_ULWaring;
        m_pSectorMap.insert(l_ID, l_sector);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgLayerDataManager::ReadDutyArea(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("dutyarea_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgDutyAreaLayer l_dutyarea;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        QByteArray l_points = l_record.value("point").toByteArray();
        int l_linestyle = l_record.value("linestyle").toInt();
        int l_fullstyle = l_record.value("fullstyle").toInt();
        int l_linewidth = l_record.value("linewidth").toInt();
        QString l_dutyman = l_record.value("dutyman").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        QString l_linecolor = l_record.value("linecolor").toString();
        QString l_fullcolor = l_record.value("fullcolor").toString();
        l_dutyarea.m_Name = l_name;
        google::protobuf::RepeatedPtrField<PointMes> l_Point;
        QDataStream in(&l_points,QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_2);
        in >> l_Point;
        for (int i = 0; i < l_Point.size(); i++)
        {
            hg::utils::PointLL l_pointLL;
            l_pointLL.setLat(l_Point.Get(i).lat());
            l_pointLL.setLon(l_Point.Get(i).lon());
            l_dutyarea.m_Polygon.push_back(l_pointLL);
        }
        l_dutyarea.m_LineStyle = l_linestyle;
        l_dutyarea.m_FullStyle = l_fullstyle;
        l_dutyarea.m_LineWidth = l_linewidth;
        l_dutyarea.m_DutyMan = l_dutyman;
        l_dutyarea.m_DrawMan = l_drawman;
        l_dutyarea.m_IsNew = l_isshare;
        l_dutyarea.m_LineColor = l_linecolor;
        l_dutyarea.m_FullColor = l_fullcolor;
        m_pDutyAreaMap.insert(l_ID, l_dutyarea);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgLayerDataManager::ReadReportLine(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("reportline_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgReportLineLayer l_reportline;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        QByteArray l_points = l_record.value("point").toByteArray();
        int l_linestyle = l_record.value("linestyle").toInt();
        int l_fullstyle = l_record.value("fullstyle").toInt();
        int l_linewidth = l_record.value("linewidth").toInt();
        QByteArray l_waringID = l_record.value("waringID").toByteArray();
        QString l_waringtype = l_record.value("waringtype").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        QString l_linecolor = l_record.value("linecolor").toString();
        QString l_fullcolor = l_record.value("fullcolor").toString();
        l_reportline.m_Name = l_name;
        google::protobuf::RepeatedPtrField<PointMes> l_Point;
        QDataStream in(&l_points,QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_2);
        in >> l_Point;
        for (int i = 0; i < l_Point.size(); i++)
        {
            hg::utils::PointLL l_pointLL;
            l_pointLL.setLat(l_Point.Get(i).lat());
            l_pointLL.setLon(l_Point.Get(i).lon());
            l_reportline.m_Polygon.push_back(l_pointLL);
        }
//         google::protobuf::RepeatedField<google::protobuf::int32> l_proID;
//         QDataStream inID(&l_waringID,QIODevice::ReadOnly);
//         inID.setVersion(QDataStream::Qt_5_2);
//         inID >> l_proID;
//         for (int i = 0; i < l_proID.size(); i++)
//         {
//             l_reportline.m_WaringID.push_back(l_proID.Get(i));
//         }
        l_reportline.m_LineStyle = l_linestyle;
        l_reportline.m_FullStyle = l_fullstyle;
        l_reportline.m_LineWidth = l_linewidth;
        l_reportline.m_DrawMan = l_drawman;
        l_reportline.m_IsNew = l_isshare;
        l_reportline.m_LineColor = l_linecolor;
        l_reportline.m_FullColor = l_fullcolor;
        m_pReportLineMap.insert(l_ID, l_reportline);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgLayerDataManager::ReadChannel(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("channel_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgChannelLayer l_channel;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        QString l_annotation = l_record.value("annotation").toString();
        int l_channeltype = l_record.value("channeltype").toInt();
        double l_width = l_record.value("width").toDouble();
        QByteArray l_points = l_record.value("point").toByteArray();
        int l_linestyle = l_record.value("linestyle").toInt();
        QString l_linecolor = l_record.value("linecolor").toString();
        QString l_waringID = l_record.value("waringID").toString();
        QString l_waringtype = l_record.value("waringtype").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        l_channel.m_Name = l_name;
        l_channel.m_Annotation = l_annotation;
        l_channel.m_ChannelType = l_channeltype;
        l_channel.m_Width = l_width;
        google::protobuf::RepeatedPtrField<ChannelWay> l_Point;
        QDataStream in(&l_points,QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_2);
        in >> l_Point;
//         for (int i = 0; i < l_Point.size(); i++)
//         {
        for (int i = 0; i < l_Point.size(); i++)
        {
            ChannelWay l_Channel = l_Point.Get(i);
            auto l_ChannelPoints = l_Channel.point();
            hg::utils::PolygonLL l_Way;
            for ( int j = 0; j < l_ChannelPoints.size(); j++ )
            {
                hg::utils::PointLL l_poiLL;
                l_poiLL.setLat(l_ChannelPoints.Get(j).lat());
                l_poiLL.setLon(l_ChannelPoints.Get(j).lon());
                l_Way.push_back(l_poiLL);
            }
            l_channel.m_AllPoint.push_back(l_Way);
            }
/*        }*/
        l_channel.m_LineStyle = l_linestyle;
        l_channel.m_LineColor = l_linecolor;
        l_channel.m_DrawMan = l_drawman;
        l_channel.m_IsNew = l_isshare;
        m_pChannelMap.insert(l_ID, l_channel);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgLayerDataManager::ReadNotes(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("notes_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgNotesLayer l_vtsnotes;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        double l_lat = l_record.value("lat").toDouble();
        double l_lon = l_record.value("lon").toDouble();
        QString l_notes = l_record.value("notes").toString();
        QString l_color = l_record.value("color").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        l_vtsnotes.m_Name = l_name;
        l_vtsnotes.m_Lat = l_lat;
        l_vtsnotes.m_Lon = l_lon;
        l_vtsnotes.m_Notes = l_notes;
        l_vtsnotes.m_Color = l_color;
        l_vtsnotes.m_DrawMan = l_drawman;
        l_vtsnotes.m_IsNew = l_isshare;
        m_pNotesMap.insert(l_ID, l_vtsnotes);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgLayerDataManager::ReadAidSail(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("aidsail_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgAidSailLayer l_aidsail;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        double l_lat = l_record.value("lat").toDouble();
        double l_lon = l_record.value("lon").toDouble();
        QString l_remarks = l_record.value("remarks").toString();
        QString l_iconURL = l_record.value("iconURL").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        l_aidsail.m_Name = l_name;
        l_aidsail.m_Lat = l_lat;
        l_aidsail.m_Lon = l_lon;
        l_aidsail.m_Remarks = l_remarks;
        l_aidsail.m_IconURL = l_iconURL;
        l_aidsail.m_DrawMan = l_drawman;
        l_aidsail.m_IsNew = l_isshare;
        m_pAidSailMap.insert(l_ID, l_aidsail);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgLayerDataManager::ReadFixedObject(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("fixedobject_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgFixedObjectLayer l_fixedobject;
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        double l_lat = l_record.value("lat").toDouble();
        double l_lon = l_record.value("lon").toDouble();
        QString l_remarks = l_record.value("remarks").toString();
        QString l_iconURL = l_record.value("iconURL").toString();
        QString l_drawman = l_record.value("drawman").toString();
        bool l_isshare = l_record.value("isshare").toBool();
        l_fixedobject.m_Name = l_name;
        l_fixedobject.m_Lat = l_lat;
        l_fixedobject.m_Lon = l_lon;
        l_fixedobject.m_Remarks = l_remarks;
        l_fixedobject.m_IconURL = l_iconURL;
        l_fixedobject.m_DrawMan = l_drawman;
        l_fixedobject.m_IsNew = l_isshare;
        m_pFixedObjectMap.insert(l_ID, l_fixedobject);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}