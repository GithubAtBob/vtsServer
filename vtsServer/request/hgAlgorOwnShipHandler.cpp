
#include "StdAfx.h"
#include "hgAlgorOwnShipHandler.h"

#include "message/hgAlgorOwnShip.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgSendManager.h"
#include "db/DBAlgorOwnShipHandler.h"

#include "Managers/hgConfigManager.h"
#include "Config/hgSysConfig.h"

hgAlgorOwnShipHandler::hgAlgorOwnShipHandler()
{

}

hgAlgorOwnShipHandler::~hgAlgorOwnShipHandler(void)
{
}

vtsRequestHandler::WorkMode hgAlgorOwnShipHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAlgorOwnShipHandler::handle(boost::asio::const_buffer& data)
{
    hgAlgorOwnShip msg;
    for (auto i = hgConfigManager::m_sSysConfig->m_OwnShipMap.begin(); i != hgConfigManager::m_sSysConfig->m_OwnShipMap.end(); ++i)
    {
			msg.add_mmsi(i->toStdString());
    }
	/*
	hgAlgorOwnShip msg;
	msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
	*/
	//msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));
	hgTargetManager::m_AlgorOwnMMSI.clear();
	for (int i = 0; i < msg.mmsi_size(); i++)
	{
		hgTargetManager::m_AlgorOwnMMSI.push_back(msg.mmsi(i).c_str());
	}
	hgSendManager::SendSpecifyMessage("AlgorOwnShip",msg,this->connection(),"s_AlgorithServer");
	hgSendManager::SendShipMessage("AlgorOwnShip",msg,this->connection());

    DBAlgorOwnShipHandler *dbHandler = new DBAlgorOwnShipHandler();
    dbHandler->m_List = hgTargetManager::m_AlgorOwnMMSI;
    postToDB(dbHandler, boost::bind(&hgAlgorOwnShipHandler::afterDb, this, dbHandler));

}

void hgAlgorOwnShipHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgAlgorOwnShipHandler::afterDb(DBAlgorOwnShipHandler* db)
{
    delete db;
    delete this;
}
