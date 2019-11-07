#include "StdAfx.h"
#include "TestTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"
#include "frame/vtsConnection.h"

#include <boost/thread.hpp>
#include <QDebug>
#include "OverLoad.h"

#include "message/hgHeartBeat.pb.h"
#include "Managers/hgSendManager.h"

vtsSETUP_TIMER("test", 3.0, TestTimerHandler);
QList <AIS *> AISTestList;
TestTimerHandler::TestTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
    m_count = 0;
}

TestTimerHandler::~TestTimerHandler(void)
{
}

vtsTimerHandler::WorkMode TestTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_main;
}

void TestTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
	hgHeartBeatPack msg;
	hgSendManager::SendAllMessage("HeartBeat", msg, this->server());

	std::vector<ConnectionPtr> conns;

	time_t now = time(NULL);
	this->server()->connectionManager().for_each(
		[&](ConnectionPtr p)
		{
			if (now - p->lastTick() >= 9)
			{
				vtsDebug << "connect no heart" << p->channel().c_str();
				conns.push_back(p);
			}
		}
	);

	for (int i = 0; i < conns.size(); i++)
	{
		this->server()->connectionManager().stop(conns[i]);
	}
	double end = GetTickCount();
	double diff = end - start;
	if (diff > 500.0)
	{
		vtsInfo << "TestTimerHandler TimeDiff: " << diff;
	}

    /*int x=1;
    google::protobuf::Message m;


    server()->connectionManager().for_each([&](ConnectionPtr p){
    vtsInfo << p->socket().native_handle();
    p->write(type, m);
    p->session().get();
    });*/

    //vtsInfo << "!!!!!" << name() << " "<< boost::this_thread::get_id();
    /*
    _server->connectionManager().for_each([](ConnectionPtr p){
        vtsInfo << p->socket().native_handle();
    });
    */
    /*auto p = server()->connectionManager().find([](ConnectionPtr p){
        return true;
    });
    if (p)
    {
        vtsInfo << p->socket().native_handle() << "\neee\n";
    }*/
}
