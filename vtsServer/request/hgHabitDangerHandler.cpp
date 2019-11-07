
#include "StdAfx.h"
#include "hgHabitDangerHandler.h"

#include "message/userhabit.pb.h"
#include "db/DBHabitDangerHandler.h"


hgHabitDangerHandler::hgHabitDangerHandler()
{

}

hgHabitDangerHandler::~hgHabitDangerHandler(void)
{
}

vtsRequestHandler::WorkMode hgHabitDangerHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgHabitDangerHandler::handle(boost::asio::const_buffer& data)
{
    DangerTargetCard msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBHabitDangerHandler *dbHandler = new DBHabitDangerHandler();
    dbHandler->m_DangerCard = msg;
    postToDB(dbHandler, boost::bind(&hgHabitDangerHandler::afterDb, this, dbHandler));
    
}

void hgHabitDangerHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgHabitDangerHandler::afterDb(DBHabitDangerHandler* db)
{
    DangerTargetCard result;
    result = db->m_DangerCard;
//     }
    response(result, boost::bind(&hgHabitDangerHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void hgHabitDangerHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
