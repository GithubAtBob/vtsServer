#include "StdAfx.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"
#include "timer/hgPolygonTimerHandler.h"
#include "timer/hgCricleTimerHandler.h"
#include "timer/hgSectorTimerHandler.h"
#include "timer/hgReportTimerHandler.h"
#include "timer/hgAnchorAreaTimerHandler.h"

#include "timer/hgAnchorAreaTimerHandler.h"
#include "timer/hgAnchorWatchTimerHandler.h"
#include "timer/hgAnchorReservTimerHandler.h"
#include "timer/hgBerthWatchTimerHandler.h"
#include "timer/hgCollisionWatchTimerHandler.h"
#include "timer/hgDomainTimerHandler.h"
#include "timer/hgGroundWatchTimerHandler.h"
#include "timer/hgNavigatChannelTimerHandler.h"
#include "timer/hgReportAreaTimerHandler.h"
#include "timer/hgSpeedWatchTimerHandler.h"
#include "timer/hgTurnCircleTimerHandler.h"
#include "timer/hgMovementEndTimerHandler.h"

#include "hgutils/PolygonLL.h"
#include "hgutils/PointLL.h"
#include "hgutils/NavUtil.h"
#include "hgutils/MathUtil.h"

#include "Managers/hgTargetManager.h"

#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"
#include "Managers/hgWarningSetManager.h"
#include "Managers/hgConfigManager.h"
#include "Config/hgSysConfig.h"
#include "hgSqlInsertCmd.h"
#include "message/hgWarningMes.pb.h"
#include "message/AlgorithmMode.pb.h"

#include "Managers/hgSendManager.h"
extern const char* hgWaringTypeGuid[];
extern const char* hgAnchorageTypeGuid[];
extern const char* hgAnchorageTypeName[];

hgLayerDataManager hgAlarmManager::m_LayerDataManager;
hgWarningSetManager hgAlarmManager::m_WarningSetManager;
QStringList hgAlarmManager::m_listArea;
QMap <QString, int> hgAlarmManager::m_ShipPosition;
int hgAlarmManager::m_AlgorithmMode = AlgorithmModeType::NoneModel;
double hgAlarmManager::m_alarm1 = 3.2;
double hgAlarmManager::m_alarm2 = 2.2;
double hgAlarmManager::m_alarm3 = 1.0;
hgAlarmManager::hgAlarmManager(void)
{

}

hgAlarmManager::~hgAlarmManager(void)
{

}

void hgAlarmManager::ReadLayerData(hgSqlOperator& sqlOperator)
{
    for (int i = 0; i < 13; i++)
    {
        m_LayerDataManager.m_ShipMap.insert(hgAnchorageTypeName[i],hgAnchorageTypeGuid[i]);
    }
    m_LayerDataManager.ReadPloygon(sqlOperator);
    m_LayerDataManager.ReadEllipse(sqlOperator);
    m_LayerDataManager.ReadCricle(sqlOperator);
    m_LayerDataManager.ReadSector(sqlOperator);
    m_LayerDataManager.ReadDutyArea(sqlOperator);
    m_LayerDataManager.ReadReportLine(sqlOperator);
    m_LayerDataManager.ReadChannel(sqlOperator);
    m_LayerDataManager.ReadNotes(sqlOperator);
    m_LayerDataManager.ReadAidSail(sqlOperator);
    m_LayerDataManager.ReadFixedObject(sqlOperator);
}

void hgAlarmManager::StartWarning(const std::string ID,int type,vtsRequestHandler *handler)
{
    if (hgConfigManager::m_sSysConfig->m_OpenWarning == false)
    {
        return;
    }
    vtsTimerHandler* l_timer = handler->getTimer(ID);
    if (l_timer != NULL)
    {
        return ;
    }
    switch (type)
    {
    case WaringPolygon:
        {
            hgPolygonTimerHandler * l_timer = new hgPolygonTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningCricle:
        {
            hgCricleTimerHandler * l_timer = new hgCricleTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningSector:
        {
            hgSectorTimerHandler * l_timer = new hgSectorTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningReportLine:
        {
            hgReportTimerHandler * l_timer = new hgReportTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;

    case WarningAnchorArea:
        {
            hgAnchorAreaTimerHandler * l_timer = new hgAnchorAreaTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningAnchorWatch:
        {
            hgAnchorWatchTimerHandler * l_timer = new hgAnchorWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningAnchorReserv:
        {
            hgAnchorReservTimerHandler * l_timer = new hgAnchorReservTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningBerthWatch:
        {
            hgBerthWatchTimerHandler * l_timer = new hgBerthWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningCollisionWatch:
        {
            hgCollisionWatchTimerHandler * l_timer = new hgCollisionWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningDomainWatch:
        {
            hgDomainTimerHandler * l_timer = new hgDomainTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningGroundWatch:
        {
            hgGroundWatchTimerHandler * l_timer = new hgGroundWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningChannel:
        {
            hgNavigatChannelTimerHandler * l_timer = new hgNavigatChannelTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;                
        break;
    case WarningReportArea:
        {
            hgReportAreaTimerHandler * l_timer = new hgReportAreaTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningSpeed:
        {
            hgSpeedWatchTimerHandler * l_timer = new hgSpeedWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningTurnCircle:
        {
            hgTurnCircleTimerHandler * l_timer = new hgTurnCircleTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    case WarningMovementEnd:
        {
            hgMovementEndTimerHandler * l_timer = new hgMovementEndTimerHandler(ID);
            l_timer->setDuration(1.0);
            handler->setTimer(l_timer);
        }
        break;
    }
}

void hgAlarmManager::StartWarning(const std::string ID,int type,vtsServer *s)
{
    if (hgConfigManager::m_sSysConfig->m_OpenWarning == false)
    {
        return;
    }
    switch (type)
    {
    case WaringPolygon:
        {
            hgPolygonTimerHandler * l_timer = new hgPolygonTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningCricle:
        {
            hgCricleTimerHandler * l_timer = new hgCricleTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningSector:
        {
            hgSectorTimerHandler * l_timer = new hgSectorTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningReportLine:
        {
            hgReportTimerHandler * l_timer = new hgReportTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;

    case WarningAnchorArea:
        {
            hgAnchorAreaTimerHandler * l_timer = new hgAnchorAreaTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningAnchorWatch:
        {
            hgAnchorWatchTimerHandler * l_timer = new hgAnchorWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningAnchorReserv:
        {
            hgAnchorReservTimerHandler * l_timer = new hgAnchorReservTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningBerthWatch:
        {
            hgBerthWatchTimerHandler * l_timer = new hgBerthWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningCollisionWatch:
        {
            hgCollisionWatchTimerHandler * l_timer = new hgCollisionWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
        }
        break;
    case WarningDomainWatch:
        {
            hgDomainTimerHandler * l_timer = new hgDomainTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningGroundWatch:
        {
            hgGroundWatchTimerHandler * l_timer = new hgGroundWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningChannel:
        {
            hgNavigatChannelTimerHandler * l_timer = new hgNavigatChannelTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;                
        break;
    case WarningReportArea:
        {
            hgReportAreaTimerHandler * l_timer = new hgReportAreaTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningSpeed:
        {
            hgSpeedWatchTimerHandler * l_timer = new hgSpeedWatchTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningTurnCircle:
        {
            hgTurnCircleTimerHandler * l_timer = new hgTurnCircleTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    case WarningMovementEnd:
        {
            hgMovementEndTimerHandler * l_timer = new hgMovementEndTimerHandler(ID);
            l_timer->setDuration(1.0);
            l_timer->start(s);
        }
        break;
    }
}

void hgAlarmManager::StopWarning(const std::string ID,vtsRequestHandler *handler)
{
    vtsTimerHandler* l_timer = handler->getTimer(ID);
    if (l_timer != NULL)
    {
        handler->clearTimer(ID);
    }
}

void hgAlarmManager::SendMessage(google::protobuf::Message& msg,const std::string msgType,vtsTimerHandler* handler)
{
    hgSendManager::SendClientMessage(msgType,msg,handler->server());
//     handler->server()->connectionManager().for_each
//         ([&](ConnectionPtr p){
//             p->write(msgType,msg);
//     });
}

void hgAlarmManager::ReadSetData(hgSqlOperator& sqlOperator, vtsServer *s)
{
    m_WarningSetManager.ReadDomain(sqlOperator,s);
    m_WarningSetManager.ReadAuthorized(sqlOperator,s);
    m_WarningSetManager.ReadAnchorArea(sqlOperator,s);
    m_WarningSetManager.ReadAnchorWatch(sqlOperator,s);
    m_WarningSetManager.ReadAnchorReserv(sqlOperator,s);
    m_WarningSetManager.ReadBerthWatch(sqlOperator,s);
    m_WarningSetManager.ReadCollisionWatch(sqlOperator,s);
    m_WarningSetManager.ReadGroundWatch(sqlOperator,s);
    m_WarningSetManager.ReadNavigatChannel(sqlOperator,s);
    m_WarningSetManager.ReadReportArea(sqlOperator,s);
    m_WarningSetManager.ReadSpeedWatch(sqlOperator,s);
    m_WarningSetManager.ReadSetShip(sqlOperator);
    m_WarningSetManager.ReadTurnCircle(sqlOperator,s);
    m_WarningSetManager.ReadMovementEnd(sqlOperator,s);
}

bool hgAlarmManager::PolygonEnterWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (l_SWI.EnterTime == -1 && l_SWI.Position == OutSidePos)
    {
        l_SWI.EnterTime = hgTargetManager::GetWarnTime();
    }
    if (hgTargetManager::GetWarnTime() - l_SWI.EnterTime >= l_Layer.m_ULWaring.enter_time//在区域内时间 
        && Ais.SOG > l_Layer.m_ULWaring.enter_speed //速度
        && l_SWI.IsSendEnter == false//是否发送过入侵警报
        && l_SWI.Position == OutSidePos)//入侵监控
    {
        l_SWI.IsSendEnter = true;//入侵警报
        l_SWI.EnterTime = -1;
        l_SWI.Position = InsidePos;//警报触发后视为真正在内部

        return true;
    }

    return false;
}

bool hgAlarmManager::PolygonLeaveWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (l_SWI.LeaveTime == -1 && l_SWI.Position == InsidePos)
    {
        l_SWI.LeaveTime =  hgTargetManager::GetWarnTime();
    }
    if (hgTargetManager::GetWarnTime() - l_SWI.LeaveTime > l_Layer.m_ULWaring.leave_time  
        && Ais.SOG > l_Layer.m_ULWaring.leave_speed
        && l_SWI.IsSendLeave == false
        && l_SWI.Position == InsidePos)//离开监控
    {

        l_SWI.Position = OutSidePos;//警报触发后视为真正在外部
        l_SWI.IsSendLeave = true;//离开警报
        l_SWI.LeaveTime = -1;
        return true;
    }
    return false;
}

bool hgAlarmManager::PolygonApproachWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    hg::utils::PointLL l_TargetPosition;
    l_TargetPosition.setLat(Ais.Lat);
    l_TargetPosition.setLon(Ais.Lon);
    double l_minDist = Ais.SOG * (l_Layer.m_ULWaring.app_time/3600.0);
    hg::utils::PointLL l_point = hg::utils::navutil::getPoint(l_TargetPosition,l_minDist,Ais.COG);
    if (l_Layer.m_Polygon.containsPoint(l_point,Qt::WindingFill))
    {
        if (l_SWI.IsSendApproach == false)//判断是否发过警告
        {
            l_SWI.IsSendApproach = true;
            return true;
        }
    }
    else
    {
        l_SWI.IsSendApproach = false;
        return false;
    }
    return false;
}

bool hgAlarmManager::PolygonProhibited(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (Ais.Class != AIS_CLASS_A && Ais.Class != AIS_CLASS_B)
    {
        return false;
    }
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    hg::utils::PolygonLL poly = l_polyiter.value().m_Polygon;
    hg::utils::PointLL l_TargetPosition;
    l_TargetPosition.setLat(Ais.Lat);
    l_TargetPosition.setLon(Ais.Lon);
    double l_a = (Ais.SOG - l_SWI.LastSOG)/((time(NULL)-l_SWI.LastTime)/*l_ais.ReportPeriod*/*3600.0);//加速度
    if (l_a < 0 
        || (l_a == 0 && Ais.SOG == 0))
    {
        double l_dist;
        if (Ais.SOG == 0)
        {
            l_dist = 0;
        }
        else
        {
            l_dist = Ais.SOG * Ais.SOG / 2. / l_a;//停下时的距离
        }
        if (poly.containsPoint(hg::utils::navutil::getPoint(l_TargetPosition,abs(l_dist),Ais.COG),Qt::WindingFill))//停下的点在形状内触发警报
        {
            if (l_SWI.IsProhibited == false)
            {
                l_SWI.IsProhibited = true;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    l_SWI.IsProhibited = false;
    return false;
}

bool hgAlarmManager::PolygonAnchorage(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    hg::utils::PolygonLL poly = l_polyiter.value().m_Polygon;
    hg::utils::PointLL l_TargetPosition;
    l_TargetPosition.setLat(Ais.Lat);
    l_TargetPosition.setLon(Ais.Lon);
    double l_a = (Ais.SOG - l_SWI.LastSOG)/((time(NULL)-l_SWI.LastTime)*3600.0);//加速度
    if (l_a < 0 
        || (l_a == 0 && Ais.SOG == 0))
    {
        double l_dist;
        if (Ais.SOG == 0)
        {
            l_dist = 0;
        }
        else
        {
            l_dist = Ais.SOG * Ais.SOG / 2. / l_a;//停下时的距离
        }
        if (poly.containsPoint(hg::utils::navutil::getPoint(l_TargetPosition,abs(l_dist),Ais.COG),Qt::WindingFill))//停下的点在形状内触发警报
        {
            if (hgAlarmManager::m_LayerDataManager.m_ShipMap.find(Ais.ShipType) != hgAlarmManager::m_LayerDataManager.m_ShipMap.end())//判断是否可抛锚
            {
                if (l_Layer.m_ULWaring.anc_type.indexOf(hgAlarmManager::m_LayerDataManager.m_ShipMap.find(Ais.ShipType).value()) == -1)
                {
                    if (l_SWI.IsAnchorage == false)
                    {
                        l_SWI.IsAnchorage = true;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
    l_SWI.IsAnchorage = false;
    return false;
}

bool hgAlarmManager::PolygonHighSpeed(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG > l_Layer.m_ULWaring.high_speed)
    {
        if (l_SWI.HighTime == -1)
        {
            l_SWI.HighTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.HighTime
                 > l_Layer.m_ULWaring.high_duration
                 && l_SWI.IsSendHighSpeed == false)
        {
            l_SWI.IsSendHighSpeed = true;
            return true;
        }
    }
    else
    {
        l_SWI.HighTime = -1;
        l_SWI.IsSendHighSpeed = false;
    }
    return false;
}

bool hgAlarmManager::PolygonLowSpeed(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG < l_Layer.m_ULWaring.low_speed)
    {
        if (l_SWI.LowTime == -1)
        {
            l_SWI.LowTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.LowTime
            > l_Layer.m_ULWaring.low_duration
            && l_SWI.IsSendLowSpeed == false)
        {
            l_SWI.IsSendLowSpeed = true;
            return true;
        }
    }
    else
    {
        l_SWI.LowTime = -1;
        l_SWI.IsSendLowSpeed = false;
    }
    return false;
}

bool hgAlarmManager::PolygonAddMaxWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG < l_SWI.LastSOG)
    {
        l_SWI.AddMaxTime = -1;
        l_SWI.IsSendAddMax = false;
        return false;
    }
    double l_dist = hg::utils::mathutil::KnToMsec(Ais.SOG - l_SWI.LastSOG);//两次速度差值节/小时->m/s
    double l_a = l_dist/((hgTargetManager::GetWarnTime()-l_SWI.LastTime)*1.0);//加速度、m/s2
    if (l_a > l_Layer.m_ULWaring.add_max)
    {
        if (l_SWI.AddMaxTime == -1)
        {
            l_SWI.AddMaxTime = hgTargetManager::GetWarnTime();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.AddMaxTime
            > l_Layer.m_ULWaring.add_duration
            && l_SWI.IsSendAddMax == false)
        {
            l_SWI.IsSendAddMax = true;
            return true;
        }
    }
    else
    {
        l_SWI.AddMaxTime = -1;
        l_SWI.IsSendAddMax = false;
    }
    return false;
}

bool hgAlarmManager::PolygonAddMinWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG > l_SWI.LastSOG)
    {
        l_SWI.AddMinTime = -1;
        l_SWI.IsSendAddMin = false;
        return false;
    }
    double l_dist = hg::utils::mathutil::KnToMsec(l_SWI.LastSOG - Ais.SOG);//两次速度差值节/小时->m/s
    double l_a = l_dist/((hgTargetManager::GetWarnTime()-l_SWI.LastTime)*1.0);//加速度、m/s2
    if (l_a > l_Layer.m_ULWaring.add_min)
    {
        if (l_SWI.AddMinTime == -1)
        {
            l_SWI.AddMinTime = hgTargetManager::GetWarnTime();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.AddMinTime
            > l_Layer.m_ULWaring.add_duration
            && l_SWI.IsSendAddMin == false)
        {
            l_SWI.IsSendAddMin = true;
            return true;
        }
    }
    else
    {
        l_SWI.AddMinTime = -1;
        l_SWI.IsSendAddMin = false;
    }
    return false;
}

bool hgAlarmManager::PolygonCongestionWatch(QString Guid)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end())
    {
        return false;
    }
    
    if (l_polyiter.value().m_InsideMMSI.size() > l_polyiter.value().m_ULWaring.con_total)
    {
        if (l_polyiter.value().m_CongesTime == -1)
        {
            l_polyiter.value().m_CongesTime = hgTargetManager::GetWarnTime();
        }
        else if (hgTargetManager::GetWarnTime() - l_polyiter.value().m_CongesTime > l_polyiter.value().m_ULWaring.con_time
            && l_polyiter.value().m_IsSendCongestion == false)
        {
            l_polyiter.value().m_IsSendCongestion = true;
            return true;
        }
    }
    else
    {
        l_polyiter.value().m_CongesTime = -1;
        l_polyiter.value().m_IsSendCongestion = false;
    }
    return false;
}

bool hgAlarmManager::PolygonGround(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.Draft > l_Layer.m_ULWaring.gro_depth)
    {
        if (l_SWI.GroundTime == -1)
        {
            l_SWI.GroundTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.GroundTime
                 > l_Layer.m_ULWaring.gro_time
                 && l_SWI.IsSendGround == false)
        {
            l_SWI.IsSendGround = true;
            return true;
        }
    }
    else
    {
        l_SWI.GroundTime = -1;
        l_SWI.IsSendGround = false;
    }
    return false;
}

bool hgAlarmManager::PolygonCourse(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.HDG > l_Layer.m_ULWaring.cou_change)
    {
        if (l_SWI.CourseTime == -1)
        {
            l_SWI.CourseTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.CourseTime
                 > l_Layer.m_ULWaring.cou_time
                 && l_SWI.IsSendCourse == false)
        {
            l_SWI.IsSendCourse = true;
            return true;
        }
    }
    else
    {
        l_SWI.CourseTime = -1;
        l_SWI.IsSendCourse = false;
    }
    return false;
}

void hgAlarmManager::PolygonCollision(QString Guid,QString MMSI,vtsTimerHandler* handler)
{
    return ;
//     auto l_lockerTarget = hgTargetManager::getMapTargetLocker();
//     auto &l_mapTarget = l_lockerTarget->raw();
//     QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
//     if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end())
//     {
//         return ;
//     }
//     hg::utils::PointLL l_pointLLOwn,l_pointLLTarget;
//     if (l_mapTarget.find(MMSI) == l_mapTarget.end())
//     {
//         return ;
//     }
//     hgTarget l_ais1 = l_mapTarget.find(MMSI).value();
//     auto l_mapCollValue = hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.find(MMSI);
//     CollisionWatch l_col;// = hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.find(MMSI).value();
//     if (l_mapCollValue != hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.end())
//     {
//         l_col = l_mapCollValue.value();
//     }
//     else
//     {
//         l_col.b_CollisionWatch = false;
//     }
//     l_pointLLOwn.setLat(l_ais1.Lat);
//     l_pointLLOwn.setLon(l_ais1.Lon);
//     auto l_coliterOth = l_polyiter.value().m_InsideMMSI.begin();
//     for ( ; l_coliterOth != l_polyiter.value().m_InsideMMSI.end(); l_coliterOth++ )
//     {
//         if (l_coliterOth.key() == MMSI)
//         {
//             continue;
//         }
//         auto &l_ais1COL = l_polyiter.value().m_CollisionData.find(MMSI); 
//         if (l_ais1COL == l_polyiter.value().m_CollisionData.end())//判断船1是否在碰撞参数内，不在则加入
//         {
//             QMap<QString, bool> l_map;
//             l_polyiter.value().m_CollisionData.insert(MMSI,l_map);
//             l_ais1COL = l_polyiter.value().m_CollisionData.find(MMSI);
//         }
//         QString l_oMMSI = l_coliterOth.key();
//         auto &l_ais1COLValue = l_ais1COL.value();//船1碰撞参数列表
//         if (l_ais1COLValue.find(l_oMMSI) == l_ais1COLValue.end())//判断船1的碰撞里是否有船2，不在则加入初始化为false
//         {
//             l_ais1COLValue.insert(l_oMMSI,false);
//         }
//         if (l_mapTarget.find(l_oMMSI) == l_mapTarget.end())
//         {
//             l_ais1COLValue.remove(l_oMMSI);
//             l_coliterOth++;
//             if (l_coliterOth == l_polyiter.value().m_InsideMMSI.end())
//             {
//                 return;
//             }
//             l_coliterOth--;
//             l_polyiter.value().m_InsideMMSI.remove(l_oMMSI);
//             continue;
//         }
//         hgTarget l_ais2 = l_mapTarget.find(l_oMMSI).value();
//         l_pointLLTarget.setLat(l_ais2.Lat);
//         l_pointLLTarget.setLon(l_ais2.Lon);
//         double l_dTCPA,l_dDCPA;
//         hg::utils::navutil::getTCPADCPA(l_pointLLOwn,l_ais1.SOG,l_ais1.COG,l_pointLLTarget,l_ais2.SOG,l_ais2.COG,&l_dTCPA,&l_dDCPA);
//         if (l_col.b_CollisionWatch == true)
//         {
//             if ( l_dDCPA < l_col.DCPA && l_dTCPA < l_col.TCPA)
//             {
//                 if (l_ais1COLValue.find(l_oMMSI).value() == false)//是否发过警报
//                 {
//                     l_ais1COLValue.find(l_oMMSI).value() = true;
//                     hgWarningMes l_mes;
//                     l_mes.set_warningid(hgWaringTypeGuid[COLLISIONWATCH]);
//                     l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
//                     l_mes.set_warningpriority(PriorityRed);
//                     l_mes.set_warningname("Collision Watch");
//                     l_mes.set_mmsi(MMSI.toStdString());
//                     l_mes.set_userlayguid(l_polyiter.key().toStdString());
//                     l_mes.set_userlayid(UserLayerType::UPolygon);
//                     l_mes.set_warningtime(hgTargetManager::GetWarnTime());
//                     hgAlarmManager::SendMessage(l_mes,"hgWarningMes",handler);
//                     //return true;
//                 }
//             }
//             else
//             {
//                 l_ais1COLValue.find(l_oMMSI).value() = false;
//                 //return false;
//             }
//         }
//         else if (l_col.b_CollisionWatch == false)
//         {
//             if ( l_dDCPA < l_polyiter.value().m_ULWaring.col_dcpa && l_dTCPA < l_polyiter.value().m_ULWaring.col_tcpa)
//             {
//                 if (l_ais1COLValue.find(l_oMMSI).value() == false)//是否发过警报
//                 {
//                     l_ais1COLValue.find(l_oMMSI).value() = true;
//                     hgWarningMes l_mes;
//                     l_mes.set_warningid(hgWaringTypeGuid[COLLISIONWATCH]);
//                     l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
//                     l_mes.set_warningpriority(PriorityRed);
//                     l_mes.set_warningname("Collision Watch");
//                     l_mes.set_mmsi(MMSI.toStdString());
//                     l_mes.set_userlayguid(l_polyiter.key().toStdString());
//                     l_mes.set_userlayid(UserLayerType::UPolygon);
//                     l_mes.set_warningtime(hgTargetManager::GetWarnTime());
//                     hgAlarmManager::SendMessage(l_mes,"hgWarningMes",handler);
//                 }
//             }
//             else
//             {
//                 l_ais1COLValue.find(l_oMMSI).value() = false;
//             }
//         }
//     }
}

void hgAlarmManager::PolygonFoggyArea(QString Guid,vtsTimerHandler* handler)
{
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(Guid);
    if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end())
    {
        return ;
    }
    QTime l_beginTime = QTime::fromString(QDateTime::fromTime_t(l_polyiter->m_ULWaring.m_FogBeginTime).toString("HH:mm:ss"),"HH:mm:ss");
    QTime l_endTime = QTime::fromString(QDateTime::fromTime_t(l_polyiter->m_ULWaring.m_FogEndTime).toString("HH:mm:ss"),"HH:mm:ss");
    for ( int i = 0; i < l_polyiter->m_ULWaring.m_FogMMSI.size(); i++ )
    {
        QString l_MMSI = l_polyiter->m_ULWaring.m_FogMMSI.at(i);
        if (l_polyiter.value().m_Info.find(l_MMSI) == l_polyiter.value().m_Info.end())
        {
            continue;
        }
        auto & l_SWI = l_polyiter.value().m_Info.find(l_MMSI).value();
        QTime l_nowTime = QTime::fromString(QDateTime::fromTime_t(hgTargetManager::GetWarnTime()).toString("HH:mm:ss"),"HH:mm:ss");
        //hgShipWarningInfo l_SWI = l_polyiter.value().m_Info.find(l_MMSI).value();
        if (l_SWI.FogTime == -1)
        {
            l_SWI.FogTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        if (l_nowTime >= l_beginTime && l_nowTime <= l_endTime)
        {
            if (hgTargetManager::GetWarnTime() - l_SWI.FogTime > l_polyiter->m_ULWaring.m_FogTime
                && l_SWI.IsSendFog == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[FoggyArea]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname("Foggy Area");
                l_mes.set_mmsi(l_MMSI.toStdString());
                l_mes.set_userlayguid(l_polyiter.key().toStdString());
                l_mes.set_userlayid(UserLayerType::UPolygon);
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",handler);
                l_SWI.IsSendFog = true;
            }
        }
        else
        {
            l_SWI.IsSendFog = false;
            l_SWI.FogTime = -1;
        }
    }
}

// void hgAlarmManager::GetApproachPoint(hg::utils::PolygonLL polygonLL, double angle,hg::utils::PointLL &point,double &dist)
// {
//     double l_dist = -1;
//     hg::utils::PointLL l_unreal = hg::utils::navutil::getPoint(point,0.75,angle);//虚构出一个点
//     hg::utils::PointLL l_node;//交点
//     hg::utils::LineLL l_TarLine(point,l_unreal);
//     for ( int i = 1; i < polygonLL.size(); i++ )
//     {
//         hg::utils::LineLL l_line(polygonLL.at(i-1),polygonLL.at(i));
//         hg::utils::PointLL l_point;
//         int l_type = l_line.intersect(l_TarLine,&l_point);
//         if (l_type == hg::utils::LineLL::IntersectType::NoIntersection)
//         {
//             continue;
//         }
//         double l_bear;
//         double l_distance;
//         hg::utils::navutil::getDistanceBearing(polygonLL.at(i-1),l_point,&l_distance,&l_bear);
//         if (l_distance < l_line.distance() && abs(l_line.bearing() - l_bear ) < 10)
//         {
//             l_node = l_point;
//             if (abs(angle - hg::utils::navutil::getBearing(point,l_node)) > 10)//方向不同 则没有不是
//             {
//                 continue;
//             }
//             double l_dis = hg::utils::navutil::getDistance(point,l_point);
//             if (l_dist = -1)
//             {
//                 l_dist = l_dis;
//             }
//             else
//             {
//                 l_dist = l_dist < l_dis ? l_dist : l_dis;
//             }
//         }
//     }
//     dist = l_dist;
// }

bool hgAlarmManager::CricleEnterWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (l_SWI.EnterTime == -1 && l_SWI.Position == OutSidePos)
    {
        l_SWI.EnterTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
    }
    if (hgTargetManager::GetWarnTime() - l_SWI.EnterTime > l_polyiter.value().m_ULWaring.enter_time//在区域内时间 
        && Ais.SOG > l_Layer.m_ULWaring.enter_speed //速度
        && l_SWI.IsSendEnter == false//是否发送过入侵警报
        && l_SWI.Position == OutSidePos)//入侵监控
    {
        l_SWI.IsSendEnter = true;//入侵警报
        l_SWI.EnterTime = -1;
        l_SWI.Position = InsidePos;//警报触发后视为真正在内部

        return true;
    }

    return false;
}

bool hgAlarmManager::CricleLeaveWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (l_SWI.LeaveTime == -1 && l_SWI.Position == InsidePos)
    {
        l_SWI.LeaveTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
    }
    if (hgTargetManager::GetWarnTime() - l_SWI.LeaveTime > l_Layer.m_ULWaring.leave_time  
        && Ais.SOG > l_Layer.m_ULWaring.leave_speed
        && l_SWI.IsSendLeave == false
        && l_SWI.Position == InsidePos)//离开监控
    {

        l_SWI.Position = OutSidePos;//警报触发后视为真正在外部
        l_SWI.IsSendLeave = true;//离开警报
        l_SWI.LeaveTime = -1;
        return true;
    }
    return false;
}

bool hgAlarmManager::CricleCongestionWatch(QString Guid)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pCricleMap.end())
    {
        return false;
    }

    if (l_polyiter.value().m_InsideMMSI.size() > l_polyiter.value().m_ULWaring.con_total)
    {
        if (l_polyiter.value().m_CongesTime == -1)
        {
            l_polyiter.value().m_CongesTime = hgTargetManager::GetWarnTime();
        }
        else if (hgTargetManager::GetWarnTime() - l_polyiter.value().m_CongesTime > l_polyiter.value().m_ULWaring.con_time
            && l_polyiter.value().m_IsSendCongestion == false)
        {
            l_polyiter.value().m_IsSendCongestion = true;
            return true;
        }
    }
    else
    {
        l_polyiter.value().m_CongesTime = -1;
        l_polyiter.value().m_IsSendCongestion = false;
    }
    return false;
}

bool hgAlarmManager::CricleGround(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.Draft > l_Layer.m_ULWaring.gro_depth)
    {
        if (l_SWI.GroundTime == -1)
        {
            l_SWI.GroundTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.GroundTime
                 > l_Layer.m_ULWaring.gro_time
                 && l_SWI.IsSendGround == false)
        {
            l_SWI.IsSendGround = true;
            return true;
        }
    }
    else
    {
        l_SWI.GroundTime = -1;
        l_SWI.IsSendGround = false;
    }
    return false;
}

bool hgAlarmManager::CricleApproachWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    hg::utils::PointLL l_TargetPosition;
    l_TargetPosition.setLat(Ais.Lat);
    l_TargetPosition.setLon(Ais.Lon);
    hg::utils::PointLL l_CenterLL;
    l_CenterLL.setLat(l_Layer.m_Lat);
    l_CenterLL.setLon(l_Layer.m_Lon);
    double l_minDist = Ais.SOG * (l_Layer.m_ULWaring.app_time/3600.0);
    hg::utils::PointLL l_point = hg::utils::navutil::getPoint(l_TargetPosition,l_minDist,Ais.COG);//将要行驶到的位置
    double l_dist = hg::utils::navutil::getDistance(l_point,l_CenterLL);
    if (l_Layer.m_Radius > l_dist)//在区域内
    {
        if (l_SWI.IsSendApproach == false)
        {
            l_SWI.IsSendApproach = true;
            return true;
        }
    }
    else
    {
        l_SWI.IsSendApproach = false;
    }
    return false;
}

bool hgAlarmManager::CricleProhibited(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (Ais.Class != AIS_CLASS_A && Ais.Class != AIS_CLASS_B)
    {
        return false;
    }
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    hg::utils::PointLL l_TargetPosition;
    l_TargetPosition.setLat(Ais.Lat);
    l_TargetPosition.setLon(Ais.Lon);
    double l_a = (Ais.SOG - l_SWI.LastSOG)/((time(NULL)-l_SWI.LastTime)*3600.0);//加速度
    if (l_a < 0
        || (l_a == 0 && Ais.SOG == 0))
    {
        double l_dist;
        if (Ais.SOG == 0)
        {
            l_dist = 0;
        }
        else
        {
            l_dist = Ais.SOG * Ais.SOG / 2. / l_a;//停下时的距离
        }
        if (abs(l_dist) < l_Layer.m_Radius)//停下的点在形状内触发警报
        {
            if (l_SWI.IsProhibited == false)
            {
                l_SWI.IsProhibited = true;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    l_SWI.IsProhibited = false;
    return false;
}

bool hgAlarmManager::CricleAnchorage(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    hg::utils::PointLL l_TargetPosition;
    l_TargetPosition.setLat(Ais.Lat);
    l_TargetPosition.setLon(Ais.Lon);
    double l_a = (Ais.SOG - l_SWI.LastSOG)/((time(NULL)-l_SWI.LastTime)*3600.0);//加速度
    if (l_a < 0
        || (l_a == 0 && Ais.SOG == 0))
    {
        double l_dist;
        if (Ais.SOG == 0)
        {
            l_dist = 0;
        }
        else
        {
            l_dist = Ais.SOG * Ais.SOG / 2. / l_a;//停下时的距离
        }
        if (abs(l_dist) < l_Layer.m_Radius)//停下的点在形状内触发警报
        {
            if (hgAlarmManager::m_LayerDataManager.m_ShipMap.find(Ais.ShipType) != hgAlarmManager::m_LayerDataManager.m_ShipMap.end())//判断是否可抛锚
            {
                if (l_Layer.m_ULWaring.anc_type.indexOf(hgAlarmManager::m_LayerDataManager.m_ShipMap.find(Ais.ShipType).value()) == -1)
                {
                    if (l_SWI.IsAnchorage == false)
                    {
                        l_SWI.IsAnchorage = true;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
    l_SWI.IsAnchorage = false;
    return false;
}

bool hgAlarmManager::CricleHighSpeed(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG > l_Layer.m_ULWaring.high_speed)
    {
        if (l_SWI.HighTime == -1)
        {
            l_SWI.HighTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.HighTime
                 > l_Layer.m_ULWaring.high_duration
                 && l_SWI.IsSendHighSpeed == false)
        {
            l_SWI.IsSendHighSpeed = true;
            return true;
        }
    }
    else
    {
        l_SWI.HighTime = -1;
        l_SWI.IsSendHighSpeed = false;
    }
    return false;
}

bool hgAlarmManager::CricleLowSpeed(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG < l_Layer.m_ULWaring.low_speed)
    {
        if (l_SWI.LowTime == -1)
        {
            l_SWI.LowTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if ( hgTargetManager::GetWarnTime() - l_SWI.LowTime > l_Layer.m_ULWaring.low_duration
                    && l_SWI.IsSendLowSpeed == false)
        {
            l_SWI.IsSendLowSpeed = true;
            return true;
        }
    }
    else
    {
        l_SWI.LowTime = -1;
        l_SWI.IsSendLowSpeed = false;
    }
    return false;
}

bool hgAlarmManager::CricleAddMaxWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG < l_SWI.LastSOG)
    {
        l_SWI.AddMaxTime = -1;
        l_SWI.IsSendAddMax = false;
        return false;
    }
    double l_dist = hg::utils::mathutil::KnToMsec(Ais.SOG - l_SWI.LastSOG);//两次速度差值节/小时->m/s
    double l_a = l_dist/((hgTargetManager::GetWarnTime()-l_SWI.LastTime)*1.0);//加速度、m/s2
    if (l_a > l_Layer.m_ULWaring.add_max)
    {
        if (l_SWI.AddMaxTime == -1)
        {
            l_SWI.AddMaxTime = hgTargetManager::GetWarnTime();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.AddMaxTime
            > l_Layer.m_ULWaring.add_duration
            && l_SWI.IsSendAddMax == false)
        {
            l_SWI.IsSendAddMax = true;
            return true;
        }
    }
    else
    {
        l_SWI.AddMaxTime = -1;
        l_SWI.IsSendAddMax = false;
    }
    return false;
}

bool hgAlarmManager::CricleAddMinWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG > l_SWI.LastSOG)
    {
        l_SWI.AddMinTime = -1;
        l_SWI.IsSendAddMin = false;
        return false;
    }
    double l_dist = hg::utils::mathutil::KnToMsec(l_SWI.LastSOG - Ais.SOG);//两次速度差值节/小时->m/s
    double l_a = l_dist/((hgTargetManager::GetWarnTime()-l_SWI.LastTime)*1.0);//加速度、m/s2
    if (l_a > l_Layer.m_ULWaring.add_min)
    {
        if (l_SWI.AddMinTime == -1)
        {
            l_SWI.AddMinTime = hgTargetManager::GetWarnTime();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.AddMinTime > l_Layer.m_ULWaring.add_duration 
            && l_SWI.IsSendAddMin == false)
        {
            l_SWI.IsSendAddMin = true;
            return true;
        }
    }
    else
    {
        l_SWI.AddMinTime = -1;
        l_SWI.IsSendAddMin = false;
    }
    return false;
}

bool hgAlarmManager::CricleCourse(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.HDG > l_Layer.m_ULWaring.cou_change)
    {
        if (l_SWI.CourseTime == -1)
        {
            l_SWI.CourseTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.CourseTime
                 > l_Layer.m_ULWaring.cou_time
                 && l_SWI.IsSendCourse == false)
        {
            l_SWI.IsSendCourse = true;
            return true;
        }
    }
    else
    {
        l_SWI.CourseTime = -1;
        l_SWI.IsSendCourse = false;
    }
    return false;
}

void hgAlarmManager::CricleCollision(QString Guid,QString MMSI,vtsTimerHandler* handler)
{
    return ;
//     auto l_lockerTarget = hgTargetManager::getMapTargetLocker();
//     auto &l_mapTarget = l_lockerTarget->raw();
//     QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
//     if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pCricleMap.end())
//     {
//         return ;
//     }
//     hg::utils::PointLL l_pointLLOwn,l_pointLLTarget;
//     if (l_mapTarget.find(MMSI) == l_mapTarget.end())
//     {
//         return ;
//     }
//     hgTarget l_ais1 = l_mapTarget.find(MMSI).value();
//     auto l_mapCollValue = hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.find(MMSI);
//     CollisionWatch l_col;
//     if (l_mapCollValue != hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.end())
//     {
//         l_col = l_mapCollValue.value();
//     }
//     else
//     {
//         l_col.b_CollisionWatch = false;
//     }
//     l_pointLLOwn.setLat(l_ais1.Lat);
//     l_pointLLOwn.setLon(l_ais1.Lon);
//     auto l_coliterOth = l_polyiter.value().m_InsideMMSI.begin();
//     for ( ; l_coliterOth != l_polyiter.value().m_InsideMMSI.end(); l_coliterOth++ )
//     {
//         if (l_coliterOth.key() == MMSI)
//         {
//             continue;
//         }
//         auto &l_ais1COL = l_polyiter.value().m_CollisionData.find(MMSI); 
//         if (l_ais1COL == l_polyiter.value().m_CollisionData.end())//判断船1是否在碰撞参数内，不在则加入
//         {
//             QMap<QString, bool> l_map;
//             l_polyiter.value().m_CollisionData.insert(MMSI,l_map);
//             l_ais1COL = l_polyiter.value().m_CollisionData.find(MMSI);
//         }
//         QString l_oMMSI = l_coliterOth.key();
//         auto &l_ais1COLValue = l_ais1COL.value();//船1碰撞参数列表
//         if (l_ais1COLValue.find(l_oMMSI) == l_ais1COLValue.end())//判断船1的碰撞里是否有船2，不在则加入初始化为false
//         {
//             l_ais1COLValue.insert(l_oMMSI,false);
//         }
//         if (l_mapTarget.find(l_oMMSI) == l_mapTarget.end())
//         {
//             l_ais1COLValue.remove(l_oMMSI);
//             l_coliterOth++;
//             if (l_coliterOth == l_polyiter.value().m_InsideMMSI.end())
//             {
//                 return;
//             }
//             l_coliterOth--;
//             l_polyiter.value().m_InsideMMSI.remove(l_oMMSI);
//             continue;
//         }
//         hgTarget l_ais2 = l_mapTarget.find(l_oMMSI).value();
//         l_pointLLTarget.setLat(l_ais2.Lat);
//         l_pointLLTarget.setLon(l_ais2.Lon);
//         double l_dTCPA,l_dDCPA;
//         hg::utils::navutil::getTCPADCPA(l_pointLLOwn,l_ais1.SOG,l_ais1.COG,l_pointLLTarget,l_ais2.SOG,l_ais2.COG,&l_dTCPA,&l_dDCPA);
//         if (l_col.b_CollisionWatch == true)
//         {
//             if ( l_dDCPA < l_col.DCPA && l_dTCPA < l_col.TCPA)
//             {
//                 if (l_ais1COLValue.find(l_oMMSI).value() == false)//是否发过警报
//                 {
//                     l_ais1COLValue.find(l_oMMSI).value() = true;
//                     hgWarningMes l_mes;
//                     l_mes.set_warningid(hgWaringTypeGuid[COLLISIONWATCH]);
//                     l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
//                     l_mes.set_warningpriority(PriorityRed);
//                     l_mes.set_warningname("Collision Watch");
//                     l_mes.set_mmsi(MMSI.toStdString());
//                     l_mes.set_userlayguid(l_polyiter.key().toStdString());
//                     l_mes.set_userlayid(UserLayerType::UCricle);
//                     l_mes.set_warningtime(hgTargetManager::GetWarnTime());
//                     hgAlarmManager::SendMessage(l_mes,"hgWarningMes",handler);
//                 }
//             }
//             else
//             {
//                 l_ais1COLValue.find(l_oMMSI).value() = false;
//             }
//         }
//         else if (l_col.b_CollisionWatch == false)
//         {
//             if ( l_dDCPA < l_polyiter.value().m_ULWaring.col_dcpa && l_dTCPA < l_polyiter.value().m_ULWaring.col_tcpa)
//             {
//                 if (l_ais1COLValue.find(l_oMMSI).value() == false)//是否发过警报
//                 {
//                     l_ais1COLValue.find(l_oMMSI).value() = true;
//                     hgWarningMes l_mes;
//                     l_mes.set_warningid(hgWaringTypeGuid[COLLISIONWATCH]);
//                     l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
//                     l_mes.set_warningpriority(PriorityRed);
//                     l_mes.set_warningname("Collision Watch");
//                     l_mes.set_mmsi(MMSI.toStdString());
//                     l_mes.set_userlayguid(l_polyiter.key().toStdString());
//                     l_mes.set_userlayid(UserLayerType::UCricle);
//                     l_mes.set_warningtime(hgTargetManager::GetWarnTime());
//                     hgAlarmManager::SendMessage(l_mes,"hgWarningMes",handler);
//                 }
//             }
//             else
//             {
//                 l_ais1COLValue.find(l_oMMSI).value() = false;
//             }
//         }
//     }
}

void hgAlarmManager::CricleFoggyArea(QString Guid,vtsTimerHandler* handler)
{
    QMap <QString,hgCricleLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pCricleMap.find(Guid);
    if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pCricleMap.end())
    {
        return ;
    }
    QTime l_beginTime = QTime::fromString(QDateTime::fromTime_t(l_polyiter->m_ULWaring.m_FogBeginTime).toString("HH:mm:ss"),"HH:mm:ss");
    QTime l_endTime = QTime::fromString(QDateTime::fromTime_t(l_polyiter->m_ULWaring.m_FogEndTime).toString("HH:mm:ss"),"HH:mm:ss");
    for ( int i = 0; i < l_polyiter->m_ULWaring.m_FogMMSI.size(); i++ )
    {
        QString l_MMSI = l_polyiter->m_ULWaring.m_FogMMSI.at(i);
        if (l_polyiter.value().m_Info.find(l_MMSI) == l_polyiter.value().m_Info.end())
        {
            continue;
        }
        QTime l_nowTime = QTime::fromString(QDateTime::fromTime_t(hgTargetManager::GetWarnTime()).toString("HH:mm:ss"),"HH:mm:ss");
        hgShipWarningInfo &l_SWI = l_polyiter.value().m_Info.find(l_MMSI).value();
        if (l_SWI.FogTime == -1)
        {
            l_SWI.FogTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        if (l_nowTime >= l_beginTime && l_nowTime <= l_endTime)
        {
            if (hgTargetManager::GetWarnTime() - l_SWI.FogTime > l_polyiter->m_ULWaring.m_FogTime
                && l_SWI.IsSendFog == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[FoggyArea]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname("Foggy Area");
                l_mes.set_mmsi(l_MMSI.toStdString());
                l_mes.set_userlayguid(l_polyiter.key().toStdString());
                l_mes.set_userlayid(UserLayerType::UCricle);
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",handler);
                l_SWI.IsSendFog = true;
            }
        }
        else
        {
            l_SWI.IsSendFog = false;
            l_SWI.FogTime = -1;
        }
    }
}

bool hgAlarmManager::SectorEnterWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (l_SWI.EnterTime == -1
        && l_SWI.Position == OutSidePos)
    {
        l_SWI.EnterTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
    }
    if (hgTargetManager::GetWarnTime() - l_SWI.EnterTime > l_Layer.m_ULWaring.enter_time//在区域内时间 
        && Ais.SOG > l_Layer.m_ULWaring.enter_speed //速度
        && l_SWI.IsSendEnter == false//是否发送过入侵警报
        && l_SWI.Position == OutSidePos)//入侵监控
    {
        l_SWI.IsSendEnter = true;//入侵警报
        l_SWI.EnterTime = -1;
        l_SWI.Position = InsidePos;//警报触发后视为真正在内部

        return true;
    }

    return false;
}

bool hgAlarmManager::SectorLeaveWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (l_SWI.LeaveTime == -1
        && l_SWI.Position == InsidePos)
    {
        l_SWI.LeaveTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
    }
    if (hgTargetManager::GetWarnTime() - l_SWI.LeaveTime > l_Layer.m_ULWaring.leave_time  
        && Ais.SOG > l_Layer.m_ULWaring.leave_speed
        && l_SWI.IsSendLeave == false
        && l_SWI.Position == InsidePos)//离开监控
    {

        l_SWI.Position = OutSidePos;//警报触发后视为真正在外部
        l_SWI.IsSendLeave = true;//离开警报
        l_SWI.LeaveTime = -1;
        return true;
    }
    return false;
}

bool hgAlarmManager::SectorApproachWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    hg::utils::PointLL l_TargetPosition;
    l_TargetPosition.setLat(Ais.Lat);
    l_TargetPosition.setLon(Ais.Lon);
    hg::utils::PointLL l_CenterLL;
    l_CenterLL.setLat(l_Layer.m_Lat);
    l_CenterLL.setLon(l_Layer.m_Lon);
    double l_minDist = Ais.SOG * (l_Layer.m_ULWaring.app_time/3600.0);//警报距离
    hg::utils::PointLL l_point = hg::utils::navutil::getPoint(l_TargetPosition,l_minDist,Ais.COG);//按当前方向与警报点获取对应点位置
    if (PointInsideSector(l_point.lat(),l_point.lon()
        ,l_Layer.m_Lat,l_Layer.m_Lon,l_Layer.m_Radius
        ,l_Layer.m_BeginAngle,l_Layer.m_EndAngle))//在区域内
    {
        if (l_SWI.IsSendApproach == false)
        {
            l_SWI.IsSendApproach = true;
            return true;
        }
    }
    else
    {
        l_SWI.IsSendApproach = false;
    }
    return false;
}

bool hgAlarmManager::SectorProhibited(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (Ais.Class != AIS_CLASS_A && Ais.Class != AIS_CLASS_B)
    {
        return false;
    }
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    hg::utils::PointLL l_TargetPosition;
    l_TargetPosition.setLat(Ais.Lat);
    l_TargetPosition.setLon(Ais.Lon);
    double l_a = (Ais.SOG - l_SWI.LastSOG)/((time(NULL)-l_SWI.LastTime)*3600.0);//加速度
    if (l_a < 0
        || (l_a == 0 && Ais.SOG == 0))
    {
        double l_dist;
        if (Ais.SOG == 0)
        {
            l_dist = 0;
        }
        else
        {
            l_dist = Ais.SOG * Ais.SOG / 2. / l_a;//停下时的距离
        }
        hg::utils::PointLL l_pointLL =  hg::utils::navutil::getPoint(l_TargetPosition,abs(l_dist),Ais.COG);
        if (PointInsideSector(l_TargetPosition.lat(),l_TargetPosition.lon(),l_Layer.m_Lat,l_Layer.m_Lon
            ,l_Layer.m_Radius,l_Layer.m_BeginAngle,l_Layer.m_EndAngle))//停下的点在形状内触发警报
        {
            if (l_SWI.IsProhibited == false)
            {
                l_SWI.IsProhibited = true;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    l_SWI.IsProhibited = false;
    return false;
}

bool hgAlarmManager::SectorAnchorage(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    hg::utils::PointLL l_TargetPosition;
    l_TargetPosition.setLat(Ais.Lat);
    l_TargetPosition.setLon(Ais.Lon);
    double l_a = (Ais.SOG - l_SWI.LastSOG)/((time(NULL)-l_SWI.LastTime)*3600.0);//加速度
    if (l_a < 0
        || (l_a == 0 && Ais.SOG == 0))
    {
        double l_dist;
        if (Ais.SOG == 0)
        {
            l_dist = 0;
        }
        else
        {
            l_dist = Ais.SOG * Ais.SOG / 2. / l_a;//停下时的距离
        }
        hg::utils::PointLL l_pointLL =  hg::utils::navutil::getPoint(l_TargetPosition,abs(l_dist),Ais.SOG);
        if (PointInsideSector(l_TargetPosition.lat(),l_TargetPosition.lon(),l_Layer.m_Lat,l_Layer.m_Lon
            ,l_Layer.m_Radius,l_Layer.m_BeginAngle,l_Layer.m_EndAngle))//停下的点在形状内触发警报
        {
            if (hgAlarmManager::m_LayerDataManager.m_ShipMap.find(Ais.ShipType) != hgAlarmManager::m_LayerDataManager.m_ShipMap.end())//判断是否可抛锚
            {
                if (l_Layer.m_ULWaring.anc_type.indexOf(hgAlarmManager::m_LayerDataManager.m_ShipMap.find(Ais.ShipType).value()) == -1)
                {
                    if (l_SWI.IsAnchorage == false)
                    {
                        l_SWI.IsAnchorage = true;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
    l_SWI.IsAnchorage = false;
    return false;
}

bool hgAlarmManager::SectorHighSpeed(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG > l_Layer.m_ULWaring.high_speed)
    {
        if (l_SWI.HighTime == -1)
        {
            l_SWI.HighTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.HighTime  > l_Layer.m_ULWaring.high_duration
            && l_SWI.IsSendHighSpeed == false)
        {
            l_SWI.IsSendHighSpeed = true;
            return true;
        }
    }
    else
    {
        l_SWI.HighTime = -1;
        l_SWI.IsSendHighSpeed = false;
    }
    return false;
}

bool hgAlarmManager::SectorLowSpeed(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG < l_Layer.m_ULWaring.low_speed)
    {
        if (l_SWI.LowTime == -1)
        {
            l_SWI.LowTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.LowTime > l_Layer.m_ULWaring.low_duration
            && l_SWI.IsSendLowSpeed == false)
        {
            l_SWI.IsSendLowSpeed = true;
            return true;
        }
    }
    else
    {
        l_SWI.LowTime = -1;
        l_SWI.IsSendLowSpeed = false;
    }
    return false;
}

bool hgAlarmManager::SectorAddMaxWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG < l_SWI.LastSOG)
    {
        l_SWI.AddMaxTime = -1;
        l_SWI.IsSendAddMax = false;
        return false;
    }
    double l_dist = hg::utils::mathutil::KnToMsec(Ais.SOG - l_SWI.LastSOG);//两次速度差值节/小时->m/s
    double l_a = l_dist/((hgTargetManager::GetWarnTime()-l_SWI.LastTime)*1.0);//加速度、m/s2
    if (l_a > l_Layer.m_ULWaring.add_max)
    {
        if (l_SWI.AddMaxTime == -1)
        {
            l_SWI.AddMaxTime = hgTargetManager::GetWarnTime();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.AddMaxTime > l_Layer.m_ULWaring.add_duration
            && l_SWI.IsSendAddMax == false)
        {
            l_SWI.IsSendAddMax = true;
            return true;
        }
    }
    else
    {
        l_SWI.AddMaxTime = -1;
        l_SWI.IsSendAddMax = false;
    }
    return false;
}

bool hgAlarmManager::SectorAddMinWatch(QString Guid,QString MMSI,hgTarget &Ais)
{
//     auto l_lockerTarget = hgTargetManager::getMapTargetLocker();
//     auto &l_mapTarget = l_lockerTarget->raw();
//     hgTarget Ais = l_mapTarget.find(MMSI).value();
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.SOG > l_SWI.LastSOG)
    {
        l_SWI.AddMinTime = -1;
        l_SWI.IsSendAddMin = false;
        return false;
    }
    double l_dist = hg::utils::mathutil::KnToMsec(l_SWI.LastSOG - Ais.SOG);//两次速度差值节/小时->m/s
    double l_a = l_dist/((hgTargetManager::GetWarnTime()-l_SWI.LastTime)*1.0);//加速度、m/s2
    if (l_a > l_Layer.m_ULWaring.add_min)
    {
        if (l_SWI.AddMinTime == -1)
        {
            l_SWI.AddMinTime = hgTargetManager::GetWarnTime();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.AddMinTime
            > l_Layer.m_ULWaring.add_duration
            && l_SWI.IsSendAddMin == false)
        {
            l_SWI.IsSendAddMin = true;
            return true;
        }
    }
    else
    {
        l_SWI.AddMinTime = -1;
        l_SWI.IsSendAddMin = false;
    }
    return false;
}

bool hgAlarmManager::SectorCongestionWatch(QString Guid)
{
//     auto l_lockerTarget = hgTargetManager::getMapTargetLocker();
//     auto &l_mapTarget = l_lockerTarget->raw();
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pSectorMap.end())
    {
        return false;
    }

    if (l_polyiter.value().m_InsideMMSI.size() > l_polyiter.value().m_ULWaring.con_total)
    {
        if (l_polyiter.value().m_CongesTime == -1)
        {
            l_polyiter.value().m_CongesTime = hgTargetManager::GetWarnTime();
        }
        else if (hgTargetManager::GetWarnTime() - l_polyiter.value().m_CongesTime > l_polyiter.value().m_ULWaring.con_time
            && l_polyiter.value().m_IsSendCongestion == false)
        {
            l_polyiter.value().m_IsSendCongestion = true;
            return true;
        }
    }
    else
    {
        l_polyiter.value().m_CongesTime = -1;
        l_polyiter.value().m_IsSendCongestion = false;
    }
    return false;
}

bool hgAlarmManager::SectorGround(QString Guid,QString MMSI,hgTarget &Ais)
{
//     auto l_lockerTarget = hgTargetManager::getMapTargetLocker();
//     auto &l_mapTarget = l_lockerTarget->raw();
//     hgTarget Ais = l_mapTarget.find(MMSI).value();
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.Draft > l_Layer.m_ULWaring.gro_depth)
    {
        if (l_SWI.GroundTime == -1)
        {
            l_SWI.GroundTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.GroundTime
                 > l_Layer.m_ULWaring.gro_time
                 && l_SWI.IsSendGround == false)
        {
            l_SWI.IsSendGround = true;
            return true;
        }
    }
    else
    {
        l_SWI.GroundTime = -1;
        l_SWI.IsSendGround = false;
    }
    return false;
}

bool hgAlarmManager::SectorCourse(QString Guid,QString MMSI,hgTarget &Ais)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    auto & l_Layer = l_polyiter.value();//对应图形参数
    if (!l_Layer.m_Info.contains(MMSI))
    {
        vtsError << "No Such MMSI";
        return false;
    }
    auto & l_SWI = l_Layer.m_Info.find(MMSI).value();//对应图形内对应船参数
    if (Ais.HDG > l_Layer.m_ULWaring.cou_change)
    {
        if (l_SWI.CourseTime == -1)
        {
            l_SWI.CourseTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        else if (hgTargetManager::GetWarnTime() - l_SWI.CourseTime > l_Layer.m_ULWaring.cou_time
            && l_SWI.IsSendCourse == false)
        {
            l_SWI.IsSendCourse = true;
            return true;
        }
    }
    else
    {
        l_SWI.CourseTime = -1;
        l_SWI.IsSendCourse = false;
    }
    return false;
}

void hgAlarmManager::SectorCollision(QString Guid,QString MMSI,vtsTimerHandler* handler)
{
    return ;
//     auto l_lockerTarget = hgTargetManager::getMapTargetLocker();
//     auto &l_mapTarget = l_lockerTarget->raw();
//     QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
//     if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pSectorMap.end())
//     {
//         return ;
//     }
//     hg::utils::PointLL l_pointLLOwn,l_pointLLTarget;
//     if (l_mapTarget.find(MMSI) == l_mapTarget.end())
//     {
//         return ;
//     }
//     hgTarget l_ais1 = l_mapTarget.find(MMSI).value();
//     auto l_mapCollValue = hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.find(MMSI);
//     CollisionWatch l_col;
//     if (l_mapCollValue != hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.end())
//     {
//         l_col = l_mapCollValue.value();
//     }
//     else
//     {
//         l_col.b_CollisionWatch = false;
//     }
//     l_pointLLOwn.setLat(l_ais1.Lat);
//     l_pointLLOwn.setLon(l_ais1.Lon);
//     auto l_coliterOth = l_polyiter.value().m_InsideMMSI.begin();
//     for ( ; l_coliterOth != l_polyiter.value().m_InsideMMSI.end(); l_coliterOth++ )
//     {
//         if (l_coliterOth.key() == MMSI)
//         {
//             continue;
//         }
//         auto &l_ais1COL = l_polyiter.value().m_CollisionData.find(MMSI); 
//         if (l_ais1COL == l_polyiter.value().m_CollisionData.end())//判断船1是否在碰撞参数内，不在则加入
//         {
//             QMap<QString, bool> l_map;
//             l_polyiter.value().m_CollisionData.insert(MMSI,l_map);
//             l_ais1COL = l_polyiter.value().m_CollisionData.find(MMSI);
//         }
//         QString l_oMMSI = l_coliterOth.key();
//         auto &l_ais1COLValue = l_ais1COL.value();//船1碰撞参数列表
//         if (l_ais1COLValue.find(l_oMMSI) == l_ais1COLValue.end())//判断船1的碰撞里是否有船2，不在则加入初始化为false
//         {
//             l_ais1COLValue.insert(l_oMMSI,false);
//         }
//         if (l_mapTarget.find(l_oMMSI) == l_mapTarget.end())
//         {
//             l_ais1COLValue.remove(l_oMMSI);
//             l_coliterOth++;
//             if (l_coliterOth == l_polyiter.value().m_InsideMMSI.end())
//             {
//                 return;
//             }
//             l_coliterOth--;
//             l_polyiter.value().m_InsideMMSI.remove(l_oMMSI);
//             continue;
//         }
//         hgTarget l_ais2 = l_mapTarget.find(l_oMMSI).value();
//         l_pointLLTarget.setLat(l_ais2.Lat);
//         l_pointLLTarget.setLon(l_ais2.Lon);
//         double l_dTCPA,l_dDCPA;
//         hg::utils::navutil::getTCPADCPA(l_pointLLOwn,l_ais1.SOG,l_ais1.COG,l_pointLLTarget,l_ais2.SOG,l_ais2.COG,&l_dTCPA,&l_dDCPA);
//         if (l_col.b_CollisionWatch == true)
//         {
//             if ( l_dDCPA < l_col.DCPA && l_dTCPA < l_col.TCPA)
//             {
//                 if (l_ais1COLValue.find(l_oMMSI).value() == false)//是否发过警报
//                 {
//                     l_ais1COLValue.find(l_oMMSI).value() = true;
//                     hgWarningMes l_mes;
//                     l_mes.set_warningid(hgWaringTypeGuid[COLLISIONWATCH]);
//                     l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
//                     l_mes.set_warningpriority(PriorityRed);
//                     l_mes.set_warningname("Collision Watch");
//                     l_mes.set_mmsi(MMSI.toStdString());
//                     l_mes.set_userlayguid(l_polyiter.key().toStdString());
//                     l_mes.set_userlayid(UserLayerType::UCricle);
//                     l_mes.set_warningtime(hgTargetManager::GetWarnTime());
//                     hgAlarmManager::SendMessage(l_mes,"hgWarningMes",handler);
//                 }
//             }
//             else
//             {
//                 l_ais1COLValue.find(l_oMMSI).value() = false;
//             }
//         }
//         else if (l_col.b_CollisionWatch == false)
//         {
//             if ( l_dDCPA < l_polyiter.value().m_ULWaring.col_dcpa && l_dTCPA < l_polyiter.value().m_ULWaring.col_tcpa)
//             {
//                 if (l_ais1COLValue.find(l_oMMSI).value() == false)//是否发过警报
//                 {
//                     l_ais1COLValue.find(l_oMMSI).value() = true;
//                     hgWarningMes l_mes;
//                     l_mes.set_warningid(hgWaringTypeGuid[COLLISIONWATCH]);
//                     l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
//                     l_mes.set_warningpriority(PriorityRed);
//                     l_mes.set_warningname("Collision Watch");
//                     l_mes.set_mmsi(MMSI.toStdString());
//                     l_mes.set_userlayguid(l_polyiter.key().toStdString());
//                     l_mes.set_userlayid(UserLayerType::UCricle);
//                     l_mes.set_warningtime(hgTargetManager::GetWarnTime());
//                     hgAlarmManager::SendMessage(l_mes,"hgWarningMes",handler);
//                 }
//             }
//             else
//             {
//                 l_ais1COLValue.find(l_oMMSI).value() = false;
//             }
//         }
//     }
}

void hgAlarmManager::SectorFoggyArea(QString Guid,vtsTimerHandler* handler)
{
    QMap <QString,hgSectorLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pSectorMap.find(Guid);
    if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pSectorMap.end())
    {
        return ;
    }
    QTime l_beginTime = QTime::fromString(QDateTime::fromTime_t(l_polyiter->m_ULWaring.m_FogBeginTime).toString("HH:mm:ss"),"HH:mm:ss");
    QTime l_endTime = QTime::fromString(QDateTime::fromTime_t(l_polyiter->m_ULWaring.m_FogEndTime).toString("HH:mm:ss"),"HH:mm:ss");
    for ( int i = 0; i < l_polyiter->m_ULWaring.m_FogMMSI.size(); i++ )
    {
        QString l_MMSI = l_polyiter->m_ULWaring.m_FogMMSI.at(i);
        if (l_polyiter.value().m_Info.find(l_MMSI) == l_polyiter.value().m_Info.end())
        {
            continue;
        }
        QTime l_nowTime = QTime::fromString(QDateTime::fromTime_t(hgTargetManager::GetWarnTime()).toString("HH:mm:ss"),"HH:mm:ss");
        hgShipWarningInfo& l_SWI = l_polyiter.value().m_Info.find(l_MMSI).value();
        if (l_SWI.FogTime == -1)
        {
            l_SWI.FogTime = hgTargetManager::GetWarnTime();//QDateTime::currentDateTime().toTime_t();
        }
        if (l_nowTime >= l_beginTime && l_nowTime <= l_endTime)
        {
            if (hgTargetManager::GetWarnTime() - l_SWI.FogTime > l_polyiter->m_ULWaring.m_FogTime
                && l_SWI.IsSendFog == false)
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[FoggyArea]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname("Foggy Area");
                l_mes.set_mmsi(l_MMSI.toStdString());
                l_mes.set_userlayguid(l_polyiter.key().toStdString());
                l_mes.set_userlayid(UserLayerType::USector);
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",handler);
                l_SWI.IsSendFog = true;
            }
        }
        else
        {
            l_SWI.IsSendFog = false;
            l_SWI.FogTime = -1;
        }
    }
}

bool hgAlarmManager::PointInsideSector(double lat,double lon,double CenterLat,double CenterLon,double radius,double Begin,double End)
{
//     auto l_lockerTarget = hgTargetManager::getMapTargetLocker();
//     auto &l_mapTarget = l_lockerTarget->raw();
    hg::utils::PointLL l_PointLL(lon,lat);
    hg::utils::PointLL l_CenterLL(CenterLon,CenterLat);
    double l_dist,l_angle;
    hg::utils::navutil::getDistanceBearing(l_CenterLL,l_PointLL,&l_dist,&l_angle);
    if (l_dist > radius || radius == 0)
    {
        return false;
    }
    if (Begin == End)
    {
        return true;
    }
    if (Begin < End)
    {
        if (l_angle > Begin && l_angle < End)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (Begin > End)
    {
        if (l_angle > Begin || l_angle < End)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}


//抛锚区
bool hgAlarmManager::FindTarget(QString id, QString MMSI,int &type,QString &GUID)
{
    mymap<QString,hgTarget>::iterator l_itAis;
    l_itAis = hgTargetManager::m_mapTarget.find(MMSI);
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter;
    for (l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.begin(); l_polyiter != hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end(); ++l_polyiter)
    {   
        if ( l_polyiter.value().m_WaringID.indexOf(hgWaringTypeGuid[ANCHORAGE]) != -1)
        {
            hg::utils::PointLL l_aisPointLL;
            l_aisPointLL.setLat(l_itAis->Lat);
            l_aisPointLL.setLon(l_itAis->Lon);
            if (l_polyiter->m_Polygon.containsPoint(l_aisPointLL,Qt::OddEvenFill))
            {
                if (l_polyiter.key() == id)
                {
                    return false;
                }
                else
                {
                    type = UPolygon; 
                    GUID = l_polyiter.key();
                    return true;
                }
            }
        }
    }

    QMap <QString,hgCricleLayer>::Iterator l_cricle;
    for (l_cricle = hgAlarmManager::m_LayerDataManager.m_pCricleMap.begin(); l_cricle != hgAlarmManager::m_LayerDataManager.m_pCricleMap.end(); ++l_cricle)
    {  
        if ( l_cricle.value().m_WaringID.indexOf(hgWaringTypeGuid[ANCHORAGE]) != -1)
        {
            hg::utils::PointLL l_aisPointLL;
            hg::utils::PointLL l_criclePointLL;
            double l_dDistance;
            l_aisPointLL.setLat(l_itAis->Lat);
            l_aisPointLL.setLon(l_itAis->Lon);
            l_criclePointLL.setLat(l_cricle->m_Lat);
            l_criclePointLL.setLon(l_cricle->m_Lon);
            l_dDistance = hg::utils::navutil::getDistance(l_aisPointLL,l_criclePointLL); 
            if (l_dDistance <= l_cricle->m_Radius)
            {
                if (l_polyiter.key() == id)
                {
                    return false;
                }
                else
                {
                    type = UCricle; 
                    GUID = l_polyiter.key();
                    return true;
                }
            }
        }
    }

    QMap <QString,hgSectorLayer>::Iterator l_sector;
    for (l_sector = hgAlarmManager::m_LayerDataManager.m_pSectorMap.begin(); l_sector != hgAlarmManager::m_LayerDataManager.m_pSectorMap.end(); l_sector++)
    {  
        if ( l_sector.value().m_WaringID.indexOf(hgWaringTypeGuid[ANCHORAGE]) != -1)
        {
            if (PointInsideSector(l_itAis->Lat,l_itAis->Lon,l_sector->m_Lat,l_sector->m_Lon,l_sector->m_Radius,l_sector->m_BeginAngle,l_sector->m_EndAngle))
            {
                if (l_polyiter.key() == id)
                {
                    return false;
                }
                else
                {
                    type = USector; 
                    GUID = l_polyiter.key();
                    return true;
                }
            }
        }
    }

    return false;
}

int hgAlarmManager::CurrentsTracks(QString id, long int eta, long int etd)
{
    int l_iCurrentCount = 0;
    QMap<QString,AnchorReserv>::iterator l_it;
    for (l_it = m_WarningSetManager.m_mapAnchorReserv.begin(); l_it != m_WarningSetManager.m_mapAnchorReserv.end(); l_it++)
    {
        if (l_it->b_AnchorReserv == true && l_it->ID == id)
        {
            if ((eta > l_it->ETA && eta < l_it->ETD) || ((eta < l_it->ETA || eta == l_it->ETA) && etd > l_it->ETD))
            {
                l_iCurrentCount++;
            }
        }
    }
    return l_iCurrentCount;
}

bool hgAlarmManager::DomainWatchMsg(QString MMSI, double lat, double lon, double distance)
{
    auto l_infoIt = m_WarningSetManager.m_mapWarnInfo.find(MMSI);
    if (l_infoIt != m_WarningSetManager.m_mapWarnInfo.end())
    {
        l_infoIt->m_listDomainCancel.clear();
    }

    if (m_WarningSetManager.m_mapWarnInfo.find(MMSI) == m_WarningSetManager.m_mapWarnInfo.end())//  [6/7/2017 LianXinDuan] 
    {
        return false;
    }
    mymap<QString,hgTarget>::iterator l_itAisLoop;
    for (l_itAisLoop = hgTargetManager::m_mapTarget.begin(); l_itAisLoop != hgTargetManager::m_mapTarget.end(); ++l_itAisLoop)
    {
        if (MMSI == l_itAisLoop->ID)
        {
            continue;
        }
        hg::utils::PointLL l_pointLLOwn,l_pointLLTarget;
        double l_dDistance;
        l_pointLLOwn.setLat(lat);
        l_pointLLOwn.setLon(lon);
        l_pointLLTarget.setLat(l_itAisLoop->Lat);
        l_pointLLTarget.setLon(l_itAisLoop->Lon);
        l_dDistance = hg::utils::navutil::getDistance(l_pointLLOwn,l_pointLLTarget)*NM2M;  //海里->米
        if (l_dDistance <= distance)
        {
            QMap<double,hgTarget>::iterator l_itDis;
            l_itDis = m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.begin();
            bool l_bSame = false;
            while (l_itDis != m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.end())
            {
                if (l_itAisLoop->MMSI == l_itDis->MMSI)
                {
                    if (l_itDis->DomainWatch == true)
                    {
                        l_bSame = true;
                    }
                    l_itDis = m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.erase(l_itDis);
                }
                else
                {
                    l_itDis++;
                }
            }
            if (l_bSame == false)
            {
                m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.insert(l_dDistance,l_itAisLoop.value());
                m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.find(l_dDistance)->DomainWatch = false;
            }
            else
            {
                m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.insert(l_dDistance,l_itAisLoop.value());
                m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.find(l_dDistance)->DomainWatch = true;
            }
        }
        else
        {
            QMap<double,hgTarget>::iterator l_itDis;
            l_itDis = m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.begin();
            while (l_itDis != m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.end())
            {
                if (l_itAisLoop->MMSI == l_itDis->MMSI)
                {
                    m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_listDomainCancel.push_back(l_itAisLoop->MMSI);
                    l_itDis = m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.erase(l_itDis);
                }
                else
                {
                    l_itDis++;
                }
            }
        }
    }
    if (m_WarningSetManager.m_mapWarnInfo.find(MMSI)->m_mapDomainWatch.size() > 0)
    {
        return true;
    } 
    else
    {
        return false;
    }
}

//报告区
bool hgAlarmManager::ReportEnter(QString MMSI)
{
    mymap<QString,hgTarget>::iterator l_itAis;
    l_itAis = hgTargetManager::m_mapTarget.find(MMSI);
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter;
    for (l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.begin(); l_polyiter != hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end(); l_polyiter++)
    {   
        if ( l_polyiter.value().m_WaringID.indexOf(hgWaringTypeGuid[REPORTINGAREA]) != -1)
        {
            hg::utils::PointLL l_aisPointLL;
            l_aisPointLL.setLat(l_itAis->Lat);
            l_aisPointLL.setLon(l_itAis->Lon);
            if (l_polyiter->m_Polygon.containsPoint(l_aisPointLL,Qt::OddEvenFill))
            {
                return true;
            }
        }
    }

    QMap <QString,hgCricleLayer>::Iterator l_cricle;
    for (l_cricle = hgAlarmManager::m_LayerDataManager.m_pCricleMap.begin(); l_cricle != hgAlarmManager::m_LayerDataManager.m_pCricleMap.end(); l_cricle++)
    {  
        if ( l_cricle.value().m_WaringID.indexOf(hgWaringTypeGuid[REPORTINGAREA]) != -1)
        {
            hg::utils::PointLL l_aisPointLL;
            hg::utils::PointLL l_criclePointLL;
            double l_dDistance;
            l_aisPointLL.setLat(l_itAis->Lat);
            l_aisPointLL.setLon(l_itAis->Lon);
            l_criclePointLL.setLat(l_cricle->m_Lat);
            l_criclePointLL.setLon(l_cricle->m_Lon);
            l_dDistance = hg::utils::navutil::getDistance(l_aisPointLL,l_criclePointLL); 
            if (l_dDistance <= l_cricle->m_Radius)
            {
                return true;
            }
        }
    }

    QMap <QString,hgSectorLayer>::Iterator l_sector;
    for (l_sector = hgAlarmManager::m_LayerDataManager.m_pSectorMap.begin(); l_sector != hgAlarmManager::m_LayerDataManager.m_pSectorMap.end(); l_sector++)
    {  
        if ( l_sector.value().m_WaringID.indexOf(hgWaringTypeGuid[REPORTINGAREA]) != -1)
        {
            if (PointInsideSector(l_itAis->Lat,l_itAis->Lon,l_sector->m_Lat,l_sector->m_Lon,l_sector->m_Radius,l_sector->m_BeginAngle,l_sector->m_EndAngle))
            {
                return true;
            }
        }
    }

    return false;
}

long int hgAlarmManager::ReportNoEnter(QMap<QString,AreaData>& map, QString MMSI)
{
    QString id;
    QMap<QString,AreaData>::iterator itArea;
    mymap<QString,hgTarget>::iterator l_itAis;
    l_itAis = hgTargetManager::m_mapTarget.find(MMSI);
    QMap <QString,hgPolygonLayer>::Iterator l_polyiter;
    for (l_polyiter = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.begin(); l_polyiter != hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end(); l_polyiter++)
    {   
        /////////报告区
        if ( l_polyiter.value().m_WaringID.indexOf(hgWaringTypeGuid[REPORTINGAREA]) != -1)
        {
            hg::utils::PointLL l_aisPointLL;
            l_aisPointLL.setLat(l_itAis->Lat);
            l_aisPointLL.setLon(l_itAis->Lon);
            if (l_polyiter->m_Polygon.containsPoint(l_aisPointLL,Qt::OddEvenFill))
            {
                itArea = map.find(l_polyiter.key());
                if (itArea != map.end())
                {
                    return time(NULL);
                }
                else
                {
                    return Yes;
                }
            }
        }
    }


    QMap <QString,hgCricleLayer>::Iterator l_cricle;
    for (l_cricle = hgAlarmManager::m_LayerDataManager.m_pCricleMap.begin(); l_cricle != hgAlarmManager::m_LayerDataManager.m_pCricleMap.end(); l_cricle++)
    {  
        if ( l_cricle.value().m_WaringID.indexOf(hgWaringTypeGuid[REPORTINGAREA]) != -1)
        {
            hg::utils::PointLL l_aisPointLL;
            hg::utils::PointLL l_criclePointLL;
            double l_dDistance;
            l_aisPointLL.setLat(l_itAis->Lat);
            l_aisPointLL.setLon(l_itAis->Lon);
            l_criclePointLL.setLat(l_cricle->m_Lat);
            l_criclePointLL.setLon(l_cricle->m_Lon);
            l_dDistance = hg::utils::navutil::getDistance(l_aisPointLL,l_criclePointLL); 
            if (l_dDistance <= l_cricle->m_Radius)
            {
                itArea = map.find(l_polyiter.key());
                if (itArea != map.end())
                {
                    return time(NULL);
                }
                else
                {
                    return Yes;
                }
            }
        }
    }

    QMap <QString,hgSectorLayer>::Iterator l_sector;
    for (l_sector = hgAlarmManager::m_LayerDataManager.m_pSectorMap.begin(); l_sector != hgAlarmManager::m_LayerDataManager.m_pSectorMap.end(); l_sector++)
    {  
        if ( l_sector.value().m_WaringID.indexOf(hgWaringTypeGuid[REPORTINGAREA]) != -1)
        {
            if (PointInsideSector(l_itAis->Lat,l_itAis->Lon,l_sector->m_Lat,l_sector->m_Lon,l_sector->m_Radius,l_sector->m_BeginAngle,l_sector->m_EndAngle))
            {
                itArea = map.find(l_polyiter.key());
                if (itArea != map.end())
                {
                    return time(NULL);
                }
                else
                {
                    return Yes;
                }
            }
        }
    }

    return No;
}

int hgAlarmManager::SpeedWatching(SpeedWatch speed)
{
    mymap<QString,hgTarget>::iterator l_itAis;
    QMap<QString,SpeedWatch>::iterator l_itSpeedWatch;
    l_itSpeedWatch = hgAlarmManager::m_WarningSetManager.m_mapSpeedWatch.find(speed.TargetID);
    l_itAis = hgTargetManager::m_mapTarget.find(speed.TargetID);

    if (l_itAis->SOG < speed.MinSpeed)
    {
        l_itSpeedWatch->MinTimeKeep++;
    }
    else
    {
        l_itSpeedWatch->MinTimeKeep = 0;
        m_WarningSetManager.m_mapWarnInfo.find(speed.TargetID)->m_bIsMinSpeed = false;
    }
    if (l_itAis->SOG > speed.MaxSpeed)
    {
        l_itSpeedWatch->MaxTimeKeep++;
    } 
    else
    {
        l_itSpeedWatch->MaxTimeKeep = 0;
        m_WarningSetManager.m_mapWarnInfo.find(speed.TargetID)->m_bIsMaxSpeed = false;
    }

    if (l_itSpeedWatch->MinTimeKeep > speed.MinDuration + 1)
    {
        return MinSpeed;
    }
    else if (l_itSpeedWatch->MaxTimeKeep > speed.MaxDuration + 3)
    {
        return MaxSpeed;
    }
    else
    {
        return Other;
    }
}

int hgAlarmManager::CollisionWatching(CollisionWatch collision, hgTarget ais, hgTarget collisionValue)
{
    hg::utils::PointLL l_pointLLOwn,l_pointLLTarget,l_pointLLEnd;
    double l_dTCPA,l_dDCPA;
    l_pointLLOwn.setLat(collisionValue.Lat);
    l_pointLLOwn.setLon(collisionValue.Lon);
    l_pointLLTarget.setLat(ais.Lat);
    l_pointLLTarget.setLon(ais.Lon);
    hg::utils::navutil::getTCPADCPA(l_pointLLOwn,collisionValue.SOG,collisionValue.COG,l_pointLLTarget,ais.SOG,ais.COG,&l_dTCPA,&l_dDCPA);
    if (l_dDCPA <= collision.DCPA && abs(l_dTCPA) <= collision.TCPA)
    {
        /*for (int i = 0; i < m_WarningSetManager.m_mapWarnInfo.find(collision.MMSI)->m_listCollision.size(); i++)
        {
            if (ais.MMSI == m_WarningSetManager.m_mapWarnInfo.find(collision.MMSI)->m_listCollision[i])
            {
                return false;
            }
        }*/
        m_WarningSetManager.m_mapWarnInfo.find(collision.TargetID)->m_listCollision.append(ais.ID);
        return IsSendWarn;
    }
    else
    {
        for (int i = 0; i < m_WarningSetManager.m_mapWarnInfo.find(collision.TargetID)->m_listCollision.size(); i++)
        {
            if (ais.ID == m_WarningSetManager.m_mapWarnInfo.find(collision.TargetID)->m_listCollision[i])
            {
                m_WarningSetManager.m_mapWarnInfo.find(collision.TargetID)->m_listCollision.removeAt(i);
                return CancelWarn;
            }
        }
        return UnSendWarn;
    }
}

bool hgAlarmManager::TurnOver(TurnCircle turn)
{
    mymap<QString,hgTarget>::iterator l_itAisMsg;
    l_itAisMsg = hgTargetManager::m_mapTarget.find(turn.TargetID);
    hg::utils::PointLL l_pointLLOwn,l_pointLLTarget;
    double l_dDistance;
    l_pointLLOwn.setLat(l_itAisMsg->Lat);
    l_pointLLOwn.setLon(l_itAisMsg->Lon);
    l_pointLLTarget.setLat(turn.TurnLat);
    l_pointLLTarget.setLon(turn.TurnLon);
    l_dDistance = hg::utils::navutil::getDistance(l_pointLLOwn,l_pointLLTarget)*NM2M;  //海里->米
    if (l_dDistance <= turn.TurnRadius)
    {
        return false;
    } 
    else
    {
        return true;
    }
}

void hgAlarmManager::SaveWarnData(hgSqlOperator& sqlOperator, hgWarningMes &msg)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("warning_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("WarnID",QString::fromStdString(msg.warningid()));
    l_data.insert("WarnDUID",QString::fromStdString(msg.warningguid()));
    l_data.insert("WarningPriority",msg.warningpriority());
    l_data.insert("WarningName",QString::fromStdString(msg.warningname()));
    //l_data.insert("Message",msg.message());
    l_data.insert("MMSI",QString::fromStdString(msg.mmsi()));
    l_data.insert("UserLayGUID",QString::fromStdString(msg.userlayguid()));
    l_data.insert("UserLayID",msg.userlayid());
    l_data.insert("ID",QString::fromStdString(msg.id()));
    l_data.insert("WarningTime",msg.warningtime());
    l_data.insert("WarningType",msg.warningtype());
    l_data.insert("TargetMMSI",QString::fromStdString(msg.targetmmsi()));
    l_pSqlInsertCmd->SetData(l_data);
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

