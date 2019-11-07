#include "StdAfx.h"
#include "hgDBHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"
#include "frame/vtsConnection.h"

#include <boost/thread.hpp>
#include <QDebug>
#include "OverLoad.h"

#include "message/hgHeartBeat.pb.h"
#include "Managers/hgSendManager.h"


#include "hgSqlRemoveCmd.h"

vtsSETUP_TIMER("hgDBHandler", 10.0, hgDBHandler);

hgDBHandler::hgDBHandler(const std::string& name)
    : vtsTimerHandler(name)
{
    m_count = 0;
}

hgDBHandler::~hgDBHandler(void)
{
}

vtsTimerHandler::WorkMode hgDBHandler::workMode()
{
    return vtsTimerHandler::WorkMode_main;
}

void hgDBHandler::handle(const boost::system::error_code& e)
{
	/*
	if (m_count == 1)
	{
		return;
	}

	m_count = 1;

	ClearMin();
	ClearMax();
	ClearFusedTarget();

	m_count = 0;
	*/
}

void hgDBHandler::ClearMax()
{
	int l_timeNow = QDateTime::currentDateTime().toTime_t();

	int l_before = l_timeNow -  30 * 24 * 3600;

	QSqlDatabase l_database = this->server()->openDBConnection();
	hgSqlOperator l_sqlOperator(l_database);

	hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
	l_pSqlRemoveCmd->SetTableName("arpaall_target_table");


	l_pSqlRemoveCmd->SetFilter(QString("time < %1 order by time limit 100").arg(l_before));

	if (!l_sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
	{
		std::cout << "Open datatabase error(arpaall_target_table Remove):" << l_sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
		return;
	}

	if (l_pSqlRemoveCmd)
	{
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
	}

	this->server()->closeDBConnection(l_database);
}

void hgDBHandler::ClearMin()
{
	int l_timeNow = QDateTime::currentDateTime().toTime_t();

	int l_before = l_timeNow -  24 * 3600;

	QSqlDatabase l_database = this->server()->openDBConnection();
	hgSqlOperator l_sqlOperator(l_database);

	hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
	l_pSqlRemoveCmd->SetTableName("arpaall_target_table_min");


	l_pSqlRemoveCmd->SetFilter(QString("time < %1 order by time limit 100").arg(l_before));

	if (!l_sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
	{
		std::cout << "Open datatabase error(arpaall_target_table Remove):" << l_sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
		return;
	}

	if (l_pSqlRemoveCmd)
	{
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
	}

	this->server()->closeDBConnection(l_database);
}

void hgDBHandler::ClearFusedTarget()
{
	int l_timeNow = QDateTime::currentDateTime().toTime_t();

	int l_before = l_timeNow - 30 * 24 * 3600;

	QSqlDatabase l_database = this->server()->openDBConnection();
	hgSqlOperator l_sqlOperator(l_database);

	hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
	l_pSqlRemoveCmd->SetTableName("fused_target_table");


	l_pSqlRemoveCmd->SetFilter(QString("time < %1 order by time limit 100").arg(l_before));

	if (!l_sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
	{
		std::cout << "Open datatabase error(fused_target_table Remove):" << l_sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
		return;
	}

	if (l_pSqlRemoveCmd)
	{
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
	}

	this->server()->closeDBConnection(l_database);
}
