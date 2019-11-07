
#include "StdAfx.h"
#include "hgHabitSystemHandler.h"

#include "message/userhabit.pb.h"
#include "db/DBHabitSystemHandler.h"


hgHabitSystemHandler::hgHabitSystemHandler()
{

}

hgHabitSystemHandler::~hgHabitSystemHandler(void)
{
}

vtsRequestHandler::WorkMode hgHabitSystemHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgHabitSystemHandler::handle(boost::asio::const_buffer& data)
{
    SystemCard msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBHabitSystemHandler *dbHandler = new DBHabitSystemHandler();
    dbHandler->m_SystemCard = msg;
    postToDB(dbHandler, boost::bind(&hgHabitSystemHandler::afterDb, this, dbHandler));
    
}

void hgHabitSystemHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgHabitSystemHandler::afterDb(DBHabitSystemHandler* db)
{
    SystemCard result;
    result = db->m_SystemCard;
    response(result, boost::bind(&hgHabitSystemHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void hgHabitSystemHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
