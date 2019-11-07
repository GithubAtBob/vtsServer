#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/ellipse.pb.h"

enum DBEllipseHandlerType{
    Add = 0,
    Update,
    Remove,
    All,
    CIsShare,
    Waring
};

class hgSqlOperator;

class DBEllipseHandler :
    public vtsDatabaseHandler
{
public:
    DBEllipseHandler(void);
    ~DBEllipseHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Sharehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    int Type;

    QString ID;

    QString Name;

    double Lat;

    double Lon;

    double ShortAxis;

    double LongAxis;

    int LineStyle;

    int FullStyle;

    int LineWidth;

    google::protobuf::RepeatedField<google::protobuf::int32> WaringID;

    QString WaringType;

    QString DrawMan;

    bool IsShare;

    QString LineColor;

    QString FullColor;

    QString Result;

    EllipseRepsone Respon;
};

