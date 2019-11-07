#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/ploygon.pb.h"

enum DBPloygonHandlerType{
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

class DBPloygonHandler :
    public vtsDatabaseHandler
{
public:
    DBPloygonHandler(void);
    ~DBPloygonHandler(void);

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

    /*QString*/google::protobuf::RepeatedPtrField<std::string> WaringID;

    google::protobuf::RepeatedPtrField<WaringInfo> Info;

    QString WaringType;

    QString DrawMan;

    bool IsShare;

    QString LineColor;

    QString FullColor;

    QString Result;

    PloygonRepsone Respon;

};

