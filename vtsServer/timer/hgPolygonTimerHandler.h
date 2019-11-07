#pragma once

#include "frame/vtsTimerHandler.h"
#include "message/hgWarningMes.pb.h"

namespace hg
{
    namespace utils
    {
        class PointLL;
        class PolygonLL;
    }
}
class hgWarningMes;
class hgPolygonLayer;
class hgTarget;
class hgPolygonTimerHandler : public vtsTimerHandler
{
public:
    hgPolygonTimerHandler(const std::string& name);
    ~hgPolygonTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

    void SQLOperate(hgWarningMes& mes);

    void InsideWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);
    void OutsideWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);

    void InitShipWarningInfo(hgPolygonLayer& layer,hgTarget& ais,QString areaID);//此船是否在图形内记录
    void InsideInitData(hgPolygonLayer& layer,hgTarget& ais,QString areaID);
    void OusideInitData(hgPolygonLayer& layer,hgTarget& ais,QString areaID);
    void FinishIninData(hgPolygonLayer& layer,hgTarget& ais,QString areaID);

    ///区域与内警报
    void NewTrack(hgPolygonLayer& layer,hgTarget& ais,QString areaID);///////////新目标抑制（没选中则有新船报警）
    void EnterWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);///////////////////入侵
    void HighSpeedWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////高速监控
    void LowSpeedWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////低速监控
    void ProhibitedWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////禁锚区
    void AnchorageWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////抛锚区
    void AddWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////加速监控
    void CourseWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////航向突变监控
    void GroundWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////搁浅监控
    void FoggyAreaWatch(QString GUID,hgPolygonLayer& layer,QString areaID);//////雾航监控

    ////区域外警报
    void LostWatch(hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////丢失目标抑制
    void LeaveWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////离开监控
    void ApproachWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////接近监控

    void CongestionWatch(QString GUID,hgPolygonLayer& layer,QString areaID);/////////拥挤区域监控
};
