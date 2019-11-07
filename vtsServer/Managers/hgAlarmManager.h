#ifndef HG_ALARMMANAGER_H_
#define HG_ALARMMANAGER_H_
#include <QMap>
#include "frame/vtsRequestHandler.h"
#include "frame/vtsTimerHandler.h"
#include "message/hgWarningMes.pb.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"
#include "Managers/hgWarningSetManager.h"
class hgWarningMes;
namespace hg
{
    namespace utils
    {
        class PointLL;
        class PolygonLL;
    }
}

enum hgAlarmManagerWaringType{//要开启的定时器类型
    WaringPolygon = 1,
    WarningCricle,
    WarningSector,
    WarningReportLine,
    WarningAnchorArea,  //抛锚区警报
    WarningAnchorWatch,//锚位监控
    WarningAnchorReserv,//预留的锚地警报
    WarningBerthWatch,//船舶在泊位的警报
    WarningCollisionWatch,//碰撞警报
    WarningDomainWatch,    //船舶领域报警
    WarningGroundWatch,    //搁浅报警
    WarningChannel,        //航道
    WarningReportArea,  //报告区域报警......
    WarningSpeed,          //最小速度
    WarningTurnCircle, //转向时候的监控  
    WarningMovementEnd, //船舶不在移动
};

enum hgReportNoEnterType{
    No = 0,
    Yes,
};

enum hgSpeedType{
    MinSpeed = 0,
    MaxSpeed,
    Other,
}; 

enum hgCollisionType{
    IsSendWarn = 0,
    UnSendWarn,
    CancelWarn,
}; 

enum hgShipPosition{
    SPNorthArea = 0,
    SPSouthArea,
    SPNorthToSouth,
    SPSouthToNorth,
    SPUnknow,
};


class hgAlarmManager
{
public:
	hgAlarmManager(void);
    ~hgAlarmManager(void);
    static void ReadLayerData(hgSqlOperator& sqlOperator);
    static void StartWarning(const std::string ID,int type,vtsRequestHandler *handler);
    static void StartWarning(const std::string ID,int type,vtsServer *s);
    static void StopWarning(const std::string ID,vtsRequestHandler *handler);
    static void SendMessage(google::protobuf::Message& msg,const std::string msgType,vtsTimerHandler* handler);
    static void ReadSetData(hgSqlOperator& sqlOperator,vtsServer *s);
    ////多边形
    static bool PolygonEnterWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonLeaveWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonApproachWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonProhibited(QString Guid,QString MMSI,hgTarget &Ais);//禁锚
    static bool PolygonAnchorage(QString Guid,QString MMSI,hgTarget &Ais);//抛锚
    static bool PolygonHighSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonLowSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonAddMaxWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonAddMinWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonCongestionWatch(QString Guid);
    static bool PolygonGround(QString Guid,QString MMSI,hgTarget &Ais);//搁浅
    static bool PolygonCourse(QString Guid,QString MMSI,hgTarget &Ais);//航向突变监控
    static void PolygonCollision(QString Guid,QString MMSI,vtsTimerHandler* handler);//碰撞返回值无意义
    static void PolygonFoggyArea(QString Guid,vtsTimerHandler* handler);

    //static void GetApproachPoint(hg::utils::PolygonLL polygonLL, double angle,hg::utils::PointLL &point,double &dist);//获取船方向上最接近的点距离//多边形

    ////圆
    static bool CricleEnterWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleLeaveWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleApproachWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleProhibited(QString Guid,QString MMSI,hgTarget &Ais);//禁锚
    static bool CricleAnchorage(QString Guid,QString MMSI,hgTarget &Ais);//抛锚
    static bool CricleHighSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleLowSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleAddMaxWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleAddMinWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleCongestionWatch(QString Guid);
    static bool CricleGround(QString Guid,QString MMSI,hgTarget &Ais);//搁浅
    static bool CricleCourse(QString Guid,QString MMSI,hgTarget &Ais);//航向突变监控
    static void CricleCollision(QString Guid,QString MMSI,vtsTimerHandler* handler);//碰撞
    static void CricleFoggyArea(QString Guid,vtsTimerHandler* handler);
    ////扇形
    static bool SectorEnterWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorLeaveWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorApproachWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorProhibited(QString Guid,QString MMSI,hgTarget &Ais);//禁锚
    static bool SectorAnchorage(QString Guid,QString MMSI,hgTarget &Ais);//抛锚
    static bool SectorHighSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorLowSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorAddMaxWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorAddMinWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorCongestionWatch(QString Guid);
    static bool SectorGround(QString Guid,QString MMSI,hgTarget &Ais);//搁浅
    static bool SectorCourse(QString Guid,QString MMSI,hgTarget &Ais);//航向突变监控
    static void SectorCollision(QString Guid,QString MMSI,vtsTimerHandler* handler);//碰撞
    static void SectorFoggyArea(QString Guid,vtsTimerHandler* handler);

    static bool PointInsideSector(double lat,double lon,double CenterLat,double CenterLon,double radius,double Begin,double End);//点坐标，圆心坐标，半径，起始角，结束角

    //target警告信息发送
    static bool FindTarget(QString id, QString MMSI,int &type,QString &GUID);  //是否进入抛锚区
    static int CurrentsTracks(QString id, long int eta, long int etd); //锚地预留位置
    static bool DomainWatchMsg(QString MMSI, double lat, double lon, double distance); //是否入侵领域
    static bool ReportEnter(QString MMSI);   //是否进入报告区
    static long int ReportNoEnter(QMap<QString,AreaData>& map, QString MMSI);   //是否进入其它报告区
    static int SpeedWatching(SpeedWatch speed); //速度检测
    static int CollisionWatching(CollisionWatch collision, hgTarget ais, hgTarget collisionValue); //碰撞检测
    static bool TurnOver(TurnCircle turn); //转向超出

    static void SaveWarnData(hgSqlOperator& sqlOperator, hgWarningMes &msg); //保存进数据库
public:

    static hgLayerDataManager m_LayerDataManager;
    static hgWarningSetManager m_WarningSetManager;
    static QStringList m_listArea;//预警不警报区域GUID
    static QMap <QString, int> m_ShipPosition;//QString mmsi int 当前船端方向 0
    static int m_AlgorithmMode;
    static double m_alarm1;
    static double m_alarm2;
    static double m_alarm3;
};

#endif //HG_DATAMANAGER_H_