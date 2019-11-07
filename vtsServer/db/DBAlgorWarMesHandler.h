#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAlgorWar.pb.h"

class hgSqlOperator;

class DBAlgorWarMesHandler :
    public vtsDatabaseHandler
{
public:
    DBAlgorWarMesHandler(void);
    ~DBAlgorWarMesHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    hgAlgorWarMes AlgorWarMes;

    QString URL;

};

