
#include "StdAfx.h"
#include "hgRadarAskHandler.h"

#include "message/RadarImagePack.pb.h"
#include "frame/vtsServer.h"

#include "Managers/hgSendManager.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgDataManager.h"

hgRadarAskHandler::hgRadarAskHandler()
{

}

hgRadarAskHandler::~hgRadarAskHandler(void)
{
}

vtsRequestHandler::WorkMode hgRadarAskHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgRadarAskHandler::handle(boost::asio::const_buffer& data)
{
    RadarRequst msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));
    msg.set_name(this->connection()->channel());
    QString l_str = msg.mess().c_str();
    if (l_str.startsWith("info:tgt="))
    {
        QString l_MMSI = l_str.right(l_str.length()-9);
        QString l_ID = l_MMSI;
        bool l_type = false;
        if (hgTargetManager::m_mapAisRadar.contains(l_MMSI))
        {
            l_type = true;
            l_ID = hgTargetManager::m_mapAisRadar.find(l_MMSI).value();
        }
        msg.set_mess(QString("info:tgt=%1").arg(l_ID).toStdString());
        if (l_type == false)
        {
            delete this;
            return ;
        }
    }
    if (l_str.startsWith("view:show=1"))
    {
        QString l_x = l_str.section("&",1,1);
        l_x = l_x.right(8);
        QString l_y = l_str.section("&",2,2);
        l_y = l_y.right(8);
        double l_lat = l_y.toInt()/600000.;
        double l_lon = l_x.toInt()/600000.;
        RadarImageCenter l_center;
        l_center.lat = l_lat;
        l_center.lon = l_lon;
        hgDataManager::m_radarCenter.insert(this->connection()->channel().c_str(),l_center);
    }
    hgSendManager::SendSpecifyMessage("RadarAsk",msg,this->connection(),"s_RadarServer");
    //this->connection()->server().connectionManager().multicast("s_RadarServer","RadarAsk",msg);
    delete this;
    return ;
}

void hgRadarAskHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

// void hgRadarAskHandler::afterDb(DBWaringHandler* db)
// {
//     WaringRepsone result;
//     result.set_result(db->Result.toStdString());
//     result.set_type(db->Type);
//     responseAsync(result, boost::bind(&hgRadarAskHandler::afterResponse, this, boost::asio::placeholders::error));
//     delete db;
// }
// 
// void hgRadarAskHandler::afterResponse(const boost::system::error_code& e)
// {
//     delete this;
// }
