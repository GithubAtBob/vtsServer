
#include "StdAfx.h"
#include "GroupHandler.h"

#include "message/Group.pb.h"
#include "db/DBGroupHandler.h"


GroupHandler::GroupHandler()
{

}

GroupHandler::~GroupHandler(void)
{
}

vtsRequestHandler::WorkMode GroupHandler::workMode()
{
    return Work_Delete_Manual;
}

void GroupHandler::handle(boost::asio::const_buffer& data)
{
    GroupRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBGroupHandler *dbHandler = new DBGroupHandler();
    dbHandler->Type = msg.type();
    dbHandler->ID = msg.id().c_str();
    dbHandler->Name = msg.name().c_str();
    dbHandler->Power = msg.power().c_str();
    dbHandler->GroupType = msg.grouptype();
    postToDB(dbHandler, boost::bind(&GroupHandler::afterDb, this, dbHandler));
    
}

void GroupHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void GroupHandler::afterDb(DBGroupHandler* db)
{
    GroupRepsone result;
    result.set_result(db->Result.toStdString());
    result.set_type(db->Type);
    response(result, boost::bind(&GroupHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void GroupHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
