#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAlgorText.pb.h"

class hgSqlOperator;

class DBAlgorTextHandler :
    public vtsDatabaseHandler
{
public:
    DBAlgorTextHandler(void);
    ~DBAlgorTextHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    hgAlgorText msg;
};

