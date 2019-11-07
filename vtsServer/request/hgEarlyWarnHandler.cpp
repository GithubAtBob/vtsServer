
#include "StdAfx.h"
#include "hgEarlyWarnHandler.h"

#include "message/hgEarlyWarnMes.pb.h"
#include "frame/vtsServer.h"

#include "Managers/hgSendManager.h"

hgEarlyWarnHandler::hgEarlyWarnHandler()
{

}

hgEarlyWarnHandler::~hgEarlyWarnHandler(void)
{
}

vtsRequestHandler::WorkMode hgEarlyWarnHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgEarlyWarnHandler::handle(boost::asio::const_buffer& data)
{
    hgEarlyWarnMes msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

	qDebug () << "EarlyWarn";

    hgSendManager::SendClientMessageUOwn("EarlyWarn",msg,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("EarlyWarn",msg);
//             }
//     });
    delete this;
    return ;
}





