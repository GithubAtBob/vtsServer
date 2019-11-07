#include "StdAfx.h"
#include "hgSectorTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>

#include "frame/vtsConnectionManager.h"
#include "OverLoad.h"
#include "hgutils/PolygonLL.h"
#include "hgutils/NavUtil.h"
#include "message/waring.pb.h"
#include "Managers/hgLayerDataManager.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgTargetManager.h"

extern const char* hgWaringTypeGuid[];

extern const char* hgAnchorageTypeGuid[];

extern const char* hgAnchorageTypeName[];

hgSectorTimerHandler::hgSectorTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgSectorTimerHandler::~hgSectorTimerHandler(void)
{
}

vtsTimerHandler::WorkMode hgSectorTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgSectorTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    for (auto l_AreaIter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.begin(); 
        l_AreaIter != hgAlarmManager::m_LayerDataManager.m_pSectorMap.end();
        l_AreaIter++)
    {
        QMap <QString,hgSectorLayer>::Iterator l_polyiter = l_AreaIter;
        hgSectorLayer& l_Layer = l_polyiter.value();
        auto l_Targetiter = hgTargetManager::m_mapTarget.begin();
        if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pSectorMap.end() || l_Targetiter == hgTargetManager::m_mapTarget.end())
        {
            continue;
        }
        for ( ; l_Targetiter != hgTargetManager::m_mapTarget.end(); ++l_Targetiter )
        {

            hgTarget l_ais = l_Targetiter.value();
            hg::utils::PointLL l_TargetPosition;
            l_TargetPosition.setLat(l_ais.Lat);
            l_TargetPosition.setLon(l_ais.Lon);
            if (!l_TargetPosition.isValid())
            {
                continue;
            }
            hg::utils::PointLL l_CenterLL;
            l_CenterLL.setLat(l_Layer.m_Lat);
            l_CenterLL.setLon(l_Layer.m_Lon);
            InitShipWarningInfo(l_Layer,l_ais,l_polyiter.key());
            if (hgAlarmManager::PointInsideSector(l_TargetPosition.lat(),l_TargetPosition.lon()
                ,l_Layer.m_Lat,l_Layer.m_Lon,l_Layer.m_Radius
                ,l_Layer.m_BeginAngle,l_Layer.m_EndAngle))//在区域内
            {
                InsideWatch(l_polyiter.key(),l_Layer,l_ais,l_polyiter.key());//内部警报
            }
            else
            {
                OutsideWatch(l_polyiter.key(),l_Layer,l_ais,l_polyiter.key());//外部警报
            }
            FinishIninData(l_Layer,l_ais,l_polyiter.key());
        }
        CongestionWatch(l_polyiter.key(),l_Layer,l_polyiter.key());
    }

    hgTargetManager::m_mapTarget.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgSectorTimerHandler TimeDiff: " << diff;
		}
//     auto l_lockerTarget = hgTargetManager::getMapTargetLocker();
//     auto &l_mapTarget = l_lockerTarget->raw();
//     auto l_Targetiter = l_mapTarget.begin();
//     QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(this->name().c_str());
//     hgSectorLayer& l_Layer = l_polyiter.value();
//     if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pSectorMap.end() || l_Targetiter == l_mapTarget.end())
//     {
//         return;
//     }
//     for ( ; l_Targetiter != l_mapTarget.end(); ++l_Targetiter )
//     {
//         
// 
//         hgTarget l_ais = l_Targetiter.value();
//         hg::utils::PointLL l_TargetPosition;
//         l_TargetPosition.setLat(l_ais.Lat);
//         l_TargetPosition.setLon(l_ais.Lon);
//         if (!l_TargetPosition.isValid())
//         {
//             continue;
//         }
//         hg::utils::PointLL l_CenterLL;
//         l_CenterLL.setLat(l_Layer.m_Lat);
//         l_CenterLL.setLon(l_Layer.m_Lon);
//         InitShipWarningInfo(l_Layer,l_ais);
//         if (hgAlarmManager::PointInsideSector(l_TargetPosition.lat(),l_TargetPosition.lon()
//             ,l_Layer.m_Lat,l_Layer.m_Lon,l_Layer.m_Radius
//             ,l_Layer.m_BeginAngle,l_Layer.m_EndAngle))//在区域内
//         {
//             InsideWatch(l_polyiter.key(),l_Layer,l_ais);//内部警报
//         }
//         else
//         {
//             OutsideWatch(l_polyiter.key(),l_Layer,l_ais);//外部警报
//         }
//         FinishIninData(l_Layer,l_ais);
//     }
//     CongestionWatch(l_polyiter.key(),l_Layer);
}

void hgSectorTimerHandler::SQLOperate(hgWarningMes& mes)
{
    QSqlDatabase database = this->server()->openDBConnection();
    hgSqlOperator l_sqlOperator(database);
    {
        hgAlarmManager::SaveWarnData(l_sqlOperator,mes);
    }
    this->server()->closeDBConnection(database);
}

void hgSectorTimerHandler::InsideWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    InsideInitData(layer,ais,areaID);//必须在最前面
    EnterWatch(GUID,layer,ais,areaID);
    HighSpeedWatch(GUID,layer,ais,areaID);
    LowSpeedWatch(GUID,layer,ais,areaID);
    ProhibitedWatch(GUID,layer,ais,areaID);
    AnchorageWatch(GUID,layer,ais,areaID);
    AddWatch(GUID,layer,ais,areaID);
    CourseWatch(GUID,layer,ais,areaID);
    GroundWatch(GUID,layer,ais,areaID);
    FoggyAreaWatch(GUID,layer,areaID);
}

void hgSectorTimerHandler::OutsideWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    OusideInitData(layer,ais,areaID);//必须在最前面
    LeaveWatch(GUID,layer,ais,areaID);
    ApproachWatch(GUID,layer,ais,areaID);
}

void hgSectorTimerHandler::InitShipWarningInfo(hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_Info.find(ais.ID) == layer.m_Info.end())//此船是否在图形内记录
    {
        hgShipWarningInfo l_SWI;
        layer.m_Info.insert(ais.ID,l_SWI);
    }
}

void hgSectorTimerHandler::InsideInitData(hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_Info.contains(ais.ID))
    {
        layer.m_Info.find(ais.ID).value().ResetOutside();
    }
    NewTrack(layer,ais,areaID);
    if (!layer.m_InsideMMSI.contains(ais.ID))
    {
        layer.m_InsideMMSI.insert(ais.ID,"");
    }
}

void hgSectorTimerHandler::OusideInitData(hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_Info.contains(ais.ID))
    {
        layer.m_Info.find(ais.ID).value().ResetInside();
    }
    LostWatch(layer,ais,areaID);
    if (layer.m_InsideMMSI.contains(ais.ID))
    {
        layer.m_InsideMMSI.remove(ais.ID);
    }
}

void hgSectorTimerHandler::FinishIninData(hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_Info.contains(ais.ID))
    {
        layer.m_Info.find(ais.ID).value().LastSOG = ais.SOG; //将上次速度改为这次速度
        layer.m_Info.find(ais.ID).value().LastTime = hgTargetManager::GetWarnTime(); //将上次时间改为这次时间
    }
}

void hgSectorTimerHandler::NewTrack(hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    ///////////新目标抑制（没选中则有新船报警）
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[NEWTRACKWARINGSUPPRESSION]) == -1)
    {
        if (layer.m_WaringID.indexOf(hgWaringTypeGuid[NEWTRACK]) != -1)
        {
            if (layer.m_InsideMMSI.find(ais.ID) == layer.m_InsideMMSI.end())
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[NEWTRACK]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname("New Track");
                l_mes.set_mmsi(ais.ID.toStdString());
                l_mes.set_userlayguid(areaID.toStdString());
                l_mes.set_userlayid(UserLayerType::USector);
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                SQLOperate(l_mes);
            }
        }
    }
}

void hgSectorTimerHandler::EnterWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    ///////////////////入侵
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[ENTERWATCH]) != -1)//先判断是否有权限
    {
        if (hgAlarmManager::SectorEnterWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[ENTERWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Enter");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
    else
    {
        if (layer.m_Info.contains(ais.ID))
        {
            layer.m_Info.find(ais.ID).value().Position = InsidePos;
        }
    }
}

void hgSectorTimerHandler::HighSpeedWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    //////高速监控
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[HIGHSPEEDWATCH]) != -1)
    {
        if (hgAlarmManager::SectorHighSpeed(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[HIGHSPEEDWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("High Speed");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
    else
    {
        if (layer.m_Info.contains(ais.ID))
        {
            layer.m_Info.find(ais.ID).value().HighTime = -1;
            layer.m_Info.find(ais.ID).value().IsSendHighSpeed = false;
        }
    }
}

void hgSectorTimerHandler::LowSpeedWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    /////低速监控
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[LOWSPEEDWATCH]) != -1)
    {
        if (hgAlarmManager::SectorLowSpeed(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[LOWSPEEDWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Low Speed");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
    else
    {
        if (layer.m_Info.contains(ais.ID))
        {
            layer.m_Info.find(ais.ID).value().LowTime = -1;
            layer.m_Info.find(ais.ID).value().IsSendLowSpeed = false;
        }
    }
}

void hgSectorTimerHandler::ProhibitedWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    /////////禁锚区
    if ( layer.m_WaringID.indexOf(hgWaringTypeGuid[PROHIBITEDANCHORAGE]) != -1)
    {
        if (hgAlarmManager::SectorProhibited(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[PROHIBITEDANCHORAGE]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Prohibited");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
}

void hgSectorTimerHandler::AnchorageWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    /////////抛锚区
    if ( layer.m_WaringID.indexOf(hgWaringTypeGuid[ANCHORAGE]) != -1)
    {
        if (hgAlarmManager::SectorAnchorage(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[ANCHORAGE]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Anchorage");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
}

void hgSectorTimerHandler::AddWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    ////////////////////////加速监控
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[ACCELERATIONWATCH]) != -1)
    {
        if (hgAlarmManager::SectorAddMaxWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[ACCELERATIONWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("AddMax");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
        if (hgAlarmManager::SectorAddMinWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[ACCELERATIONWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("AddMin");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
    else
    {
        if (layer.m_Info.contains(ais.ID))
        {
            layer.m_Info.find(ais.ID).value().AddMaxTime = -1;
            layer.m_Info.find(ais.ID).value().IsSendAddMax = false;
            layer.m_Info.find(ais.ID).value().AddMinTime = -1;
            layer.m_Info.find(ais.ID).value().IsSendAddMin = false;
        }
    }
}

void hgSectorTimerHandler::CourseWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    ///航向突变监控(Course Change Watch)
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[COURSECHANGEWATCH]) != -1)
    {
        if (hgAlarmManager::SectorCourse(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[COURSECHANGEWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Course Change Watch");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
    else
    {
        if (layer.m_Info.contains(ais.ID))
        {
            layer.m_Info.find(ais.ID).value().CourseTime = -1;
            layer.m_Info.find(ais.ID).value().IsSendCourse = false;
        }
    }
}

void hgSectorTimerHandler::GroundWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    ///搁浅监控(Ground Watch)
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[GROUNDINGWATCH]) != -1)
    {
        if (hgAlarmManager::SectorGround(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[GROUNDINGWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Ground Watch");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
    else
    {
        if (layer.m_Info.contains(ais.ID))
        {
            layer.m_Info.find(ais.ID).value().GroundTime = -1;
            layer.m_Info.find(ais.ID).value().IsSendGround = false;
        }
    }
}

void hgSectorTimerHandler::FoggyAreaWatch(QString GUID,hgSectorLayer& layer,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[FoggyArea]) != -1)
    {
        hgAlarmManager::SectorFoggyArea(GUID,this);
    }
}

void hgSectorTimerHandler::LostWatch(hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    ///////////丢失目标抑制（没选中则有离开区域报警）
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[LOSTTRACKWARINGSUPPRESSION]) == -1)
    {
        if (layer.m_WaringID.indexOf(hgWaringTypeGuid[LOSTTRACK]) != -1)
        {
            if (layer.m_InsideMMSI.find(ais.ID) != layer.m_InsideMMSI.end())
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[LOSTTRACK]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname("Lost Track");
                l_mes.set_mmsi(ais.ID.toStdString());
                l_mes.set_userlayguid(areaID.toStdString());
                l_mes.set_userlayid(UserLayerType::USector);
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                SQLOperate(l_mes);
            }
        }
    }
}

void hgSectorTimerHandler::LeaveWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[LEAVINGWATCH]) != -1)
    {
        if (hgAlarmManager::SectorLeaveWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[LEAVINGWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Leave");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
    else
    {
        if (layer.m_Info.contains(ais.ID))
        {
            layer.m_Info.find(ais.ID).value().Position = OutSidePos;
        }
    }
}

void hgSectorTimerHandler::ApproachWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[APPROACHINGWATCH]) != -1)
    {
        if (hgAlarmManager::SectorApproachWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[APPROACHINGWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Approach");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
}

void hgSectorTimerHandler::CongestionWatch(QString GUID,hgSectorLayer& layer,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[CONGESTIONWATCH]) != -1)
    {
        if (hgAlarmManager::SectorCongestionWatch(GUID))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[CONGESTIONWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Congestion");
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::USector);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
}
