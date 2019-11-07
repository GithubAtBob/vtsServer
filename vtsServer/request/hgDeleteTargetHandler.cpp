
#include "StdAfx.h"
#include "hgDeleteTargetHandler.h"

#include "message/hgDeleteTarget.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgTargetManager.h"

#include "Managers/hgSendManager.h"
hgDeleteTargetHandler::hgDeleteTargetHandler()
{

}

hgDeleteTargetHandler::~hgDeleteTargetHandler(void)
{
}

vtsRequestHandler::WorkMode hgDeleteTargetHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgDeleteTargetHandler::handle(boost::asio::const_buffer& data)
{
    hgDeleteTarget msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    switch(msg.deletetype())
    {
    case DeleteAll:
        hgTargetManager::DeleteAll();
        break;
    case DeleteSim:
        hgTargetManager::DeleteSim();
        break;
    case DeleteLost:
        hgTargetManager::DeleteLost();
        break;
    }

    hgSendManager::SendClientMessageUOwn("DeleteTarget",msg,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("DeleteTarget",msg);
//             }
//     });
    delete this;
}


