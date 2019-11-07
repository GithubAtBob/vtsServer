#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAuthorized.pb.h"

class hgSqlOperator;

class DBGroundWatchHandler :
    public vtsDatabaseHandler
{
public:
    DBGroundWatchHandler(void);
    ~DBGroundWatchHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);


    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString MMSI;
    bool b_GroundWatch; 
    double GroundDraught;   
    double KeelClearance;    

    QString Result;

};

