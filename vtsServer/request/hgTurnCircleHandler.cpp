
#include "StdAfx.h"
#include "hgTurnCircleHandler.h"

#include "message/hgTurnCircle.pb.h"
#include "db/DBTurnCircleHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgTurnCircleTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
hgTurnCircleHandler::hgTurnCircleHandler()
{

}

hgTurnCircleHandler::~hgTurnCircleHandler(void)
{
}

vtsRequestHandler::WorkMode hgTurnCircleHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgTurnCircleHandler::handle(boost::asio::const_buffer& data)
{
    hgTurnCircle msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));


    hgAlarmManager::StartWarning("TurnCircle",WarningTurnCircle,this);

    DBTurnCircleHandler *dbHandler = new DBTurnCircleHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_TurnCircle = msg.turncircle();
    dbHandler->TurnRadius = msg.radius();
    dbHandler->TurnLat = msg.lat();
    dbHandler->TurnLon = msg.lon();

    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsTurnCircle);

    postToDB(dbHandler, boost::bind(&hgTurnCircleHandler::afterDb, this, dbHandler));
    
}


void hgTurnCircleHandler::afterDb(DBTurnCircleHandler* db)
{
    TurnCircle l_TurnCircle;
    l_TurnCircle.TargetID = db->MMSI;
    l_TurnCircle.b_TurnCircle = db->b_TurnCircle;
    l_TurnCircle.TurnRadius = db->TurnRadius;
    l_TurnCircle.TurnLat = db->TurnLat;
    l_TurnCircle.TurnLon = db->TurnLon;
    hgAlarmManager::m_WarningSetManager.SaveTurnCircle(l_TurnCircle);

    hgTurnCircle result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_turncircle(db->b_TurnCircle);
    result.set_radius(db->TurnRadius);
    result.set_lat(db->TurnLat);
    result.set_lon(db->TurnLon);
    hgSendManager::SendClientMessageUOwn("TurnCircle",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("TurnCircle",result);
//             }
//     });
    delete db;
    delete this;
}


