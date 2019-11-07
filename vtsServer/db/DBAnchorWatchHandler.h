#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAuthorized.pb.h"

class hgSqlOperator;

class DBAnchorWatchHandler :
    public vtsDatabaseHandler
{
public:
    DBAnchorWatchHandler(void);
    ~DBAnchorWatchHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);


    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString MMSI;
    bool b_AnchorWatch; //êλ���
    double Clubbing;    //��ê
    double Dragging;    //��ê
    double AnchorLat;
    double AnchorLon;

    QString Result;

    hgAuthorized Respon;
};

