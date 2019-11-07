
#include "StdAfx.h"
#include "DBCPAHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlOperator.h"
#include "hgSqlSelectCmd.h"
#include "hgutils/NavUtil.h"


DBCPAHandler::DBCPAHandler(void)
{
    m_dTCPA = 0;
    m_dCPA = 0;
}


DBCPAHandler::~DBCPAHandler(void)
{
}

void DBCPAHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
     hg::utils::navutil::getTCPADCPA(m_pointLLOwn,m_dOwnSog,m_dOwnCog,m_pointLLTarget,m_dTargetSog,m_dTargetCog,&m_dTCPA,&m_dCPA);
}

    


void DBCPAHandler::UpdateDynamicAis(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{

}

