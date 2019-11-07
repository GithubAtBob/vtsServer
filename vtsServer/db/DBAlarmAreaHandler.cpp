
#include "StdAfx.h"
#include "DBAlarmAreaHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"


DBAlarmAreaHandler::DBAlarmAreaHandler(void)
{
}


DBAlarmAreaHandler::~DBAlarmAreaHandler(void)
{
}

void DBAlarmAreaHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    if (m_type == 1)
    {
        Updatehandle(s, sqlOperator);
    }
    else if (m_type == 2)
    {
        Readhandle(s, sqlOperator);
    }
}

void DBAlarmAreaHandler::Updatehandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlRemoveCmd* l_pSqlRemoveCmd = new hgSqlRemoveCmd;
    l_pSqlRemoveCmd->SetTableName("alarmarea_table");
    if (!sqlOperator.ImplementCmd(l_pSqlRemoveCmd))
    {
		std::cout << "Open datatabase error(alarmarea_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
		delete l_pSqlRemoveCmd;
		l_pSqlRemoveCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (l_pSqlRemoveCmd)
    {
        delete l_pSqlRemoveCmd;
        l_pSqlRemoveCmd = NULL;
    }
    for (int i = 0; i < m_List.size(); i++)
    {
        hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
        l_pSqlInsertCmd->SetTableName("alarmarea_table");
        QMap<QString, QVariant> l_data;
        //l_data.insert("point",Point);
        l_data.insert("Guid",m_List.at(i));
        l_pSqlInsertCmd->SetData(l_data);
        if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
        {
			std::cout << "Open datatabase error(alarmarea_table Update):" << sqlOperator.LastError().text().toLatin1().data() << endl;
			delete l_pSqlInsertCmd;
			l_pSqlInsertCmd = NULL;
            return;
        }

        QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
        //////////////////
        if (l_pSqlInsertCmd)
        {
            delete l_pSqlInsertCmd;
            l_pSqlInsertCmd = NULL;
        }
    }
}
void DBAlarmAreaHandler::Readhandle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("alarmarea_table");
 
    //l_pSqlSelectCmd->SetFilter(QString("drawman = '%1' or isshare = '1'").arg(DrawMan));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(alarmarea_table Read):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    m_List.clear();
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        std::string l_Guid = l_record.value("Guid").toString().toStdString();
        m_List.push_back(l_Guid.c_str());
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}