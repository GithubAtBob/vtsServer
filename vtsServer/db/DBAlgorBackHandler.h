#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAlgorBack.pb.h"
#include "Managers/hgTargetManager.h"

class hgSqlOperator;
class DBAlgorBackHandler :
    public vtsDatabaseHandler
{
public:
    DBAlgorBackHandler(void);
    ~DBAlgorBackHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);
    void GetAisMess(hgAisMessage* message, ARPA_TARGET_PACKET* ais, ARPA_TARGET_PACKET* radar);

    hgAlgorBackRequest Request;
    hgAlgorBackRepsone Repsone;
    bool Sql;
};

