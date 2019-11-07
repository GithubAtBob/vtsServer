
#include "StdAfx.h"
#include "DutyAreaHandler.h"

#include "message/DutyArea.pb.h"
#include "message/adduserlay.pb.h"
#include "frame/vtsServer.h"
#include "db/DBDutyAreaHandler.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

vtsDECLARE_REQUEST_HANDLER("dutyarea", DutyAreaHandler);

DutyAreaHandler::DutyAreaHandler()
{

}

DutyAreaHandler::~DutyAreaHandler(void)
{
}

vtsRequestHandler::WorkMode DutyAreaHandler::workMode()
{
    return Work_Delete_Manual;
}

void DutyAreaHandler::handle(boost::asio::const_buffer& data)
{
    DutyAreaRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBDutyAreaHandler *dbHandler = new DBDutyAreaHandler();
    dbHandler->Type = msg.type();
    dbHandler->ID = msg.id().c_str();
    dbHandler->Name = msg.name().c_str();
    dbHandler->Point = msg.point();
    dbHandler->LineStyle = msg.linestyle();
    dbHandler->FullStyle = msg.fullstyle();
    dbHandler->LineWidth = msg.linewidth();
    dbHandler->DutyMan = msg.dutyman().c_str();
    dbHandler->DrawMan = msg.drawman().c_str();
    dbHandler->IsShare = msg.isshare();
    dbHandler->LineColor = msg.linecolor().c_str();
    dbHandler->FullColor = msg.fullcolor().c_str();
    switch (msg.type())
    {
    case DBDutyAreaHandlerType::Add:
    case DBDutyAreaHandlerType::Update:
        UpdateFunction(msg);
        break;
    case DBDutyAreaHandlerType::Remove:
        RemoveFunction(msg);
        break;
    case DBDutyAreaHandlerType::All:
        AllFunction(msg);
        delete dbHandler;
        delete this;
        return ;
        break;
    }
    postToDB(dbHandler, boost::bind(&DutyAreaHandler::afterDb, this, dbHandler));
    
}

void DutyAreaHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void DutyAreaHandler::afterDb(DBDutyAreaHandler* db)
{
    //添加成功发广播
    if (db->Type == DBDutyAreaHandlerType::Add || db->Type == DBDutyAreaHandlerType::Update || db->Type == DBDutyAreaHandlerType::Remove)
    {
        if (db->Type == DBDutyAreaHandlerType::Add && db->Result == "OK")
        {
            AddUserLay l_userlay;
            l_userlay.set_id(db->ID.toStdString());
            l_userlay.set_pic("DutyArea");
            l_userlay.set_drawman(db->DrawMan.toStdString());
            switch (db->Type)
            {
            case DBDutyAreaHandlerType::Add:
                l_userlay.set_type("create");
                break;
            case DBDutyAreaHandlerType::Update:
                l_userlay.set_type("change");
                break;
            case DBDutyAreaHandlerType::Remove:
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

void DutyAreaHandler::UpdateFunction(DutyAreaRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pDutyAreaMap;
    if (p.contains(msg.id().c_str()))
    {
        auto &l_layer = p[msg.id().c_str()];
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
        l_layer.m_DutyMan = msg.dutyman().c_str();
        l_layer.m_IsNew = msg.isshare();
        l_layer.m_LineColor = msg.linecolor().c_str(); 
        l_layer.m_FullColor = msg.fullcolor().c_str(); 
    }
    else
    {
        hgDutyAreaLayer l_layer;
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
        l_layer.m_DutyMan = msg.dutyman().c_str();
        l_layer.m_IsNew = msg.isshare();
        l_layer.m_LineColor = msg.linecolor().c_str(); 
        l_layer.m_FullColor = msg.fullcolor().c_str(); 
        p.insert(msg.id().c_str(), l_layer);
    }
}

void DutyAreaHandler::RemoveFunction(DutyAreaRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pDutyAreaMap;
    if (p.contains(msg.id().c_str()))
    {
        p.remove(msg.id().c_str());
    }
}

void DutyAreaHandler::AllFunction(DutyAreaRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pDutyAreaMap;
    DutyAreaRepsone l_Respone;
    l_Respone.set_type(msg.type());
    for (auto l_Iter = p.begin(); l_Iter != p.end(); l_Iter++)
    {
        auto l_Layer = l_Iter.value();
        DutyAreaRequest* l_Request = l_Respone.add_dutyareas();
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
        l_Request->set_dutyman(l_Layer.m_DutyMan.toStdString());
        l_Request->set_drawman(l_Layer.m_DrawMan.toStdString());
        l_Request->set_isshare(l_Layer.m_IsNew);
        l_Request->set_linecolor(l_Layer.m_LineColor.toStdString());
        l_Request->set_fullcolor(l_Layer.m_FullColor.toStdString());
    }

    hgSendManager::SendCurrentMessage("dutyarea",l_Respone,this->connection());
    //this->connection()->write("dutyarea",l_Respone);

}

void DutyAreaHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
