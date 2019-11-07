
#include "StdAfx.h"
#include "hgShipHdgHandler.h"

#include "message/hgShipHdg.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgTargetManager.h"

vtsDECLARE_REQUEST_HANDLER("ShipHdg", hgShipHdgHandler);

hgShipHdgHandler::hgShipHdgHandler()
{

}

hgShipHdgHandler::~hgShipHdgHandler(void)
{
}

vtsRequestHandler::WorkMode hgShipHdgHandler::workMode()
{
    return Work_Delete_Auto;
}

void hgShipHdgHandler::handle(boost::asio::const_buffer& data)
{
    hgShipHdg msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

	hgTargetManager::m_GPSHdg[msg.mmsi().c_str()] = msg.type();
	qDebug() << msg.mmsi().c_str() << " hdg" << msg.type();
}

void hgShipHdgHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}