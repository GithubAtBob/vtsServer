#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/userhabit.pb.h"

class hgSqlOperator;

class DBHabitDangerHandler :
    public vtsDatabaseHandler
{
public:
    DBHabitDangerHandler(void);
    ~DBHabitDangerHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    virtual void Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    virtual void Readhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    DangerTargetCard m_DangerCard;
};

