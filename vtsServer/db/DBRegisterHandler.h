#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"

class hgSqlOperator;

class DBRegisterHandler :
    public vtsDatabaseHandler
{
public:
    DBRegisterHandler(void);
    ~DBRegisterHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString Account;

    QString UserID;

    QString LoginName;

    QString UserName;

    QString Password;

    QString Phone;

    QString UserGroup;

    QString avatar;

    int GroupType;

    QString Result;

    QString Message;

};

