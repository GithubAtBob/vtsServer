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
    hg::utils::PolygonLL m_AreaLL;     //�����;�������
    int m_iLostTime;  //��ʧʱ��
    int m_iDeleteTime; //ɾ��ʱ��
    int m_iRadarLost;
    int m_iRadarDelete;

    int m_iclassASmall;  //a,b�౨��ʱ��
    int m_iclassAMedium;
    int m_iclassABig;
    int m_iclassBLowest;
    int m_iclassBSmall;
    int m_iclassBMedium;
    int m_iclassBBig;

    int m_iTrackPredict; //�Ƿ����켣Ԥ��
    double m_dShipLength; //����С����
    double m_dShipWidth;

    int m_OpenWarning;//�Ƿ�������

    int m_SaveFile;
    time_t m_filename;//�ļ���savefileΪ1ʱ����ͼƬ�ļ���


    int m_transpondMode;  // ais����
    int m_aisServer;  // ais����
    QString m_comName;
    int m_comBaud;
    int m_netMode;   //����ģʽ��
    int m_comMode; //����ģʽ
    QString m_RadarAisIP;
    int m_RadarAisPort;


    int m_radarServer; //�״�����

    int m_GPSOpen;

    int m_radarStatic;//�Ƿ����״﷢���ľ�̬����
    int m_FuseType;//�ں�ģʽ 1 �״���ں� 2�Լ����ں�
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