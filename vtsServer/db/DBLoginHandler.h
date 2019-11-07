#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"

class hgSqlOperator;

class DBLoginHandler :
    public vtsDatabaseHandler
{
public:
    DBLoginHandler(void);
    ~DBLoginHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    virtual void GroupRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    virtual void UserRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    virtual void NotesRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    virtual void FixedObjRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    virtual void AidSailRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString UserName;

    QString Password;

    ///Ó¦´ðÊý¾Ý
    QString Result;

    QString LoginRole;

    QString GroupRecord;

    QString UserRecord;

    QString NotesRecord;

    QString FixedObjRecord;

    QString AidSailRecord;

    int GroupType;

};

