#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"

enum DBWaringHandlerType{
    Add = 0,
    Update,
    Remove
};

class hgSqlOperator;

class DBWaringHandler :
    public vtsDatabaseHandler
{
public:
    DBWaringHandler(void);
    ~DBWaringHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    int Type;

    int ID;

    QString Name;
    
    int WaringType;

    QString Time;
    
    QString Result;

};

