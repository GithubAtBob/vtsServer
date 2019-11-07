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

enum hgAlarmManagerWaringType{//Ҫ�����Ķ�ʱ������
    WaringPolygon = 1,
    WarningCricle,
    WarningSector,
    WarningReportLine,
    WarningAnchorArea,  //��ê������
    WarningAnchorWatch,//êλ���
    WarningAnchorReserv,//Ԥ����ê�ؾ���
    WarningBerthWatch,//�����ڲ�λ�ľ���
    WarningCollisionWatch,//��ײ����
    WarningDomainWatch,    //�������򱨾�
    WarningGroundWatch,    //��ǳ����
    WarningChannel,        //����
    WarningReportArea,  //�������򱨾�......
    WarningSpeed,          //��С�ٶ�
    WarningTurnCircle, //ת��ʱ��ļ��  
    WarningMovementEnd, //���������ƶ�
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
    ////�����
    static bool PolygonEnterWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonLeaveWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonApproachWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonProhibited(QString Guid,QString MMSI,hgTarget &Ais);//��ê
    static bool PolygonAnchorage(QString Guid,QString MMSI,hgTarget &Ais);//��ê
    static bool PolygonHighSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonLowSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonAddMaxWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonAddMinWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool PolygonCongestionWatch(QString Guid);
    static bool PolygonGround(QString Guid,QString MMSI,hgTarget &Ais);//��ǳ
    static bool PolygonCourse(QString Guid,QString MMSI,hgTarget &Ais);//����ͻ����
    static void PolygonCollision(QString Guid,QString MMSI,vtsTimerHandler* handler);//��ײ����ֵ������
    static void PolygonFoggyArea(QString Guid,vtsTimerHandler* handler);

    //static void GetApproachPoint(hg::utils::PolygonLL polygonLL, double angle,hg::utils::PointLL &point,double &dist);//��ȡ����������ӽ��ĵ����//�����

    ////Բ
    static bool CricleEnterWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleLeaveWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleApproachWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleProhibited(QString Guid,QString MMSI,hgTarget &Ais);//��ê
    static bool CricleAnchorage(QString Guid,QString MMSI,hgTarget &Ais);//��ê
    static bool CricleHighSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleLowSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleAddMaxWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleAddMinWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool CricleCongestionWatch(QString Guid);
    static bool CricleGround(QString Guid,QString MMSI,hgTarget &Ais);//��ǳ
    static bool CricleCourse(QString Guid,QString MMSI,hgTarget &Ais);//����ͻ����
    static void CricleCollision(QString Guid,QString MMSI,vtsTimerHandler* handler);//��ײ
    static void CricleFoggyArea(QString Guid,vtsTimerHandler* handler);
    ////����
    static bool SectorEnterWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorLeaveWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorApproachWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorProhibited(QString Guid,QString MMSI,hgTarget &Ais);//��ê
    static bool SectorAnchorage(QString Guid,QString MMSI,hgTarget &Ais);//��ê
    static bool SectorHighSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorLowSpeed(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorAddMaxWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorAddMinWatch(QString Guid,QString MMSI,hgTarget &Ais);
    static bool SectorCongestionWatch(QString Guid);
    static bool SectorGround(QString Guid,QString MMSI,hgTarget &Ais);//��ǳ
    static bool SectorCourse(QString Guid,QString MMSI,hgTarget &Ais);//����ͻ����
    static void SectorCollision(QString Guid,QString MMSI,vtsTimerHandler* handler);//��ײ
    static void SectorFoggyArea(QString Guid,vtsTimerHandler* handler);

    static bool PointInsideSector(double lat,double lon,double CenterLat,double CenterLon,double radius,double Begin,double End);//�����꣬Բ�����꣬�뾶����ʼ�ǣ�������

    //target������Ϣ����
    static bool FindTarget(QString id, QString MMSI,int &type,QString &GUID);  //�Ƿ������ê��
    static int CurrentsTracks(QString id, long int eta, long int etd); //ê��Ԥ��λ��
    static bool DomainWatchMsg(QString MMSI, double lat, double lon, double distance); //�Ƿ���������
    static bool ReportEnter(QString MMSI);   //�Ƿ���뱨����
    static long int ReportNoEnter(QMap<QString,AreaData>& map, QString MMSI);   //�Ƿ��������������
    static int SpeedWatching(SpeedWatch speed); //�ٶȼ��
    static int CollisionWatching(CollisionWatch collision, hgTarget ais, hgTarget collisionValue); //��ײ���
    static bool TurnOver(TurnCircle turn); //ת�򳬳�

    static void SaveWarnData(hgSqlOperator& sqlOperator, hgWarningMes &msg); //��������ݿ�
public:

    static hgLayerDataManager m_LayerDataManager;
    static hgWarningSetManager m_WarningSetManager;
    static QStringList m_listArea;//Ԥ������������GUID
    static QMap <QString, int> m_ShipPosition;//QString mmsi int ��ǰ���˷��� 0
    static int m_AlgorithmMode;
    static double m_alarm1;
    static double m_alarm2;
    static double m_alarm3;
};

#endif //HG_DATAMANAGER_H_