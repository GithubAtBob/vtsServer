
#include "StdAfx.h"
#include "hgHabitTarSetHandler.h"

#include "message/userhabit.pb.h"
#include "db/DBHabitTarSetHandler.h"


hgHabitTarSetHandler::hgHabitTarSetHandler()
{

}

hgHabitTarSetHandler::~hgHabitTarSetHandler(void)
{
}

vtsRequestHandler::WorkMode hgHabitTarSetHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgHabitTarSetHandler::handle(boost::asio::const_buffer& data)
{
    TargetInfoCard msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBHabitTarSetHandler *dbHandler = new DBHabitTarSetHandler();
    dbHandler->m_TargetInfoCard = msg;
    postToDB(dbHandler, boost::bind(&hgHabitTarSetHandler::afterDb, this, dbHandler));
    
}

void hgHabitTarSetHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgHabitTarSetHandler::afterDb(DBHabitTarSetHandler* db)
{
    TargetInfoCard result;
    result = db->m_TargetInfoCard;
//     }
    response(result, boost::bind(&hgHabitTarSetHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void hgHabitTarSetHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
