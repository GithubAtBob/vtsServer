
#include "StdAfx.h"
#include "hgServerModeHandler.h"

#include "message/hgServerMode.pb.h"
#include "Config/hgSysConfig.h"
#include "Managers/hgConfigManager.h"
#include "Managers/hgSendManager.h"

hgServerModeHandler::hgServerModeHandler()
{

}

hgServerModeHandler::~hgServerModeHandler(void)
{
}

vtsRequestHandler::WorkMode hgServerModeHandler::workMode()
{
    return Work_Delete_Auto;
}

void hgServerModeHandler::handle(boost::asio::const_buffer& data)
{
    hgServerMode msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    msg.set_playback(hgConfigManager::m_sSysConfig->m_netMode);
    msg.set_freshmode(hgConfigManager::m_sSysConfig->m_comMode);
    msg.set_aisdata(hgConfigManager::m_sSysConfig->m_aisServer);
    msg.set_radardata(hgConfigManager::m_sSysConfig->m_radarServer);

    hgSendManager::SendCurrentMessage("hgServerMode",msg,this->connection());
    
}

void hgServerModeHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}