#include "StdAfx.h"
#include "LayerData/hgShipWarningInfo.h"

hgShipWarningInfo::hgShipWarningInfo(void)
    :EnterTime(-1),LeaveTime(-1),IsInside(false),IsSendEnter(false),IsSendLeave(false)
    ,IsSendApproach(false),Position(ShipOutSidePos),LastSOG(-1),HighTime(-1),LowTime(-1)
    ,IsSendHighSpeed(false),IsSendLowSpeed(false),AddMaxTime(-1),AddMinTime(-1)
    ,IsSendAddMax(false),IsSendAddMin(false),IsProhibited(false),IsAnchorage(false)
    ,IsSendGround(false),GroundTime(-1),CourseTime(-1),IsSendCourse(false),LastTime(-1)
    ,IsSendFog(false),FogTime(-1)
{
    ResetReport();
}

hgShipWarningInfo::~hgShipWarningInfo(void)
{

}

void hgShipWarningInfo::ResetOutside()
{
    LeaveTime = -1;
    IsInside = true;
    IsSendLeave = false;
    IsSendApproach = false;
}

void hgShipWarningInfo::ResetInside()
{
    IsInside = false;
    IsSendEnter = false;
    IsSendHighSpeed = false;
    IsSendLowSpeed = false;
    IsSendAddMax = false;
    IsSendAddMin = false;
    IsProhibited = false;
    IsAnchorage = false;
    IsSendGround = false;
    IsSendCourse = false;
    EnterTime = -1;
    HighTime = -1;
    LowTime = -1;
    AddMaxTime = -1;
    AddMinTime = -1;
    GroundTime = -1;
    CourseTime = -1;
    IsSendFog = false;
    FogTime = -1;
}

void hgShipWarningInfo::ResetReport()
{
    IsSendReport = false;
    LastLat = -1;
    LastLon = -1;
}

void hgShipWarningInfo::InitShipWarningInfo()
{
    m_bIsAnchorArea = false; //��ê������
    m_bIsClubbing = false;  //��ê����
    m_bIsDragging = false;  //��ê����
    m_bIsAnchorReserv = false; //Ԥ����ê�ؾ���
    m_bIsBerthWatch = false; //�����ڲ�λ�ľ���
    //bool m_bIsCollisionWatch; //��ײ����
    m_bIsDomainWatch = false;     //�������򱨾�
    m_bIsGroundWatch = false;     //��ǳ����
    m_bIsChannel = false;        //����

    m_bIsReportArea = false;   //�������򱨾�......
    m_bIsEarlist = false;
    m_bIsLatest = false;
    m_bIsMinSpeed = false;          //��С�ٶ�
    m_bIsMaxSpeed = false;          //����ٶ�
    m_bIsTurnCircle = false;   //ת��ʱ��ļ��  
    m_bIsMovementEnd = false;  //���������ƶ�
}

void hgShipWarningInfo::SetShipWarningInfo(int type, bool warning)
{
    switch (type)
    {
    case IsAnchorArea:
        m_bIsAnchorArea = warning;
        break;
    case IsClubbing:
        m_bIsClubbing = warning;
        break;
    case IsDragging:
        m_bIsDragging = warning;
        break;
    case IsAnchorReserv:
        m_bIsAnchorReserv = warning;
        break;
    case IsBerthWatch:
        m_bIsBerthWatch = warning;
        break;
    case IsDomainWatch:
        m_bIsDomainWatch = warning;
        break;
    case IsGroundWatch:
        m_bIsGroundWatch = warning;
        break;
    case IsChannel:
        m_bIsChannel = warning;
        break;
    case IsReportArea:
        m_bIsReportArea = warning;
        break;
    case IsReportTime:
        m_bIsReportTime = warning;
        break;
    case IsEarlist:
        m_bIsEarlist = warning;
        break;
    case IsLatest:
        m_bIsLatest = warning;
        break;
    case IsMinSpeed:
        m_bIsMinSpeed = warning;
        break;
    case IsMaxSpeed:
        m_bIsMaxSpeed = warning;
        break;
    case IsTurnCircle:
        m_bIsTurnCircle = warning;
        break;
    case IsMovementEnd:
        m_bIsMovementEnd = warning;
        break;
    case OtherType:
        break;
    }
}
