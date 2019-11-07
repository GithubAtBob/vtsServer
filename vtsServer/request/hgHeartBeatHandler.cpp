
#include "StdAfx.h"
#include "hgHeartBeatHandler.h"

#include "message/hgHeartBeat.pb.h"
#include "Managers/hgSendManager.h"

hgHeartBeatHandler::hgHeartBeatHandler()
{

}

hgHeartBeatHandler::~hgHeartBeatHandler(void)
{
}

vtsRequestHandler::WorkMode hgHeartBeatHandler::workMode()
{
    return Work_Delete_Auto;
}

void hgHeartBeatHandler::handle(boost::asio::const_buffer& data)
{
    hgHeartBeatPack msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));

    //hgSendManager::SendCurrentMessage("HeartBeat",msg,this->connection());
}

void hgHeartBeatHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}
