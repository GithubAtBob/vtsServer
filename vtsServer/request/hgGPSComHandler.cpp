#include "StdAfx.h"
#include "hgGPSComHandler.h"
#include "Managers/hgSendManager.h"
#include "message/hgGPSCom.pb.h"

vtsDECLARE_REQUEST_HANDLER("GPSCom", hgGPSComHandler);

hgGPSComHandler::hgGPSComHandler()
{

}

hgGPSComHandler::~hgGPSComHandler(void)
{
}

vtsRequestHandler::WorkMode hgGPSComHandler::workMode()
{
	return Work_Delete_Manual;
}

void hgGPSComHandler::handle(boost::asio::const_buffer & data)
{
	hgGPSCom msg;
	msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
	std::cout << "&&&& Send GPSCom" << std::endl;
	hgSendManager::SendExceptShipMessage("GPSCom", msg, this->connection());
}

void hgGPSComHandler::afterResponse(const boost::system::error_code & e)
{
	delete this;
}
