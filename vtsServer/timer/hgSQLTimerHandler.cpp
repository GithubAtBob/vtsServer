#include "StdAfx.h"
#include "hgSQLTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"
#include "message/deviceinfo.pb.h"

#include <boost/thread.hpp>

#include "Managers/hgSendManager.h"
vtsSETUP_TIMER("hgSQLTimerHandler", 5.0, hgSQLTimerHandler);
hgSQLTimerHandler::hgSQLTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{

}

hgSQLTimerHandler::~hgSQLTimerHandler(void)
{
}

vtsTimerHandler::WorkMode hgSQLTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgSQLTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    QSqlDatabase database = this->server()->openDBConnection();
    if (database.isOpen())
    {
        Device l_DeviceInfo;
        l_DeviceInfo.set_type(DeviceType::DeviceSQL);
        l_DeviceInfo.set_status(true);
        hgSendManager::SendClientMessage("Device",l_DeviceInfo,this->server());
//         this->server()->connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 p->write("Device",l_DeviceInfo);
//         });
    }
    else
    {
        Device l_DeviceInfo;
        l_DeviceInfo.set_type(DeviceType::DeviceSQL);
        l_DeviceInfo.set_status(false);
        hgSendManager::SendClientMessage("Device",l_DeviceInfo,this->server());
//         this->server()->connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 p->write("Device",l_DeviceInfo);
//         });
    }
    this->server()->closeDBConnection(database);
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgSQLTimerHandler TimeDiff: " << diff;
		}
}
