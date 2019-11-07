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

#define HOURTOSEC 3600.0 //Сʱ->��
#define HOURTOMIN 60 //Сʱ->��
#define ORIGIN_LAT 24.4777449
#define ORIGIN_LON 118.0575033
#define TKS_TO_MS (1852.0/3600)
#define ANGLE_TO_RADIAN (3.1415926535897/180.0)    //�Ƕ�-������
#define DISTANCE 200.0 //����50��
#define DIF_SOG 2.0 //�ٶȲ�2kts
#define DIF_COG 30.0 //�����

enum
{
    Stop = 1,
    Start = 2,
};

enum
{
    AIS_DATA = 0, //��Դ��ais�������
    RADAR_AIS_DATA, //��Դ���״��ais����
    RADAR_RADAR_DATA, //��Դ���״���״�����
    FUSE_DATA,//��Դ���ں�����
    AIS_FUSE, //�ں�Դֻ��ais
    RADAR_FUSE, //�ں���Դֻ��radar
    AIS_RADAR_FUSE, //�ں���Դais���״�
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
    QString MMSI;         //idӦ��MMSI��
    QString RadarID;
    QString RadarGUID;    //�״�GUID
    int DisCount;            //����ƥ��ɹ�����
    int current;          //��ǰƥ��λ��
    int DisSucc[50];      //ÿ��ƥ����
    double AvCog;         //�����ֵ��ֵ
    int SogCount;         //�ٶ�ƥ��ɹ�������
    int SogSucc[50];      //�ٶ�ƥ����
    int CogCount;         //����ƥ��ɹ�������
    int CogSucc[50];      //�ٶ�ƥ����
};

struct hgTarget{

    QString                   ID;
    QString                   MMSI;			// �û�ID
    QString                   RadarID;      //�״�ID
    QString                   RadarGUID;      //�״�GUID
    int                       Source;       //��Դ
    int                       Result;       //�ںϽ��

    int                       Reserved;     //2���ֽڣ������ARPA����AIS���ݰ����ֽ��Ǳ���ʹ�ã�reserved��������Ǳ�����Ϣ�����ֽ�Ϊ����HDG��������Ϣ 
    int                       Rng;          //�ز�����У׼���ֱ���1m����������Ŀ��ͺ�ͼ�ı���ƥ�� 
    double                    RadarBrg;     //2���ֽڣ��ز���λУ׼���ֱ���0.0878�ȣ�360��/4096������������Ŀ��ͺ�ͼ�ķ�λƥ�� 
    double                    Spd;          //2���ֽڣ�Ŀ������ٶȣ��ֱ���0.1 kn��0xffffΪ������Ϣ���������Ŀ��ձ�������Ϣ��û�������
    double                    Crs;          //2���ֽڣ�Ŀ����Ժ��򣬷ֱ���0.1�ȣ�0xffffΪ������Ϣ�� 
    int                       Scans;        //2���ֽڣ�Ŀ�����ʱ�䣬��λΪ����ת�� 
    int                       Flags;        //2���ֽڣ�Ŀ�����״̬����- b1:1=�Զ�����ģ�0=�ֶ�����ģ�b3��1=ʧ�ٵ�Ŀ�꣬0=�������ٵġ�

    //unsigned short int sog;      //2���ֽڣ�Ŀ���ٶȶԵأ��ֱ���0.1 kn��0xffffΪ������Ϣ�� 
    //unsigned short int cog;      //2���ֽڣ�Ŀ�꺽�����򣩶Ա����ֱ���0.1�ȣ�0xffffΪ������Ϣ�� 
    //int longitude;               //4���ֽڣ� ���ȣ� �ֱ���1/600000�ȣ�1/10000�� 
    //int latitude;                //4���ֽڣ� γ�ȣ��ֱ���1/600000�ȣ�1/10000�� 

    //��̬����
    int                       MID;			// ����ID
    QString                   ShipName;	// ����
    QString                   ChShipName;
    QString                   CallSign;	// ����             // includes terminator
    hgAisClass                Class;		// ת��ָʾ��
    int                       IMO;			// IMO����
    QString                   ShipType;		// �������������
    int	                      EquipmentType;	//��λ�豸����
    int                       DimA;
    int                       DimB;
    int                       DimC;
    int                       DimD;
    double                    Length;
    double                    Width;
    bool                      SetShipSize;   //���ô��Ļ�������
    QString                   Destination;	// Ŀ�ĵ�
    int                       ETA_Mo;		// ETA
    int                       ETA_Day;
    int                       ETA_Hr;
    int                       ETA_Min;
    double                    Draft;		// ��ǰ���̬��ˮ
    bool                      Simulation;   //ģ�����

    QString                   Note;  //ע��
    QString                   Nationality;//����
    //��̬����
    int                       NavStatus;	// ����״̬
    double                    Lon;			// ����
    double                    Lat;			// γ��
    double                    COG;			// ʵ�ʺ���COG
    double                    SOG;			// ʵ�ʺ���SOG      ��/Сʱ
    double                    HDG;			// ������
    int                       ROTAIS;       // ��������ROT
    time_t                    ReportTicks;  //����ʱ��
    int                       ReportPeriod; //��������          s
    int                       ReportInterval;//����ʱ����
    int	                      PosAccuracy;	//λ�þ�ȷ��



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

    bool                      RadarMissing;  //�״��Ƿ�ʧ

    int                       RadarInterval;  //�����״��ʱ����

    //hgSplineInterpolation     Prediction; //ais�켣Ԥ��

};



typedef struct 
{ 
    unsigned short int number;   //2���ֽڣ�����Ŀ��ı��0x0000��0x0800, 0xffff-��վ��Ϣ 
    unsigned short int reserved; //2���ֽڣ������ARPA����AIS���ݰ����ֽ��Ǳ���ʹ�ã�reserved��������Ǳ�����Ϣ�����ֽ�Ϊ����HDG��������Ϣ 
    unsigned short int rng;      //2���ֽڣ��ز�����У׼���ֱ���1m����������Ŀ��ͺ�ͼ�ı���ƥ��  
	unsigned short int brg;      //2���ֽڣ��ز���λУ׼���ֱ���0.0878�ȣ�360��/4096������������Ŀ��ͺ�ͼ�ķ�λƥ�� 
	unsigned int orientation_size;//4���ֽڣ�Ŀ��ĳ߶Ⱥʹ�����angle������L�����W������angle���ֱ���0.1�ȣ�pack.orientation_size = angle|(L<<12)|(W<<22);��ע����Ϊ����������ͺ��з��򾭳���һ�£��ر����ֶɴ��ģ����Կͻ��˿���ѡ����ʾ����ʸ����
	// 	unsigned short int spd;      //2���ֽڣ�Ŀ������ٶȣ��ֱ���0.1 kn��0xffffΪ������Ϣ���������Ŀ��ձ�������Ϣ��û������� 
	// 	unsigned short int crs;      //2���ֽڣ�Ŀ����Ժ��򣬷ֱ���0.1�ȣ�0xffffΪ������Ϣ�� 
    unsigned short int sog;      //2���ֽڣ�Ŀ���ٶȶԵأ��ֱ���0.1 kn��0xffffΪ������Ϣ�� 
    unsigned short int cog;      //2���ֽڣ�Ŀ�꺽�����򣩶Ա����ֱ���0.1�ȣ�0xffffΪ������Ϣ�� 
    unsigned int scans;          //2���ֽڣ�Ŀ�����ʱ�䣬��λΪ����ת�� 
    unsigned int flags;          //2���ֽڣ�Ŀ�����״̬����- b1:1=�Զ�����ģ�0=�ֶ�����ģ�b3��1=ʧ�ٵ�Ŀ�꣬0=�������ٵġ� 
    int longitude;               //4���ֽڣ� ���ȣ� �ֱ���1/600000�ȣ�1/10000�� 
    int latitude;                //4���ֽڣ� γ�ȣ��ֱ���1/600000�ȣ�1/10000�� 
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
    static void Assembly(hgTarget &ais,hgSqlOperator& sqlOperator);//�ںϼ��

	//�״��ں�ʱ��   GPS��Ӧ���״����
	static void AssemGPSRadar(hgTarget &ais);
	static bool SameObjectGPSRadar(hgTarget ais,hgTarget radar);


    static void SameObject(hgTarget ais,hgTarget radar,double &dist,bool &bDist,bool &bAngle,bool &bSOG/*double &dist,double &angle,double &SOG*/);
    static bool SameObjectD(hgTarget ais,hgTarget radar,double &dist,double &angle,double &SOG);
    static bool ChangeAIS(hgTarget newAis,hgTarget oldAis);//�ж�2��AIS�Ƿ���ͬһ����Ϣtrue �ı� false û�ı�
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

    static void ChangeAisToShip(hgAisMessage ais, hgShipAisMessage &shipais, int hdgtype = 0);//����Ϣת��Ϊ���˽��յ�����

    //���ݿ����
    static void SaveAis(hgSqlOperator& sqlOperator, hgAisMessage ais);
    static void ReadStaticAis(hgSqlOperator& sqlOperator);
    static void ReadLloydAis(hgSqlOperator& sqlOperator);
    static void AddStaticAis(hgSqlOperator& sqlOperator, hgAisMessage ais);
    static void AddDynamicAis(hgSqlOperator& sqlOperator, hgAisMessage ais);
    static void UpdateStaticAis(hgSqlOperator& sqlOperator, hgAisMessage ais);
    static void AddFuaeResult(hgSqlOperator& sqlOperator, hgResult result, bool fuse, int time);

    //static CPlaneProjection m_CPlaneProjection;

public:

    static mymap<QString,hgTarget> m_mapTarget; //��

    static mymap<QString,hgTarget> m_mapAis;  //aisĿ��

    static mymap<QString,hgTarget> m_mapRadar;  //�״��б�

    static QStringList m_RadarList;//�״�ͬһʱ�̷����Ĵ�

    static QMap<QString,QString> m_mapAisRadar;  //AIS  ��Ӧ �״���10000+ ��¼�״���ID 

    static QMap<QString,QString> m_mapRadarAis;  //�״���1+  ��ӦMMSI   ��¼���ںϵ�MMSI,û���ں�Ϊ0  ��Ҫ�ж��Ƿ��ں�

    static QStringList m_AlgorOwnMMSI;//Ԥ������ı���

	static QStringList m_GPSMMSI;//GPS�յ��ı����б�

	static QStringList m_GPSMMSIPos;//GPS�յ��ı����б� λ��

	static QStringList m_GPSMMSIHdg;//GPS�յ��ı����б� HDG

	static QMap<QString, int> m_GPSHdg;//gps ����Ӧ�ķ�λ

    static QStringList m_OwnMMSI;

    static QMap<QString,hgTarget> m_mapStatic; //��̬����  �û����õ� target_static_table �������

    static QMap<QString,hgTarget> m_mapShipData; //csv�ļ�ais���ݣ�¼�뵽 lloyd_table ������ݣ�

    static QMap<QString,hgResult> m_mapResult;  //�ںϽ��

    static QMap<QString,hgTarget> m_mapRadarDel; 

    static QMap<QString,hgTarget> m_mapRadarStatic;

	//�״��ں�ʱ��   GPS��Ӧ���״����
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