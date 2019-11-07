#include "StdAfx.h"
#include "hgWarningSetManager.h"
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "hgSqlInsertCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgutils/NavUtil.h"
#include "Managers/hgSendManager.h"
#include "message/hgCollisionWatch.pb.h"
#include "message/hgAnchorAreaMes.pb.h"
#include "message/hgAnchorWatch.pb.h"
#include "message/hgAnchorReserv.pb.h"
#include "message/hgBerthWatch.pb.h"
#include "message/hgCollisionWatch.pb.h"
#include "message/hgDomain.pb.h"
#include "message/hgGroundWatch.pb.h"
#include "message/hgReportArea.pb.h"
#include "message/hgSpeedWatch.pb.h"
#include "message/hgSetShip.pb.h"
#include "message/hgTurnCircle.pb.h"
#include "message/hgMovementEnd.pb.h"
#include "message/hgNavigatChannel.pb.h"
#include "message/hgCPAData.pb.h"
#include "message/hgAuthorized.pb.h"
#include "LayerData/hgShipWarningInfo.h"
#include "hgSqlOperator.h"
#include "Managers/hgAlarmManager.h"

hgWarningSetManager::hgWarningSetManager(void)
{
}

hgWarningSetManager::~hgWarningSetManager(void)
{

}


void hgWarningSetManager::SetWarnInfo(QString MMSI,int type)
{
    QMap<QString,hgShipWarningInfo>::iterator l_it =  m_mapWarnInfo.find(MMSI);
    if (l_it != m_mapWarnInfo.end())
    {
        l_it->SetShipWarningInfo(type,false);
    } 
    else
    {
        hgShipWarningInfo l_ShipWarningInfo;
        m_mapWarnInfo.insert(MMSI,l_ShipWarningInfo);
    }
}

void hgWarningSetManager::SaveAuthorized(Authorized &authorized)
{
    QMap<QString,Authorized>::iterator l_it = m_mapAuthorized.find(authorized.TargetID);
    if (l_it != m_mapAuthorized.end())
    {
        l_it->Authorize = authorized.Authorize;
    }
    else
    {
        m_mapAuthorized.insert(authorized.TargetID,authorized);
    }
}

void hgWarningSetManager::SaveDomain(Domain &domain)
{
    QMap<QString,Domain>::iterator l_it = m_mapDomain.find(domain.TargetID);
    if (l_it != m_mapDomain.end())
    {
        l_it->DomainWatch = domain.DomainWatch;
        l_it->DomainRadius = domain.DomainRadius;
        l_it->DomainColorB = domain.DomainColorB;
        l_it->DomainColorG = domain.DomainColorG;
        l_it->DomainColorR = domain.DomainColorR;
        l_it->DomainShow = domain.DomainShow;
    }
    else
    {
        m_mapDomain.insert(domain.TargetID,domain);
    }
}

void hgWarningSetManager::SaveAnchorArea(AnchorArea &anchor)
{
    QMap<QString,AnchorArea>::iterator l_it = m_mapAnchorArea.find(anchor.TargetID);
    if (l_it != m_mapAnchorArea.end())
    {
        l_it->b_AnchorArea = anchor.b_AnchorArea;
    }
    else
    {
        m_mapAnchorArea.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveAnchorWatch(AnchorWatch &anchor)
{
    QMap<QString,AnchorWatch>::iterator l_it = m_mapAnchorWatch.find(anchor.TargetID);
    if (l_it != m_mapAnchorWatch.end())
    {
        l_it->b_AnchorWatch = anchor.b_AnchorWatch;
        l_it->Clubbing = anchor.Clubbing;
        l_it->Dragging = anchor.Dragging;
        l_it->AnchorLat = anchor.AnchorLat;
        l_it->AnchorLon = anchor.AnchorLon;
    }
    else
    {
        m_mapAnchorWatch.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveAnchorReserv(AnchorReserv &anchor)
{
    QMap<QString,AnchorReserv>::iterator l_it = m_mapAnchorReserv.find(anchor.TargetID);
    if (l_it != m_mapAnchorReserv.end())
    {
        l_it->b_AnchorReserv = anchor.b_AnchorReserv;
        l_it->ID = anchor.ID;
        l_it->Type = anchor.Type;
        l_it->ETA = anchor.ETA;
        l_it->ETD = anchor.ETD;
        l_it->Tracks = anchor.Tracks;
    }
    else
    {
        m_mapAnchorReserv.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveBerthWatch(BerthWatch &anchor)
{
    QMap<QString,BerthWatch>::iterator l_it = m_mapBerthWatch.find(anchor.TargetID);
    if (l_it != m_mapBerthWatch.end())
    {
        l_it->b_BerthWatch = anchor.b_BerthWatch;
        l_it->Distance = anchor.Distance;
        l_it->BerthLat = anchor.BerthLat;
        l_it->BerthLon = anchor.BerthLon;
    }
    else
    {
        m_mapBerthWatch.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveCollisionWatch(CollisionWatch &anchor)
{
    QMap<QString,CollisionWatch>::iterator l_it = m_mapCollisionWatch.find(anchor.TargetID);
    if (l_it != m_mapCollisionWatch.end())
    {
        l_it->b_CollisionWatch = anchor.b_CollisionWatch;
        l_it->DCPA = anchor.DCPA;
        l_it->TCPA = anchor.TCPA;
        if (anchor.Type == Custom)
        {
            l_it->CustomDCPA = anchor.DCPA;
            l_it->CustomTCPA = anchor.TCPA;
        }
    }
    else
    {
        if (anchor.Type == Custom)
        {
            l_it->CustomDCPA = anchor.DCPA;
            l_it->CustomTCPA = anchor.TCPA;
        }
        else
        {
            l_it->CustomDCPA = 0;
            l_it->CustomTCPA = 0;
        }
        m_mapCollisionWatch.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveGroundWatch(GroundWatch &anchor)
{
    QMap<QString,GroundWatch>::iterator l_it = m_mapGroundWatch.find(anchor.TargetID);
    if (l_it != m_mapGroundWatch.end())
    {
        l_it->b_GroundWatch = anchor.b_GroundWatch;
        l_it->GroundDraught = anchor.GroundDraught;
        l_it->KeelClearance = anchor.KeelClearance;
    }
    else
    {
        m_mapGroundWatch.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveNavigatChannel(NavigatChannel &anchor)
{
    QMap<QString,NavigatChannel>::iterator l_it = m_mapNavigatChannel.find(anchor.TargetID);
    if (l_it != m_mapNavigatChannel.end())
    {
        l_it->b_NavigatChannel = anchor.b_NavigatChannel;
        l_it->ID = anchor.ID;
        l_it->Type = anchor.Type;
    }
    else
    {
        m_mapNavigatChannel.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveReportArea(ReportArea &anchor)
{
    QMap<QString,ReportArea>::iterator l_it = m_mapReportArea.find(anchor.TargetID);
    if (l_it != m_mapReportArea.end())
    {
        l_it->b_ReportArea = anchor.b_ReportArea;
        l_it->b_Pattern = anchor.b_Pattern;
        l_it->mapAreaData = anchor.mapAreaData;
        l_it->EarilestTime = anchor.EarilestTime;
        l_it->LatestTime = anchor.LatestTime;
        l_it->enter = false;
    }
    else
    {
        m_mapReportArea.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveSpeedWatch(SpeedWatch &anchor)
{
    QMap<QString,SpeedWatch>::iterator l_it = m_mapSpeedWatch.find(anchor.TargetID);
    if (l_it != m_mapSpeedWatch.end())
    {
        l_it->b_SpeedWatch = anchor.b_SpeedWatch;
        l_it->MinSpeed = anchor.MinSpeed;
        l_it->MinDuration = anchor.MinDuration;
        l_it->MaxSpeed = anchor.MaxSpeed;
        l_it->MaxDuration = anchor.MaxDuration;
    }
    else
    {
        m_mapSpeedWatch.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveSetShip(SetShip &anchor)
{
    QMap<QString,SetShip>::iterator l_it = m_mapSetShip.find(anchor.TargetID);
    if (l_it != m_mapSetShip.end())
    {
        l_it->b_SetShip = anchor.b_SetShip;
        l_it->ShipType = anchor.ShipType;
        l_it->Length = anchor.Length;
        l_it->With = anchor.With;
    }
    else
    {
        m_mapSetShip.insert(anchor.TargetID,anchor);
    }
}

void hgWarningSetManager::SaveTurnCircle(TurnCircle &anchor)
{
    QMap<QString,TurnCircle>::iterator l_it = m_mapTurnCircle.find(anchor.TargetID);
    if (l_it != m_mapTurnCircle.end())
    {
        l_it->b_TurnCircle = anchor.b_TurnCircle;
        l_it->TurnRadius = anchor.TurnRadius;
        l_it->TurnLat = anchor.TurnLat;
        l_it->TurnLon = anchor.TurnLon;
    }
    else
    {
        m_mapTurnCircle.insert(anchor.TargetID,anchor);
    }
}


void hgWarningSetManager::SaveMovementEnd(MovementEnd &anchor)
{
    QMap<QString,MovementEnd>::iterator l_it = m_mapMovementEnd.find(anchor.TargetID);
    if (l_it != m_mapMovementEnd.end())
    {
        l_it->b_MovementEnd = anchor.b_MovementEnd;
        l_it->EndTime = anchor.EndTime;
        l_it->EndLat = anchor.EndLat;
        l_it->EndLon = anchor.EndLon;
    }
    else
    {
        m_mapMovementEnd.insert(anchor.TargetID,anchor);
    }
}



void hgWarningSetManager::SaveCollisionWarn(QString MMSI, QString RefMMSI)
{
    QMap<QString,QStringList>::iterator l_it = m_mapCollisionWarn.find(MMSI);
    if (l_it != m_mapCollisionWarn.end())
    {
        for (int i = 0; i < l_it.value().size(); i++)
        {
            if(l_it.value()[i] == RefMMSI)
            {
                return;
            }
        }
        l_it.value().append(RefMMSI);
    }
    else
    {
        m_mapCollisionWarn.insert(MMSI,QStringList(RefMMSI));
    }
}

void hgWarningSetManager::ReadDomain(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("domain_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        Domain l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.DomainWatch = l_record.value("DomainWatch").toInt();
        l_data.DomainRadius = l_record.value("DomainRadius").toDouble();
        l_data.DomainColorR = l_record.value("DomainColorR").toInt();
        l_data.DomainColorG = l_record.value("DomainColorG").toInt();
        l_data.DomainColorB = l_record.value("DomainColorB").toInt();
        l_data.DomainShow = l_record.value("DomainShow").toInt();
        m_mapDomain.insert(l_data.TargetID,l_data);
        if (l_data.DomainWatch == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,OtherType);
        }
    }
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("Domain",WarningDomainWatch,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadAuthorized(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("authorized_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
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
        Authorized l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.Authorize = l_record.value("Authorize").toInt();
        m_mapAuthorized.insert(l_data.TargetID,l_data);
    }  
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadAnchorArea(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("anchor_area_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        AnchorArea l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_AnchorArea = l_record.value("b_AnchorArea").toInt();
        l_data.ID = l_record.value("ID").toString();
        l_data.Type = l_record.value("Type").toInt();
        m_mapAnchorArea.insert(l_data.TargetID,l_data);
        if (l_data.b_AnchorArea == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.ID,IsAnchorArea);
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("AnchorArea",WarningAnchorArea,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadAnchorWatch(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("anchor_watch_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        AnchorWatch l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_AnchorWatch = l_record.value("b_AnchorWatch").toInt();
        l_data.Clubbing = l_record.value("Clubbing").toDouble();
        l_data.Dragging = l_record.value("Dragging").toDouble();
        l_data.AnchorLat = l_record.value("AnchorLat").toDouble();
        l_data.AnchorLon = l_record.value("AnchorLon").toDouble();
        m_mapAnchorWatch.insert(l_data.TargetID,l_data);
        if (l_data.b_AnchorWatch == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsClubbing);
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsDragging);
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("AnchorWatch",WarningAnchorWatch,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadAnchorReserv(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("anchor_reserv_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        AnchorReserv l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_AnchorReserv = l_record.value("b_AnchorReserv").toInt();
        l_data.ID = l_record.value("ID").toString();
        l_data.Type = l_record.value("Type").toInt();
        l_data.ETA = l_record.value("ETA").toInt();
        l_data.ETD = l_record.value("ETD").toInt();
        l_data.Tracks = l_record.value("Tracks").toInt();
        m_mapAnchorReserv.insert(l_data.TargetID,l_data);
        if (l_data.b_AnchorReserv == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsAnchorReserv);
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("AnchorReserv",WarningAnchorReserv,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadBerthWatch(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("berth_watch_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        BerthWatch l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_BerthWatch = l_record.value("b_BerthWatch").toInt();
        l_data.Distance = l_record.value("Distance").toDouble();
        l_data.BerthLat = l_record.value("BerthLat").toDouble();
        l_data.BerthLon = l_record.value("BerthLon").toDouble();
        m_mapBerthWatch.insert(l_data.TargetID,l_data);
        if (l_data.b_BerthWatch == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsBerthWatch);
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("BerthWatch",WarningBerthWatch,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadCollisionWatch(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("collision_watch_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        CollisionWatch l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_CollisionWatch = l_record.value("b_CollisionWatch").toInt();
        l_data.DCPA = l_record.value("DCPA").toDouble();
        l_data.TCPA = l_record.value("TCPA").toDouble();
        m_mapCollisionWatch.insert(l_data.TargetID,l_data);
        if (l_data.b_CollisionWatch == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,OtherType);
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("GroundWatch",WarningGroundWatch,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadGroundWatch(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("ground_watch_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        GroundWatch l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_GroundWatch = l_record.value("b_GroundWatch").toInt();
        l_data.GroundDraught = l_record.value("GroundDraught").toDouble();
        l_data.KeelClearance = l_record.value("KeelClearance").toDouble();
        m_mapGroundWatch.insert(l_data.TargetID,l_data);
        if (l_data.b_GroundWatch == true)
        {
            l_find = true;
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("GroundWatch",WarningGroundWatch,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadNavigatChannel(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("navigat_channel_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        NavigatChannel l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_NavigatChannel = l_record.value("b_NavigatChannel").toInt();
        l_data.ID = l_record.value("ID").toString();
        l_data.Type = l_record.value("Type").toInt();
        m_mapNavigatChannel.insert(l_data.TargetID,l_data);
        if (l_data.b_NavigatChannel == true)
        {
            l_find = true;
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("NavigatChannel",WarningChannel,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadReportArea(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("report_area_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        ReportArea l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_ReportArea = l_record.value("b_ReportArea").toInt();
        l_data.b_Pattern = l_record.value("b_Pattern").toInt();

        QByteArray area = l_record.value("AreaData").toByteArray();
        QDataStream in(&area,QIODevice::ReadOnly);
        for (int i = 0; ; i++)
        {
            if (in.atEnd())
            {
                break;
            }
            AreaData l_AreaData;
            in >> l_AreaData.ID >> l_AreaData.type;
            l_data.mapAreaData.insert(l_AreaData.ID,l_AreaData);
        }

        l_data.EarilestTime = l_record.value("EarilestTime").toInt();
        l_data.LatestTime = l_record.value("LatestTime").toInt();
        m_mapReportArea.insert(l_data.TargetID,l_data);
        if (l_data.b_ReportArea == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsReportArea);
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsReportTime);
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("ReportArea",WarningReportArea,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadSpeedWatch(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("speed_watch_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        SpeedWatch l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_SpeedWatch = l_record.value("b_SpeedWatch").toInt();
        l_data.MinSpeed = l_record.value("MinSpeed").toDouble();
        l_data.MinDuration = l_record.value("MinDuration").toDouble();
        l_data.MaxSpeed = l_record.value("MaxSpeed").toDouble();
        l_data.MaxDuration = l_record.value("MaxDuration").toDouble();
        l_data.MinTimeKeep = l_record.value("MinTimeKeep").toDouble();
        l_data.MaxTimeKeep = l_record.value("MaxTimeKeep").toDouble();
        m_mapSpeedWatch.insert(l_data.TargetID,l_data);
        if (l_data.b_SpeedWatch == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsMinSpeed);
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsMaxSpeed);
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("SpeedWatch",WarningSpeed,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadSetShip(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("set_ship_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
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
        SetShip l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_SetShip = l_record.value("b_SetShip").toInt();
        l_data.ShipType = l_record.value("ShipType").toString();
        l_data.With = l_record.value("ShipWidth").toDouble();
        l_data.Length = l_record.value("ShipLength").toDouble();
        m_mapSetShip.insert(l_data.TargetID,l_data);
    }  
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadTurnCircle(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("turn_circle_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        TurnCircle l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_TurnCircle = l_record.value("b_TurnCircle").toInt();
        l_data.TurnRadius = l_record.value("TurnRadius").toDouble();
        l_data.TurnLat = l_record.value("TurnLat").toDouble();
        l_data.TurnLon = l_record.value("TurnLon").toDouble();
        m_mapTurnCircle.insert(l_data.TargetID,l_data);
        if (l_data.b_TurnCircle == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsTurnCircle);
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("TurnCircle",WarningTurnCircle,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::ReadMovementEnd(hgSqlOperator& sqlOperator, vtsServer *s)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("movement_end_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    bool l_find = false;
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        MovementEnd l_data;
        l_data.TargetID = l_record.value("MMSI").toString();
        l_data.b_MovementEnd = l_record.value("b_MovementEnd").toInt();
        l_data.EndTime = l_record.value("EndTime").toDouble();
        l_data.EndLat = l_record.value("EndLat").toInt();
        l_data.EndLon = l_record.value("EndLon").toInt();
        m_mapMovementEnd.insert(l_data.TargetID,l_data);
        if (l_data.b_MovementEnd == true)
        {
            l_find = true;
            hgAlarmManager::m_WarningSetManager.SetWarnInfo(l_data.TargetID,IsMovementEnd);
        }
    }  
    if (l_find == true)
    {
        hgAlarmManager::StartWarning("MovementEnd",WarningMovementEnd,s);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgWarningSetManager::SendWarnSet(QString ID, ConnectionPtr& connect)
{
    QMap<QString,Authorized>::iterator l_itAuthorized = m_mapAuthorized.find(ID);
    if (l_itAuthorized != m_mapAuthorized.end())
    {
        hgAuthorized l_Authorized;
        l_Authorized.set_mmsi(l_itAuthorized->TargetID.toStdString());
        l_Authorized.set_authorized(l_itAuthorized->Authorize);

        hgSendManager::SendExceptShipMessage("Authorized",l_Authorized,connect);
    }

    QMap<QString,AnchorArea>::iterator l_itArea = m_mapAnchorArea.find(ID);
    if (l_itArea != m_mapAnchorArea.end())
    {
        hgAnchorAreaMes l_AnchorArea;
        l_AnchorArea.set_mmsi(l_itArea->TargetID.toStdString());
        l_AnchorArea.set_anchorarea(l_itArea->b_AnchorArea); 
        l_AnchorArea.set_id(l_itArea->ID.toStdString());
        l_AnchorArea.set_type(l_itArea->Type);

        hgSendManager::SendExceptShipMessage("AnchorArea",l_AnchorArea,connect);
    }

    QMap<QString,AnchorWatch>::iterator l_itAnchorWatch = m_mapAnchorWatch.find(ID);
    if (l_itAnchorWatch != m_mapAnchorWatch.end())
    {
        hgAnchorWatch l_AnchorWatch;
        l_AnchorWatch.set_mmsi(l_itAnchorWatch->TargetID.toStdString());
        l_AnchorWatch.set_anchorwatch(l_itAnchorWatch->b_AnchorWatch);
        l_AnchorWatch.set_clubbing(l_itAnchorWatch->Clubbing);
        l_AnchorWatch.set_dragging(l_itAnchorWatch->Dragging);
        l_AnchorWatch.set_lat(l_itAnchorWatch->AnchorLat);
        l_AnchorWatch.set_lon(l_itAnchorWatch->AnchorLon);

        hgSendManager::SendExceptShipMessage("AnchorWatch",l_AnchorWatch,connect);
    }

    QMap<QString,AnchorReserv>::iterator l_itAnchorReserv = m_mapAnchorReserv.find(ID);
    if (l_itAnchorReserv != m_mapAnchorReserv.end())
    {
        hgAnchorReserv l_AnchorReserv;
        l_AnchorReserv.set_mmsi(l_itAnchorReserv->TargetID.toStdString());
        l_AnchorReserv.set_anchorreserv(l_itAnchorReserv->b_AnchorReserv);
        l_AnchorReserv.set_id(l_itAnchorReserv->ID.toStdString());
        l_AnchorReserv.set_type(l_itAnchorReserv->Type);
        l_AnchorReserv.set_eta(l_itAnchorReserv->ETA);
        l_AnchorReserv.set_etd(l_itAnchorReserv->ETD);
        l_AnchorReserv.set_tracks(l_itAnchorReserv->Tracks);

        hgSendManager::SendExceptShipMessage("AnchorReserv",l_AnchorReserv,connect);
    }

    QMap<QString,BerthWatch>::iterator l_itBerthWatch = m_mapBerthWatch.find(ID);
    if (l_itBerthWatch != m_mapBerthWatch.end())
    {
        hgBerthWatch l_BerthWatch;
        l_BerthWatch.set_mmsi(l_itBerthWatch->TargetID.toStdString());
        l_BerthWatch.set_berthwatch(l_itBerthWatch->b_BerthWatch);
        l_BerthWatch.set_distance(l_itBerthWatch->Distance);
        l_BerthWatch.set_lat(l_itBerthWatch->BerthLat);
        l_BerthWatch.set_lon(l_itBerthWatch->BerthLon);

        hgSendManager::SendExceptShipMessage("BerthWatch",l_BerthWatch,connect);
    }

    QMap<QString,CollisionWatch>::iterator l_itCollisionWatch = m_mapCollisionWatch.find(ID);
    if (l_itCollisionWatch != m_mapCollisionWatch.end())
    {
        hgCollisionWatch l_CollisionWatch;
        l_CollisionWatch.set_mmsi(l_itCollisionWatch->TargetID.toStdString());
        l_CollisionWatch.set_collisionwatch(l_itCollisionWatch->b_CollisionWatch);
        l_CollisionWatch.set_dcpa(l_itCollisionWatch->DCPA);
        l_CollisionWatch.set_tcpa(l_itCollisionWatch->TCPA);
        l_CollisionWatch.set_tcpa(l_itCollisionWatch->Type);

        hgSendManager::SendExceptShipMessage("CollisionWatch",l_CollisionWatch,connect);
    }

    QMap<QString,Domain>::iterator l_itDomain = m_mapDomain.find(ID);
    if (l_itDomain != m_mapDomain.end())
    {
        hgDomain l_Domain;
        l_Domain.set_mmsi(l_itDomain->TargetID.toStdString());
        l_Domain.set_domainwatch(l_itDomain->DomainWatch);
        l_Domain.set_domainradius(l_itDomain->DomainRadius);
        l_Domain.set_domaincolorr(l_itDomain->DomainColorR);
        l_Domain.set_domaincolorg(l_itDomain->DomainColorG);
        l_Domain.set_domaincolorb(l_itDomain->DomainColorB);
        l_Domain.set_domainshow(l_itDomain->DomainShow);

        hgSendManager::SendExceptShipMessage("Domain",l_Domain,connect);
    }

    QMap<QString,GroundWatch>::iterator l_itGroundWatch = m_mapGroundWatch.find(ID);
    if (l_itGroundWatch != m_mapGroundWatch.end())
    {
        hgGroundWatch l_GroundWatch;
        l_GroundWatch.set_mmsi(l_itGroundWatch->TargetID.toStdString());
        l_GroundWatch.set_groundwatch(l_itGroundWatch->b_GroundWatch);
        l_GroundWatch.set_grounddraught(l_itGroundWatch->GroundDraught);
        l_GroundWatch.set_keelclearance(l_itGroundWatch->KeelClearance);

        hgSendManager::SendExceptShipMessage("GroundWatch",l_GroundWatch,connect);
    }

    QMap<QString,NavigatChannel>::iterator l_itNavigatChannel = m_mapNavigatChannel.find(ID);
    if (l_itNavigatChannel != m_mapNavigatChannel.end())
    {
        hgNavigatChannel l_NavigatChannel;
        l_NavigatChannel.set_mmsi(l_itNavigatChannel->TargetID.toStdString());
        l_NavigatChannel.set_channel(l_itNavigatChannel->b_NavigatChannel);
        l_NavigatChannel.set_id(l_itNavigatChannel->ID.toStdString());
        l_NavigatChannel.set_type(l_itNavigatChannel->Type);

        hgSendManager::SendExceptShipMessage("NavigatChannel",l_NavigatChannel,connect);
    }

    QMap<QString,ReportArea>::iterator l_itReportArea = m_mapReportArea.find(ID); 
    if (l_itReportArea != m_mapReportArea.end())
    {
        hgReportArea l_ReportArea;
        l_ReportArea.set_mmsi(l_itReportArea->TargetID.toStdString());
        l_ReportArea.set_reportarea(l_itReportArea->b_ReportArea);
        l_ReportArea.set_pattern(l_itReportArea->b_Pattern);
        
        hgAreaData* l_AreaData = l_ReportArea.add_areadata();
        QMap<QString,AreaData>::iterator it = l_itReportArea->mapAreaData.begin();
        for (it; it != l_itReportArea->mapAreaData.end(); ++it)
        {
            l_AreaData->set_id(it->ID.toStdString());
            l_AreaData->set_type(it->type);
        }

        l_ReportArea.set_earlisttime(l_itReportArea->EarilestTime);
        l_ReportArea.set_latesttime(l_itReportArea->LatestTime);

        hgSendManager::SendExceptShipMessage("ReportArea",l_ReportArea,connect);
    }

    QMap<QString,SpeedWatch>::iterator l_itSpeedWatch = m_mapSpeedWatch.find(ID); 
    if (l_itSpeedWatch != m_mapSpeedWatch.end())
    {
        hgSpeedWatch l_SpeedWatch;
        l_SpeedWatch.set_mmsi(l_itSpeedWatch->TargetID.toStdString());
        l_SpeedWatch.set_speedwatch(l_itSpeedWatch->b_SpeedWatch);
        l_SpeedWatch.set_minspeed(l_itSpeedWatch->MinSpeed);
        l_SpeedWatch.set_minduration(l_itSpeedWatch->MinDuration);
        l_SpeedWatch.set_maxspeed(l_itSpeedWatch->MaxSpeed);
        l_SpeedWatch.set_maxduration(l_itSpeedWatch->MaxDuration);

        hgSendManager::SendExceptShipMessage("SpeedWatch",l_SpeedWatch,connect);
    }

    QMap<QString,SetShip>::iterator l_itSetShip = m_mapSetShip.find(ID); 
    if (l_itSetShip != m_mapSetShip.end())
    {
        hgSetShip l_SetShip;
        l_SetShip.set_mmsi(l_itSetShip->TargetID.toStdString());
        l_SetShip.set_setship(l_itSetShip->b_SetShip);
        l_SetShip.set_shiplength(l_itSetShip->Length);
        l_SetShip.set_shipwidth(l_itSetShip->With); 
        l_SetShip.set_shiptype(l_itSetShip->ShipType.toStdString());

        hgSendManager::SendExceptShipMessage("SetShip",l_SetShip,connect);
    }

    QMap<QString,TurnCircle>::iterator l_itTurn = m_mapTurnCircle.find(ID); 
    if (l_itTurn != m_mapTurnCircle.end())
    {
        hgTurnCircle l_TurnCircle;
        l_TurnCircle.set_mmsi(l_itTurn->TargetID.toStdString());
        l_TurnCircle.set_turncircle(l_itTurn->b_TurnCircle);
        l_TurnCircle.set_radius(l_itTurn->TurnRadius);
        l_TurnCircle.set_lat(l_itTurn->TurnLat);
        l_TurnCircle.set_lon(l_itTurn->TurnLon);

        hgSendManager::SendExceptShipMessage("TurnCircle",l_TurnCircle,connect);
    }

    QMap<QString,MovementEnd>::iterator l_itMovementEnd = m_mapMovementEnd.find(ID); 
    if (l_itMovementEnd != m_mapMovementEnd.end())
    {
        hgMovementEnd l_MovementEnd;
        l_MovementEnd.set_mmsi(l_itMovementEnd->TargetID.toStdString());
        l_MovementEnd.set_movementend(l_itMovementEnd->b_MovementEnd);
        l_MovementEnd.set_time(l_itMovementEnd->EndTime);

        hgSendManager::SendExceptShipMessage("MovementEnd",l_MovementEnd,connect);
    }
}
