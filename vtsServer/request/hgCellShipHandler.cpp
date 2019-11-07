
#include "StdAfx.h"
#include "hgCellShipHandler.h"

#include "message/hgCellularShip.pb.h"
#include "frame/vtsServer.h"

#include "Managers/hgSendManager.h"

hgCellShipHandler::hgCellShipHandler()
{

}

hgCellShipHandler::~hgCellShipHandler(void)
{
}

vtsRequestHandler::WorkMode hgCellShipHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgCellShipHandler::handle(boost::asio::const_buffer& data)
{
    hgCellularShip msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));


    hgSendManager::SendClientMessageUOwn("CellularShip",msg,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("CellularShip",msg);
//             }
//     });
    delete this;
    return ;
}





