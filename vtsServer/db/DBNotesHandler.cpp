
#include "StdAfx.h"
#include "DBNotesHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"


DBNotesHandler::DBNotesHandler(void)
{
}


DBNotesHandler::~DBNotesHandler(void)
{
}

void DBNotesHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    switch (Type)
    {
    case /*DBNotesHandlerType::*/Add:
        Addhandle(s, sqlOperator);
        break;
    case /*DBNotesHandlerType::*/Update:
        Updatehandle(s, sqlOperator);
        break;
    case /*DBNotesHandlerType::*/Remove:
        Removehandle(s, sqlOperator);
        break;
    }
}

void DBNotesHandler::Addhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("notes_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("lat",Lat);
    l_data.insert("lon",Lon);
    l_data.insert("notes",Notes);
    l_data.insert("color",Color);
    l_data.insert("drawman",DrawMan);
    l_data.insert("isshare",IsShare);
    l_pSqlInsertCmd->SetData(l_data);
    Result = "add false";
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error(notes_table add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBNotesHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("notes_table");
    QMap<QString, QVariant> l_data;
    //l_data.insert("ID",ID);
    l_data.insert("name",Name);
    l_data.insert("lat",Lat);
    l_data.insert("lon",Lon);
    l_data.insert("notes",Notes);
    l_data.insert("color",Color);
    l_data.insert("drawman",DrawMan);
    //l_data.insert("isshare",IsShare);
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(ID));

    Result = "Update false";
    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error(notes_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

void DBNotesHandler::Removehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
    l_pSqlRemoveCmd->SetTableName("notes_table");

    l_pSqlRemoveCmd->SetFilter(QString("ID = '%1'").arg(ID));

    Result = "Remove false";
    if (!sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
    {
		std::cout << "Open datatabase error(notes_table Remove):" << sqlOperator.LastError().text().toLatin1().data() << endl;
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

// void DBNotesHandler::Allhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
// {
//     hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
//     l_pSqlSelectCmd->SetTableName("notes_table");
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
//     Respon.clear_notess();
//     for (int i = 0; i < l_pSqlRecord->count(); i++)
//     {
//         QSqlRecord l_record = l_pSqlRecord->at(i);
//         NotesRequest* l_requst = Respon.add_notess();
//         std::string l_ID = l_record.value("ID").toString().toStdString();
//         std::string l_name = l_record.value("name").toString().toStdString();
//         double l_lat = l_record.value("lat").toDouble();
//         double l_lon = l_record.value("lon").toDouble();
//         std::string l_notes = l_record.value("notes").toString().toStdString();
//         std::string l_color = l_record.value("color").toString().toStdString();
//         std::string l_drawman = l_record.value("drawman").toString().toStdString();
//         bool l_isshare = l_record.value("isshare").toBool();
//         l_requst->set_type(Type);
//         l_requst->set_id(l_ID);
//         l_requst->set_name(l_name);
//         l_requst->set_lat(l_lat);
//         l_requst->set_lon(l_lon);
//         l_requst->set_notes(l_notes);
//         l_requst->set_color(l_color);
//         l_requst->set_drawman(l_drawman);
//         l_requst->set_isshare(l_isshare);
//     }
//     if (l_pSqlSelectCmd)
//     {
//         delete l_pSqlSelectCmd;
//         l_pSqlSelectCmd = NULL;
//     }
// }