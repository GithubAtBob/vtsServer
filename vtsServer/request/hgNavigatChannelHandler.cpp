
#include "StdAfx.h"
#include "hgNavigatChannelHandler.h"

#include "message/hgNavigatChannel.pb.h"
#include "db/DBNavigatChannelHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgNavigatChannelTimerHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
hgNavigatChannelHandler::hgNavigatChannelHandler()
{

}

hgNavigatChannelHandler::~hgNavigatChannelHandler(void)
{
}

vtsRequestHandler::WorkMode hgNavigatChannelHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgNavigatChannelHandler::handle(boost::asio::const_buffer& data)
{
    hgNavigatChannel msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgAlarmManager::StartWarning("NavigatChannel",WarningChannel,this);


    DBNavigatChannelHandler *dbHandler = new DBNavigatChannelHandler();
    dbHandler->MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->b_NavigatChannel = msg.channel();
    dbHandler->ID = QString::fromStdString(msg.id());
    dbHandler->Type = msg.type();


    NavigatChannel l_NavigatChannel;
    l_NavigatChannel.TargetID = dbHandler->MMSI;
    l_NavigatChannel.b_NavigatChannel = dbHandler->b_NavigatChannel;
    l_NavigatChannel.ID = dbHandler->ID;
    l_NavigatChannel.Type = dbHandler->Type;
    hgAlarmManager::m_WarningSetManager.SaveNavigatChannel(l_NavigatChannel);

    postToDB(dbHandler, boost::bind(&hgNavigatChannelHandler::afterDb, this, dbHandler));
    
}


void hgNavigatChannelHandler::afterDb(DBNavigatChannelHandler* db)
{

    hgNavigatChannel result;
    result.set_mmsi(db->MMSI.toStdString());
    result.set_mmsi(db->MMSI.toStdString());
    result.set_channel(db->b_NavigatChannel);
    result.set_id(db->ID.toStdString());
    result.set_type(db->Type);
    hgSendManager::SendClientMessageUOwn("NavigatChannel",result,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("NavigatChannel",result);
//             }
//     });
    
    delete db;
    delete this;
}

