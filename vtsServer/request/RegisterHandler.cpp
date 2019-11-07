
#include "StdAfx.h"
#include "RegisterHandler.h"

#include "message/register.pb.h"
#include "db/DBRegisterHandler.h"
#include "Managers/hgTargetManager.h"


RegisterHandler::RegisterHandler()
{

}

RegisterHandler::~RegisterHandler(void)
{
}

vtsRequestHandler::WorkMode RegisterHandler::workMode()
{
    return Work_Delete_Manual;
}

void RegisterHandler::handle(boost::asio::const_buffer& data)
{
    t1 = clock();
    RegisterRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBRegisterHandler *dbHandler = new DBRegisterHandler();
    dbHandler->Account = msg.account().c_str();
    dbHandler->LoginName = msg.loginname().c_str();
    dbHandler->UserID = msg.userid().c_str();
    dbHandler->UserName = msg.username().c_str();
    dbHandler->Password = msg.password().c_str();
    dbHandler->Phone = msg.phone().c_str();
    dbHandler->UserGroup = msg.groupid().c_str();
    dbHandler->avatar = msg.avatar().c_str();
    dbHandler->GroupType = msg.grouptype();
    postToDB(dbHandler, boost::bind(&RegisterHandler::afterDb, this, dbHandler));
    
}

void RegisterHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void RegisterHandler::afterDb(DBRegisterHandler* db)
{
    RegisterRepsone result;
    result.set_result(db->Result.toStdString());
    result.set_message(db->Message.toStdString());
    response(result, boost::bind(&RegisterHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void RegisterHandler::afterResponse(const boost::system::error_code& e)
{
    t2 = clock();
    //vtsInfo << "Send Register Result, HandlerTime : " << t2-t1;
    //qDebug() << "Register HandlerTime : " << t2-t1;
    delete this;
}
