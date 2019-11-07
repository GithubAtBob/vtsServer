
#include "StdAfx.h"
#include "ReportLineHandler.h"

#include "message/ReportLine.pb.h"
#include "message/adduserlay.pb.h"
#include "frame/vtsServer.h"
#include "db/DBReportLineHandler.h"
#include "timer/hgReportTimerHandler.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
ReportLineHandler::ReportLineHandler()
{

}

ReportLineHandler::~ReportLineHandler(void)
{
}

vtsRequestHandler::WorkMode ReportLineHandler::workMode()
{
    return Work_Delete_Manual;
}

void ReportLineHandler::handle(boost::asio::const_buffer& data)
{
    ReportLineRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

     if (msg.type() == DBReportLineHandlerType::All)
     {
         hgAlarmManager::StartWarning(msg.id(),WarningReportLine,this);
     }

    DBReportLineHandler *dbHandler = new DBReportLineHandler();
    dbHandler->Type = msg.type();
    dbHandler->ID = msg.id().c_str();
    dbHandler->Name = msg.name().c_str();
    dbHandler->Point = msg.point();
    dbHandler->LineStyle = msg.linestyle();
    dbHandler->FullStyle = msg.fullstyle();
    dbHandler->LineWidth = msg.linewidth();
//    dbHandler->WaringID = msg.waringid();
    dbHandler->WaringType = msg.waringtype().c_str();
    dbHandler->DrawMan = msg.drawman().c_str();
    dbHandler->IsShare = msg.isshare();
    dbHandler->LineColor = msg.linecolor().c_str();
    dbHandler->FullColor = msg.fullcolor().c_str();
    //    dbHandler->Info = msg.info();

    if (hgAlarmManager::m_LayerDataManager.m_pReportLineMap.size() > 0)
    {
        hgAlarmManager::StartWarning("hgReportTimerHandler",WarningReportLine,this);
    }
    else
    {
        hgAlarmManager::StopWarning("hgReportTimerHandler",this);
    }
    switch (msg.type())
    {
    case DBReportLineHandlerType::Add:
    case DBReportLineHandlerType::Update:
        UpdateFunction(msg);
        break;
    case DBReportLineHandlerType::Remove:
        RemoveFunction(msg);
        break;
    case DBReportLineHandlerType::All:
        AllFunction(msg);
        delete dbHandler;
        delete this;
        return ;
        break;
    }
    if (hgAlarmManager::m_LayerDataManager.m_pReportLineMap.size() == 0)
    {
        hgAlarmManager::StopWarning("hgReportTimerHandler",this);
    }
    postToDB(dbHandler, boost::bind(&ReportLineHandler::afterDb, this, dbHandler));
    
}

void ReportLineHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void ReportLineHandler::afterDb(DBReportLineHandler* db)
{
    //添加成功发广播
    if (db->Type == DBReportLineHandlerType::Add || db->Type == DBReportLineHandlerType::Update || db->Type == DBReportLineHandlerType::Remove)
    {
        if (db->Result == "OK")
        {
            AddUserLay l_userlay;
            l_userlay.set_id(db->ID.toStdString());
            l_userlay.set_pic("ReportLine");
            l_userlay.set_drawman(db->DrawMan.toStdString());
            switch (db->Type)
            {
            case DBReportLineHandlerType::Add:
                l_userlay.set_type("create");
                break;
            case DBReportLineHandlerType::Update:
                l_userlay.set_type("change");
                break;
            case DBReportLineHandlerType::Remove:
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
    delete this;
}

void ReportLineHandler::UpdateFunction(ReportLineRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pReportLineMap;
    if (p.contains(msg.id().c_str()))
    {
        auto &l_layer = p[msg.id().c_str()];
        l_layer.m_Polygon.clear();
        for (int i = 0; i < msg.point_size(); i++)
        {
            hg::utils::PointLL l_pointLL;
            l_pointLL.setLat(msg.point(i).lat());
            l_pointLL.setLon(msg.point(i).lon());
            l_layer.m_Polygon.push_back(l_pointLL);
        }
        l_layer.m_Name = msg.name().c_str();
        l_layer.m_LineStyle = msg.linestyle();
        l_layer.m_FullStyle = msg.fullstyle();
        l_layer.m_LineWidth = msg.linewidth();
        l_layer.m_DrawMan = msg.drawman().c_str();
        l_layer.m_IsNew = msg.isshare();
        l_layer.m_LineColor = msg.linecolor().c_str(); 
        l_layer.m_FullColor = msg.fullcolor().c_str(); 
    }
    else
    {
        hgReportLineLayer l_layer;
        for (int i = 0; i < msg.point_size(); i++)
        {
            hg::utils::PointLL l_pointLL;
            l_pointLL.setLat(msg.point(i).lat());
            l_pointLL.setLon(msg.point(i).lon());
            l_layer.m_Polygon.push_back(l_pointLL);
        }
        l_layer.m_Name = msg.name().c_str();
        l_layer.m_LineStyle = msg.linestyle();
        l_layer.m_FullStyle = msg.fullstyle();
        l_layer.m_LineWidth = msg.linewidth();
        l_layer.m_DrawMan = msg.drawman().c_str();
        l_layer.m_IsNew = msg.isshare();
        l_layer.m_LineColor = msg.linecolor().c_str(); 
        l_layer.m_FullColor = msg.fullcolor().c_str(); 
        p.insert(msg.id().c_str(), l_layer);
    }
}

void ReportLineHandler::RemoveFunction(ReportLineRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pReportLineMap;
    if (p.contains(msg.id().c_str()))
    {
        p.remove(msg.id().c_str());
    }
}

void ReportLineHandler::AllFunction(ReportLineRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pReportLineMap;
    ReportLineRepsone l_Respone;
    l_Respone.set_type(msg.type());
    for (auto l_Iter = p.begin(); l_Iter != p.end(); l_Iter++)
    {
        auto l_Layer = l_Iter.value();
        ReportLineRequest* l_Request = l_Respone.add_ploylines();
        for (int i = 0; i < l_Layer.m_Polygon.size(); i++)
        {
            PointMes* l_mes = l_Request->add_point();
            l_mes->set_lat(l_Layer.m_Polygon.at(i).lat());
            l_mes->set_lon(l_Layer.m_Polygon.at(i).lon());
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
    }
    hgSendManager::SendCurrentMessage("reportline",l_Respone,this->connection());
    //this->connection()->write("reportline",l_Respone);
}

void ReportLineHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
