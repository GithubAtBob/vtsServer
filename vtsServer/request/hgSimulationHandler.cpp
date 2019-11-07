
#include "StdAfx.h"
#include "hgSimulationHandler.h"

#include "message/hgAisMessage.pb.h"
#include "db/DBBerthWatchHandler.h"
#include "timer/hgChannelTimerHandler.h"
#include "frame/vtsServer.h"
#include "timer/hgSimulationTimerHandler.h"
#include "Managers/hgTargetManager.h"


hgSimulationHandler::hgSimulationHandler()
{

}

hgSimulationHandler::~hgSimulationHandler(void)
{
}

vtsRequestHandler::WorkMode hgSimulationHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgSimulationHandler::handle(boost::asio::const_buffer& data)
{
    hgAisMessage msg;

    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));


    vtsTimerHandler* l_timer = this->getTimer("Simulation");
    if (l_timer == NULL)
    {
        hgSimulationTimerHandler * l_timer = new hgSimulationTimerHandler("Simulation");
        l_timer->setDuration(1.0);
        this->setTimer(l_timer);
    }

    hgTargetManager::AddTarget(msg);
    hgTargetManager::AddAis(msg);

    response(msg, boost::bind(&hgSimulationHandler::afterResponse, this, boost::asio::placeholders::error));

}



void hgSimulationHandler::afterDb(DBBerthWatchHandler* db)
{

}

void hgSimulationHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
