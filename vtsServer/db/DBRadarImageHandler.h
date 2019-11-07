#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/RadarImagePack.pb.h"

class hgSqlOperator;

class DBRadarImageHandler :
    public vtsDatabaseHandler
{
public:
    DBRadarImageHandler(void);
    ~DBRadarImageHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    RadarImagePack RadarImage;

    QString URL;

};

