#pragma once

#include "frame/vtsTimerHandler.h"

class hgWarningMes;
class hgSectorLayer;
class hgTarget;
class hgSectorTimerHandler : public vtsTimerHandler
{
public:
    hgSectorTimerHandler(const std::string& name);
    ~hgSectorTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

    void SQLOperate(hgWarningMes& mes);

    void InsideWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);
    void OutsideWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);

    void InitShipWarningInfo(hgSectorLayer& layer,hgTarget& ais,QString areaID);//�˴��Ƿ���ͼ���ڼ�¼
    void InsideInitData(hgSectorLayer& layer,hgTarget& ais,QString areaID);
    void OusideInitData(hgSectorLayer& layer,hgTarget& ais,QString areaID);
    void FinishIninData(hgSectorLayer& layer,hgTarget& ais,QString areaID);

    ///�������ھ���
    void NewTrack(hgSectorLayer& layer,hgTarget& ais,QString areaID);///////////��Ŀ�����ƣ�ûѡ�������´�������
    void EnterWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);///////////////////����
    void HighSpeedWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);//////���ټ��
    void LowSpeedWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);//////���ټ��
    void ProhibitedWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);//////��ê��
    void AnchorageWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);//////��ê��
    void AddWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);//////���ټ��
    void CourseWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);//////����ͻ����
    void GroundWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);//////��ǳ���
    void FoggyAreaWatch(QString GUID,hgSectorLayer& layer,QString areaID);//////�����

    ////�����⾯��
    void LostWatch(hgSectorLayer& layer,hgTarget& ais,QString areaID);//////��ʧĿ������
    void LeaveWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);//////�뿪���
    void ApproachWatch(QString GUID,hgSectorLayer& layer,hgTarget& ais,QString areaID);//////�ӽ����

    void CongestionWatch(QString GUID,hgSectorLayer& layer,QString areaID);/////////ӵ��������

};
