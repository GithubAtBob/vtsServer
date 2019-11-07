
#include "StdAfx.h"
#include "hgSetShipHandler.h"

#include "message/hgSetShip.pb.h"
#include "db/DBSetShipHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

hgSetShipHandler::hgSetShipHandler()
{

}

hgSetShipHandler::~hgSetShipHandler(void)
{
}

vtsRequestHandler::WorkMode hgSetShipHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgSetShipHandler::handle(boost::asio::const_buffer& data)
{
    //hgSetShip msg;

    //msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    ////msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    //mymap<QString,hgTarget>::iterator l_it;
    //l_it = hgTargetManager::m_mapTarget.find(QString::fromStdString(msg.mmsi()));
    //if (hgTargetManager::m_mapTarget.find(QString::fromStdString(msg.mmsi())) != hgTargetManager::m_mapTarget.end())
    //{
    //    QString a = QString::fromStdString(msg.shiptype());
    //    l_it->ShipType = QString::fromStdString(msg.shiptype());
    //    l_it->DimA = msg.shiplength()/2;
    //    l_it->DimB = msg.shiplength()/2;
    //    l_it->DimC = msg.shipwidth()/2;
    //    l_it->DimD = msg.shipwidth()/2;
    //}
    //auto l_lockerAis = hgTargetManager::getMapAisLocker();
    //auto &l_mapAis = l_lockerAis->raw();
    //l_it = l_mapAis.find(QString::fromStdString(msg.mmsi()));
    //if (l_mapAis.find(QString::fromStdString(msg.mmsi())) != l_mapAis.end())
    //{
    //    l_it->ShipType = QString::fromStdString(msg.shiptype());
    //    l_it->DimA = msg.shiplength()/2;
    //    l_it->DimB = msg.shiplength()/2;
    //    l_it->DimC = msg.shipwidth()/2;
    //    l_it->DimD = msg.shipwidth()/2;
    //}
    //auto l_lockerSim = hgTargetManager::getMapRadarLocker();
    //auto &l_mapSim = l_lockerSim->raw();
    //l_it = l_mapSim.find(QString::fromStdString(msg.mmsi()));
    //if (l_mapSim.find(QString::fromStdString(msg.mmsi())) != l_mapSim.end())
    //{
    //    l_it->ShipType = QString::fromStdString(msg.shiptype());
    //    l_it->DimA = msg.shiplength()/2;
    //    l_it->DimB = msg.shiplength()/2;
    //    l_it->DimC = msg.shipwidth()/2;
    //    l_it->DimD = msg.shipwidth()/2;
    //}

    //DBSetShipHandler *dbHandler = new DBSetShipHandler();
    //dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    //dbHandler->b_SetShip = msg.setship();
    //dbHandler->ShipType = QString::fromStdString(msg.shiptype());
    //dbHandler->ShipLength = msg.shiplength();
    //dbHandler->ShipWidth = msg.shipwidth();


    //SetShip l_SetShip;
    //l_SetShip.TargetID = dbHandler->MMSI;
    //l_SetShip.b_SetShip = dbHandler->b_SetShip;
    //l_SetShip.ShipType = dbHandler->ShipType;
    //l_SetShip.Length = dbHandler->ShipLength;
    //l_SetShip.With = dbHandler->ShipWidth;
    //hgAlarmManager::m_WarningSetManager.SaveSetShip(l_SetShip);

    //postToDB(dbHandler, boost::bind(&hgSetShipHandler::afterDb, this, dbHandler));
    
}

void hgSetShipHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgSetShipHandler::afterDb(DBSetShipHandler* db)
{
    hgSetShip result;
    //添加成功发广播
    //if (db->Type == DBChannelHandlerType::Add && db->Result == "OK")
    {
        hgSetShip result;
        result.set_mmsi(db->MMSI.toStdString());
        result.set_setship(db->b_SetShip);
        result.set_shiptype(db->ShipType.toStdString());
        result.set_shiplength(db->ShipLength);
        result.set_shipwidth(db->ShipWidth);

        hgSendManager::SendClientMessage("ReportArea",result,this->connection());
//         this->connection()->server().connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 //if (p != this->connection())//自己不要发送
//                 {
//                     p->write("SetShip",result);
//                 }
//         });
    }
    delete db;
    delete this;
}

