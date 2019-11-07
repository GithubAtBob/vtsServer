
#include "StdAfx.h"
#include "hgBerthWatchHandler.h"

#include "message/hgBerthWatch.pb.h"
#include "db/DBBerthWatchHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgBerthWatchTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
hgBerthWatchHandler::hgBerthWatchHandler()
{

}

hgBerthWatchHandler::~hgBerthWatchHandler(void)
{
}

vtsRequestHandler::WorkMode hgBerthWatchHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgBerthWatchHandler::handle(boost::asio::const_buffer& data)
{
    hgBerthWatch msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgAlarmManager::StartWarning("BerthWatch",WarningBerthWatch,this);


    DBBerthWatchHandler *dbHandler = new DBBerthWatchHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_BerthWatch = msg.berthwatch();
    dbHandler->Distance = msg.distance();
    dbHandler->BerthLat = msg.lat();
    dbHandler->BerthLon = msg.lon();


    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsBerthWatch);

    postToDB(dbHandler, boost::bind(&hgBerthWatchHandler::afterDb, this, dbHandler));
    
}


void hgBerthWatchHandler::afterDb(DBBerthWatchHandler* db)
{
    BerthWatch l_BerthWatch;
    l_BerthWatch.TargetID = db->MMSI;
    l_BerthWatch.b_BerthWatch = db->b_BerthWatch;
    l_BerthWatch.Distance = db->Distance;
    l_BerthWatch.BerthLat = db->BerthLat;
    l_BerthWatch.BerthLon = db->BerthLon;
    hgAlarmManager::m_WarningSetManager.SaveBerthWatch(l_BerthWatch);

    hgBerthWatch result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_berthwatch(db->b_BerthWatch);
    result.set_distance(db->Distance);
    result.set_lat(db->BerthLat);
    result.set_lon(db->BerthLon);
    hgSendManager::SendClientMessageUOwn("BerthWatch",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("BerthWatch",result);
//             }
//     });

    delete db;
    delete this;
}


