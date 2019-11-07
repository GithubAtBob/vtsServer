
#include "StdAfx.h"
#include "ChannelHandler.h"

#include "message/Channel.pb.h"
#include "message/adduserlay.pb.h"
#include "db/DBChannelHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

vtsDECLARE_REQUEST_HANDLER("channel", ChannelHandler);

ChannelHandler::ChannelHandler()
{

}

ChannelHandler::~ChannelHandler(void)
{
}

vtsRequestHandler::WorkMode ChannelHandler::workMode()
{
    return Work_Delete_Manual;
}

void ChannelHandler::handle(boost::asio::const_buffer& data)
{
    ChannelRequest msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    if (msg.type() == DBChannelHandlerType::Waring)
    {
        hgChannelTimerHandler * l_timer = new hgChannelTimerHandler(msg.id());
        l_timer->setDuration(1.0);
        this->setTimer(l_timer);
        //         delete this;
        return ;
    }

    DBChannelHandler *dbHandler = new DBChannelHandler();
    dbHandler->Type = msg.type();
    dbHandler->ID = msg.id().c_str();
    dbHandler->Name = msg.name().c_str();
    dbHandler->Annotation = msg.annotation().c_str();
    dbHandler->ChannelType = msg.channeltype();
    dbHandler->Width = msg.width();
    dbHandler->Channel = msg.channel();
    dbHandler->LineStyle = msg.linestyle();
    dbHandler->LineColor = msg.linecolor().c_str();
    dbHandler->WaringID = msg.waringid().c_str();
    dbHandler->WaringType = msg.waringtype().c_str();
    dbHandler->DrawMan = msg.drawman().c_str();
    dbHandler->IsShare = msg.isshare();
    dbHandler->Info = msg.info();
    switch (msg.type())
    {
    case DBChannelHandlerType::Add:
    case DBChannelHandlerType::Update:
        UpdateFunction(msg);
        break;
    case DBChannelHandlerType::Remove:
        RemoveFunction(msg);
        break;
    case DBChannelHandlerType::All:
        AllFunction(msg);
        delete dbHandler;
        delete this;
        return ;
        break;
    }
    postToDB(dbHandler, boost::bind(&ChannelHandler::afterDb, this, dbHandler));
    
}

void ChannelHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void ChannelHandler::afterDb(DBChannelHandler* db)
{
    //添加成功发广播
    if (db->Type == DBChannelHandlerType::Add || db->Type == DBChannelHandlerType::Update || db->Type == DBChannelHandlerType::Remove)
    {
        if (db->Result == "OK")
        {
            AddUserLay l_userlay;
            l_userlay.set_id(db->ID.toStdString());
            l_userlay.set_pic("Channel");
            l_userlay.set_drawman(db->DrawMan.toStdString());
            switch (db->Type)
            {
            case DBChannelHandlerType::Add:
                l_userlay.set_type("create");
                break;
            case DBChannelHandlerType::Update:
                l_userlay.set_type("change");
                break;
            case DBChannelHandlerType::Remove:
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

void ChannelHandler::UpdateFunction(ChannelRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pChannelMap;
    if (p.contains(msg.id().c_str()))
    {
        auto &l_layer = p[msg.id().c_str()];
        l_layer.m_AllPoint.clear();
        for (int i = 0; i < msg.channel_size(); i++)
        {
            ChannelWay l_ChannelWay = msg.channel(i);
            auto l_ChannelPoints = l_ChannelWay.point();
            hg::utils::PolygonLL l_Way;
            for ( int j = 0; j < l_ChannelPoints.size(); j++ )
            {
                hg::utils::PointLL l_poiLL;
                l_poiLL.setLat(l_ChannelPoints.Get(j).lat());
                l_poiLL.setLon(l_ChannelPoints.Get(j).lon());
                l_Way.push_back(l_poiLL);
            }
            l_layer.m_AllPoint.push_back(l_Way);
        }
        l_layer.m_Name = msg.name().c_str();
        l_layer.m_Annotation = msg.annotation().c_str();
        l_layer.m_ChannelType = msg.channeltype();
        l_layer.m_Width = msg.width(); 
        l_layer.m_LineStyle = msg.linestyle();
        l_layer.m_LineColor = msg.linecolor().c_str();
        l_layer.m_DrawMan = msg.drawman().c_str();
        l_layer.m_IsNew = msg.isshare();
        if (msg.info_size() > 0)
        {
            l_layer.m_Info = msg.info(0);
        }
    }
    else
    {
        hgChannelLayer l_layer;
        for (int i = 0; i < msg.channel_size(); i++)
        {
            ChannelWay l_ChannelWay = msg.channel(i);
            auto l_ChannelPoints = l_ChannelWay.point();
            hg::utils::PolygonLL l_Way;
            for ( int j = 0; j < l_ChannelPoints.size(); j++ )
            {
                hg::utils::PointLL l_poiLL;
                l_poiLL.setLat(l_ChannelPoints.Get(j).lat());
                l_poiLL.setLon(l_ChannelPoints.Get(j).lon());
                l_Way.push_back(l_poiLL);
            }
            l_layer.m_AllPoint.push_back(l_Way);
        }
        l_layer.m_Name = msg.name().c_str();
        l_layer.m_Annotation = msg.annotation().c_str();
        l_layer.m_ChannelType = msg.channeltype();
        l_layer.m_Width = msg.width(); 
        l_layer.m_LineStyle = msg.linestyle();
        l_layer.m_LineColor = msg.linecolor().c_str();
        l_layer.m_DrawMan = msg.drawman().c_str();
        l_layer.m_IsNew = msg.isshare();
        if (msg.info_size() > 0)
        {
            l_layer.m_Info = msg.info(0);
        }
        p.insert(msg.id().c_str(), l_layer);
    }
}

void ChannelHandler::RemoveFunction(ChannelRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pChannelMap;
    if (p.contains(msg.id().c_str()))
    {
        p.remove(msg.id().c_str());
    }
}

void ChannelHandler::AllFunction(ChannelRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pChannelMap;
    ChannelRepsone l_Respone;
    l_Respone.set_type(msg.type());
    for (auto l_Iter = p.begin(); l_Iter != p.end(); l_Iter++)
    {
        auto& l_Layer = l_Iter.value();
        ChannelRequest* l_Request = l_Respone.add_channels();
        for (int i = 0; i < l_Layer.m_AllPoint.size(); i++ )
        {
            auto l_Way = l_Layer.m_AllPoint.at(i);
            ChannelWay* l_ChannelWay = l_Request->add_channel();
            for (int j = 0; j < l_Way.size(); j++)
            {
                PointMes* l_mes = l_ChannelWay->add_point();
                l_mes->set_lat(l_Way.at(j).lat());
                l_mes->set_lon(l_Way.at(j).lon());
            }
        }
        l_Request->set_type(msg.type());
        l_Request->set_id(l_Iter.key().toStdString());
        l_Request->set_name(l_Layer.m_Name.toStdString());
        l_Request->set_annotation(l_Layer.m_Annotation.toStdString());
        l_Request->set_channeltype(l_Layer.m_ChannelType);
        l_Request->set_width(l_Layer.m_Width);
        l_Request->set_linestyle(l_Layer.m_LineStyle);
        l_Request->set_linecolor(l_Layer.m_LineColor.toStdString());
        l_Request->set_waringid("");
        l_Request->set_waringtype("");
        l_Request->set_drawman(l_Layer.m_DrawMan.toStdString());
        l_Request->set_isshare(l_Layer.m_IsNew);
        ChannelWarInfo* l_info = l_Request->add_info();
        l_info->set_depth(l_Layer.m_Info.depth());
        l_info->set_minborder(l_Layer.m_Info.minborder());
        l_info->set_maxborder(l_Layer.m_Info.maxborder());
        l_info->set_minangle(l_Layer.m_Info.minangle());
        l_info->set_maxangle(l_Layer.m_Info.maxangle());
        l_info->set_maxlong(l_Layer.m_Info.maxlong());
        l_info->set_entertype(l_Layer.m_Info.entertype());
        l_info->set_fcourse(l_Layer.m_Info.fcourse());
        l_info->set_fangle(l_Layer.m_Info.fangle());
        l_info->set_fminspeed(l_Layer.m_Info.fminspeed());
        l_info->set_fmaxspeed(l_Layer.m_Info.fmaxspeed());
        l_info->set_fminspeedtime(l_Layer.m_Info.fminspeedtime());
        l_info->set_fmaxspeedtime(l_Layer.m_Info.fmaxspeedtime());
        l_info->set_fendist(l_Layer.m_Info.fendist());
        l_info->set_fdisendist(l_Layer.m_Info.fdisendist());
        l_info->set_fsailendist(l_Layer.m_Info.fsailendist());
        l_info->set_bcourse(l_Layer.m_Info.bcourse());
        l_info->set_bangle(l_Layer.m_Info.bangle());
        l_info->set_bminspeed(l_Layer.m_Info.bminspeed());
        l_info->set_bmaxspeed(l_Layer.m_Info.bmaxspeed());
        l_info->set_bminspeedtime(l_Layer.m_Info.bminspeedtime());
        l_info->set_bmaxspeedtime(l_Layer.m_Info.bmaxspeedtime());
        l_info->set_bendist(l_Layer.m_Info.bendist());
        l_info->set_bdisendist(l_Layer.m_Info.bdisendist());
        l_info->set_bsailendist(l_Layer.m_Info.bsailendist());
    }
    hgSendManager::SendCurrentMessage("channel",l_Respone,this->connection());
    //this->connection()->write("channel",l_Respone);
}

void ChannelHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
