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

	//�����ݱ�   ɾ��30��ǰ����
    void Savehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

	//С�����ݱ�ÿ ɾ�� 2��ǰ����
	void Savehandle2(boost::asio::io_service &s, hgSqlOperator& sqlOperator);

    hgArpaAllPack pack;

};

