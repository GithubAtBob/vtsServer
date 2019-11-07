#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/cricle.pb.h"

enum DBCricleHandlerType{
    Add = 0,
    Update,
    Remove,
    All,
    CIsShare,
    Waring,
    Search
};

class hgSqlOperator;
class WaringInfo;

class DBCricleHandler :
    public vtsDatabaseHandler
{
public:
    DBCricleHandler(void);
    ~DBCricleHandler(void);

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

    double Radius;

    int LineStyle;

    int FullStyle;

    int LineWidth;

    google::protobuf::RepeatedPtrField<google::protobuf::string> WaringID;

    google::protobuf::RepeatedPtrField<WaringInfo> Info;

    QString WaringType;

    QString DrawMan;

    bool IsShare;

    QString LineColor;

    QString FullColor;

    QString Result;

    CricleRepsone Respon;
};

