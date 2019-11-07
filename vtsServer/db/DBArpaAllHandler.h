#pragma once

#include <boost/asio.hpp>

#include <QString>
#include <QSqlDatabase>

#include "frame/vtsDatabaseHandler.h"
#include "message/hgArpaAll.pb.h"

class hgSqlOperator;

class DBArpaAllHandler :
    public vtsDatabaseHandler
{
public:
    DBArpaAllHandler(void);
    ~DBArpaAllHandler(void);

    virtual void handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

	//大数据表   删除30天前数据
    void Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

	//小的数据表每 删除 2天前数据
	void Savehandle2(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    hgArpaAllPack pack;

};

