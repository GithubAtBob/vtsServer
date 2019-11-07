
#include "StdAfx.h"
#include "hgAlgorWarMesHandler.h"

#include "message/hgAlgorWar.pb.h"
#include "frame/vtsServer.h"
#include "db/DBAlgorWarMesHandler.h"

#include "Managers/hgSendManager.h"

hgAlgorWarMesHandler::hgAlgorWarMesHandler()
{

}

hgAlgorWarMesHandler::~hgAlgorWarMesHandler(void)
{
}

vtsRequestHandler::WorkMode hgAlgorWarMesHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAlgorWarMesHandler::handle(boost::asio::const_buffer& data)
{
    hgAlgorWarMes msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));


    DBAlgorWarMesHandler *dbHandler = new DBAlgorWarMesHandler();
    dbHandler->AlgorWarMes = msg;
    postToDB(dbHandler, boost::bind(&hgAlgorWarMesHandler::afterDb, this, dbHandler));
}


void hgAlgorWarMesHandler::afterDb(DBAlgorWarMesHandler* db)
{
    hgSendManager::SendClientMessageUOwn("hgAlgorWarMes",db->AlgorWarMes,this->connection());
    //std::string l_name = db->AlgorWarMes.mmsi();
    //hgSendManager::SendSpecifyMessage("hgAlgorWarMes",db->AlgorWarMes,this->connection(),"g_"+l_name);
    //hgSendManager::SendShipMessage("hgAlgorWarMes",db->AlgorWarMes,this->connection());
    std::string l_channel = "g_" + db->AlgorWarMes.mmsi();
    hgSendManager::SendSpecifyMessage("hgAlgorWarMes",db->AlgorWarMes,this->connection(),l_channel);//发送到指定船端
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("hgAlgorWarMes",db->AlgorWarMes);
//             }
//     });
    delete db;
    delete this;
}

void hgAlgorWarMesHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
