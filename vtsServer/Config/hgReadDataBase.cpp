
#include "stdafx.h"

#include "hgReadDataBase.h"
#include "frame\vtsServer.h"
#include "Managers\hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

vtsSETUP_PREPROCESS_HANDLER(hgReadDataBase);

hgReadDataBase::hgReadDataBase()
{
}

hgReadDataBase::~hgReadDataBase(void)
{
}

void hgReadDataBase::beforeServerRun(vtsServer *s)
{
    QSqlDatabase database = s->openDBConnection();
    hgSqlOperator l_sqlOperator(database);
    {
        hgTargetManager::ReadLloydAis(l_sqlOperator);  //ÀÍÊÏÊý¾Ý
        hgTargetManager::ReadStaticAis(l_sqlOperator);
        hgAlarmManager::ReadLayerData(l_sqlOperator);
        hgAlarmManager::ReadSetData(l_sqlOperator,s);
    }
    s->closeDBConnection(database);
}
