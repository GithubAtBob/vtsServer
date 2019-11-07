#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/RadarImagePack.pb.h"
#include "message/hgAisMessage.pb.h"

class hgSqlOperator;

class DBArpaTargetHandler :
    public vtsDatabaseHandler
{
public:
    DBArpaTargetHandler(void);
    ~DBArpaTargetHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    hgAisMessage ArpaTarget;

};

