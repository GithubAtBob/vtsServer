
#include "StdAfx.h"
#include "UserHandler.h"

#include "message/User.pb.h"
#include "db/DBUserHandler.h"


UserHandler::UserHandler()
{

}

UserHandler::~UserHandler(void)
{
}

vtsRequestHandler::WorkMode UserHandler::workMode()
{
    return Work_Delete_Manual;
}

void UserHandler::handle(boost::asio::const_buffer& data)
{
    UserRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBUserHandler *dbHandler = new DBUserHandler();
    dbHandler->Type = msg.type();
    dbHandler->OldName = msg.oldloginname().c_str();
    dbHandler->Account = msg.account().c_str();
    dbHandler->LoginName = msg.loginname().c_str();
    dbHandler->UserID = msg.userid().c_str();
    dbHandler->UserName = msg.username().c_str();
    dbHandler->Password = msg.password().c_str();
    dbHandler->Phone = msg.phone().c_str();
    dbHandler->UserGroup = msg.groupid().c_str();
    dbHandler->avatar = msg.avatar().c_str();
    postToDB(dbHandler, boost::bind(&UserHandler::afterDb, this, dbHandler));
    
}

void UserHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void UserHandler::afterDb(DBUserHandler* db)
{
    UserRepsone result;
    result.set_type(db->Type);
    result.set_result(db->Result.toStdString());
    result.set_message(db->Message.toStdString());
    response(result, boost::bind(&UserHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void UserHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
