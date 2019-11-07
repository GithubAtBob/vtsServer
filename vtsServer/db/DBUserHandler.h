#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"

enum DBUserHandlerType{
    Update,
    Remove
};

class hgSqlOperator;

class DBUserHandler :
    public vtsDatabaseHandler
{
public:
    DBUserHandler(void);
    ~DBUserHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void DeleHandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void UpdateHandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    int Type;

    QString Account;

    QString UserID;

    QString LoginName;

    QString UserName;

    QString OldName;

    QString Password;

    QString Phone;

    QString UserGroup;

    QString avatar;

    QString Result;

    QString Message;

};

