
#include "StdAfx.h"
#include "hgCPAHandler.h"

#include "message/hgCPA.pb.h"
#include "db/DBCPAHandler.h"
#include "hgAisDecoder.h"

hgCPAHandler::hgCPAHandler()
{

}

hgCPAHandler::~hgCPAHandler(void)
{
}

vtsRequestHandler::WorkMode hgCPAHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgCPAHandler::handle(boost::asio::const_buffer& data)
{
    hgCPA msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));


    DBCPAHandler *dbHandler = new DBCPAHandler();
    dbHandler->m_MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->m_dOwnCog = msg.owncog();
    dbHandler->m_dOwnSog = msg.ownsog();
    dbHandler->m_pointLLOwn.setLat(msg.ownlat());
    dbHandler->m_pointLLOwn.setLon(msg.ownlon());
    dbHandler->m_dTargetCog = msg.targetcog();
    dbHandler->m_dTargetSog = msg.targetsog();
    dbHandler->m_pointLLTarget.setLat(msg.targetlat());
    dbHandler->m_pointLLTarget.setLon(msg.targetlon());


 
    postToDB(dbHandler, boost::bind(&hgCPAHandler::afterDb, this, dbHandler));
}



void hgCPAHandler::afterDb(DBCPAHandler* db)
{
    hgCPARepsone result;
    result.set_mmsi(db->m_MMSI.toStdString());
    result.set_cpa(db->m_dCPA);
    result.set_tcpa(db->m_dTCPA);
    response(result, boost::bind(&hgCPAHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
}

void hgCPAHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
