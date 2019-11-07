
#include "StdAfx.h"
#include "SectorHandler.h"

#include "message/Sector.pb.h"
#include "message/adduserlay.pb.h"
#include "frame/vtsServer.h"
#include "db/DBSectorHandler.h"
#include "timer/hgSectorTimerHandler.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
SectorHandler::SectorHandler()
{

}

SectorHandler::~SectorHandler(void)
{
}

vtsRequestHandler::WorkMode SectorHandler::workMode()
{
    return Work_Delete_Manual;
}

void SectorHandler::handle(boost::asio::const_buffer& data)
{
    SectorRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    if (msg.type() == DBSectorHandlerType::CIsShare
        || msg.type() == DBSectorHandlerType::Search)
    {
        delete this;
        return ;
    }
    if (msg.type() == DBSectorHandlerType::Waring)
    {
        delete this;
        return ;
    }

    if (hgAlarmManager::m_LayerDataManager.m_pSectorMap.size() > 0)
    {
        hgAlarmManager::StartWarning("hgSectorTimerHandler",WarningSector,this);
    }
    else
    {
        hgAlarmManager::StopWarning("hgSectorTimerHandler",this);
    }

    DBSectorHandler *dbHandler = new DBSectorHandler();
    dbHandler->Type = msg.type();
    dbHandler->ID = msg.id().c_str();
    dbHandler->Name = msg.name().c_str();
    dbHandler->Lat = msg.lat();
    dbHandler->Lon = msg.lon();
    dbHandler->Radius = msg.radius();
    dbHandler->BeginAngle = msg.beginangle();
    dbHandler->EndAngle = msg.endangle();
    dbHandler->LineStyle = msg.linestyle();
    dbHandler->FullStyle = msg.fullstyle();
    dbHandler->LineWidth = msg.linewidth();
    dbHandler->WaringID = msg.waringid();
    dbHandler->WaringType = msg.waringtype().c_str();
    dbHandler->DrawMan = msg.drawman().c_str();
    dbHandler->IsShare = msg.isshare();
    dbHandler->LineColor = msg.linecolor().c_str();
    dbHandler->FullColor = msg.fullcolor().c_str();
    dbHandler->Info = msg.info();
    switch (msg.type())
    {
    case DBSectorHandlerType::Add:
    case DBSectorHandlerType::Update:
        UpdateSector(msg);
        break;
    case DBSectorHandlerType::Remove:
        RemoveSector(msg);
        break;
    case DBSectorHandlerType::All:
        {
            AllSector(msg);
            delete dbHandler;
            delete this;
            return ;
        }
        break;
    }
    if (hgAlarmManager::m_LayerDataManager.m_pSectorMap.size() == 0)
    {
        hgAlarmManager::StopWarning("hgSectorTimerHandler",this);
    }
    postToDB(dbHandler, boost::bind(&SectorHandler::afterDb, this, dbHandler));
    
}

void SectorHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void SectorHandler::afterDb(DBSectorHandler* db)
{
    SectorRepsone result;
    result = db->Respon;
    result.set_type(db->Type);
    response(result, boost::bind(&SectorHandler::afterResponse, this, boost::asio::placeholders::error));
    //添加成功发广播
    if (db->Type == DBSectorHandlerType::Add || db->Type == DBSectorHandlerType::Update || db->Type == DBSectorHandlerType::Remove)
    {
        if (db->Result == "OK")
        {
            AddUserLay l_userlay;
            l_userlay.set_id(db->ID.toStdString());
            l_userlay.set_pic("Sector");
            l_userlay.set_drawman(db->DrawMan.toStdString());
            switch (db->Type)
            {
            case DBSectorHandlerType::Add:
                l_userlay.set_type("create");
                break;
            case DBSectorHandlerType::Update:
                l_userlay.set_type("change");
                break;
            case DBSectorHandlerType::Remove:
                l_userlay.set_type("Remove");
                break;
            }
            hgSendManager::SendClientMessageUOwn("adduserlay",l_userlay,this->connection());
//             this->connection()->server().connectionManager().for_each
//                 ([&](ConnectionPtr p){
//                     if (p != this->connection())//自己不要发送
//                     {
//                         p->write("adduserlay",l_userlay);
//                     }
//             });
        }
    }
    delete db;
}

void SectorHandler::UpdateSector(SectorRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pSectorMap;
    if (p.contains(msg.id().c_str()))
    {
        auto &l_sector = p[msg.id().c_str()];
        l_sector.m_WaringID.clear();
        for (int i = 0; i < msg.waringid_size(); i++)
        {
            l_sector.m_WaringID.push_back(msg.waringid(i).c_str());
        }
        l_sector.m_Name = msg.name().c_str();
        l_sector.m_Lat = msg.lat();
        l_sector.m_Lon = msg.lon();
        l_sector.m_Radius = msg.radius();
        l_sector.m_BeginAngle = msg.beginangle();
        l_sector.m_EndAngle = msg.endangle();
        l_sector.m_LineStyle = msg.linestyle();
        l_sector.m_FullStyle = msg.fullstyle();
        l_sector.m_LineWidth = msg.linewidth(); 
        l_sector.m_DrawMan = msg.drawman().c_str();
        l_sector.m_IsNew = msg.isshare();
        l_sector.m_LineColor = msg.linecolor().c_str();
        l_sector.m_FullColor = msg.fullcolor().c_str();
        if (msg.info_size() > 0)
        {
            WaringInfo l_info = msg.info(0);
            l_sector.m_ULWaring.anc_type.clear();
            l_sector.m_ULWaring.m_FogMMSI.clear();
            for (int i = 0; i < l_info.anc_type_size(); i++)
            {
                l_sector.m_ULWaring.anc_type.push_back(l_info.anc_type(i).c_str());
            }
            for (int i = 0; i < l_info.fog_mmsi_size(); i++)
            {
                l_sector.m_ULWaring.m_FogMMSI.push_back(l_info.fog_mmsi(i).c_str());
            }
            l_sector.m_ULWaring.enter_time = l_info.enter_time();
            l_sector.m_ULWaring.enter_speed = l_info.enter_speed();
            l_sector.m_ULWaring.leave_time = l_info.leave_time();
            l_sector.m_ULWaring.leave_speed = l_info.leave_speed();
            l_sector.m_ULWaring.app_time = l_info.app_time();
            l_sector.m_ULWaring.high_duration = l_info.high_duration();//高速
            l_sector.m_ULWaring.high_speed = l_info.high_speed();
            l_sector.m_ULWaring.low_duration = l_info.low_duration();//低速
            l_sector.m_ULWaring.low_speed = l_info.low_speed();
            l_sector.m_ULWaring.pro_duration = l_info.pro_duration();//禁锚
            l_sector.m_ULWaring.pro_lat = l_info.pro_lat();
            l_sector.m_ULWaring.pro_lon = l_info.pro_lon();
            l_sector.m_ULWaring.add_max = l_info.add_max();//加速
            l_sector.m_ULWaring.add_min = l_info.add_min();
            l_sector.m_ULWaring.add_duration = l_info.add_duration();
            l_sector.m_ULWaring.col_cpa = l_info.col_cpa();//碰撞
            l_sector.m_ULWaring.col_tcpa = l_info.col_tcpa();
            l_sector.m_ULWaring.col_dcpa = l_info.col_dcpa();
            l_sector.m_ULWaring.col_dist = l_info.col_dist();
            l_sector.m_ULWaring.con_time = l_info.con_time();//拥挤
            l_sector.m_ULWaring.con_total = l_info.con_total();
            l_sector.m_ULWaring.gro_depth = l_info.gro_depth();//搁浅
            l_sector.m_ULWaring.gro_time = l_info.gro_time();
            l_sector.m_ULWaring.app_time = l_info.app_time();//接近
            l_sector.m_ULWaring.cou_change = l_info.cou_change();
            l_sector.m_ULWaring.cou_time = l_info.cou_time();
            l_sector.m_ULWaring.m_FogBeginTime = l_info.fog_begin_time();
            l_sector.m_ULWaring.m_FogEndTime = l_info.fog_end_time();
            l_sector.m_ULWaring.m_FogTime = l_info.fog_time();
        }
    }
    else
    {
        hgSectorLayer l_sector;
        l_sector.m_Name = msg.name().c_str();
        l_sector.m_Lat = msg.lat();
        l_sector.m_Lon = msg.lon();
        l_sector.m_Radius = msg.radius();
        l_sector.m_BeginAngle = msg.beginangle();
        l_sector.m_EndAngle = msg.endangle();
        l_sector.m_LineStyle = msg.linestyle();
        l_sector.m_FullStyle = msg.fullstyle();
        l_sector.m_LineWidth = msg.linewidth(); 
        l_sector.m_DrawMan = msg.drawman().c_str();
        l_sector.m_IsNew = msg.isshare();
        l_sector.m_LineColor = msg.linecolor().c_str();
        l_sector.m_FullColor = msg.fullcolor().c_str();
        p.insert(msg.id().c_str(),l_sector);
    }
}

void SectorHandler::RemoveSector(SectorRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pSectorMap;
    if (p.contains(msg.id().c_str()))
    {
        p.remove(msg.id().c_str());
    }
}

void SectorHandler::AllSector(SectorRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pSectorMap;
    SectorRepsone l_Respon;
    l_Respon.set_type(msg.type());
    for (auto l_Iter = p.begin(); l_Iter != p.end(); l_Iter++)
    {
        auto l_Layer = l_Iter.value();
        SectorRequest* l_Request = l_Respon.add_sectors();
        for (int i = 0; i < l_Layer.m_WaringID.size(); i++)
        {
            l_Request->add_waringid(l_Layer.m_WaringID.at(i).toStdString());
        }
        l_Request->set_type(msg.type());
        l_Request->set_id(l_Iter.key().toStdString());
        l_Request->set_name(l_Layer.m_Name.toStdString());
        l_Request->set_lat(l_Layer.m_Lat);
        l_Request->set_lon(l_Layer.m_Lon);
        l_Request->set_radius(l_Layer.m_Radius);
        l_Request->set_beginangle(l_Layer.m_BeginAngle);
        l_Request->set_endangle(l_Layer.m_EndAngle);
        l_Request->set_linestyle(l_Layer.m_LineStyle);
        l_Request->set_fullstyle(l_Layer.m_FullStyle);
        l_Request->set_linewidth(l_Layer.m_LineWidth);
        l_Request->set_waringtype("");
        l_Request->set_drawman(l_Layer.m_DrawMan.toStdString());
        l_Request->set_isshare(l_Layer.m_IsNew);
        l_Request->set_linecolor(l_Layer.m_LineColor.toStdString());
        l_Request->set_fullcolor(l_Layer.m_FullColor.toStdString());
        WaringInfo* l_Info = l_Request->add_info();
        for (int i = 0; i < l_Layer.m_ULWaring.anc_type.size(); i++)
        {
            l_Info->add_anc_type(l_Layer.m_ULWaring.anc_type.at(i).toStdString());
        }
        for (int i = 0; i < l_Layer.m_ULWaring.m_FogMMSI.size(); i++)
        {
            l_Info->add_fog_mmsi(l_Layer.m_ULWaring.m_FogMMSI.at(i).toStdString());
        }
        l_Info->set_enter_time(l_Layer.m_ULWaring.enter_time);
        l_Info->set_enter_speed(l_Layer.m_ULWaring.enter_speed);
        l_Info->set_enter_acceleration(0);
        l_Info->set_leave_time(l_Layer.m_ULWaring.leave_time);
        l_Info->set_leave_speed(l_Layer.m_ULWaring.leave_speed);
        l_Info->set_leave_acceleration(0);
        l_Info->set_inside_time(l_Layer.m_ULWaring.inside_time);
        l_Info->set_inside_speed(l_Layer.m_ULWaring.inside_speed);
        l_Info->set_inside_acceleration(0);
        l_Info->set_outside_time(l_Layer.m_ULWaring.outside_time);
        l_Info->set_outside_speed(l_Layer.m_ULWaring.outside_speed);
        l_Info->set_outside_acceleration(0);
        l_Info->set_high_duration(l_Layer.m_ULWaring.high_duration);
        l_Info->set_high_speed(l_Layer.m_ULWaring.high_speed);
        l_Info->set_low_duration(l_Layer.m_ULWaring.low_duration);
        l_Info->set_low_speed(l_Layer.m_ULWaring.low_speed);
        l_Info->set_pro_duration(l_Layer.m_ULWaring.pro_duration);
        l_Info->set_pro_lat(l_Layer.m_ULWaring.pro_lat);
        l_Info->set_pro_lon(l_Layer.m_ULWaring.pro_lon);
        l_Info->set_add_max(l_Layer.m_ULWaring.add_max);
        l_Info->set_add_min(l_Layer.m_ULWaring.add_min);
        l_Info->set_add_duration(l_Layer.m_ULWaring.add_duration);
        l_Info->set_col_cpa(l_Layer.m_ULWaring.col_cpa);
        l_Info->set_col_tcpa(l_Layer.m_ULWaring.col_tcpa);
        l_Info->set_col_dcpa(l_Layer.m_ULWaring.col_dcpa);
        l_Info->set_con_time(l_Layer.m_ULWaring.con_time);
        l_Info->set_con_total(l_Layer.m_ULWaring.con_total);
        l_Info->set_gro_depth(l_Layer.m_ULWaring.gro_depth);
        l_Info->set_gro_time(l_Layer.m_ULWaring.gro_time);
        l_Info->set_app_time(l_Layer.m_ULWaring.app_time);
        l_Info->set_cou_change(l_Layer.m_ULWaring.cou_change);
        l_Info->set_cou_time(l_Layer.m_ULWaring.cou_time);
        l_Info->set_fog_begin_time(l_Layer.m_ULWaring.m_FogBeginTime);
        l_Info->set_fog_end_time(l_Layer.m_ULWaring.m_FogEndTime);
        l_Info->set_fog_time(l_Layer.m_ULWaring.m_FogTime);
    }
    hgSendManager::SendCurrentMessage("sector",l_Respon,this->connection());
    //this->connection()->write("sector",l_Respon);
}

void SectorHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
