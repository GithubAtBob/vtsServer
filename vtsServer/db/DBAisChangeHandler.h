#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"


class hgSqlOperator;

class DBAisChangeHandler :
    public vtsDatabaseHandler
{
public:
    DBAisChangeHandler(void);
    ~DBAisChangeHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    QString m_MMSI;
    QString m_ShipNameEN;
    QString m_ShipNameCH;
    QString m_Callsign;
    QString m_Nationality;
    int m_IMO;
    int m_Class;
    QString m_ShipType;
    int m_DimA;
    int m_DimB;
    int m_DimC;
    int m_DimD;
    QString m_Note;


    QString Result;
};

