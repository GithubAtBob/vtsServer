
#include "StdAfx.h"
#include "hgTargetHandler.h"

#include "message/hgAuthorized.pb.h"
#include "db/DBLoginHandler.h"
#include "Managers/hgTargetManager.h"
#include "frame/vtsServer.h"
#include "Managers/hgWarningSetManager.h"
#include "Managers/hgAlarmManager.h"
#include "message/hgAisMessage.pb.h"
#include "message/hgCPAData.pb.h"
#include "Managers/hgConfigManager.h"

#include "Managers/hgSendManager.h"
hgTargetHandler::hgTargetHandler()
{

}

hgTargetHandler::~hgTargetHandler(void)
{
}

vtsRequestHandler::WorkMode hgTargetHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgTargetHandler::handle(boost::asio::const_buffer& data)
{
    

    hgAisMessage msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    hgAlarmManager::m_WarningSetManager.SendWarnSet(msg.id().c_str(),this->connection());

    hgCPAData l_CPAData;
    l_CPAData.set_daycpa(hgConfigManager::m_sSysConfig->m_dayCPA);
    l_CPAData.set_daytcpa(hgConfigManager::m_sSysConfig->m_dayTCPA);
    l_CPAData.set_nightcpa(hgConfigManager::m_sSysConfig->m_nightCPA);
    l_CPAData.set_nighttcpa(hgConfigManager::m_sSysConfig->m_nightTCPA);
    l_CPAData.set_customcpa(hgConfigManager::m_sSysConfig->m_customCPA);
    l_CPAData.set_customtcpa(hgConfigManager::m_sSysConfig->m_customTCPA);

    hgSendManager::SendCurrentMessage("CPAData",l_CPAData,this->connection());
    delete this;
}




