
#include "StdAfx.h"
#include "hgFuseSetHandler.h"

#include "message/hgFuseSet.pb.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgConfigManager.h"
#include "Config/hgSysConfig.h"
#include "Managers/hgSendManager.h"

hgFuseSetHandler::hgFuseSetHandler()
{

}

hgFuseSetHandler::~hgFuseSetHandler(void)
{
}

vtsRequestHandler::WorkMode hgFuseSetHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgFuseSetHandler::handle(boost::asio::const_buffer& data)
{
    hgFuseSet msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));

    if (msg.fusecount() == -1)
    {
        hgFuseSet l_msg;
        l_msg.set_hdg(hgTargetManager::m_HDGDif);
        l_msg.set_sog(hgTargetManager::m_SOGDif);
        l_msg.set_dis(hgTargetManager::m_DisDif);
        l_msg.set_fusecount(hgTargetManager::m_FuseCount);
        l_msg.set_fusedis(hgTargetManager::m_DisSuccess);
        l_msg.set_fusesog(hgTargetManager::m_SogSuccess);
        l_msg.set_fusecog(hgTargetManager::m_CogSuccess);
        hgSendManager::SendCurrentMessage("FuseSet",l_msg,this->connection());
    }
    else
    {
        hgTargetManager::m_HDGDif = msg.hdg();
        hgTargetManager::m_SOGDif = msg.sog();
        hgTargetManager::m_DisDif = msg.dis();
        hgTargetManager::m_FuseCount = msg.fusecount();
        hgTargetManager::m_DisSuccess = msg.fusedis();
        hgTargetManager::m_SogSuccess = msg.fusesog();
        hgTargetManager::m_CogSuccess = msg.fusecog();
        hgConfigManager::m_sSysConfig->SetValue("/FuseSetData/FuseHdg",hgTargetManager::m_HDGDif);
        hgConfigManager::m_sSysConfig->SetValue("/FuseSetData/FuseSog",hgTargetManager::m_SOGDif);
        hgConfigManager::m_sSysConfig->SetValue("/FuseSetData/FuseDis",hgTargetManager::m_DisDif);
        hgConfigManager::m_sSysConfig->SetValue("/FuseSetData/FuseCount",hgTargetManager::m_FuseCount);
        hgConfigManager::m_sSysConfig->SetValue("/FuseSetData/FuseDisSuccess",hgTargetManager::m_DisSuccess);
        hgConfigManager::m_sSysConfig->SetValue("/FuseSetData/FuseSogSuccess",hgTargetManager::m_SogSuccess);
        hgConfigManager::m_sSysConfig->SetValue("/FuseSetData/FuseCogSuccess",hgTargetManager::m_CogSuccess);
    }
    qDebug () << "Fuse Data" 
        << hgTargetManager::m_HDGDif 
        << hgTargetManager::m_SOGDif
        << hgTargetManager::m_DisDif
        << hgTargetManager::m_FuseCount
        << hgTargetManager::m_DisSuccess
        << hgTargetManager::m_SogSuccess
        << hgTargetManager::m_CogSuccess;

    delete this;
}



