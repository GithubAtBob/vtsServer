#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgWarningMes.pb.h"

class hgSqlOperator;

class DBWarnHistoryHandler :
    public vtsDatabaseHandler
{
public:
    DBWarnHistoryHandler(void);
    ~DBWarnHistoryHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);


    QString m_MMSI;
    QVector<hgWarningMes> m_WarnVec;
    
};

