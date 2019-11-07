#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAuthorized.pb.h"

class hgSqlOperator;

class DBSpeedWatchHandler :
    public vtsDatabaseHandler
{
public:
    DBSpeedWatchHandler(void);
    ~DBSpeedWatchHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);


    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString MMSI;
    bool b_SpeedWatch;
    double MinSpeed;
    double MinDuration;
    double MaxSpeed;
    double MaxDuration; 

    QString Result;

};

