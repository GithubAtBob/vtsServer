
#include "StdAfx.h"
#include "hgAlgorTextHandler.h"
#include "db/DBAlgorTextHandler.h"

#include "message/hgAlgorText.pb.h"
#include "frame/vtsServer.h"

#include "Managers/hgSendManager.h"
#include "Managers/hgTargetManager.h"

hgAlgorTextHandler::hgAlgorTextHandler()
{

}

hgAlgorTextHandler::~hgAlgorTextHandler(void)
{
}

vtsRequestHandler::WorkMode hgAlgorTextHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAlgorTextHandler::handle(boost::asio::const_buffer& data)
{
    hgAlgorText msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));


    time_t a = hgTargetManager::GetWarnTime();
    DBAlgorTextHandler *dbHandler = new DBAlgorTextHandler();
    dbHandler->msg = msg;

    postToDB(dbHandler, boost::bind(&hgAlgorTextHandler::afterDb, this, dbHandler));
}

void hgAlgorTextHandler::timeout(time_t last)
{
}

void hgAlgorTextHandler::afterDb(DBAlgorTextHandler* db)
{

    hgSendManager::SendClientMessage("AlgorText",db->msg,this->connection());
    //     std::string l_name;
    //     if (msg.bown() == 1)
    //     {
    //         l_name =msg.tarmmsi();
    //     }
    //     else
    //     {
    //         l_name = msg.ownmmsi();
    //     }
    //    hgSendManager::SendSpecifyMessage("hgAlgorWarMes",db->AlgorWarMes,this->connection(),"g_"+l_name);
    hgSendManager::SendShipMessage("AlgorText",db->msg,this->connection());
    //     this->connection()->server().connectionManager().for_each
    //         ([&](ConnectionPtr p){
    //             if (p != this->connection())//自己不要发送
    //             {
    //                 p->write("AlgorText",msg);
    //             }
    //     });
    delete db;
    delete this;
}

