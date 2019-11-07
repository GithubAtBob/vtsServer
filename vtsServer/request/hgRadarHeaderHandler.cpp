
#include "StdAfx.h"
#include "hgRadarHeaderHandler.h"

#include "message/RadarImagePack.pb.h"
#include "frame/vtsServer.h"

#include "Managers/hgSendManager.h"
#include "Managers/hgConfigManager.h"
#include "timer/hgPortTimerHandler.h"

hgRadarHeaderHandler::hgRadarHeaderHandler()
{

}

hgRadarHeaderHandler::~hgRadarHeaderHandler(void)
{
}

vtsRequestHandler::WorkMode hgRadarHeaderHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgRadarHeaderHandler::handle(boost::asio::const_buffer& data)
{
    if (hgConfigManager::m_sSysConfig->m_radarServer != TurnOn)
    {
        delete this;
        return;
    }

    RadarHeader msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));
    //msg.set_name(this->connection()->channel());
    //this->connection()->server().connectionManager().multicast(msg.clientname(),"RadarHeader",msg);
    hgSendManager::SendClientMessage("RadarHeader",msg,this->connection());
    //this->connection()->server().connectionManager().broadcast("RadarHeader",msg);
    delete this;
    return ;
}

void hgRadarHeaderHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

// void hgRadarHeaderHandler::afterDb(DBWaringHandler* db)
// {
//     WaringRepsone result;
//     result.set_result(db->Result.toStdString());
//     result.set_type(db->Type);
//     responseAsync(result, boost::bind(&hgRadarHeaderHandler::afterResponse, this, boost::asio::placeholders::error));
//     delete db;
// }
// 
// void hgRadarHeaderHandler::afterResponse(const boost::system::error_code& e)
// {
//     delete this;
// }
