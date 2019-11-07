
#include "StdAfx.h"
#include "hgSpeedWatchHandler.h"

#include "message/hgSpeedWatch.pb.h"
#include "db/DBSpeedWatchHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgSpeedWatchTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
hgSpeedWatchHandler::hgSpeedWatchHandler()
{

}

hgSpeedWatchHandler::~hgSpeedWatchHandler(void)
{
}

vtsRequestHandler::WorkMode hgSpeedWatchHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgSpeedWatchHandler::handle(boost::asio::const_buffer& data)
{
    hgSpeedWatch msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));


    hgAlarmManager::StartWarning("SpeedWatch",WarningSpeed,this);

    DBSpeedWatchHandler *dbHandler = new DBSpeedWatchHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_SpeedWatch = msg.speedwatch();
    dbHandler->MinSpeed = msg.minspeed();
    dbHandler->MinDuration = msg.minduration();
    dbHandler->MaxSpeed = msg.maxspeed();
    dbHandler->MaxDuration = msg.maxduration();

    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsMinSpeed);
    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsMaxSpeed);

    postToDB(dbHandler, boost::bind(&hgSpeedWatchHandler::afterDb, this, dbHandler));
    
}



void hgSpeedWatchHandler::afterDb(DBSpeedWatchHandler* db)
{

    SpeedWatch l_SpeedWatch;
    l_SpeedWatch.TargetID = db->MMSI;
    l_SpeedWatch.b_SpeedWatch = db->b_SpeedWatch;
    l_SpeedWatch.MinSpeed = db->MinSpeed;
    l_SpeedWatch.MinDuration = db->MinDuration;
    l_SpeedWatch.MaxSpeed = db->MaxSpeed;
    l_SpeedWatch.MaxDuration = db->MaxDuration;
    l_SpeedWatch.MinTimeKeep = 0;
    l_SpeedWatch.MaxTimeKeep = 0;
    hgAlarmManager::m_WarningSetManager.SaveSpeedWatch(l_SpeedWatch);

    hgSpeedWatch result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_speedwatch(db->b_SpeedWatch);
    result.set_minspeed(db->MinSpeed);
    result.set_minduration(db->MinDuration);
    result.set_maxspeed(db->MaxSpeed);
    result.set_maxduration(db->MaxDuration);
    hgSendManager::SendClientMessageUOwn("ReportArea",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("SpeedWatch",result);
//             }
//     });
    delete db;
    delete this;
}


