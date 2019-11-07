
#include "StdAfx.h"
#include "NotesHandler.h"

#include "message/Notes.pb.h"
#include "message/adduserlay.pb.h"
#include "frame/vtsServer.h"
#include "db/DBNotesHandler.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

NotesHandler::NotesHandler()
{

}

NotesHandler::~NotesHandler(void)
{
}

vtsRequestHandler::WorkMode NotesHandler::workMode()
{
    return Work_Delete_Manual;
}

void NotesHandler::handle(boost::asio::const_buffer& data)
{
    NotesRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBNotesHandler *dbHandler = new DBNotesHandler();
    dbHandler->Type = msg.type();
    dbHandler->ID = msg.id().c_str();
    dbHandler->Name = msg.name().c_str();
    dbHandler->Lat = msg.lat();
    dbHandler->Lon = msg.lon();
    dbHandler->Notes = msg.notes().c_str();
    dbHandler->Color = msg.color().c_str();
    dbHandler->DrawMan = msg.drawman().c_str();
    dbHandler->IsShare = msg.isshare();
    switch (msg.type())
    {
    case DBNotesHandlerType::Add:
    case DBNotesHandlerType::Update:
        UpdateFunction(msg);
        break;
    case DBNotesHandlerType::Remove:
        RemoveFunction(msg);
        break;
    case DBNotesHandlerType::All:
        AllFunction(msg);
        delete this;
        return ;
        break;
    }
    postToDB(dbHandler, boost::bind(&NotesHandler::afterDb, this, dbHandler));
    
}

void NotesHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void NotesHandler::afterDb(DBNotesHandler* db)
{
    //添加成功发广播
    if (db->Type == DBNotesHandlerType::Add || db->Type == DBNotesHandlerType::Update || db->Type == DBNotesHandlerType::Remove)
    {
        if (db->Result == "OK")
        {
            AddUserLay l_userlay;
            l_userlay.set_id(db->ID.toStdString());
            l_userlay.set_pic("Notes");
            l_userlay.set_drawman(db->DrawMan.toStdString());
            switch (db->Type)
            {
            case DBNotesHandlerType::Add:
                l_userlay.set_type("create");
                break;
            case DBNotesHandlerType::Update:
                l_userlay.set_type("change");
                break;
            case DBNotesHandlerType::Remove:
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

void NotesHandler::UpdateFunction(NotesRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pNotesMap;
    if (p.contains(msg.id().c_str()))
    {
        auto &l_layer = p[msg.id().c_str()];
        l_layer.m_Name = msg.name().c_str();
        l_layer.m_Lat = msg.lat();
        l_layer.m_Lon = msg.lon();
        l_layer.m_Notes = msg.notes().c_str();
        l_layer.m_Color = msg.color().c_str(); 
        l_layer.m_DrawMan = msg.drawman().c_str();
        l_layer.m_IsNew = msg.isshare();
    }
    else
    {
        hgNotesLayer l_layer;
        l_layer.m_Name = msg.name().c_str();
        l_layer.m_Lat = msg.lat();
        l_layer.m_Lon = msg.lon();
        l_layer.m_Notes = msg.notes().c_str();
        l_layer.m_Color = msg.color().c_str(); 
        l_layer.m_DrawMan = msg.drawman().c_str();
        l_layer.m_IsNew = msg.isshare();
        p.insert(msg.id().c_str(), l_layer);
    }
}

void NotesHandler::RemoveFunction(NotesRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pNotesMap;
    if (p.contains(msg.id().c_str()))
    {
        p.remove(msg.id().c_str());
    }
}

void NotesHandler::AllFunction(NotesRequest msg)
{
    auto &p = hgAlarmManager::m_LayerDataManager.m_pNotesMap;
    NotesRepsone l_Respone;
    l_Respone.set_type(msg.type());
    for (auto l_Iter = p.begin(); l_Iter != p.end(); l_Iter++)
    {
        auto l_Layer = l_Iter.value();
        NotesRequest* l_Request = l_Respone.add_notess();
        l_Request->set_type(msg.type());
        l_Request->set_id(l_Iter.key().toStdString());
        l_Request->set_name(l_Layer.m_Name.toStdString());
        l_Request->set_lat(l_Layer.m_Lat);
        l_Request->set_lon(l_Layer.m_Lon);
        l_Request->set_notes(l_Layer.m_Notes.toStdString());
        l_Request->set_color(l_Layer.m_Color.toStdString());
        l_Request->set_drawman(l_Layer.m_DrawMan.toStdString());
        l_Request->set_isshare(l_Layer.m_IsNew);
    }
    hgSendManager::SendCurrentMessage("notes",l_Respone,this->connection());
    //this->connection()->write("notes",l_Respone);
}

void NotesHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
