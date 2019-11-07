#include "StdAfx.h"
#include "hgPolygonTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include <QUuid>

#include "frame/vtsConnectionManager.h"
#include "OverLoad.h"
#include "hgutils/PolygonLL.h"
#include "hgutils/NavUtil.h"
#include "message/waring.pb.h"
//#include "message/hgWarningMes.pb.h"
#include "Managers/hgLayerDataManager.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgAlarmManager.h"

extern const char* hgWaringTypeGuid[];
extern const char* hgAnchorageTypeGuid[];
extern const char* hgAnchorageTypeName[];

hgPolygonTimerHandler::hgPolygonTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgPolygonTimerHandler::~hgPolygonTimerHandler(void)
{
}

vtsTimerHandler::WorkMode hgPolygonTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgPolygonTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    for (auto l_AreaIter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.begin(); 
        l_AreaIter != hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end();
        l_AreaIter++)
    {
        QMap <QString,hgPolygonLayer>::Iterator &l_polyiter =  l_AreaIter;
        hgPolygonLayer& l_Layer = l_polyiter.value();
        auto l_Targetiter = hgTargetManager::m_mapTarget.begin();
        if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end() || l_Targetiter == hgTargetManager::m_mapTarget.end())
        {
            continue;
        }
        for ( ; l_Targetiter != hgTargetManager::m_mapTarget.end(); ++l_Targetiter)
        {
            hgTarget l_ais = l_Targetiter.value();
            hg::utils::PointLL l_TargetPosition;
            l_TargetPosition.setLat(l_ais.Lat);
            l_TargetPosition.setLon(l_ais.Lon);
            if (!l_TargetPosition.isValid())
            {
                continue;
            }
            InitShipWarningInfo(l_Layer,l_ais,l_polyiter.key());
            if (l_Layer.m_Polygon.containsPoint(l_TargetPosition,Qt::WindingFill))     //在多边形内
            {
                InsideWatch(l_polyiter.key(),l_Layer,l_ais,l_polyiter.key());//内部警报
            }
            else//在外部
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
			vtsInfo << "hgPolygonTimerHandler TimeDiff: " << diff;
		}

//     ///AIS等数据 单个
//     auto l_lockerTarget = hgTargetManager::getMapTargetLocker();
//     auto &l_mapTarget = l_lockerTarget->raw();
//     auto l_Targetiter = l_mapTarget.begin();
//     ///区域数据
//     QMap <QString,hgPolygonLayer>::Iterator &l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(this->name().c_str());
//     hgPolygonLayer& l_Layer = l_polyiter.value();
//      if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end() || l_Targetiter == l_mapTarget.end())
//      {
//          return;
//      }
//      for ( ; l_Targetiter != l_mapTarget.end(); ++l_Targetiter)
//      {
//          hgTarget l_ais = l_Targetiter.value();
//          hg::utils::PointLL l_TargetPosition;
//          l_TargetPosition.setLat(l_ais.Lat);
//          l_TargetPosition.setLon(l_ais.Lon);
//          if (!l_TargetPosition.isValid())
//          {
//              continue;
//          }
//          InitShipWarningInfo(l_Layer,l_ais);
//         if (l_Layer.m_Polygon.containsPoint(l_TargetPosition,Qt::WindingFill))     //在多边形内
//         {
//             InsideWatch(l_polyiter.key(),l_Layer,l_ais);//内部警报
//         }
//         else//在外部
//         {
//             OutsideWatch(l_polyiter.key(),l_Layer,l_ais);//外部警报
//         }
//         FinishIninData(l_Layer,l_ais);
//     }
//         
//     CongestionWatch(l_polyiter.key(),l_Layer);
}

void hgPolygonTimerHandler::SQLOperate(hgWarningMes& mes)
{
    QSqlDatabase database = this->server()->openDBConnection();
    hgSqlOperator l_sqlOperator(database);
    {
        hgAlarmManager::SaveWarnData(l_sqlOperator,mes);
    }
    this->server()->closeDBConnection(database);
}

void hgPolygonTimerHandler::InsideWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
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

void hgPolygonTimerHandler::OutsideWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    OusideInitData(layer,ais,areaID);//必须在最前面
    LeaveWatch(GUID,layer,ais,areaID);
    ApproachWatch(GUID,layer,ais,areaID);
}

void hgPolygonTimerHandler::InitShipWarningInfo(hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_Info.find(ais.ID) == layer.m_Info.end())//此船是否在图形内记录
    {
        hgShipWarningInfo l_SWI;
        layer.m_Info.insert(ais.ID,l_SWI);
    }
}

void hgPolygonTimerHandler::InsideInitData(hgPolygonLayer& layer,hgTarget& ais,QString areaID)
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

void hgPolygonTimerHandler::OusideInitData(hgPolygonLayer& layer,hgTarget& ais,QString areaID)
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

void hgPolygonTimerHandler::FinishIninData(hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_Info.contains(ais.ID))
    {
        layer.m_Info.find(ais.ID).value().LastSOG = ais.SOG; //将上次速度改为这次速度
        layer.m_Info.find(ais.ID).value().LastTime = hgTargetManager::GetWarnTime(); //将上次时间改为这次时间
    }
}

void hgPolygonTimerHandler::NewTrack(hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
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
                l_mes.set_userlayid(UserLayerType::UPolygon);
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                SQLOperate(l_mes);
            }
        }
    }
}

void hgPolygonTimerHandler::EnterWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[ENTERWATCH]) != -1)//先判断是否有权限
    {
        if (hgAlarmManager::PolygonEnterWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[ENTERWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Enter");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
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

void hgPolygonTimerHandler::HighSpeedWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[HIGHSPEEDWATCH]) != -1)
    {
        if (hgAlarmManager::PolygonHighSpeed(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[HIGHSPEEDWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("High Speed");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
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

void hgPolygonTimerHandler::LowSpeedWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[LOWSPEEDWATCH]) != -1)
    {
        if (hgAlarmManager::PolygonLowSpeed(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[LOWSPEEDWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Low Speed");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
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

void hgPolygonTimerHandler::ProhibitedWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if ( layer.m_WaringID.indexOf(hgWaringTypeGuid[PROHIBITEDANCHORAGE]) != -1)
    {
        if (hgAlarmManager::PolygonProhibited(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[PROHIBITEDANCHORAGE]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Prohibited");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
}

void hgPolygonTimerHandler::AnchorageWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if ( layer.m_WaringID.indexOf(hgWaringTypeGuid[ANCHORAGE]) != -1)
    {
        if (hgAlarmManager::PolygonAnchorage(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[ANCHORAGE]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Anchorage");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
}

void hgPolygonTimerHandler::AddWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[ACCELERATIONWATCH]) != -1)
    {
        if (hgAlarmManager::PolygonAddMaxWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[ACCELERATIONWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("AddMax");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
        if (hgAlarmManager::PolygonAddMinWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[ACCELERATIONWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("AddMin");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
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

void hgPolygonTimerHandler::CourseWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[COURSECHANGEWATCH]) != -1)
    {
        if (hgAlarmManager::PolygonCourse(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[COURSECHANGEWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Course Change Watch");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
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

void hgPolygonTimerHandler::GroundWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[GROUNDINGWATCH]) != -1)
    {
        if (hgAlarmManager::PolygonGround(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[GROUNDINGWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Ground Watch");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
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

void hgPolygonTimerHandler::FoggyAreaWatch(QString GUID,hgPolygonLayer& layer,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[FoggyArea]) != -1)
    {
        hgAlarmManager::PolygonFoggyArea(GUID,this);
    }
}

void hgPolygonTimerHandler::LostWatch(hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
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
                l_mes.set_userlayid(UserLayerType::UPolygon);
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

                SQLOperate(l_mes);
            }
        }
    }
}

void hgPolygonTimerHandler::LeaveWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[LEAVINGWATCH]) != -1)
    {
        if (hgAlarmManager::PolygonLeaveWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[LEAVINGWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Leave");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
    else
    {
        layer.m_Info.find(ais.ID).value().Position = OutSidePos;
    }
}

void hgPolygonTimerHandler::ApproachWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[APPROACHINGWATCH]) != -1)
    {
        if (hgAlarmManager::PolygonApproachWatch(GUID,ais.ID,ais))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[APPROACHINGWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Approach");
            l_mes.set_mmsi(ais.ID.toStdString());
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
}

void hgPolygonTimerHandler::CongestionWatch(QString GUID,hgPolygonLayer& layer,QString areaID)
{
    if (layer.m_WaringID.indexOf(hgWaringTypeGuid[CONGESTIONWATCH]) != -1)
    {
        if (hgAlarmManager::PolygonCongestionWatch(GUID))
        {
            hgWarningMes l_mes;
            l_mes.set_warningid(hgWaringTypeGuid[CONGESTIONWATCH]);
            l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
            l_mes.set_warningpriority(PriorityRed);
            l_mes.set_warningname("Congestion");
            l_mes.set_userlayguid(areaID.toStdString());
            l_mes.set_userlayid(UserLayerType::UPolygon);
            l_mes.set_warningtime(hgTargetManager::GetWarnTime());
            hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);

            SQLOperate(l_mes);
        }
    }
}
