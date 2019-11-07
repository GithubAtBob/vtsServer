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

    void InitShipWarningInfo(hgPolygonLayer& layer,hgTarget& ais,QString areaID);//�˴��Ƿ���ͼ���ڼ�¼
    void InsideInitData(hgPolygonLayer& layer,hgTarget& ais,QString areaID);
    void OusideInitData(hgPolygonLayer& layer,hgTarget& ais,QString areaID);
    void FinishIninData(hgPolygonLayer& layer,hgTarget& ais,QString areaID);

    ///�������ھ���
    void NewTrack(hgPolygonLayer& layer,hgTarget& ais,QString areaID);///////////��Ŀ�����ƣ�ûѡ�������´�������
    void EnterWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);///////////////////����
    void HighSpeedWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////���ټ��
    void LowSpeedWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////���ټ��
    void ProhibitedWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////��ê��
    void AnchorageWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////��ê��
    void AddWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////���ټ��
    void CourseWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////����ͻ����
    void GroundWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////��ǳ���
    void FoggyAreaWatch(QString GUID,hgPolygonLayer& layer,QString areaID);//////�����

    ////�����⾯��
    void LostWatch(hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////��ʧĿ������
    void LeaveWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////�뿪���
    void ApproachWatch(QString GUID,hgPolygonLayer& layer,hgTarget& ais,QString areaID);//////�ӽ����

    void CongestionWatch(QString GUID,hgPolygonLayer& layer,QString areaID);/////////ӵ��������
};
