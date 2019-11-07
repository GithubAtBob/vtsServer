#ifndef HG_SYSCONFIG_H_
#define HG_SYSCONFIG_H_

#include "Config/hgConfigBase.h"
#include "hgutils/PolygonLL.h"

enum ModeType
{
    OFF = 0,
    ON = 1,
};

class hgSysConfig : public hgConfigBase
{
public:
	hgSysConfig(const QString& path, QSettings::Format format = QSettings::IniFormat, QObject* parent = NULL);
	~hgSysConfig(void);

public:
    void ReadSysConfig();
    void ReadAreaLL();
	void WriteSysConfig();
    void ModeInfo();
public:
    QString m_databaseType;
    QString m_databaseName;
    QString m_hostName;
    QString m_username;
    QString m_password;
    int m_maxConnectionCount;
    int m_maxWaitTime;
    int m_waitInterval;
    int m_testOnBorrow;
    QString m_testOnBorrowSql;
    int m_testTime;
    int m_Threads;
    QString m_IP;
    QString m_Port;
    double m_dayCPA;
    double m_dayTCPA;
    double m_nightCPA;
    double m_nightTCPA;
    double m_customCPA;
    double m_customTCPA;
    int m_AISMaxTime;
    int m_iCellularMode;
    QString m_strCellularName;
    hg::utils::PolygonLL m_AreaLL;     //不发送警报区域
    int m_iLostTime;  //丢失时间
    int m_iDeleteTime; //删除时间
    int m_iRadarLost;
    int m_iRadarDelete;

    int m_iclassASmall;  //a,b类报告时间
    int m_iclassAMedium;
    int m_iclassABig;
    int m_iclassBLowest;
    int m_iclassBSmall;
    int m_iclassBMedium;
    int m_iclassBBig;

    int m_iTrackPredict; //是否开启轨迹预测
    double m_dShipLength; //船大小设置
    double m_dShipWidth;

    int m_OpenWarning;//是否开启警报

    int m_SaveFile;
    time_t m_filename;//文件名savefile为1时创建图片文件夹


    int m_transpondMode;  // ais数据
    int m_aisServer;  // ais数据
    QString m_comName;
    int m_comBaud;
    int m_netMode;   //网络模式，
    int m_comMode; //串口模式
    QString m_RadarAisIP;
    int m_RadarAisPort;


    int m_radarServer; //雷达数据

    int m_GPSOpen;

    int m_radarStatic;//是否处理雷达发来的静态数据
    int m_FuseType;//融合模式 1 雷达的融合 2自己的融合
	int m_useRadarAis;

    double m_FuseHdg;
    double m_FuseSog;
    double m_FuseDis;
    int m_FuseCount;
    int m_FuseDisS;
    int m_FuseSogS;
    int m_FuseCogS;

    double m_Yellow1Lat;
    double m_Yellow1Lon;
    double m_Yellow2Lat;
    double m_Yellow2Lon;
    double m_Yellow3Lat;
    double m_Yellow3Lon;
    double m_112_1Lat;
    double m_112_1Lon;
    double m_lightLat;
    double m_lightLon;
    double m_FixedDist;
    double m_FixedSOG;

	int m_backSec;

	int m_OwnSHipNum;
	QVector <QString> m_OwnShipMap;
};

#endif //HG_SYSCONFIG_H_