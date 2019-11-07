#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/dutyarea.pb.h"

enum DBDutyAreaHandlerType{
    Add = 0,
    Update,
    Remove,
    All,
    CIsShare
};

class hgSqlOperator;

class DBDutyAreaHandler :
    public vtsDatabaseHandler
{
public:
    DBDutyAreaHandler(void);
    ~DBDutyAreaHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    //void Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    int Type;

    QString ID;

    QString Name;

    //QString Point;
    google::protobuf::RepeatedPtrField<PointMes> Point;

    int LineStyle;

    int FullStyle;

    int LineWidth;

    QString DutyMan;

    QString DrawMan;

    bool IsShare;

    QString LineColor;

    QString FullColor;

    QString Result;

    DutyAreaRepsone Respon;

};

