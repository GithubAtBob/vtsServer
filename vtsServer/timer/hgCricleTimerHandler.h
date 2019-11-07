#pragma once

#include "frame/vtsTimerHandler.h"

class hgWarningMes;
class hgCricleLayer;
class hgTarget;
class hgCricleTimerHandler : public vtsTimerHandler
{
public:
    hgCricleTimerHandler(const std::string& name);
    ~hgCricleTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

    void SQLOperate(hgWarningMes& mes);

    void InsideWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);
    void OutsideWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);

    void InitShipWarningInfo(hgCricleLayer& layer,hgTarget& ais,QString areaID);//�˴��Ƿ���ͼ���ڼ�¼
    void InsideInitData(hgCricleLayer& layer,hgTarget& ais,QString areaID);
    void OusideInitData(hgCricleLayer& layer,hgTarget& ais,QString areaID);
    void FinishIninData(hgCricleLayer& layer,hgTarget& ais,QString areaID);

    ///�������ھ���
    void NewTrack(hgCricleLayer& layer,hgTarget& ais,QString areaID);///////////��Ŀ�����ƣ�ûѡ�������´�������
    void EnterWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);///////////////////����
    void HighSpeedWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);//////���ټ��
    void LowSpeedWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);//////���ټ��
    void ProhibitedWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);//////��ê��
    void AnchorageWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);//////��ê��
    void AddWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);//////���ټ��
    void CourseWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);//////����ͻ����
    void GroundWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);//////��ǳ���
    void FoggyAreaWatch(QString GUID,hgCricleLayer& layer,QString areaID);//////�����

    ////�����⾯��
    void LostWatch(hgCricleLayer& layer,hgTarget& ais,QString areaID);//////��ʧĿ������
    void LeaveWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);//////�뿪���
    void ApproachWatch(QString GUID,hgCricleLayer& layer,hgTarget& ais,QString areaID);//////�ӽ����

    void CongestionWatch(QString GUID,hgCricleLayer& layer,QString areaID);/////////ӵ��������

};
