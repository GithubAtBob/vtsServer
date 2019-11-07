
#include "StdAfx.h"
#include "hgAnchorAreaHandler.h"

#include "message/hgAnchorAreaMes.pb.h"
#include "db/DBAnchorAreaHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgAnchorAreaTimerHandler.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"

hgAnchorAreaHandler::hgAnchorAreaHandler()
{

}

hgAnchorAreaHandler::~hgAnchorAreaHandler(void)
{
}

vtsRequestHandler::WorkMode hgAnchorAreaHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAnchorAreaHandler::handle(boost::asio::const_buffer& data)
{
    //return;
    hgAnchorAreaMes msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgAlarmManager::StartWarning("AnchorArea",WarningAnchorArea,this);


    DBAnchorAreaHandler *dbHandler = new DBAnchorAreaHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_AnchorArea = msg.anchorarea();
    dbHandler->ID = QString::fromStdString(msg.id());
    dbHandler->Type = msg.type();


    hgAlarmManager::m_WarningSetManager.SetWarnInfo(dbHandler->MMSI,IsAnchorArea);

    postToDB(dbHandler, boost::bind(&hgAnchorAreaHandler::afterDb, this, dbHandler));
    
}



void hgAnchorAreaHandler::afterDb(DBAnchorAreaHandler* db)
{
    AnchorArea l_AnchorArea;
    l_AnchorArea.TargetID = db->MMSI;
    l_AnchorArea.b_AnchorArea = db->b_AnchorArea;
    l_AnchorArea.ID = db->ID;
    l_AnchorArea.Type = db->Type;
    hgAlarmManager::m_WarningSetManager.SaveAnchorArea(l_AnchorArea);
 
    hgAnchorAreaMes result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_anchorarea(db->b_AnchorArea);
    result.set_id(db->ID.toStdString());
    result.set_type(db->Type);
    //result.set_authorized(db->Authorize);
    hgSendManager::SendClientMessageUOwn("AnchorArea",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("AnchorArea",result);
//             }
//     });

    delete db;
    delete this;
}


