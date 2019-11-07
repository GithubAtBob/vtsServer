
#include "StdAfx.h"
#include "hgAnchorWatchHandler.h"

#include "message/hgAnchorWatch.pb.h"
#include "db/DBAnchorWatchHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgAnchorWatchTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
hgAnchorWatchHandler::hgAnchorWatchHandler()
{

}

hgAnchorWatchHandler::~hgAnchorWatchHandler(void)
{
}

vtsRequestHandler::WorkMode hgAnchorWatchHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAnchorWatchHandler::handle(boost::asio::const_buffer& data)
{

    hgAnchorWatch msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgAlarmManager::StartWarning("AnchorWatch",WarningAnchorWatch,this);


    DBAnchorWatchHandler *dbHandler = new DBAnchorWatchHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_AnchorWatch = msg.anchorwatch();
    dbHandler->Clubbing = msg.clubbing();
    dbHandler->Dragging = msg.dragging();
    dbHandler->AnchorLat = msg.lat();
    dbHandler->AnchorLon = msg.lon(); 


    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsClubbing);
    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsDragging);

    postToDB(dbHandler, boost::bind(&hgAnchorWatchHandler::afterDb, this, dbHandler));
    
}


void hgAnchorWatchHandler::afterDb(DBAnchorWatchHandler* db)
{
    AnchorWatch l_AnchorWatch;
    l_AnchorWatch.TargetID = db->MMSI;
    l_AnchorWatch.b_AnchorWatch = db->b_AnchorWatch;
    l_AnchorWatch.Clubbing = db->Clubbing;
    l_AnchorWatch.Dragging = db->Dragging;
    l_AnchorWatch.AnchorLat = db->AnchorLat;
    l_AnchorWatch.AnchorLon = db->AnchorLon;
    hgAlarmManager::m_WarningSetManager.SaveAnchorWatch(l_AnchorWatch);

    hgAnchorWatch result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_anchorwatch(db->b_AnchorWatch);
    result.set_clubbing(db->Clubbing);
    result.set_dragging(db->Dragging);
    result.set_lat(db->AnchorLat);
    result.set_lon(db->AnchorLon);
    hgSendManager::SendClientMessageUOwn("AnchorWatch",result,this->connection());

//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("AnchorWatch",result);
//             }
//     });
    delete db;
    delete this;
}


