
#include "StdAfx.h"
#include "hgAlgorBackHandler.h"

#include "db/DBAlgorBackHandler.h"
#include "message/hgAlgorBack.pb.h"
#include "Managers/hgSendManager.h"

hgAlgorBackHandler::hgAlgorBackHandler()
{

}

hgAlgorBackHandler::~hgAlgorBackHandler(void)
{
}

vtsRequestHandler::WorkMode hgAlgorBackHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAlgorBackHandler::handle(boost::asio::const_buffer& data)
{
    hgAlgorBackRequest msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));


    DBAlgorBackHandler *dbHandler = new DBAlgorBackHandler();
    dbHandler->Request = msg;
    qDebug () << "back Begin" << clock();
    postToDB(dbHandler, boost::bind(&hgAlgorBackHandler::afterDb, this, dbHandler));
}

void hgAlgorBackHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgAlgorBackHandler::afterDb(DBAlgorBackHandler* db)
{
    hgAlgorBackRepsone Repsone;
    Repsone = db->Repsone;
    qDebug() << "Back" << Repsone.target().size() << clock();
    hgSendManager::SendCurrentMessage("hgAlgorBack",Repsone,this->connection());
    delete db;
    delete this;
}

void hgAlgorBackHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
