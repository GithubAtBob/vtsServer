
#include "StdAfx.h"
#include "hgCPAWarningHandler.h"

#include "message/hgCPAWarning.pb.h"
#include "frame/vtsServer.h"

#include "Managers/hgSendManager.h"

hgCPAWarningHandler::hgCPAWarningHandler()
{

}

hgCPAWarningHandler::~hgCPAWarningHandler(void)
{
}

vtsRequestHandler::WorkMode hgCPAWarningHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgCPAWarningHandler::handle(boost::asio::const_buffer& data)
{
    hgCPAWarning msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    hgSendManager::SendClientMessageUOwn("CPAWarning",msg,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 p->write("CPAWarning",msg);
//             }
//     });
    delete this;
    return ;
}



// void hgCPAWarningHandler::afterDb(DBWaringHandler* db)
// {
//     WaringRepsone result;
//     result.set_result(db->Result.toStdString());
//     result.set_type(db->Type);
//     responseAsync(result, boost::bind(&hgCPAWarningHandler::afterResponse, this, boost::asio::placeholders::error));
//     delete db;
// }
// 
// void hgCPAWarningHandler::afterResponse(const boost::system::error_code& e)
// {
//     delete this;
// }
