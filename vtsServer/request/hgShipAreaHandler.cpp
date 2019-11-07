
#include "StdAfx.h"
#include "hgShipAreaHandler.h"

#include "message/hgShipArea.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgDataManager.h"

#include "Managers/hgSendManager.h"
hgShipAreaHandler::hgShipAreaHandler()
{

}

hgShipAreaHandler::~hgShipAreaHandler(void)
{
}

vtsRequestHandler::WorkMode hgShipAreaHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgShipAreaHandler::handle(boost::asio::const_buffer& data)
{
    hgShipArea msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    
    if (hgDataManager::m_ShipAreaMap.contains(msg.mmsi().c_str()))
    {
        hg::utils::PolygonLL l_PolygonLL;
        for (int i = 0; i < msg.point_size(); i++)
        {
            hg::utils::PointLL l_PointLL(msg.point(i).lon(),msg.point(i).lat());
            l_PolygonLL.push_back(l_PointLL);
        }
        hgDataManager::m_ShipAreaMap[msg.mmsi().c_str()] = l_PolygonLL;
    }
    else
    {
        hg::utils::PolygonLL l_PolygonLL;
        for (int i = 0; i < msg.point_size(); i++)
        {
            hg::utils::PointLL l_PointLL(msg.point(i).lon(),msg.point(i).lat());
            l_PolygonLL.push_back(l_PointLL);
        }
        hgDataManager::m_ShipAreaMap.insert(msg.mmsi().c_str(),l_PolygonLL);
    }

    delete this;
    return ;
}

void hgShipAreaHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}