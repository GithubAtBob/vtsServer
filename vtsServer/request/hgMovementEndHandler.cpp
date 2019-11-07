
#include "StdAfx.h"
#include "hgMovementEndHandler.h"

#include "message/hgMovementEnd.pb.h"
#include "db/DBMovementEndHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgMovementEndTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
hgMovementEndHandler::hgMovementEndHandler()
{
}

hgMovementEndHandler::~hgMovementEndHandler(void)
{
}

vtsRequestHandler::WorkMode hgMovementEndHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgMovementEndHandler::handle(boost::asio::const_buffer& data)
{
    hgMovementEnd msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgAlarmManager::StartWarning("MovementEnd",WarningMovementEnd,this);

    DBMovementEndHandler *dbHandler = new DBMovementEndHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_MovementEnd = msg.movementend();
    dbHandler->EndTime = msg.time();

    {
        mymap<QString,hgTarget>::iterator l_it;
        l_it = hgTargetManager::m_mapTarget.find(dbHandler->MMSI);
        if (l_it != hgTargetManager::m_mapTarget.end())
        {
            dbHandler->EndLat = l_it->Lat;
            dbHandler->EndLon = l_it->Lon;
        }

        hgTargetManager::m_mapTarget.UnLockAll();
    }


    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsMovementEnd);

    postToDB(dbHandler, boost::bind(&hgMovementEndHandler::afterDb, this, dbHandler));
}



void hgMovementEndHandler::afterDb(DBMovementEndHandler* db)
{
    MovementEnd l_MovementEnd;
    l_MovementEnd.TargetID = db->MMSI;
    l_MovementEnd.b_MovementEnd = db->b_MovementEnd;
    l_MovementEnd.EndTime = db->EndTime;
    l_MovementEnd.EndLat = db->EndLat;
    l_MovementEnd.EndLon = db->EndLon;
    hgAlarmManager::m_WarningSetManager.SaveMovementEnd(l_MovementEnd);

    hgMovementEnd result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_movementend(db->b_MovementEnd);
    result.set_time(db->EndTime);
    hgSendManager::SendClientMessageUOwn("MovementEnd",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("MovementEnd",result);
//             }
//     });
    delete db;
    delete this;
}


