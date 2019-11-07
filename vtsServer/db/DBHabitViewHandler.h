#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/userhabit.pb.h"

class hgSqlOperator;

class DBHabitViewHandler :
    public vtsDatabaseHandler
{
public:
    DBHabitViewHandler(void);
    ~DBHabitViewHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    virtual void Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    virtual void Readhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString UserID;

    double Lat;
    double Lon;

    int Range;

    google::protobuf::RepeatedPtrField<QuickData> Quick;
    
    CardMesType Type;
};

