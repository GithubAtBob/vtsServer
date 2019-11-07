#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "hgutils/PointLL.h"

class hgSqlOperator;
enum hgDBAisHandlerType{
    Add = 0,
    Update,
    Remove
};

class DBCPAHandler :
    public vtsDatabaseHandler
{
public:
    DBCPAHandler(void);
    ~DBCPAHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void UpdateDynamicAis(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString m_MMSI;
    hg::utils::PointLL m_pointLLOwn;
    double m_dOwnSog;
    double m_dOwnCog;		
    hg::utils::PointLL m_pointLLTarget;
    double m_dTargetSog;
    double m_dTargetCog;

    //Ó¦´ð
    double m_dCPA;
    double m_dTCPA;

    QString Result;
};

