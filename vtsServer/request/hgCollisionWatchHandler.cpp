
#include "StdAfx.h"
#include "hgCollisionWatchHandler.h"

#include "message/hgCollisionWatch.pb.h"
#include "db/DBCollisionWatchHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgCollisionWatchTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"
#include "Config/hgCPAConfig.h"
#include "Managers/hgConfigManager.h"

#include "Managers/hgSendManager.h"
hgCollisionWatchHandler::hgCollisionWatchHandler()
{

}

hgCollisionWatchHandler::~hgCollisionWatchHandler(void)
{
}

vtsRequestHandler::WorkMode hgCollisionWatchHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgCollisionWatchHandler::handle(boost::asio::const_buffer& data)
{
    hgCollisionWatch msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    if (msg.type() == CPArecord)
    {
        hgCollisionWatch result;
        mymap<QString,hgTarget>::iterator l_itAis;
        QMap<QString,CollisionWatch>::iterator l_itCollisionWatch;
        QMap<QString,ShipCPAData>::iterator l_itDayCPA; //m_DayCPAMap;
        switch (msg.getcpa())
        {
        case Custom:
            l_itCollisionWatch = hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.find(QString::fromStdString(msg.mmsi()));
            if (l_itCollisionWatch != hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.end())
            {
                result.set_dcpa(l_itCollisionWatch->CustomDCPA);
                result.set_tcpa(l_itCollisionWatch->CustomTCPA);
            } 
            else
            {
                result.set_dcpa(0);
                result.set_tcpa(0);
            }
            break;
        case DayDefault:
            result.set_dcpa(hgConfigManager::m_sSysConfig->m_dayCPA);
            result.set_tcpa(hgConfigManager::m_sSysConfig->m_dayTCPA);
            break;
        case DayShipType:
            l_itAis = hgTargetManager::m_mapTarget.find(QString::fromStdString(msg.mmsi()));
            if (l_itAis != hgTargetManager::m_mapTarget.end())
            {
                l_itDayCPA = hgConfigManager::m_sCPAConfig->m_DayCPAMap.find(l_itAis->ShipType);
                if (l_itDayCPA != hgConfigManager::m_sCPAConfig->m_DayCPAMap.end())
                {
                    result.set_dcpa(l_itDayCPA->m_dDCPA);
                    result.set_tcpa(l_itDayCPA->m_dTCPA);
                } 
                else
                {
                    result.set_dcpa(hgConfigManager::m_sCPAConfig->m_DayCPAMap["Unknown"].m_dDCPA);
                    result.set_tcpa(hgConfigManager::m_sCPAConfig->m_DayCPAMap["Unknown"].m_dTCPA);
                }
            }
            break;
        case NightDefault:
            result.set_dcpa(hgConfigManager::m_sSysConfig->m_nightCPA);
            result.set_tcpa(hgConfigManager::m_sSysConfig->m_nightTCPA);
            break;
        case NightShipType:
            l_itAis = hgTargetManager::m_mapTarget.find(QString::fromStdString(msg.mmsi()));
            if (l_itAis != hgTargetManager::m_mapTarget.end())
            {
                l_itDayCPA = hgConfigManager::m_sCPAConfig->m_NightCPAMap.find(l_itAis->ShipType);
                if (l_itDayCPA != hgConfigManager::m_sCPAConfig->m_NightCPAMap.end())
                {
                    result.set_dcpa(l_itDayCPA->m_dDCPA);
                    result.set_tcpa(l_itDayCPA->m_dTCPA);
                } 
                else
                {
                    result.set_dcpa(hgConfigManager::m_sCPAConfig->m_NightCPAMap["Unknown"].m_dDCPA);
                    result.set_tcpa(hgConfigManager::m_sCPAConfig->m_NightCPAMap["Unknown"].m_dTCPA);
                }
            }
            break;
        }
        result.set_mmsi(msg.mmsi());
        result.set_collisionwatch(false);
        result.set_type(CPArecord);
        result.set_getcpa(msg.getcpa());
        response(result, boost::bind(&hgCollisionWatchHandler::afterResponse, this, boost::asio::placeholders::error));
    } 
    else
    {

        hgAlarmManager::StartWarning("CollisionWatch",WarningCollisionWatch,this);


        DBCollisionWatchHandler *dbHandler = new DBCollisionWatchHandler();
        dbHandler->MMSI = QString::fromStdString(msg.mmsi());
        dbHandler->b_CollisionWatch = msg.collisionwatch();
        dbHandler->DCPA = msg.dcpa();
        dbHandler->TCPA = msg.tcpa();
        dbHandler->Type = msg.type();
        if (dbHandler->Type == Custom)
        {
            dbHandler->CustomDCPA = msg.dcpa();
            dbHandler->CustomTCPA = msg.tcpa();
        }


        hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,OtherType);


        postToDB(dbHandler, boost::bind(&hgCollisionWatchHandler::afterDb, this, dbHandler));
    }


    hgTargetManager::m_mapTarget.UnLockAll();
}


void hgCollisionWatchHandler::afterDb(DBCollisionWatchHandler* db)
{
    CollisionWatch l_CollisionWatch;
    l_CollisionWatch.TargetID = db->MMSI;
    l_CollisionWatch.b_CollisionWatch = db->b_CollisionWatch;
    l_CollisionWatch.DCPA = db->DCPA;
    l_CollisionWatch.TCPA = db->TCPA;
    l_CollisionWatch.Type = db->Type;

    hgAlarmManager::m_WarningSetManager.SaveCollisionWatch(l_CollisionWatch);
    hgCollisionWatch result;
    result.set_type(db->Type);
    result.set_mmsi(db->MMSI.toStdString());
    result.set_collisionwatch(db->b_CollisionWatch);
    result.set_dcpa(db->DCPA);
    result.set_tcpa(db->TCPA);
    result.set_type(db->Type);
    hgSendManager::SendClientMessageUOwn("CollisionWatch",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("CollisionWatch",result);
//             }
//     });
  
    delete db;
    delete this;
}

void hgCollisionWatchHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}

