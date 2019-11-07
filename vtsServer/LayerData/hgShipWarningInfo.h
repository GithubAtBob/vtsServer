#ifndef HG_SHIPWARNINGINFO_H_
#define HG_SHIPWARNINGINFO_H_
#include "Managers/hgTargetManager.h"

enum hgShipInfoPosType{
    ShipInsidePos = 1,
    ShipOutSidePos
};

enum hgShipWarningType{
    IsAnchorArea = 1,  //抛锚区警报
    IsClubbing, //拖锚警报
    IsDragging, //拖锚警报
    IsAnchorReserv,//预留的锚地警报
    IsBerthWatch,//船舶在泊位的警报
    //bool m_bIsCollisionWatch,//碰撞警报
    IsDomainWatch,    //船舶领域报警
    IsGroundWatch,    //搁浅报警
    IsChannel,        //航道
    IsReportArea,  //报告区域报警......
    IsReportTime,
    IsEarlist,
    IsLatest,
    IsMinSpeed,          //最小速度
    IsMaxSpeed,          //最大速度
    IsTurnCircle, //转向时候的监控  
    IsMovementEnd, //船舶不在移动
    OtherType,
};

class hgShipWarningInfo//船舶标志位类
{
public:
	hgShipWarningInfo(void);
    ~hgShipWarningInfo(void);
    void ResetOutside();//重置在区域外参数（当进入区域时）
    void ResetInside();//重置在区域内参数（当离开区域时）
    void InitShipWarningInfo();
    void SetShipWarningInfo(int type, bool warning);
    void ResetReport();

public:
    bool IsSendEnter;//是否发过入侵警报
    bool IsSendLeave;//是否发过离开警报
    bool IsSendApproach;//接近
    bool IsSendHighSpeed;//高速
    bool IsSendLowSpeed;//低速
    bool IsSendAddMax;//加速
    bool IsSendAddMin;//减速
    bool IsProhibited;//禁锚
    bool IsAnchorage;//抛锚
    bool IsSendGround;//搁浅
    bool IsSendCourse;//航向突变
    bool IsSendFog;

    time_t EnterTime;//进入区域时刻
    time_t LeaveTime;//离开区域时刻
    time_t GroundTime;//搁浅开始时刻
    time_t CourseTime;//航向突变开始时刻
    bool IsInside;//是否在内部
    int Position;//当前位置 1在形状内部2在形状外部 //VtsShipInfoPosType
    double LastSOG;//上次速度
    double LastTime;//上次时间
    time_t HighTime;//高速开始时刻
    time_t LowTime;//低速开始时刻
    time_t AddMaxTime;//加速开始时刻
    time_t AddMinTime;//减速开始时刻
    time_t FogTime;//雾航区域开始时刻
    ///报告线
    bool IsSendReport;//穿过报警线
    double LastLat;
    double LastLon;

    //target警告信息发送标志

    bool m_bIsAnchorArea; //抛锚区警报
    bool m_bIsClubbing;  //拖锚警报
    bool m_bIsDragging;  //走锚警报
    bool m_bIsAnchorReserv; //预留的锚地警报
    bool m_bIsBerthWatch; //船舶在泊位的警报
    //bool m_bIsCollisionWatch; //碰撞警报
    QStringList  m_listCollision;
    bool m_bIsDomainWatch;     //船舶领域报警
    QMap<double,hgTarget> m_mapDomainWatch;//船舶领域报警
    QStringList m_listDomainCancel; //取消船舶领域报警
    bool m_bIsGroundWatch;     //搁浅报警
    bool m_bIsChannel;         //航道

    bool m_bIsReportArea;   //报告区域偏离报警
    bool m_bIsReportTime;   //报告区到达时间报警
    bool m_bIsEarlist;
    bool m_bIsLatest;
    bool m_bIsMinSpeed;           //最小速度
    bool m_bIsMaxSpeed;           //最大速度
    bool m_bIsTurnCircle;  //转向时候的监控  
    bool m_bIsMovementEnd;  //船舶不在移动
};

#endif //HG_DATAMANAGER_H_