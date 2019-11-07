#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAuthorized.pb.h"

class hgSqlOperator;

class DBBerthWatchHandler :
    public vtsDatabaseHandler
{
public:
    DBBerthWatchHandler(void);
    ~DBBerthWatchHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);


    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString MMSI;
    bool b_BerthWatch; //²´Î»¼à¿Ø
    double Distance;    
    double BerthLat;
    double BerthLon;

    QString Result;

};

