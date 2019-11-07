#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/fixedobject.pb.h"

enum DBFixedObjectHandlerType{
    Add = 0,
    Update,
    Remove,
    All,
    CIsShare
};

class hgSqlOperator;

class DBFixedObjectHandler :
    public vtsDatabaseHandler
{
public:
    DBFixedObjectHandler(void);
    ~DBFixedObjectHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    //void Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    int Type;

    QString ID;

    QString Name;

    double Lat;

    double Lon;

    QString Remarks;

    QString IconURL;

    QString DrawMan;

    bool IsShare;

    QString Result;

    FixedObjectRepsone Respon;

};

