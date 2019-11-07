
#include "StdAfx.h"
#include "AidSailHandler.h"

#include "message/aidsail.pb.h"
#include "message/adduserlay.pb.h"
#include "frame/vtsServer.h"
#include "db/DBAidSailHandler.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

vtsDECLARE_REQUEST_HANDLER("aidsail", AidSailHandler);

AidSailHandler::AidSailHandler()
{

}

AidSailHandler::~AidSailHandler(void)
{
}

vtsRequestHandler::WorkMode AidSailHandler::workMode()
{
    return Work_Delete_Manual;
}

void AidSailHandler::handle(boost::asio::const_buffer& data)
{
    AidSailRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBAidSailHandler *dbHandler = new DBAidSailHandler();
    dbHandler->Type = msg.type();
    dbHandler->ID = msg.id().c_str();
    dbHandler->Name = msg.name().c_str();
    dbHandler->Lat = msg.lat();
    dbHandler->Lon = msg.lon();
    dbHandler->Remarks = msg.remarks().c_str();
    dbHandler->IconURL = msg.iconurl().c_str();
    dbHandler->DrawMan = msg.drawman().c_str();
    dbHandler->IsShare = msg.isshare();
    switch (msg.type())
    {
    case DBAidSailHandlerType::Add:
    case DBAidSailHandlerType::Update:
        UpdateFunction(msg);
        break;
    case DBAidSailHandlerType::Remove:
        RemoveFunction(msg);
        break;
    case DBAidSailHandlerType::All:
        AllFunction(msg);
        delete dbHandler;
        delete this;
        return ;
        break;
    }
    postToDB(dbHandler, boost::bind(&AidSailHandler::afterDb, this, dbHandler));
    
}

void AidSailHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void AidSailHandler::afterDb(DBAidSailHandler* db)
{
    //添加成功发广播
    if (db->Type == DBAidSailHandlerType::Add || db->Type == DBAidSailHandlerType::Update || db->Type == DBAidSailHandlerType::Remove)
    {
        if (db->Type == DBAidSailHandlerType::Add && db->Result == "OK")
        {
            AddUserLay l_userlay;
            l_userlay.set_id(db->ID.toStdString());
            l_userlay.set_pic("AidSail");
            l_userlay.set_drawman(db->DrawMan.toStdString());
            switch (db->Type)
            {
            case DBAidSailHandlerType::Add:
                l_userlay.set_type("create");
                break;
            case DBAidSailHandlerType::Update:
                l_userlay.set_type("change");
                break;
            case DBAidSailHandlerType::Remove:
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
    delete this ;
}

void AidSailHandler::UpdateFunction(AidSailRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pAidSailMap;
    if (p.contains(msg.id().c_str()))
    {
        auto &l_layer = p[msg.id().c_str()];
        l_layer.m_Name = msg.name().c_str();
        l_layer.m_Lat = msg.lat();
        l_layer.m_Lon = msg.lon();
        l_layer.m_Remarks = msg.remarks().c_str();
        l_layer.m_IconURL = msg.iconurl().c_str(); 
        l_layer.m_DrawMan = msg.drawman().c_str();
        l_layer.m_IsNew = msg.isshare();
    }
    else
    {
        hgAidSailLayer l_layer;
        l_layer.m_Name = msg.name().c_str();
        l_layer.m_Lat = msg.lat();
        l_layer.m_Lon = msg.lon();
        l_layer.m_Remarks = msg.remarks().c_str();
        l_layer.m_IconURL = msg.iconurl().c_str(); 
        l_layer.m_DrawMan = msg.drawman().c_str();
        l_layer.m_IsNew = msg.isshare();
        p.insert(msg.id().c_str(), l_layer);
    }
}

void AidSailHandler::RemoveFunction(AidSailRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pAidSailMap;
    if (p.contains(msg.id().c_str()))
    {
        p.remove(msg.id().c_str());
    }
}

void AidSailHandler::AllFunction(AidSailRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pAidSailMap;
    AidSailRepsone l_Respone;
    l_Respone.set_type(msg.type());
    for (auto l_Iter = p.begin(); l_Iter != p.end(); l_Iter++)
    {
        auto l_Layer = l_Iter.value();
        AidSailRequest* l_Request = l_Respone.add_aidsails();
        l_Request->set_type(msg.type());
        l_Request->set_id(l_Iter.key().toStdString());
        l_Request->set_name(l_Layer.m_Name.toStdString());
        l_Request->set_lat(l_Layer.m_Lat);
        l_Request->set_lon(l_Layer.m_Lon);
        l_Request->set_remarks(l_Layer.m_Remarks.toStdString());
        l_Request->set_iconurl(l_Layer.m_IconURL.toStdString());
        l_Request->set_drawman(l_Layer.m_DrawMan.toStdString());
        l_Request->set_isshare(l_Layer.m_IsNew);
    }
    hgSendManager::SendCurrentMessage("aidsail",l_Respone,this->connection());
    //this->connection()->write("aidsail",l_Respone);
}

void AidSailHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
