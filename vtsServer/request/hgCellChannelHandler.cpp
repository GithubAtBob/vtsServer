
#include "StdAfx.h"
#include "hgCellChannelHandler.h"

#include "message/hgChannelMsg.pb.h"
#include "frame/vtsServer.h"

#include "Managers/hgSendManager.h"

hgCellChannelHandler::hgCellChannelHandler()
{

}

hgCellChannelHandler::~hgCellChannelHandler(void)
{
}

vtsRequestHandler::WorkMode hgCellChannelHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgCellChannelHandler::handle(boost::asio::const_buffer& data)
{
    hgChannelMsg msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgSendManager::SendClientMessageUOwn("CellChannel",msg,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("CellChannel",msg);
//             }
//     });
    delete this;
    return ;
}

