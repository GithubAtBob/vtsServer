#pragma once

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <QSqlDatabase>
class hgSqlOperator;

class vtsDatabaseHandler :
    private boost::noncopyable
{
public:

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator) = 0;
};

