#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAuthorized.pb.h"

class hgSqlOperator;

class DBAnchorReservHandler :
    public vtsDatabaseHandler
{
public:
    DBAnchorReservHandler(void);
    ~DBAnchorReservHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);


    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString MMSI;
    bool b_AnchorReserv; 
    QString ID;
    int Type;
    long int ETA;
    long int ETD;
    int Tracks;

    QString Result;

    hgAuthorized Respon;
};

