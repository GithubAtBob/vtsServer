#ifndef HG_WARNINGSETMANAGE_H_
#define HG_WARNINGSETMANAGE_H_

#include <QMap>
#include <QObject>
class hgShipWarningInfo;
class hgSqlOperator;

#define HOURTOMIN 60 //Сʱ->��


struct AreaData
{
    QString ID;
    int type;
};

struct Authorized 
{
    QString TargetID;
    bool Authorize;
};

struct AnchorArea 
{
    QString TargetID;
    bool b_AnchorArea;
    QString ID;
    int Type; 
};

struct Domain 
{
    QString TargetID;
    bool DomainWatch;
    double DomainRadius;
    int DomainColorR;
    int DomainColorG;		
    int DomainColorB;
    bool DomainShow; 
};

struct AnchorWatch
{
    QString TargetID;
    bool b_AnchorWatch; //êλ���
    double Clubbing;    //��ê
    double Dragging;    //��ê
    double AnchorLat;
    double AnchorLon;
};

struct AnchorReserv 
{
    QString TargetID;
    bool b_AnchorReserv;
    QString ID;
    int Type;
    long int ETA;
    long int ETD;
    int Tracks;
};

struct BerthWatch
{
    QString TargetID;
    bool b_BerthWatch; 
    double Distance;    
    double BerthLat;
    double BerthLon;
};

struct CollisionWatch
{
    QString TargetID;
    int Type;
    bool b_CollisionWatch; 
    double DCPA;   
    double TCPA; 
    double CustomDCPA;   
    double CustomTCPA; 
};

struct GroundWatch
{
    QString TargetID;
    bool b_GroundWatch; 
    double GroundDraught;   
    double KeelClearance;    
};

struct NavigatChannel
{
    QString TargetID;
    bool b_NavigatChannel;
    QString ID;
    int Type;
};

struct ReportArea
{
    QString TargetID;
    bool b_ReportArea;
    bool b_Pattern;
    QMap<QString,AreaData> mapAreaData;
    long int EarilestTime;
    long int LatestTime;
    bool enter;
};

struct SpeedWatch
{
    QString TargetID;
    bool b_SpeedWatch;
    double MinSpeed;
    double MinDuration;
    double MaxSpeed;
    double MaxDuration;
    int MinTimeKeep;
    int MaxTimeKeep;
};

struct SetShip
{
    QString TargetID; 
    bool b_SetShip;
    QString ShipType;
    double Length;
    double With;
};

struct TurnCircle
{
    QString TargetID;
    bool b_TurnCircle; 
    double TurnRadius;    
    double TurnLat;
    double TurnLon;
};


struct MovementEnd
{
    QString TargetID;
    bool b_MovementEnd; 
    long int EndTime;    
    double EndLat;
    double EndLon;
};



class hgWarningSetManager 
{
public:
    hgWarningSetManager(void);
    virtual ~hgWarningSetManager(void);

    void SetWarnInfo(QString MMSI,int type);

    
    void SaveDomain(Domain &domain);
    void SaveAuthorized(Authorized &authorized);
    void SaveAnchorArea(AnchorArea &anchor);
    void SaveAnchorWatch(AnchorWatch &anchor);
    void SaveAnchorReserv(AnchorReserv &anchor);
    void SaveBerthWatch(BerthWatch &anchor);
    void SaveCollisionWatch(CollisionWatch &anchor);
    void SaveGroundWatch(GroundWatch &anchor);
    void SaveNavigatChannel(NavigatChannel &anchor);
    void SaveReportArea(ReportArea &anchor);
    void SaveSpeedWatch(SpeedWatch &anchor);
    void SaveSetShip(SetShip &anchor);
    void SaveTurnCircle(TurnCircle &anchor);
    void SaveMovementEnd(MovementEnd &anchor);
    void SaveCollisionWarn(QString MMSI, QString RefMMSI);

    void ReadDomain(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadAuthorized(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadAnchorArea(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadAnchorWatch(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadAnchorReserv(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadBerthWatch(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadCollisionWatch(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadGroundWatch(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadNavigatChannel(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadReportArea(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadSpeedWatch(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadSetShip(hgSqlOperator& sqlOperator);
    void ReadTurnCircle(hgSqlOperator& sqlOperator, vtsServer *s);
    void ReadMovementEnd(hgSqlOperator& sqlOperator, vtsServer *s);

    void SendWarnSet(QString ID, ConnectionPtr& connect);

public:
    QMap<QString,Authorized> m_mapAuthorized;
    QMap<QString,AnchorArea> m_mapAnchorArea;
    QMap<QString,Domain> m_mapDomain;
    QMap<QString,AnchorWatch> m_mapAnchorWatch;
    QMap<QString,AnchorReserv> m_mapAnchorReserv;
    QMap<QString,BerthWatch> m_mapBerthWatch;
    QMap<QString,CollisionWatch> m_mapCollisionWatch;
    QMap<QString,GroundWatch> m_mapGroundWatch;
    QMap<QString,NavigatChannel> m_mapNavigatChannel;
    QMap<QString,ReportArea> m_mapReportArea;
    QMap<QString,SpeedWatch> m_mapSpeedWatch;
    QMap<QString,SetShip> m_mapSetShip;
    QMap<QString,TurnCircle> m_mapTurnCircle;
    QMap<QString,MovementEnd> m_mapMovementEnd;
    QMap<QString,hgShipWarningInfo> m_mapWarnInfo; //���淢�ͱ�־
    QMap<QString,QStringList> m_mapCollisionWarn;  //ȫ����ײ���
    QMap<QString,QStringList> m_mapWarnValue;  //�Ƿ��͹�������ֵ��key=channel��value=mmsi
private:


};

#endif //HG_WARNINGSETMANAGE_H_