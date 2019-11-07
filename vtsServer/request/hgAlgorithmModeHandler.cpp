
#include "StdAfx.h"
#include "hgAlgorithmModeHandler.h"

#include "message/AlgorithmMode.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgAlarmManager.h"

#include "Managers/hgSendManager.h"
hgAlgorithmModeHandler::hgAlgorithmModeHandler()
{

}

hgAlgorithmModeHandler::~hgAlgorithmModeHandler(void)
{
}

vtsRequestHandler::WorkMode hgAlgorithmModeHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAlgorithmModeHandler::handle(boost::asio::const_buffer& data)
{
    hgAlgorithmMode msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));

    if (msg.mode() == EarlyModel 
        || msg.mode() == ManualModel
        || msg.mode() == AutoModel)
    {
        hgAlarmManager::m_AlgorithmMode = msg.mode();
        hgAlarmManager::m_alarm1 = msg.alarm1();
        hgAlarmManager::m_alarm2 = msg.alarm2();
        hgAlarmManager::m_alarm3 = msg.alarm3();
        hgSendManager::SendSpecifyMessage("AlgorithmMode",msg,this->connection(),"s_AlgorithServer");
        //this->connection()->connectionManager().broadcast("AlgorithmMode",msg);
    }
    else if (msg.mode() == AskModel)
    {
        hgAlgorithmMode l_msg;
        l_msg.set_mode(hgAlarmManager::m_AlgorithmMode);
        l_msg.set_alarm1(hgAlarmManager::m_alarm1);
        l_msg.set_alarm2(hgAlarmManager::m_alarm2);
        l_msg.set_alarm3(hgAlarmManager::m_alarm3);
        hgSendManager::SendCurrentMessage("AlgorithmMode",l_msg,this->connection());
        //this->connection()->write("AlgorithmMode",l_msg);
    }
    else if (msg.mode() == SetModel)
    {
        hgAlarmManager::m_alarm1 = msg.alarm1();
        hgAlarmManager::m_alarm2 = msg.alarm2();
        hgAlarmManager::m_alarm3 = msg.alarm3();
        hgSendManager::SendSpecifyMessage("AlgorithmMode",msg,this->connection(),"s_AlgorithServer");
        //this->connection()->connectionManager().multicast("s_AlgorithServer","AlgorithmMode",msg);
    }
    else if (msg.mode() == SetManualModel
        || msg.mode() == SetAutoModel)
    {
        hgAlarmManager::m_AlgorithmMode = msg.mode() == SetManualModel ? ManualModel : AutoModel;
        hgSendManager::SendSpecifyMessage("AlgorithmMode",msg,this->connection(),"s_AlgorithServer");
        //this->connection()->connectionManager().multicast("s_AlgorithServer","AlgorithmMode",msg);
    }
    delete this;
    return ;
}