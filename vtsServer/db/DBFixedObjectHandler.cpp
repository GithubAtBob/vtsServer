
#include "StdAfx.h"
#include "DBFixedObjectHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"


DBFixedObjectHandler::DBFixedObjectHandler(void)
{
}


DBFixedObjectHandler::~DBFixedObjectHandler(void)
{
}

void DBFixedObjectHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (Type)
    {
    case DBFixedObjectHandlerType::Add:
        Addhandle(s, sqlOperator);
        break;
    case DBFixedObjectHandlerType::Update:
        Updatehandle(s, sqlOperator);
        break;
    case DBFixedObjectHandlerType::Remove:
        Removehandle(s, sqlOperator);
        break;
    }
}

void DBFixedObjectHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("fixedobject_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("lat",Lat);
    l_data.insert("lon",Lon);
    l_data.insert("remarks",Remarks);
    l_data.insert("iconURL",IconURL);
    l_data.insert("drawman",DrawMan);
    l_data.insert("isshare",IsShare);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "add false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(fixedobject_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

void DBFixedObjectHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("fixedobject_table");
    QMap<QString, QVariant> l_data;
    //l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("lat",Lat);
    l_data.insert("lon",Lon);
    l_data.insert("remarks",Remarks);
    l_data.insert("iconURL",IconURL);
    l_data.insert("drawman",DrawMan);
//    l_data.insert("isshare",IsShare);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));

//     l_pSqlUpdateCmd->SetData("lon",10);          ///更新具体某项
//     l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));
    Result = "Update false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(fixedobject_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }
}

void DBFixedObjectHandler::Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
    l_pSqlRemoveCmd->SetTableName("fixedobject_table");

    l_pSqlRemoveCmd->SetFilter(QString("ID = '%1'").arg(ID));

    Result = "Remove false";
    if (!sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
    {
		std::cout << "Open datatabase error(fixedobject_table Remove):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    Result = "OK";
    std::cout << Result.toStdString();
    if (l_pSqlRemoveCmd)
    {
        delete l_pSqlRemoveCmd;
        l_pSqlRemoveCmd = NULL;
    }
}

// void DBFixedObjectHandler::Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
// {
//     hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
//     l_pSqlSelectCmd->SetTableName("fixedobject_table");
// 
//     //l_pSqlSelectCmd->SetFilter(QString("drawman = '%1' or isshare = '1'").arg(DrawMan));
//     if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
//     {
//         std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
//         if (l_pSqlSelectCmd)
//         {
//             delete l_pSqlSelectCmd;
//             l_pSqlSelectCmd = NULL;
//         }
//         return;
//     }
//     Respon.set_type(Type); 
//     QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
//     Respon.clear_fixedobjs();
//     for (int i = 0; i < l_pSqlRecord->count(); i++)
//     {
//         QSqlRecord l_record = l_pSqlRecord->at(i);
//         FixedObjectRequest* l_requst = Respon.add_fixedobjs();
//         std::string l_ID = l_record.value("ID").toString().toStdString();
//         std::string l_name = l_record.value("name").toString().toStdString();
//         double l_lat = l_record.value("lat").toDouble();
//         double l_lon = l_record.value("lon").toDouble();
//         std::string l_remarks = l_record.value("remarks").toString().toStdString();
//         std::string l_iconURL = l_record.value("iconURL").toString().toStdString();
//         std::string l_drawman = l_record.value("drawman").toString().toStdString();
//         bool l_isshare = l_record.value("isshare").toBool();
//         l_requst->set_type(Type);
//         l_requst->set_id(l_ID);
//         l_requst->set_name(l_name);
//         l_requst->set_lat(l_lat);
//         l_requst->set_lon(l_lon);
//         l_requst->set_remarks(l_remarks);
//         l_requst->set_iconurl(l_iconURL);
//         l_requst->set_drawman(l_drawman);
//         l_requst->set_isshare(l_isshare);
//     }
//     if (l_pSqlSelectCmd)
//     {
//         delete l_pSqlSelectCmd;
//         l_pSqlSelectCmd = NULL;
//     }
// }
