#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"

class hgSqlOperator;

class DBAlgorOwnShipHandler :
    public vtsDatabaseHandler
{
public:
    DBAlgorOwnShipHandler(void);
    ~DBAlgorOwnShipHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QStringList m_List;
};

