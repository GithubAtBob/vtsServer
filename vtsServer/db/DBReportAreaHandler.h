#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgAuthorized.pb.h"
#include "Managers/hgWarningSetManager.h"

class hgSqlOperator;

class DBReportAreaHandler :
    public vtsDatabaseHandler
{
public:
    DBReportAreaHandler(void);
    ~DBReportAreaHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);


    void Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    void Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString MMSI;
    bool b_ReportArea;
    bool b_Pattern;
    QMap<QString,AreaData> mapAreaData;
    long int EarilestTime;
    long int LatestTime;

    QString Result;

};

