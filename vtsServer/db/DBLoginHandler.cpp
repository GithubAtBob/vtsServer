
#include "StdAfx.h"
#include "DBLoginHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlSelectCmd.h"
#include "hgSqlInsertCmd.h"
#include "hgSqlOperator.h"


DBLoginHandler::DBLoginHandler(void)
{
}


DBLoginHandler::~DBLoginHandler(void)
{
}

void DBLoginHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{

    //{
    //    long int t7 = clock();

    //    for (int i = 0; i < 10000; i++)
    //    {
    //        hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    //        l_pSqlInsertCmd->SetTableName("user_table");
    //        QMap<QString, QVariant> l_data;
    //        l_data.insert("userid","333");
    //        l_data.insert("loginname",i);
    //        l_data.insert("password","111111");
    //        l_data.insert("groupType","5555");
    //        l_data.insert("groupID","groupID");
    //        l_pSqlInsertCmd->SetData(l_data);

    //        if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    //        {
    //            qDebug() << "Open datatabase error(user_table Add):" << sqlOperator.LastError().text().toLatin1().data() << endl;
    //        }

    //        if (l_pSqlInsertCmd)
    //        {
    //            delete l_pSqlInsertCmd;
    //            l_pSqlInsertCmd = NULL;
    //        }
    //    }
    //    long int t8 = clock();
    //    qDebug() << "insert time : " <<  t8 - t7;
    //}

	hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
	l_pSqlSelectCmd->SetTableName("user_table");

    l_pSqlSelectCmd->SetFilter(QString("loginname = '%1'").arg(UserName));

	//l_pSqlSelectCmd->SetFilter(QString("name = '%1' and password = '%2'").arg(UserName).arg(Password));

	if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(user_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        Result = "Search Error";
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
		return;
	}

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (!(l_pSqlRecord->size() > 0))
    {
        Result = "Account does not exist";
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return ;
    }
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);

        QString l_str = l_record.value("password").toString();
        if (Password == l_str)
        {
            Result = "OK";
            LoginRole = l_record.value("groupID").toString();
            GroupType = l_record.value("groupType").toInt();
            GroupRecordhandle(s, sqlOperator);
            UserRecordhandle(s, sqlOperator);
            //NotesRecordhandle(s, sqlOperator);
            //FixedObjRecordhandle(s, sqlOperator);
            //AidSailRecordhandle(s, sqlOperator);
            if (l_pSqlSelectCmd)
            {
                delete l_pSqlSelectCmd;
                l_pSqlSelectCmd = NULL;
            }
            return;
        }
    }
    Result = "Incorrect Password";
    //QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    //if (l_pSqlRecord->size() > 0)
    //{
    //    Result = "OK";
    //}

	if (l_pSqlSelectCmd)
	{
		delete l_pSqlSelectCmd;
		l_pSqlSelectCmd = NULL;
	}
}

void DBLoginHandler::GroupRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("group_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(group_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    GroupRecord.clear();
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        if (i != 0)
        {
            GroupRecord.append("#");
        }
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        QString l_power = l_record.value("power").toString();
        QString l_type = l_record.value("type").toString();
        GroupRecord.append(l_ID);
        GroupRecord.append(";");
        GroupRecord.append(l_name);
        GroupRecord.append(";");
        GroupRecord.append(l_power);
        GroupRecord.append(";");
        GroupRecord.append(l_type);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void DBLoginHandler::UserRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("user_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(user_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    UserRecord.clear();
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        if (i != 0)
        {
            UserRecord.append("#");
        }
        QString l_userid = l_record.value("userid").toString();
        QString l_loginname = l_record.value("loginname").toString();
        QString l_username = l_record.value("username").toString();
        QString l_password = l_record.value("password").toString();
        QString l_phone = l_record.value("phone").toString();
        QString l_groupID = l_record.value("groupID").toString();
        QString l_avatar = l_record.value("avatar").toString();
        QString l_groupType = l_record.value("groupType").toString();
        UserRecord.append(l_userid);
        UserRecord.append(";");
        UserRecord.append(l_loginname);
        UserRecord.append(";");
        UserRecord.append(l_username);
        UserRecord.append(";");
        UserRecord.append(l_password);
        UserRecord.append(";");
        UserRecord.append(l_phone);
        UserRecord.append(";");
        UserRecord.append(l_groupID);
        UserRecord.append(";");
        UserRecord.append(l_avatar);
        UserRecord.append(";");
        UserRecord.append(l_groupType);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void DBLoginHandler::NotesRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("notes_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(notes_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    NotesRecord.clear();
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        if (i != 0)
        {
            NotesRecord.append("#");
        }
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        QString l_lat = l_record.value("lat").toString();
        QString l_lon = l_record.value("lon").toString();
        QString l_notes = l_record.value("notes").toString();
        QString l_color = l_record.value("color").toString();
        QString l_drawman = l_record.value("drawman").toString();
        QString l_isshare = l_record.value("isshare").toString();
        NotesRecord.append(l_ID);
        NotesRecord.append(";");
        NotesRecord.append(l_name);
        NotesRecord.append(";");
        NotesRecord.append(l_lat);
        NotesRecord.append(";");
        NotesRecord.append(l_lon);
        NotesRecord.append(";");
        NotesRecord.append(l_notes);
        NotesRecord.append(";");
        NotesRecord.append(l_color);
        NotesRecord.append(";");
        NotesRecord.append(l_drawman);
        NotesRecord.append(";");
        NotesRecord.append(l_isshare);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void DBLoginHandler::FixedObjRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("fixedobject_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(fixedobject_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    FixedObjRecord.clear();
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        if (i != 0)
        {
            FixedObjRecord.append("#");
        }
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        QString l_lat = l_record.value("lat").toString();
        QString l_lon = l_record.value("lon").toString();
        QString l_remarks = l_record.value("remarks").toString();
        QString l_iconURL = l_record.value("iconURL").toString();
        QString l_drawman = l_record.value("drawman").toString();
        QString l_isshare = l_record.value("isshare").toString();
        FixedObjRecord.append(l_ID);
        FixedObjRecord.append(";");
        FixedObjRecord.append(l_name);
        FixedObjRecord.append(";");
        FixedObjRecord.append(l_lat);
        FixedObjRecord.append(";");
        FixedObjRecord.append(l_lon);
        FixedObjRecord.append(";");
        FixedObjRecord.append(l_remarks);
        FixedObjRecord.append(";");
        FixedObjRecord.append(l_iconURL);
        FixedObjRecord.append(";");
        FixedObjRecord.append(l_drawman);
        FixedObjRecord.append(";");
        FixedObjRecord.append(l_isshare);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void DBLoginHandler::AidSailRecordhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("aidsail_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(aidsail_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    AidSailRecord.clear();
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        if (i != 0)
        {
            AidSailRecord.append("#");
        }
        QString l_ID = l_record.value("ID").toString();
        QString l_name = l_record.value("name").toString();
        QString l_lat = l_record.value("lat").toString();
        QString l_lon = l_record.value("lon").toString();
        QString l_remarks = l_record.value("remarks").toString();
        QString l_iconURL = l_record.value("iconURL").toString();
        QString l_drawman = l_record.value("drawman").toString();
        QString l_isshare = l_record.value("isshare").toString();
        AidSailRecord.append(l_ID);
        AidSailRecord.append(";");
        AidSailRecord.append(l_name);
        AidSailRecord.append(";");
        AidSailRecord.append(l_lat);
        AidSailRecord.append(";");
        AidSailRecord.append(l_lon);
        AidSailRecord.append(";");
        AidSailRecord.append(l_remarks);
        AidSailRecord.append(";");
        AidSailRecord.append(l_iconURL);
        AidSailRecord.append(";");
        AidSailRecord.append(l_drawman);
        AidSailRecord.append(";");
        AidSailRecord.append(l_isshare);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}