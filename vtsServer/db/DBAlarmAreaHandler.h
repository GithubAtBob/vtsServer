#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/notes.pb.h"

enum DBNotesHandlerType{
    Add = 0,
    Update,
    Remove,
    All,
    CIsShare
};

class hgSqlOperator;

class DBAlarmAreaHandler :
    public vtsDatabaseHandler
{
public:
    DBAlarmAreaHandler(void);
    ~DBAlarmAreaHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Readhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QStringList m_List ;
    int m_type;

};

