#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAisMessage.pb.h"

class hgSqlOperator;

class DBSaveAisHandler :
    public vtsDatabaseHandler
{
public:
    DBSaveAisHandler(void);
    ~DBSaveAisHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    hgAisMessage AISMessage;
};

