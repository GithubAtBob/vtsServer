#ifndef HG_SHIPWARNINGINFO_H_
#define HG_SHIPWARNINGINFO_H_
#include "Managers/hgTargetManager.h"

enum hgShipInfoPosType{
    ShipInsidePos = 1,
    ShipOutSidePos
};

enum hgShipWarningType{
    IsAnchorArea = 1,  //��ê������
    IsClubbing, //��ê����
    IsDragging, //��ê����
    IsAnchorReserv,//Ԥ����ê�ؾ���
    IsBerthWatch,//�����ڲ�λ�ľ���
    //bool m_bIsCollisionWatch,//��ײ����
    IsDomainWatch,    //�������򱨾�
    IsGroundWatch,    //��ǳ����
    IsChannel,        //����
    IsReportArea,  //�������򱨾�......
    IsReportTime,
    IsEarlist,
    IsLatest,
    IsMinSpeed,          //��С�ٶ�
    IsMaxSpeed,          //����ٶ�
    IsTurnCircle, //ת��ʱ��ļ��  
    IsMovementEnd, //���������ƶ�
    OtherType,
};

class hgShipWarningInfo//������־λ��
{
public:
	hgShipWarningInfo(void);
    ~hgShipWarningInfo(void);
    void ResetOutside();//���������������������������ʱ��
    void ResetInside();//�����������ڲ��������뿪����ʱ��
    void InitShipWarningInfo();
    void SetShipWarningInfo(int type, bool warning);
    void ResetReport();

public:
    bool IsSendEnter;//�Ƿ񷢹����־���
    bool IsSendLeave;//�Ƿ񷢹��뿪����
    bool IsSendApproach;//�ӽ�
    bool IsSendHighSpeed;//����
    bool IsSendLowSpeed;//����
    bool IsSendAddMax;//����
    bool IsSendAddMin;//����
    bool IsProhibited;//��ê
    bool IsAnchorage;//��ê
    bool IsSendGround;//��ǳ
    bool IsSendCourse;//����ͻ��
    bool IsSendFog;

    time_t EnterTime;//��������ʱ��
    time_t LeaveTime;//�뿪����ʱ��
    time_t GroundTime;//��ǳ��ʼʱ��
    time_t CourseTime;//����ͻ�俪ʼʱ��
    bool IsInside;//�Ƿ����ڲ�
    int Position;//��ǰλ�� 1����״�ڲ�2����״�ⲿ //VtsShipInfoPosType
    double LastSOG;//�ϴ��ٶ�
    double LastTime;//�ϴ�ʱ��
    time_t HighTime;//���ٿ�ʼʱ��
    time_t LowTime;//���ٿ�ʼʱ��
    time_t AddMaxTime;//���ٿ�ʼʱ��
    time_t AddMinTime;//���ٿ�ʼʱ��
    time_t FogTime;//������ʼʱ��
    ///������
    bool IsSendReport;//����������
    double LastLat;
    double LastLon;

    //target������Ϣ���ͱ�־

    bool m_bIsAnchorArea; //��ê������
    bool m_bIsClubbing;  //��ê����
    bool m_bIsDragging;  //��ê����
    bool m_bIsAnchorReserv; //Ԥ����ê�ؾ���
    bool m_bIsBerthWatch; //�����ڲ�λ�ľ���
    //bool m_bIsCollisionWatch; //��ײ����
    QStringList  m_listCollision;
    bool m_bIsDomainWatch;     //�������򱨾�
    QMap<double,hgTarget> m_mapDomainWatch;//�������򱨾�
    QStringList m_listDomainCancel; //ȡ���������򱨾�
    bool m_bIsGroundWatch;     //��ǳ����
    bool m_bIsChannel;         //����

    bool m_bIsReportArea;   //��������ƫ�뱨��
    bool m_bIsReportTime;   //����������ʱ�䱨��
    bool m_bIsEarlist;
    bool m_bIsLatest;
    bool m_bIsMinSpeed;           //��С�ٶ�
    bool m_bIsMaxSpeed;           //����ٶ�
    bool m_bIsTurnCircle;  //ת��ʱ��ļ��  
    bool m_bIsMovementEnd;  //���������ƶ�
};

#endif //HG_DATAMANAGER_H_