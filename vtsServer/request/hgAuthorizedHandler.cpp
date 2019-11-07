
#include "StdAfx.h"
#include "hgAuthorizedHandler.h"

#include "message/hgDomain.pb.h"
#include "db/DBAuthorizedHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

hgAuthorizedHandler::hgAuthorizedHandler()
{

}

hgAuthorizedHandler::~hgAuthorizedHandler(void)
{
}

vtsRequestHandler::WorkMode hgAuthorizedHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAuthorizedHandler::handle(boost::asio::const_buffer& data)
{
    hgDomain msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));


    DBAuthorizedHandler *dbHandler = new DBAuthorizedHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->Authorize = msg.domainwatch();



    postToDB(dbHandler, boost::bind(&hgAuthorizedHandler::afterDb, this, dbHandler));
    
}


void hgAuthorizedHandler::afterDb(DBAuthorizedHandler* db)
{
    Authorized l_Authorized;
    l_Authorized.TargetID = db->MMSI;
    l_Authorized.Authorize = db->Authorize;
    hgAlarmManager::m_WarningSetManager.SaveAuthorized(l_Authorized);

    hgAuthorized result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_authorized(db->Authorize);
    hgSendManager::SendClientMessageUOwn("Authorized",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("Authorized",result);
//             }
//     });
    
    delete db;
    delete this;
}


