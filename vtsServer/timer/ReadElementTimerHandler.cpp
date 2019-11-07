#include "StdAfx.h"
#include "ReadElementTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgLayerDataManager.h"
#include "Managers/hgAlarmManager.h"

//vtsSETUP_TIMER("readelement", 1.0, ReadElementTimerHandler);
ReadElementTimerHandler::ReadElementTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
    m_count = 0;
}

ReadElementTimerHandler::~ReadElementTimerHandler(void)
{
}

vtsTimerHandler::WorkMode ReadElementTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void ReadElementTimerHandler::handle(const boost::system::error_code& e)
{
    return ;
    if (m_count != 0)
    {
        return ;
    }
    m_count = 1;
    vtsInfo << "!!!!!+++++++++++++++++++++++++++\n";
    QSqlDatabase database = this->server()->openDBConnection();
    hgSqlOperator l_sqlOperator(database);
    {
        hgAlarmManager::ReadLayerData(l_sqlOperator);
    }
    this->server()->closeDBConnection(database);
}
