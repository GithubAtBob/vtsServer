#pragma once

#include <QSqlDatabase>
#include <boost/asio/io_service.hpp>

class vtsServerBase
{
public:
    virtual boost::asio::io_service& mainService() = 0;
    virtual boost::asio::io_service& dbService() = 0;
    virtual QSqlDatabase openDBConnection() =0;
    virtual void closeDBConnection(QSqlDatabase connection) = 0;
};