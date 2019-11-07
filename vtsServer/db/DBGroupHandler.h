#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"

enum DBGroupHandlerType{
    Add = 0,
    Update,
    Remove
};

class hgSqlOperator;

class DBGroupHandler :
    public vtsDatabaseHandler
{
public:
    DBGroupHandler(void);
    ~DBGroupHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    int Type;

    QString ID;

    QString Name;
    
    QString Power;
    
    QString Result;

    int GroupType;

};

