
#include "StdAfx.h"
#include "VoltagesHandler.h"

#include "message/Voltages.pb.h"
#include "Managers/hgDataManager.h"
#include "Managers/hgSendManager.h"
#include "frame/vtsServer.h"

VoltagesHandler::VoltagesHandler()
{

}

VoltagesHandler::~VoltagesHandler(void)
{
}

vtsRequestHandler::WorkMode VoltagesHandler::workMode()
{
    return Work_Delete_Auto;
}

void VoltagesHandler::handle(boost::asio::const_buffer& data)
{
    VoltagesPack msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
	
	if (this->connection()->channel() == "s_RadarServer")
	{
		hgDataManager::m_radarState.flags = msg.stateflags();
		hgDataManager::m_radarState.error = msg.error();
		hgSendManager::SendClientMessage("Voltages", msg, this->connection());
	}
	else
	{
		hgDataManager::m_radarState.flags = msg.stateflags();
		hgSendManager::SendSpecifyMessage("Voltages",msg,this->connection(),"s_RadarServer");
	}
}

void VoltagesHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}