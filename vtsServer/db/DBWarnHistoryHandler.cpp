
#include "StdAfx.h"
#include "DBWarnHistoryHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "OverLoad.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

DBWarnHistoryHandler::DBWarnHistoryHandler(void)
{
}


DBWarnHistoryHandler::~DBWarnHistoryHandler(void)
{
}

void DBWarnHistoryHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    int l_history = time(NULL) - 24*60*60;

    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("warning_table");
    l_pSqlSelectCmd->SetFilter(QString("MMSI = '%1' and WarningTime > '%2'").arg(m_MMSI).arg(l_history));
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error(warning_table):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgWarningMes l_data;
        l_data.set_warningid(l_record.value("WarnID").toString().toStdString());
        l_data.set_warningguid(l_record.value("WarnDUID").toString().toStdString());
        l_data.set_warningpriority((hgWarningPriority)l_record.value("WarningPriority").toInt());
        l_data.set_warningname(l_record.value("WarningName").toString().toStdString());
        //l_data.set_message() = l_record.value("Message").toString();
        l_data.set_mmsi(l_record.value("MMSI").toString().toStdString());
        l_data.set_userlayguid(l_record.value("UserLayGUID").toString().toStdString());
        l_data.set_userlayid((UserLayerType)l_record.value("UserLayID").toInt());
        l_data.set_id(l_record.value("ID").toString().toStdString());
        l_data.set_warningtime(l_record.value("WarningTime").toInt());
        l_data.set_warningtype((hgWarningType)l_record.value("WarningType").toInt());
        l_data.set_targetmmsi(l_record.value("TargetMMSI").toString().toStdString());
        m_WarnVec.push_back(l_data);
    }

    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}


