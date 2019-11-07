
#include "StdAfx.h"
#include "WaringHandler.h"

#include "message/Waring.pb.h"
#include "db/DBWaringHandler.h"


WaringHandler::WaringHandler()
{

}

WaringHandler::~WaringHandler(void)
{
}

vtsRequestHandler::WorkMode WaringHandler::workMode()
{
    return Work_Delete_Manual;
}

void WaringHandler::handle(boost::asio::const_buffer& data)
{
    WaringRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBWaringHandler *dbHandler = new DBWaringHandler();
    dbHandler->Type = msg.type();
    //dbHandler->ID = msg.id();
    dbHandler->Name = msg.name().c_str();
    dbHandler->WaringType = msg.waringtype();
    dbHandler->Time = msg.name().c_str();
    postToDB(dbHandler, boost::bind(&WaringHandler::afterDb, this, dbHandler));
    
}

void WaringHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void WaringHandler::afterDb(DBWaringHandler* db)
{
    WaringRepsone result;
    result.set_result(db->Result.toStdString());
    result.set_type(db->Type);
    response(result, boost::bind(&WaringHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void WaringHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
