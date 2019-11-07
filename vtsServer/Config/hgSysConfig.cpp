#include "StdAfx.h"
#include "Config/hgSysConfig.h"
#include "Managers/hgTargetManager.h"

hgSysConfig::hgSysConfig(const QString& path, QSettings::Format format /*= QSettings::IniFormat*/, QObject* parent /*= NULL*/) : hgConfigBase(path, format, parent)
{
}


hgSysConfig::~hgSysConfig(void)
{
}

void hgSysConfig::ReadSysConfig()
{
	QString str = GetPath();
	GetValue("/DBPoolConfig/databaseType", m_databaseType);
    GetValue("/DBPoolConfig/databaseName", m_databaseName);
    GetValue("/DBPoolConfig/hostName", m_hostName);
    GetValue("/DBPoolConfig/username", m_username);
    GetValue("/DBPoolConfig/password", m_password);
    GetValue("/DBPoolConfig/maxConnectionCount", m_maxConnectionCount);
    GetValue("/DBPoolConfig/maxWaitTime", m_maxWaitTime);
    GetValue("/DBPoolConfig/waitInterval", m_waitInterval);
    GetValue("/DBPoolConfig/testOnBorrow", m_testOnBorrow);
    GetValue("/DBPoolConfig/testOnBorrowSql", m_testOnBorrowSql);
    GetValue("/DBPoolConfig/testTime", m_testTime);
    GetValue("/DBPoolConfig/threads", m_Threads);
    GetValue("/NetWork/ip", m_IP);
    GetValue("/NetWork/port", m_Port);
    GetValue("/Collision/dayCPA", m_dayCPA);
    GetValue("/Collision/datTCPA", m_dayTCPA);
    GetValue("/Collision/nightCPA", m_nightCPA);
    GetValue("/Collision/nightTCPA", m_nightTCPA);
    GetValue("/Collision/customCPA", m_customCPA);
    GetValue("/Collision/customTCPA", m_customTCPA);
    GetValue("/Collision/customTCPA", m_customTCPA);
    GetValue("/Device/AISMaxWaitTime", m_AISMaxTime);
    GetValue("/ServerMode/cellularMode", m_iCellularMode);
    GetValue("/ServerMode/cellularName", m_strCellularName);

    ReadAreaLL();
    GetValue("/LostTarget/lostTime", m_iLostTime);
    GetValue("/LostTarget/deleteTime", m_iDeleteTime);
    GetValue("/LostTarget/radarLost", m_iRadarLost);
    GetValue("/LostTarget/radarDelete", m_iRadarDelete);

    GetValue("/ReportPeriod/classASmall", m_iclassASmall);
    GetValue("/ReportPeriod/classAMedium", m_iclassAMedium);
    GetValue("/ReportPeriod/classABig", m_iclassABig);
    GetValue("/ReportPeriod/classBLowest", m_iclassBLowest);
    GetValue("/ReportPeriod/classBSmall", m_iclassBSmall);
    GetValue("/ReportPeriod/classBMedium", m_iclassBMedium);
    GetValue("/ReportPeriod/classBBig", m_iclassBBig);

    GetValue("/TrackPredict/trackPredict", m_iTrackPredict);
    GetValue("/ShipSize/length", m_dShipLength);
    GetValue("/ShipSize/width", m_dShipWidth);

    GetValue("/Warning/open", m_OpenWarning);

		GetValue("/OwnShip/number", m_OwnSHipNum);
		for (int i = 0; i < m_OwnSHipNum; i++)
		{
		    QString l_value;
		    GetValue(QString("/OwnShip/Ship%1").arg(i), l_value);
		    m_OwnShipMap.push_back(l_value);
		}


    GetValue("/SaveFile/save", m_SaveFile);
     if (m_SaveFile == 1)
     {
		   m_filename = time(NULL);
       QDir l_dir;
       l_dir.mkdir(QString("./Data/RadarImgPack/%1").arg(m_filename));
     }


    AddValue("/AisDataMode/transpondMode", 0);
    GetValue("/AisDataMode/transpondMode", m_transpondMode);

    AddValue("/AisDataMode/comName", "COM1");
    GetValue("/AisDataMode/comName", m_comName);
    AddValue("/AisDataMode/combBaud", 38400);
    GetValue("/AisDataMode/combBaud", m_comBaud);

    AddValue("/AisDataMode/aisServer", 1);
    GetValue("/AisDataMode/aisServer", m_aisServer);
    AddValue("/AisDataMode/netMode", 1);
    GetValue("/AisDataMode/netMode", m_netMode);
    AddValue("/AisDataMode/comMode", 1);
    GetValue("/AisDataMode/comMode", m_comMode);

    AddValue("/AisDataMode/radarAisIP", "127.0.0.1");
    GetValue("/AisDataMode/radarAisIP", m_RadarAisIP);

    AddValue("/AisDataMode/radarAisPort", 8006);
    GetValue("/AisDataMode/radarAisPort", m_RadarAisPort);


    AddValue("/RadarDataMode/radarServer", 1);
    GetValue("/RadarDataMode/radarServer", m_radarServer);

    AddValue("/AisDataMode/GPSOpen", 1);
    GetValue("/AisDataMode/GPSOpen", m_GPSOpen);

    AddValue("/RadarDataMode/radarStatic", 1);
    GetValue("/RadarDataMode/radarStatic", m_radarStatic);

    AddValue("/RadarDataMode/FuseType", 1);
    GetValue("/RadarDataMode/FuseType", m_FuseType);

    AddValue("/FuseSetData/FuseHdg", 30);
    GetValue("/FuseSetData/FuseHdg", m_FuseHdg);
    AddValue("/FuseSetData/FuseSog", 2);
    GetValue("/FuseSetData/FuseSog", m_FuseSog);
    AddValue("/FuseSetData/FuseDis", 200);
    GetValue("/FuseSetData/FuseDis", m_FuseDis);
    AddValue("/FuseSetData/FuseCount", 10);
    GetValue("/FuseSetData/FuseCount", m_FuseCount);
    AddValue("/FuseSetData/FuseDisSuccess", 8);
    GetValue("/FuseSetData/FuseDisSuccess", m_FuseDisS);
    AddValue("/FuseSetData/FuseSogSuccess", 7);
    GetValue("/FuseSetData/FuseSogSuccess", m_FuseSogS);
    AddValue("/FuseSetData/FuseCogSuccess", 6);
    GetValue("/FuseSetData/FuseCogSuccess", m_FuseCogS);
    hgTargetManager::m_HDGDif = m_FuseHdg;
    hgTargetManager::m_SOGDif = m_FuseSog;
    hgTargetManager::m_DisDif = m_FuseDis;
    hgTargetManager::m_FuseCount = m_FuseCount;
    hgTargetManager::m_DisSuccess = m_FuseDisS;
    hgTargetManager::m_SogSuccess = m_FuseSogS;
    hgTargetManager::m_CogSuccess = m_FuseCogS;


    AddValue("/Fixed/Yellow1Lat", 32.23198);
    GetValue("/Fixed/Yellow1Lat", m_Yellow1Lat);
    AddValue("/Fixed/Yellow1Lon", 119.38402);
    GetValue("/Fixed/Yellow1Lon", m_Yellow1Lon);
    AddValue("/Fixed/Yellow2Lat", 32.23153);
    GetValue("/Fixed/Yellow2Lat", m_Yellow2Lat);
    AddValue("/Fixed/Yellow2Lon", 119.38351);
    GetValue("/Fixed/Yellow2Lon", m_Yellow2Lon);
    AddValue("/Fixed/Yellow3Lat", 32.23084);
    GetValue("/Fixed/Yellow3Lat", m_Yellow3Lat);
    AddValue("/Fixed/Yellow3Lon", 119.38312);
    GetValue("/Fixed/Yellow3Lon", m_Yellow3Lon);
    AddValue("/Fixed/112_1Lat", 32.22495);
    GetValue("/Fixed/112_1Lat", m_112_1Lat);
    AddValue("/Fixed/112_1Lon", 119.38154);
    GetValue("/Fixed/112_1Lon", m_112_1Lon);
    AddValue("/Fixed/lightLat", 32.22303);
    GetValue("/Fixed/lightLat", m_lightLat);
    AddValue("/Fixed/lightLon", 119.38487);
    GetValue("/Fixed/lightLon", m_lightLon);
    AddValue("/Fixed/Dist", 30);
    GetValue("/Fixed/Dist", m_FixedDist);
    AddValue("/Fixed/SOG", 1);
    GetValue("/Fixed/SOG", m_FixedSOG);

	AddValue("/RadarDataMode/UseRadarAis", 1);
	GetValue("/RadarDataMode/UseRadarAis", m_useRadarAis);

	AddValue("/PlayBack/time", 60);
	GetValue("/PlayBack/time", m_backSec);


    ModeInfo(); //打印个模式信息
}

    

void hgSysConfig::ReadAreaLL()
{
    QFile l_File("./data/Area/Area.txt");
    QStringList l_List;
    if ( l_File.open(QIODevice::ReadWrite) )
    {
        QTextStream stream(&l_File); 
        while (!stream.atEnd()) 
        { 
            QString line = stream.readLine();
            l_List.push_back(line);             
        } 
        l_File.close(); 
    }
    qDebug() << l_List.at(0).toInt() << l_List.size();
    if (l_List.at(0).toInt() != 0 && l_List.size() >= 4)
    {
        for ( int i = 1; i < l_List.size(); i++ )
        {
            QString l_str = l_List.at(i);
            hg::utils::PointLL l_Point(l_str.section(',',1,1).toDouble(),l_str.section(',',0,0).toDouble());
            m_AreaLL.push_back(l_Point);
        }
    }
}

void hgSysConfig::WriteSysConfig()
{

}

void hgSysConfig::ModeInfo()
{
    if (m_transpondMode == OFF)
    {
        vtsInfo << "##### " << "Transpond Mode is Client !";
    }
    else if (m_transpondMode == ON)
    {
        vtsInfo << "##### " << "Transpond Mode is Server !";
    }


    if (m_aisServer == OFF)
    {
        vtsInfo << "##### " << "Ais is OFF !";
    }
    else if (m_aisServer == ON)
    {
        vtsInfo << "##### " << "Ais is ON !";
    }

    if (m_netMode == OFF)
    {
        vtsInfo << "##### " << "Ais Net Mode is OFF !";
    }
    else if (m_netMode == ON)
    {
        vtsInfo << "##### " << "Ais Net Mode is ON !";
    }


    if (m_comMode == OFF)
    {
        vtsInfo << "##### " << "Ais Com Mode is OFF !";
    }
    else if (m_comMode == ON)
    {
        vtsInfo << "##### " << "Ais Com Mode is ON !";
    }

    if (m_radarServer == OFF)
    {
        vtsInfo << "##### " << "Radar is OFF !";
    }
    else if (m_radarServer == ON)
    {
        vtsInfo << "##### " << "Radar is ON !";
    }
}
