
#include "StdAfx.h"
#include "hgHabitViewHandler.h"

#include "message/userhabit.pb.h"
#include "db/DBHabitViewHandler.h"


hgHabitViewHandler::hgHabitViewHandler()
{

}

hgHabitViewHandler::~hgHabitViewHandler(void)
{
}

vtsRequestHandler::WorkMode hgHabitViewHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgHabitViewHandler::handle(boost::asio::const_buffer& data)
{
    ViewCard msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));

    DBHabitViewHandler *dbHandler = new DBHabitViewHandler();
    dbHandler->UserID = msg.userid().c_str();
    dbHandler->Lat = msg.lat();
    dbHandler->Lon = msg.lon();
    dbHandler->Range = msg.range();
    dbHandler->Quick = msg.quick();
    dbHandler->Type = msg.type();
    postToDB(dbHandler, boost::bind(&hgHabitViewHandler::afterDb, this, dbHandler));
    
}

void hgHabitViewHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgHabitViewHandler::afterDb(DBHabitViewHandler* db)
{
    ViewCard result;
    result.set_type(db->Type);
    result.set_userid(db->UserID.toStdString());
    result.set_lat(db->Lat);
    result.set_lon(db->Lon);
    result.set_range(db->Range);
    for (int i = 0; i < db->Quick.size(); i++)
    {
        QuickData* l_mes = result.add_quick();
        l_mes->set_name(db->Quick.Get(i).name().c_str());
        l_mes->set_lat(db->Quick.Get(i).lat());
        l_mes->set_lon(db->Quick.Get(i).lon());
    }
    response(result, boost::bind(&hgHabitViewHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void hgHabitViewHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
