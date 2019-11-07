#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/channel.pb.h"

enum DBChannelHandlerType{
    Add = 0,
    Update,
    Remove,
    All,
    CIsShare,
    Waring
};

class hgSqlOperator;

class DBChannelHandler :
    public vtsDatabaseHandler
{
public:
    DBChannelHandler(void);
    ~DBChannelHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    //void Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    int Type;

    QString ID;

    QString Name;

    QString Annotation;

    int ChannelType;

    double Width;

    google::protobuf::RepeatedPtrField< ChannelWay > Channel;

    google::protobuf::RepeatedPtrField< ChannelWarInfo > Info;

    int LineStyle;

    QString LineColor;

    QString WaringID;

    QString WaringType;

    QString DrawMan;

    bool IsShare;

    QString Result;

    ChannelRepsone Respon;
};

