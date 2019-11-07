#ifndef HG_TARGETMANAGER_H_
#define HG_TARGETMANAGER_H_

#include <QString>
#include <QMap>
#include <QObject>
#include <QVector>
#include <QMutex>
#include <QSharedPointer>
#include "hgAisDecoder.h"
#include "hgutils/PointLL.h"
#include <stdio.h>
#include <time.h>
#include <string>
#include "message/hgAisMessage.pb.h"
#include "hgSqlOperator.h"
#include "AisReckoning/hgAisDeadReckoning.h"
#include "message/RadarImagePack.pb.h"
#include "message/hgShipAisMessage.pb.h"
#include "hgMyMap.h"
//#include "AisReckoning/hgSplineInterpolation.h"
//#include "AisAnalysis/hgPlaneProjection.h"

#define HOURTOSEC 3600.0 //小时->秒
#define HOURTOMIN 60 //小时->分
#define ORIGIN_LAT 24.4777449
#define ORIGIN_LON 118.0575033
#define TKS_TO_MS (1852.0/3600)
#define ANGLE_TO_RADIAN (3.1415926535897/180.0)    //角度-》弧度
#define DISTANCE 200.0 //距离50米
#define DIF_SOG 2.0 //速度差2kts
#define DIF_COG 30.0 //方向差

enum
{
    Stop = 1,
    Start = 2,
};

enum
{
    AIS_DATA = 0, //来源于ais真机数据
    RADAR_AIS_DATA, //来源于雷达的ais数据
    RADAR_RADAR_DATA, //来源于雷达的雷达数据
    FUSE_DATA,//来源于融合数据
    AIS_FUSE, //融合源只有ais
    RADAR_FUSE, //融合来源只有radar
    AIS_RADAR_FUSE, //融合来源ais和雷达
};

enum
{
    COM_SPEED = 2,
    COM_COG = 10,
    COM_DISTANCE = 1000,
};

template <class T>
class MapLocker
{
public:
    MapLocker(T& t, QMutex& m)
        :_t(t), _m(m)
    {
        //vtsInfo << GetCurrentThreadId() << " lock";
        _m.lock();
    }

    ~MapLocker()
    {
        _m.unlock();
        //vtsInfo << GetCurrentThreadId() << " unlock";
    }

    T* operator->()
    {
        return &_t;
    }

    T &raw()
    {
        return _t;
    }

protected:
    T &_t;
    QMutex &_m;
};

struct hgResult
{
    QString ID;           //
    QString MMSI;         //id应的MMSI对
    QString RadarID;
    QString RadarGUID;    //雷达GUID
    int DisCount;            //距离匹配成功次数
    int current;          //当前匹配位置
    int DisSucc[50];      //每次匹配存放
    double AvCog;         //航向差值均值
    int SogCount;         //速度匹配成功次数比
    int SogSucc[50];      //速度匹配存放
    int CogCount;         //航向匹配成功次数比
    int CogSucc[50];      //速度匹配存放
};

struct hgTarget{

    QString                   ID;
    QString                   MMSI;			// 用户ID
    QString                   RadarID;      //雷达ID
    QString                   RadarGUID;      //雷达GUID
    int                       Source;       //来源
    int                       Result;       //融合结果

    int                       Reserved;     //2个字节：如果是ARPA或者AIS数据包此字节是保留使用（reserved），如果是本船信息，此字节为本船HDG（艏向）信息 
    int                       Rng;          //回波距离校准，分辨率1m，用来调整目标和海图的比例匹配 
    double                    RadarBrg;     //2个字节：回波方位校准，分辨率0.0878度（360度/4096），用来调整目标和海图的方位匹配 
    double                    Spd;          //2个字节：目标相对速度，分辨率0.1 kn，0xffff为“无信息“（像如果目标刚被捕获，信息还没算出来）
    double                    Crs;          //2个字节：目标相对航向，分辨率0.1度，0xffff为“无信息“ 
    int                       Scans;        //2个字节：目标跟踪时间，单位为天线转数 
    int                       Flags;        //2个字节：目标跟踪状态比特- b1:1=自动捕获的，0=手动捕获的，b3：1=失踪的目标，0=正常跟踪的。

    //unsigned short int sog;      //2个字节：目标速度对地，分辨率0.1 kn，0xffff为“无信息“ 
    //unsigned short int cog;      //2个字节：目标航向（轴向）对北，分辨率0.1度，0xffff为“无信息“ 
    //int longitude;               //4个字节： 经度， 分辨率1/600000度，1/10000分 
    //int latitude;                //4个字节： 纬度，分辨率1/600000度，1/10000分 

    //静态数据
    int                       MID;			// 电文ID
    QString                   ShipName;	// 船名
    QString                   ChShipName;
    QString                   CallSign;	// 呼号             // includes terminator
    hgAisClass                Class;		// 转发指示器
    int                       IMO;			// IMO号码
    QString                   ShipType;		// 船型与货物种类
    int	                      EquipmentType;	//定位设备类型
    int                       DimA;
    int                       DimB;
    int                       DimC;
    int                       DimD;
    double                    Length;
    double                    Width;
    bool                      SetShipSize;   //设置船的基础长宽
    QString                   Destination;	// 目的地
    int                       ETA_Mo;		// ETA
    int                       ETA_Day;
    int                       ETA_Hr;
    int                       ETA_Min;
    double                    Draft;		// 当前最大静态吃水
    bool                      Simulation;   //模拟物标

    QString                   Note;  //注释
    QString                   Nationality;//国籍
    //动态数据
    int                       NavStatus;	// 航行状态
    double                    Lon;			// 经度
    double                    Lat;			// 纬度
    double                    COG;			// 实际航向COG
    double                    SOG;			// 实际航速SOG      节/小时
    double                    HDG;			// 真艏向
    int                       ROTAIS;       // 旋回速率ROT
    time_t                    ReportTicks;  //报告时间
    int                       ReportPeriod; //报告周期          s
    int                       ReportInterval;//报告时间间隔
    int	                      PosAccuracy;	//位置精确度



    int                       utc_hour;
    int                       utc_min;
    int                       utc_sec;

    double                    Range_NM;
    double                    Brg;
    int                       SyncState;
    int                       SlotTO;

    bool                      CPA_Valid;
    double                    TCPA;                     // Minutes
    double                    CPA;                      // Nautical Miles

    bool                      Missing;

    bool                      DomainWatch;


    bool                      OwnShip;

    bool                      RadarMissing;  //雷达是否丢失

    int                       RadarInterval;  //接收雷达的时间间隔

    //hgSplineInterpolation     Prediction; //ais轨迹预测

};



typedef struct 
{ 
    unsigned short int number;   //2个字节：跟踪目标的编号0x0000至0x0800, 0xffff-本站信息 
    unsigned short int reserved; //2个字节：如果是ARPA或者AIS数据包此字节是保留使用（reserved），如果是本船信息，此字节为本船HDG（艏向）信息 
    unsigned short int rng;      //2个字节：回波距离校准，分辨率1m，用来调整目标和海图的比例匹配  
	unsigned short int brg;      //2个字节：回波方位校准，分辨率0.0878度（360度/4096），用来调整目标和海图的方位匹配 
	unsigned int orientation_size;//4个字节：目标的尺度和船轴向angle，长度L，宽度W，轴向angle，分辨率0.1度：pack.orientation_size = angle|(L<<12)|(W<<22);备注：因为船舶的轴向和航行方向经常不一致，特别是轮渡船的，所以客户端可以选择显示两种矢量。
	// 	unsigned short int spd;      //2个字节：目标相对速度，分辨率0.1 kn，0xffff为“无信息“（像如果目标刚被捕获，信息还没算出来） 
	// 	unsigned short int crs;      //2个字节：目标相对航向，分辨率0.1度，0xffff为“无信息“ 
    unsigned short int sog;      //2个字节：目标速度对地，分辨率0.1 kn，0xffff为“无信息“ 
    unsigned short int cog;      //2个字节：目标航向（轴向）对北，分辨率0.1度，0xffff为“无信息“ 
    unsigned int scans;          //2个字节：目标跟踪时间，单位为天线转数 
    unsigned int flags;          //2个字节：目标跟踪状态比特- b1:1=自动捕获的，0=手动捕获的，b3：1=失踪的目标，0=正常跟踪的。 
    int longitude;               //4个字节： 经度， 分辨率1/600000度，1/10000分 
    int latitude;                //4个字节： 纬度，分辨率1/600000度，1/10000分 
}ARPA_TARGET_PACKET; 


class hgTargetManager : public QObject
{
    Q_OBJECT
public:
    hgTargetManager(void);
    virtual ~hgTargetManager(void);
    typedef MapLocker< QMap< QString, hgTarget > > __MapLocker;
    typedef QSharedPointer< __MapLocker > MyMapLocker;

    static void AssemblyTarget(hgAisData &aisData,hgTarget &ais,hgSqlOperator& sqlOperator);
    static void Assembly(hgTarget &ais,hgSqlOperator& sqlOperator);//融合检测

	//雷达融合时，   GPS对应的雷达物标
	static void AssemGPSRadar(hgTarget &ais);
	static bool SameObjectGPSRadar(hgTarget ais,hgTarget radar);


    static void SameObject(hgTarget ais,hgTarget radar,double &dist,bool &bDist,bool &bAngle,bool &bSOG/*double &dist,double &angle,double &SOG*/);
    static bool SameObjectD(hgTarget ais,hgTarget radar,double &dist,double &angle,double &SOG);
    static bool ChangeAIS(hgTarget newAis,hgTarget oldAis);//判断2次AIS是否是同一条消息true 改变 false 没改变
    //static void AssemblyTargetGPS(hgTarget &ais,hgSqlOperator& sqlOperator);
    static void AddRadarData(ArpaTargetPack &msg,hgTarget &target);
    static void AddRadarAISData(ArpaTargetPack &msg,hgTarget &target);
    static void InitRadarData(ArpaTargetPack &msg,hgTarget &target);
    static void InitRadarAISData(ArpaTargetPack &msg,hgTarget &target);
    static void UpdateRadarData(ArpaTargetPack &msg,hgTarget &target);
    //static void UpdateRadarAISData(ArpaTargetPack &msg,hgTarget &target);
    static void FindRadarGUID(ArpaTargetPack &msg, hgTarget& target);
    static void AddTarget(hgAisMessage &ais);
    static void AddTarget(hgTarget &ais);
    static void AddAis(hgAisMessage ais);
    static void AddSim(hgAisMessage ais);

    static void DeleteAll();
    static void DeleteSim();
    static void DeleteLost();
    static void SetPlayBack(int time);

    static void ChangeAisToShip(hgAisMessage ais, hgShipAisMessage &shipais, int hdgtype = 0);//将信息转化为船端接收的数据

    //数据库操作
    static void SaveAis(hgSqlOperator& sqlOperator, hgAisMessage ais);
    static void ReadStaticAis(hgSqlOperator& sqlOperator);
    static void ReadLloydAis(hgSqlOperator& sqlOperator);
    static void AddStaticAis(hgSqlOperator& sqlOperator, hgAisMessage ais);
    static void AddDynamicAis(hgSqlOperator& sqlOperator, hgAisMessage ais);
    static void UpdateStaticAis(hgSqlOperator& sqlOperator, hgAisMessage ais);
    static void AddFuaeResult(hgSqlOperator& sqlOperator, hgResult result, bool fuse, int time);

    //static CPlaneProjection m_CPlaneProjection;

public:

    static mymap<QString,hgTarget> m_mapTarget; //总

    static mymap<QString,hgTarget> m_mapAis;  //ais目标

    static mymap<QString,hgTarget> m_mapRadar;  //雷达列表

    static QStringList m_RadarList;//雷达同一时刻发来的船

    static QMap<QString,QString> m_mapAisRadar;  //AIS  对应 雷达编号10000+ 记录雷达标记ID 

    static QMap<QString,QString> m_mapRadarAis;  //雷达编号1+  对应MMSI   记录所融合的MMSI,没有融合为0  主要判断是否融合

    static QStringList m_AlgorOwnMMSI;//预警处理的本船

	static QStringList m_GPSMMSI;//GPS收到的本船列表

	static QStringList m_GPSMMSIPos;//GPS收到的本船列表 位置

	static QStringList m_GPSMMSIHdg;//GPS收到的本船列表 HDG

	static QMap<QString, int> m_GPSHdg;//gps 船对应的方位

    static QStringList m_OwnMMSI;

    static QMap<QString,hgTarget> m_mapStatic; //静态数据  用户设置到 target_static_table 表的数据

    static QMap<QString,hgTarget> m_mapShipData; //csv文件ais数据（录入到 lloyd_table 表的数据）

    static QMap<QString,hgResult> m_mapResult;  //融合结果

    static QMap<QString,hgTarget> m_mapRadarDel; 

    static QMap<QString,hgTarget> m_mapRadarStatic;

	//雷达融合时，   GPS对应的雷达物标
	static QMap<QString, QString> m_mapGpsRadar;

    /*static MyMapLocker getMapAisLocker()
    {
        MyMapLocker locker(new __MapLocker(m_mapAis, m_mutexAis) );
        return locker;
    }

    static MyMapLocker getMapTargetLocker()
    {
        MyMapLocker locker(new __MapLocker(m_mapTarget, m_mutexTarget) );
        return locker;
    }

    static MyMapLocker getMapRadarLocker()
    {
        MyMapLocker locker(new __MapLocker(m_mapRadar, m_mutexRadar) );
        return locker;
    }*/

    static void SetPredict(bool predict);

    static bool GetPredict();

    static int GetWarnTime();

    static void SetWarnTime(int time);


    static hgAisDecoder* m_AisDecoder;

    static double m_HDGDif;
    static double m_SOGDif;
    static double m_DisDif;
    static int m_FuseCount;
    static int m_DisSuccess;//
    static int m_SogSuccess;
    static int m_CogSuccess;

private:

    static bool m_bReceieAis;

    static QMutex m_mutexAis;

    static QMutex m_mutexRadar;

    static QMutex m_mutexTarget;
/*
    static int m_mutexAisCount;

    static int m_mutexRadarCount;

    static int m_mutexTargetCount;*/

    static bool m_bPredict;

    static int m_iWarnTime;

};

#endif //HG_TARGETMANAGER_H_