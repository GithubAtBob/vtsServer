#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAuthorized.pb.h"

class hgSqlOperator;

class DBMovementEndHandler :
    public vtsDatabaseHandler
{
public:
    DBMovementEndHandler(void);
    ~DBMovementEndHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);


    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString MMSI;
    bool b_MovementEnd; 
    long int EndTime;    
    double EndLat;
    double EndLon;

    QString Result;

};

