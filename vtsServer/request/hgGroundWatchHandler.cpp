
#include "StdAfx.h"
#include "hgGroundWatchHandler.h"

#include "message/hgGroundWatch.pb.h"
#include "db/DBGroundWatchHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgGroundWatchTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
hgGroundWatchHandler::hgGroundWatchHandler()
{

}

hgGroundWatchHandler::~hgGroundWatchHandler(void)
{
}

vtsRequestHandler::WorkMode hgGroundWatchHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgGroundWatchHandler::handle(boost::asio::const_buffer& data)
{

    hgGroundWatch msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgAlarmManager::StartWarning("GroundWatch",WarningGroundWatch,this);


    DBGroundWatchHandler *dbHandler = new DBGroundWatchHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_GroundWatch = msg.groundwatch();
    dbHandler->GroundDraught = msg.grounddraught();
    dbHandler->KeelClearance = msg.keelclearance();



    postToDB(dbHandler, boost::bind(&hgGroundWatchHandler::afterDb, this, dbHandler));
    
}


void hgGroundWatchHandler::afterDb(DBGroundWatchHandler* db)
{
    GroundWatch l_GroundWatch;
    l_GroundWatch.TargetID = db->MMSI;
    l_GroundWatch.b_GroundWatch = db->b_GroundWatch;
    l_GroundWatch.GroundDraught = db->GroundDraught;
    l_GroundWatch.KeelClearance = db->KeelClearance;
    hgAlarmManager::m_WarningSetManager.SaveGroundWatch(l_GroundWatch);

    hgGroundWatch result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_groundwatch(db->b_GroundWatch);
    result.set_grounddraught(db->GroundDraught);
    result.set_keelclearance(db->KeelClearance);

    hgSendManager::SendClientMessageUOwn("GroundWatch",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("GroundWatch",result);
//             }
//     });

    delete db;
    delete this;
}


