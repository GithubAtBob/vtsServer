
#include "StdAfx.h"
#include "hgHabitChartHandler.h"

#include "message/userhabit.pb.h"
#include "db/DBHabitChartHandler.h"


hgHabitChartHandler::hgHabitChartHandler()
{

}

hgHabitChartHandler::~hgHabitChartHandler(void)
{
}

vtsRequestHandler::WorkMode hgHabitChartHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgHabitChartHandler::handle(boost::asio::const_buffer& data)
{
    ChartCard msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBHabitChartHandler *dbHandler = new DBHabitChartHandler();
    dbHandler->m_ChartCard = msg;
    postToDB(dbHandler, boost::bind(&hgHabitChartHandler::afterDb, this, dbHandler));
    
}

void hgHabitChartHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgHabitChartHandler::afterDb(DBHabitChartHandler* db)
{
    ChartCard result;
    result = db->m_ChartCard;
//     }
    response(result, boost::bind(&hgHabitChartHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void hgHabitChartHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
