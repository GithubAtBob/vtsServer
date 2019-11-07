
#include "StdAfx.h"
#include "PloygonHandler.h"

#include "message/Ploygon.pb.h"
#include "message/adduserlay.pb.h"
#include "message/hgAlarmArea.pb.h"
#include "frame/vtsServer.h"
#include "db/DBPloygonHandler.h"

#include "timer/hgPolygonTimerHandler.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

PloygonHandler::PloygonHandler()
{

}

PloygonHandler::~PloygonHandler(void)
{
}

vtsRequestHandler::WorkMode PloygonHandler::workMode()
{
    return Work_Delete_Manual;
}

void PloygonHandler::handle(boost::asio::const_buffer& data)
{
    PloygonRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    if (msg.type() == DBPloygonHandlerType::CIsShare
        || msg.type() == DBPloygonHandlerType::Search)
    {
        delete this;
        return ;
    }
    if (msg.type() == DBPloygonHandlerType::Waring)
    {
        delete this;
        return ;
    }
        
    if (hgAlarmManager::m_LayerDataManager.m_pPloygonMap.size() > 0)
    {
        hgAlarmManager::StartWarning("hgPolygonTimerHandler",WaringPolygon,this);
    }
    else
    {
        hgAlarmManager::StopWarning("hgPolygonTimerHandler",this);
    }

    DBPloygonHandler *dbHandler = new DBPloygonHandler();
    dbHandler->Type = msg.type();
    dbHandler->ID = msg.id().c_str();
    dbHandler->Name = msg.name().c_str();
    dbHandler->Point = msg.point();
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
    case DBPloygonHandlerType::Add:
    case DBPloygonHandlerType::Update:
        UpdatePolygon(msg);
        break;
    case DBPloygonHandlerType::Remove:
        RemovePolygon(msg);
        break;
    case DBPloygonHandlerType::All:
        {
            AllPolygon(msg);
            delete dbHandler;
            delete this;
            return ;
        }
        break;
    }
    if (hgAlarmManager::m_LayerDataManager.m_pPloygonMap.size() == 0)
    {
        hgAlarmManager::StopWarning("hgPolygonTimerHandler",this);
    }
    postToDB(dbHandler, boost::bind(&PloygonHandler::afterDb, this, dbHandler));
    
}

void PloygonHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void PloygonHandler::afterDb(DBPloygonHandler* db)
{
    //添加成功发广播
    if (db->Type == DBPloygonHandlerType::Add || db->Type == DBPloygonHandlerType::Update || db->Type == DBPloygonHandlerType::Remove)
    {
        if (db->Result == "OK")
        {
            AddUserLay l_userlay;
            l_userlay.set_id(db->ID.toStdString());
            l_userlay.set_pic("Ploygon");
            l_userlay.set_drawman(db->DrawMan.toStdString());
            switch (db->Type)
            {
            case DBPloygonHandlerType::Add:
                l_userlay.set_type("create");
                break;
            case DBPloygonHandlerType::Update:
                l_userlay.set_type("change");
                break;
            case DBPloygonHandlerType::Remove:
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
    SendChangeToAlgor();
    delete db;
    delete this;
}

void PloygonHandler::UpdatePolygon(PloygonRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pPloygonMap;
    if (p.contains(msg.id().c_str()))
    {
        auto &polygon = p[msg.id().c_str()];
        polygon.m_Polygon.clear();
        polygon.m_WaringID.clear();
        for (int i = 0; i < msg.point_size(); i++)
        {
            hg::utils::PointLL l_pointLL;
            l_pointLL.setLat(msg.point(i).lat());
            l_pointLL.setLon(msg.point(i).lon());
            polygon.m_Polygon.push_back(l_pointLL);
        }
        for (int i = 0; i < msg.waringid_size(); i++)
        {
            polygon.m_WaringID.push_back(msg.waringid(i).c_str());
        }
        polygon.m_Name = msg.name().c_str();
        polygon.m_LineStyle = msg.linestyle();
        polygon.m_FullStyle = msg.fullstyle();
        polygon.m_LineWidth = msg.linewidth(); 
        polygon.m_DrawMan = msg.drawman().c_str();
        polygon.m_IsNew = msg.isshare();
        polygon.m_LineColor = msg.linecolor().c_str();
        polygon.m_FullColor = msg.fullcolor().c_str();
        if (msg.info_size() > 0)
        {
            WaringInfo l_info = msg.info(0);
            polygon.m_ULWaring.anc_type.clear();
            polygon.m_ULWaring.m_FogMMSI.clear();
            for (int i = 0; i < l_info.anc_type_size(); i++)
            {
                polygon.m_ULWaring.anc_type.push_back(l_info.anc_type(i).c_str());
            }
            for (int i = 0; i < l_info.fog_mmsi_size(); i++)
            {
                polygon.m_ULWaring.m_FogMMSI.push_back(l_info.fog_mmsi(i).c_str());
            }
            polygon.m_ULWaring.enter_time = l_info.enter_time();
            polygon.m_ULWaring.enter_speed = l_info.enter_speed();
            polygon.m_ULWaring.leave_time = l_info.leave_time();
            polygon.m_ULWaring.leave_speed = l_info.leave_speed();
            polygon.m_ULWaring.app_time = l_info.app_time();
            polygon.m_ULWaring.high_duration = l_info.high_duration();//高速
            polygon.m_ULWaring.high_speed = l_info.high_speed();
            polygon.m_ULWaring.low_duration = l_info.low_duration();//低速
            polygon.m_ULWaring.low_speed = l_info.low_speed();
            polygon.m_ULWaring.pro_duration = l_info.pro_duration();//禁锚
            polygon.m_ULWaring.pro_lat = l_info.pro_lat();
            polygon.m_ULWaring.pro_lon = l_info.pro_lon();
            polygon.m_ULWaring.add_max = l_info.add_max();//加速
            polygon.m_ULWaring.add_min = l_info.add_min();
            polygon.m_ULWaring.add_duration = l_info.add_duration();
            polygon.m_ULWaring.col_cpa = l_info.col_cpa();//碰撞
            polygon.m_ULWaring.col_tcpa = l_info.col_tcpa();
            polygon.m_ULWaring.col_dcpa = l_info.col_dcpa();
            polygon.m_ULWaring.col_dist = l_info.col_dist();
            polygon.m_ULWaring.con_time = l_info.con_time();//拥挤
            polygon.m_ULWaring.con_total = l_info.con_total();
            polygon.m_ULWaring.gro_depth = l_info.gro_depth();//搁浅
            polygon.m_ULWaring.gro_time = l_info.gro_time();
            polygon.m_ULWaring.app_time = l_info.app_time();//接近
            polygon.m_ULWaring.cou_change = l_info.cou_change();
            polygon.m_ULWaring.cou_time = l_info.cou_time();
            polygon.m_ULWaring.m_FogBeginTime = l_info.fog_begin_time();
            polygon.m_ULWaring.m_FogEndTime = l_info.fog_end_time();
            polygon.m_ULWaring.m_FogTime = l_info.fog_time();
        }
    }
    else
    {
        hgPolygonLayer l_polygon;
        for (int i = 0; i < msg.point_size(); i++)
        {
            hg::utils::PointLL l_pointLL;
            l_pointLL.setLat(msg.point(i).lat());
            l_pointLL.setLon(msg.point(i).lon());
            l_polygon.m_Polygon.push_back(l_pointLL);
        }
        l_polygon.m_Name = msg.name().c_str();
        l_polygon.m_LineStyle = msg.linestyle();
        l_polygon.m_FullStyle = msg.fullstyle();
        l_polygon.m_LineWidth = msg.linewidth(); 
        l_polygon.m_DrawMan = msg.drawman().c_str();
        l_polygon.m_IsNew = msg.isshare();
        l_polygon.m_LineColor = msg.linecolor().c_str();
        l_polygon.m_FullColor = msg.fullcolor().c_str();
        p.insert(msg.id().c_str(),l_polygon);
    }
}

void PloygonHandler::RemovePolygon(PloygonRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pPloygonMap;
    if (p.contains(msg.id().c_str()))
    {
        p.remove(msg.id().c_str());
    }
}

void PloygonHandler::AllPolygon(PloygonRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pPloygonMap;
    PloygonRepsone l_Respon;
    l_Respon.set_type(msg.type());
    for (auto l_Iter = p.begin(); l_Iter != p.end(); l_Iter++)
    {
        auto l_Layer = l_Iter.value();
        PloygonRequest* l_Request = l_Respon.add_ploygons();
        for (int i = 0; i < l_Layer.m_Polygon.size(); i++)
        {
            PointMes* l_mes = l_Request->add_point();
            l_mes->set_lat(l_Layer.m_Polygon.at(i).lat());
            l_mes->set_lon(l_Layer.m_Polygon.at(i).lon());
        }
        for (int i = 0; i < l_Layer.m_WaringID.size(); i++)
        {
            l_Request->add_waringid(l_Layer.m_WaringID.at(i).toStdString());
        }
        l_Request->set_type(msg.type());
        l_Request->set_id(l_Iter.key().toStdString());
        l_Request->set_name(l_Layer.m_Name.toStdString());
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
    hgSendManager::SendCurrentMessage("ploygon",l_Respon,this->connection());
    //this->connection()->write("ploygon",l_Respon);
}

void PloygonHandler::SendChangeToAlgor()
{
    hgAlarmArea msg;
    msg.set_type(1);
    for (int i = 0; i < hgAlarmManager::m_listArea.size(); i++)
    {
        QString l_mmsi = hgAlarmManager::m_listArea.at(i);
        auto l_polygon = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(l_mmsi);
        if (l_polygon == hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end())
        {
            vtsWarning << "AlarmArea No Such Area";
            continue;
        }
        msg.add_mmsi(l_mmsi.toStdString());
        hgPolygonMes* l_polygonMes = msg.add_polygon();
        for (int j = 0; j < l_polygon->m_Polygon.size(); j++)
        {
            PointMes* l_point = l_polygonMes->add_point();
            l_point->set_lat(l_polygon->m_Polygon.at(j).lat());
            l_point->set_lon(l_polygon->m_Polygon.at(j).lon());
        }
    }
    hgSendManager::SendSpecifyMessage("AlarmArea",msg,this->connection(),"s_AlgorithServer");
}

void PloygonHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
