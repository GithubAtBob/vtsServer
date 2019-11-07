
#include "StdAfx.h"
#include "hgAnchorReservHandler.h"

#include "message/hgAnchorReserv.pb.h"
#include "db/DBAnchorReservHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgAnchorReservTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgWarningSetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

hgAnchorReservHandler::hgAnchorReservHandler()
{

}

hgAnchorReservHandler::~hgAnchorReservHandler(void)
{
}

vtsRequestHandler::WorkMode hgAnchorReservHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAnchorReservHandler::handle(boost::asio::const_buffer& data)
{
    hgAnchorReserv msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgAlarmManager::StartWarning("AnchorReserv",WarningAnchorReserv,this);


    DBAnchorReservHandler *dbHandler = new DBAnchorReservHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_AnchorReserv = msg.anchorreserv();
    dbHandler->ID = QString::fromStdString(msg.id());
    dbHandler->Type = msg.type();
    dbHandler->ETA = msg.eta();
    dbHandler->ETD = msg.etd();
    dbHandler->Tracks = msg.tracks();


    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsAnchorReserv);

    postToDB(dbHandler, boost::bind(&hgAnchorReservHandler::afterDb, this, dbHandler));
    
}


void hgAnchorReservHandler::afterDb(DBAnchorReservHandler* db)
{
    AnchorReserv l_AnchorReserv;
    l_AnchorReserv.TargetID = db->MMSI;
    l_AnchorReserv.b_AnchorReserv = db->b_AnchorReserv;
    l_AnchorReserv.ID = db->ID;
    l_AnchorReserv.Type = db->Type;
    l_AnchorReserv.ETA = db->ETA;
    l_AnchorReserv.ETD = db->ETD;
    l_AnchorReserv.Tracks = db->Tracks;
    hgAlarmManager::m_WarningSetManager.SaveAnchorReserv(l_AnchorReserv);
    
    hgAnchorReserv result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_anchorreserv(db->b_AnchorReserv);
    result.set_id(db->ID.toStdString());
    result.set_type(db->Type);
    result.set_eta(db->ETA);
    result.set_etd(db->ETD);
    result.set_tracks(hgAlarmManager::CurrentsTracks(db->ID,db->ETA,db->ETD));
    hgSendManager::SendClientMessageUOwn("AnchorReserv",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             //if (p != this->connection())//自己不要发送
//             {
//                 p->write("AnchorReserv",result);
//             }
//     });  
    delete db;
    delete this;
}

