#include "StdAfx.h"
#include "hgTargetManager.h"
#include <QTextStream>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include "hgSqlInsertCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgutils/NavUtil.h"
#include "Managers/hgConfigManager.h"
#include "timer/hgPortTimerHandler.h"
#include "hgutils/PointLL.h"
#include "hgutils/NavUtil.h"
#include "hgutils/MathUtil.h"

mymap <QString, hgTarget> hgTargetManager::m_mapTarget;
mymap <QString, hgTarget> hgTargetManager::m_mapAis;
mymap <QString, hgTarget> hgTargetManager::m_mapRadar;
QMap <QString, QString> hgTargetManager::m_mapAisRadar;
QMap <QString, QString> hgTargetManager::m_mapRadarAis;
QMap<QString,hgTarget> hgTargetManager::m_mapStatic;
QMap<QString,hgTarget> hgTargetManager::m_mapShipData;
QMap<QString,hgTarget> hgTargetManager::m_mapRadarDel;
QMap<QString,hgResult> hgTargetManager::m_mapResult;
QMap<QString,int> hgTargetManager::m_GPSHdg;
QMap<QString, QString> hgTargetManager::m_mapGpsRadar;
QStringList hgTargetManager::m_RadarList;

QMutex hgTargetManager::m_mutexAis;
QMutex hgTargetManager::m_mutexRadar;
QMutex hgTargetManager::m_mutexTarget;
bool hgTargetManager::m_bReceieAis = false;
bool hgTargetManager::m_bPredict = false;
//CPlaneProjection hgTargetManager::m_CPlaneProjection;
int hgTargetManager::m_iWarnTime = 0;
QStringList hgTargetManager::m_OwnMMSI;
QStringList hgTargetManager::m_AlgorOwnMMSI;
QStringList hgTargetManager::m_GPSMMSI;
QStringList hgTargetManager::m_GPSMMSIPos;
QStringList hgTargetManager::m_GPSMMSIHdg;
hgAisDecoder* hgTargetManager::m_AisDecoder = NULL;

//int hgTargetManager::m_mutexAisCount = 0;
//int hgTargetManager::m_mutexRadarCount = 0;
//int hgTargetManager::m_mutexTargetCount = 0;
double hgTargetManager::m_HDGDif = DIF_COG;
double hgTargetManager::m_SOGDif = DIF_SOG;
double hgTargetManager::m_DisDif = DISTANCE;
int hgTargetManager::m_FuseCount = 10;
int hgTargetManager::m_DisSuccess = 8;
int hgTargetManager::m_SogSuccess = 7;
int hgTargetManager::m_CogSuccess = 6;
QMap<QString,hgTarget> hgTargetManager::m_mapRadarStatic;

static hgTargetManager s_manager;

hgTargetManager::hgTargetManager(void)
{
    m_AisDecoder = new hgAisDecoder();
    /*
    double fOriLL[2];
    fOriLL[0] = ORIGIN_LAT*ANGLE_TO_RADIAN;
    fOriLL[1] = ORIGIN_LON*ANGLE_TO_RADIAN;
    m_CPlaneProjection.set_origin(fOriLL);*/
}

hgTargetManager::~hgTargetManager(void)
{
    if (m_AisDecoder != NULL)
    {
        delete m_AisDecoder;
        m_AisDecoder = NULL;
    }
}


void hgTargetManager::SetPredict(bool predict)
{
    m_bPredict = predict;
}


bool hgTargetManager::GetPredict()
{
    return m_bPredict;
}

int hgTargetManager::GetWarnTime()
{
   /* if (hgConfigManager::m_sSysConfig->m_playBack == TurnOn && hgConfigManager::m_sSysConfig->m_freshMode == TurnOff)
    {
        if (m_iWarnTime == 0)
        {
            return time(NULL);
        }
        return m_iWarnTime;
    }
    if (hgConfigManager::m_sSysConfig->m_freshMode == TurnOn)
    {
        return time(NULL);
    }*/
    
    return time(NULL);
}

void hgTargetManager::SetWarnTime(int time)
{
    m_iWarnTime = time;
}

void hgTargetManager::AssemblyTarget(hgAisData &aisData,hgTarget &ais,hgSqlOperator& sqlOperator)
{
    if (aisData.COG >= 360)
    {
        aisData.COG = 360;
    }
    aisData.HDG = aisData.COG;
    if (hgTargetManager::m_GPSMMSI.contains(ais.MMSI))
    {
        return ;
    }
 

    ais.ID = QString::number(aisData.MMSI);

    ais.Source = AIS_DATA;
    ais.Result = AIS_FUSE;
    ais.Reserved = 0;
    ais.Rng = 0;
    ais.RadarBrg = 0;
    ais.Spd = 0;
    ais.Crs = 0;
    ais.Scans = 0;
    ais.Flags = 0;

    ais.MMSI = QString::number(aisData.MMSI);
    ais.MID = aisData.MID;
    ais.Class = aisData.Class;
    ais.ReportTicks = aisData.ReportTicks;
    ais.Simulation = false;
    ais.Missing = false;
    ais.OwnShip = aisData.OwnShip;
    ais.ReportInterval = 0;
    ais.DimA = 0;
    ais.DimB = 0;
    ais.DimC = 0;
    ais.DimD = 0;
    ais.Range_NM = aisData.Range_NM;
    ais.Brg = aisData.Brg;
    ais.TCPA = aisData.TCPA;
    ais.CPA = aisData.CPA;
    ais.SyncState = aisData.SyncState;
    ais.SlotTO = aisData.SlotTO;

    {
        {
            mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapAis.find(QString::number(aisData.MMSI));
            if (l_it != hgTargetManager::m_mapAis.end())
            {
                ais.SetShipSize = l_it->SetShipSize;
                ais.ReportPeriod = ais.ReportTicks - l_it->ReportTicks;


                ais.ETA_Mo = l_it->ETA_Mo;
                ais.ETA_Day = l_it->ETA_Day;
                ais.ETA_Hr = l_it->ETA_Hr;
                ais.ETA_Min = l_it->ETA_Min;

                //ais.Prediction = l_it->Prediction;

                switch(aisData.MID)
                {
                case 1:
                case 2:
                case 3://A动态信息
                    ais.IMO = l_it->IMO;
                    ais.Length = l_it->Length;
                    ais.Width = l_it->Width;
                    ais.ShipName = l_it->ShipName;
                    ais.ShipType = l_it->ShipType;
                    ais.ChShipName = l_it->ChShipName;
                    ais.Nationality = l_it->Nationality;
                    ais.Note = l_it->Note;

                    ais.CallSign = l_it->CallSign;
                    ais.EquipmentType = l_it->EquipmentType;
                    ais.DimA = l_it->DimA;
                    ais.DimB = l_it->DimB;
                    ais.DimC = l_it->DimC;
                    ais.DimD = l_it->DimD;
                    ais.Destination = l_it->Destination;
                    ais.ETA_Mo = l_it->ETA_Mo;
                    ais.ETA_Day = l_it->ETA_Day;
                    ais.ETA_Hr = l_it->ETA_Hr;
                    ais.ETA_Min = l_it->ETA_Min;
                    ais.Draft = l_it->Draft;

                    ais.NavStatus = aisData.NavStatus;
                    ais.SOG = aisData.SOG;
                    ais.PosAccuracy = aisData.PosAccuracy;
                    ais.Lon = aisData.Lon;
                    ais.Lat = aisData.Lat;
                    ais.COG = aisData.COG;
                    ais.HDG = aisData.HDG;
                    ais.ROTAIS = aisData.ROTAIS;
                    ais.utc_sec = aisData.m_utc_sec;
                    ais.utc_hour = aisData.m_utc_hour;
                    ais.utc_min = aisData.m_utc_min;
                    //ais.Prediction.AddPointLL(ais.ReportTicks,hg::utils::PointLL(ais.Lon,ais.Lat));
                    //vtsError << aisData.MMSI << " " << aisData.ReportTicks << " "<< aisData.Lat << " "<< aisData.Lon;
                    break;
                case 4://基站
                    ais.Lon = aisData.Lon;
                    ais.Lat = aisData.Lat;
                    ais.PosAccuracy = aisData.PosAccuracy;
                    ais.utc_sec = aisData.m_utc_sec;
                    ais.utc_hour = aisData.m_utc_hour;
                    ais.utc_min = aisData.m_utc_min;
                    ais.EquipmentType = aisData.EquipmentType;
                    ais.HDG = aisData.HDG;
                    ais.COG = aisData.COG;
                    ais.SOG = aisData.SOG;
                    ais.NavStatus = aisData.NavStatus;
                    ais.PosAccuracy = aisData.PosAccuracy;
                    ais.ROTAIS = aisData.ROTAIS;
                    ais.IMO = aisData.IMO;
                    ais.Length = hgConfigManager::m_sSysConfig->m_dShipLength;
                    ais.Width = hgConfigManager::m_sSysConfig->m_dShipWidth;
                    ais.ShipName = aisData.ShipName;
                    ais.ShipType = aisData.ShipType;
                    ais.ChShipName = l_it->ChShipName;
                    ais.Nationality = l_it->Nationality;
                    ais.Note = l_it->Note;
                    ais.CallSign = l_it->CallSign;
                    ais.DimA = hgConfigManager::m_sSysConfig->m_dShipLength * 0.75;
                    ais.DimB = hgConfigManager::m_sSysConfig->m_dShipLength * 0.25;
                    ais.DimC = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.25;
                    ais.DimD = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.75;
                    ais.Destination = aisData.Destination;
                    ais.ETA_Mo = aisData.ETA_Mo;
                    ais.ETA_Hr = aisData.ETA_Hr;
                    ais.ETA_Min = aisData.ETA_Min;
                    ais.Draft = aisData.Draft;
                    ais.SetShipSize = true;
                    break;
                case 5://A静态信息
                    if (l_it->IMO == 0)
                    {
                        ais.IMO = aisData.IMO;
                    } 
                    else
                    {
                        ais.IMO = l_it->IMO;
                    }
                    if (l_it->ShipName == NULL)
                    {
                        ais.ShipName = QString(aisData.ShipName).replace(QRegExp("@"), "");
                    } 
                    else
                    {
                        ais.ShipName = l_it->ShipName;
                    }

                    if (l_it->CallSign == NULL)
                    {
                        ais.CallSign = QString(aisData.CallSign).replace(QRegExp("@"), "");
                    } 
                    else
                    {
                        ais.CallSign = l_it->CallSign;
                    }

                    if (l_it->Destination == NULL)
                    {
                        ais.Destination = QString(aisData.Destination).replace(QRegExp("@"), "");
                    } 
                    else
                    {
                        ais.Destination = l_it->Destination;
                    }

                    if (aisData.DimA != 0 && aisData.DimB != 0 && aisData.DimC != 0 && aisData.DimD != 0)
                    {
                        if (l_it->Length == hgConfigManager::m_sSysConfig->m_dShipLength && l_it->Width == hgConfigManager::m_sSysConfig->m_dShipWidth)
                        {
                            ais.DimA = aisData.DimA;
                            ais.DimB = aisData.DimB;
                            ais.DimC = aisData.DimC;
                            ais.DimD = aisData.DimD;
                            ais.Length = aisData.DimA + aisData.DimB;
                            ais.Width = aisData.DimC + aisData.DimD;
                            ais.SetShipSize = false;
                        }
                        else
                        {
                            ais.DimA = l_it->DimA;
                            ais.DimB = l_it->DimB;
                            ais.DimC = l_it->DimC;
                            ais.DimD = l_it->DimD;
                            ais.Length = l_it->Length;
                            ais.Width = l_it->Width;
                            ais.SetShipSize = l_it->SetShipSize;
                        }
                    } 
                    else
                    {
                        ais.DimA = l_it->DimA;
                        ais.DimB = l_it->DimB;
                        ais.DimC = l_it->DimC;
                        ais.DimD = l_it->DimD;
                        ais.Length = l_it->Length;
                        ais.Width = l_it->Width;
                        ais.SetShipSize = l_it->SetShipSize;
                    }

                    ais.EquipmentType = aisData.EquipmentType;
                    ais.ETA_Mo = aisData.ETA_Mo;
                    ais.ETA_Day = aisData.ETA_Day;
                    ais.ETA_Hr = aisData.ETA_Hr;
                    ais.ETA_Min = aisData.ETA_Min;
                    ais.Draft = aisData.Draft;

                    ais.NavStatus = aisData.NavStatus;
                    ais.SOG = aisData.SOG;
                    ais.PosAccuracy = aisData.PosAccuracy;

                    if (aisData.Lat < 1 || aisData.Lon < 1)
                    {
                        ais.Lon = l_it->Lon;
                        ais.Lat = l_it->Lat;
                    }
                    else
                    {
                        ais.Lon = aisData.Lon;
                        ais.Lat = aisData.Lat;
                    }
                    ais.COG = l_it->COG;
                    ais.HDG = l_it->HDG;
                    ais.SOG = l_it->SOG;
                    ais.ROTAIS = aisData.ROTAIS;
                    ais.utc_sec = l_it->utc_sec;
                    ais.utc_hour = l_it->utc_hour;
                    ais.utc_min = l_it->utc_min;
                    ais.ChShipName = l_it->ChShipName;
                    ais.Nationality = l_it->Nationality;
                    ais.Note = l_it->Note;
                    break;
                case 18://标准的B类设备位置报告
                    //ais.IMO = l_it->IMO;
                    ais.Length = l_it->Length;
                    ais.Width = l_it->Width;
                    ais.ShipName = l_it->ShipName;
                    ais.ShipType = l_it->ShipType;
                    ais.ChShipName = l_it->ChShipName;
                    ais.Nationality = l_it->Nationality;
                    ais.Note = l_it->Note; 
                    ais.Draft = l_it->Draft;


                    ais.CallSign = l_it->CallSign;
                    ais.DimA = l_it->DimA;
                    ais.DimB = l_it->DimB;
                    ais.DimC = l_it->DimC;
                    ais.DimD = l_it->DimD;

                    ais.SOG = aisData.SOG;
                    ais.PosAccuracy = aisData.PosAccuracy;
                    ais.Lon = aisData.Lon;
                    ais.Lat = aisData.Lat;
                    ais.COG = aisData.COG;
                    ais.HDG = aisData.HDG;
                    ais.utc_sec = aisData.m_utc_sec;

                    //ais.Prediction.AddPointLL(ais.ReportTicks,hg::utils::PointLL(ais.Lon,ais.Lat));
                    //vtsError << aisData.MMSI << " " << aisData.ReportTicks << " "<< aisData.Lat << " "<< aisData.Lon;
                    break;
                case 19://扩展的B类设备位置报告
                    ais.ShipName = l_it->ShipName;
                    ais.ShipType = l_it->ShipType;
                    ais.CallSign = l_it->CallSign;
                    ais.ChShipName = l_it->ChShipName;
                    ais.Nationality = l_it->Nationality;
                    ais.Note = l_it->Note;
                    ais.Draft = l_it->Draft;


                    if (aisData.DimA != 0 && aisData.DimB != 0 && aisData.DimC != 0 && aisData.DimD != 0)
                    {
                        if (l_it->Length == hgConfigManager::m_sSysConfig->m_dShipLength && l_it->Width == hgConfigManager::m_sSysConfig->m_dShipWidth)
                        {
                            ais.DimA = aisData.DimA;
                            ais.DimB = aisData.DimB;
                            ais.DimC = aisData.DimC;
                            ais.DimD = aisData.DimD;
                            ais.Length = aisData.DimA + aisData.DimB;
                            ais.Width = aisData.DimC + aisData.DimD;
                            ais.SetShipSize = false;
                        }
                        else
                        {
                            ais.DimA = l_it->DimA;
                            ais.DimB = l_it->DimB;
                            ais.DimC = l_it->DimC;
                            ais.DimD = l_it->DimD;
                            ais.Length = l_it->Length;
                            ais.Width = l_it->Width;
                            ais.SetShipSize = l_it->SetShipSize;
                        }
                    } 
                    else
                    {
                        ais.DimA = l_it->DimA;
                        ais.DimB = l_it->DimB;
                        ais.DimC = l_it->DimC;
                        ais.DimD = l_it->DimD;
                        ais.Length = l_it->Length;
                        ais.Width = l_it->Width;
                        ais.SetShipSize = l_it->SetShipSize;
                    }
                    ais.SOG = aisData.SOG;
                    ais.PosAccuracy = aisData.PosAccuracy;
                    ais.Lon = aisData.Lon;
                    ais.Lat = aisData.Lat;
                    ais.COG = aisData.COG;
                    ais.HDG = aisData.HDG;
                    ais.utc_sec = aisData.m_utc_sec;
                    //ais.Prediction.AddPointLL(ais.ReportTicks,hg::utils::PointLL(ais.Lon,ais.Lat));
                    //vtsError << aisData.MMSI << " " << aisData.ReportTicks << " "<< aisData.Lat << " "<< aisData.Lon;
                    break;
                case 21://助航设备报告
                    if (l_it->ShipName == NULL)
                    {
                        ais.ShipName = QString(aisData.ShipName).replace(QRegExp("@"), "");
                    } 
                    else
                    {
                        ais.ShipName = l_it->ShipName;
                    }

                    ais.DimA = aisData.DimA;
                    ais.DimB = aisData.DimB;
                    ais.DimC = aisData.DimC;
                    ais.DimD = aisData.DimD;
                    ais.utc_sec = aisData.m_utc_sec;
                    ais.ChShipName = l_it->ChShipName;
                    ais.Nationality = l_it->Nationality;
                    ais.Note = l_it->Note;
                    ais.HDG = aisData.HDG;
                    ais.COG = aisData.COG;
                    ais.SOG = aisData.SOG;
                    break;
                case 24://B静态数据报告
                    ais.Draft = aisData.Draft;

                    if (l_it->ShipName == NULL)
                    {
                        ais.ShipName = QString(aisData.ShipName).replace(QRegExp("@"), "");
                    } 
                    else
                    {
                        ais.ShipName = l_it->ShipName;
                    }

                    if (l_it->CallSign == NULL)
                    {
                        ais.CallSign = QString(aisData.CallSign).replace(QRegExp("@"), "");
                    } 
                    else
                    {
                        ais.CallSign = l_it->CallSign;
                    }
                    if (aisData.DimA != 0 && aisData.DimB != 0 && aisData.DimC != 0 && aisData.DimD != 0)
                    {
                        if (l_it->Length == hgConfigManager::m_sSysConfig->m_dShipLength && l_it->Width == hgConfigManager::m_sSysConfig->m_dShipWidth)
                        {
                            ais.DimA = aisData.DimA;
                            ais.DimB = aisData.DimB;
                            ais.DimC = aisData.DimC;
                            ais.DimD = aisData.DimD;
                            ais.Length = aisData.DimA + aisData.DimB;
                            ais.Width = aisData.DimC + aisData.DimD;
                            ais.SetShipSize = false;
                        }
                        else
                        {
                            ais.DimA = l_it->DimA;
                            ais.DimB = l_it->DimB;
                            ais.DimC = l_it->DimC;
                            ais.DimD = l_it->DimD;
                            ais.Length = l_it->Length;
                            ais.Width = l_it->Width;
                            ais.SetShipSize = l_it->SetShipSize;
                        }
                    } 
                    else
                    {
                        ais.DimA = l_it->DimA;
                        ais.DimB = l_it->DimB;
                        ais.DimC = l_it->DimC;
                        ais.DimD = l_it->DimD;
                        ais.Length = l_it->Length;
                        ais.Width = l_it->Width;
                        ais.SetShipSize = l_it->SetShipSize;
                    }

                    ais.SOG = l_it->SOG;
                    ais.PosAccuracy = l_it->PosAccuracy;
                    ais.Lon = l_it->Lon;
                    ais.Lat = l_it->Lat;
                    ais.COG = l_it->COG;
                    ais.HDG = l_it->HDG;
                    ais.utc_sec = l_it->utc_sec;
                    ais.ChShipName = l_it->ChShipName;
                    ais.Nationality = l_it->Nationality;
                    ais.Note = l_it->Note;
                    break;

                }
            }
            else
            {
                //std::clock_t t1 = clock();
                QMap<QString,hgTarget>::iterator l_itSta = m_mapStatic.find(QString::number(aisData.MMSI));
                QMap<QString,hgTarget>::iterator l_itCsv = m_mapShipData.find(QString::number(aisData.MMSI));
                //std::clock_t t2 = clock();
                //qDebug() << "find(...............)" << t2-t1 << m_mapStatic.size();
                bool l_findCsv = false,l_findStatic = false;
                if (l_itCsv != m_mapShipData.end())
                {
                    l_findCsv = true;
                    ais.IMO = l_itCsv->IMO;
                    ais.ShipName = l_itCsv->ShipName;
                    ais.DimA = l_itCsv->DimA;
                    ais.DimB = l_itCsv->DimB;
                    ais.DimC = l_itCsv->DimC;
                    ais.DimD = l_itCsv->DimD;
                    ais.Length = l_itCsv->DimA + l_itCsv->DimB;
                    ais.Width = l_itCsv->DimC + l_itCsv->DimD; 
                    ais.SetShipSize = false;


                    ais.CallSign = aisData.CallSign;
                    ais.Destination = aisData.Destination;
                    ais.EquipmentType = aisData.EquipmentType;
                    ais.ETA_Mo = aisData.ETA_Mo;
                    ais.ETA_Day = aisData.ETA_Day;
                    ais.ETA_Hr = aisData.ETA_Hr;
                    ais.ETA_Min = aisData.ETA_Min;
                    ais.Draft = aisData.Draft;
                }
                if (l_itSta != m_mapStatic.end())
                {
                    l_findStatic = true;
                    if (l_findCsv == false)
                    {
                        ais.IMO = l_itSta->IMO;
                        ais.ShipName = l_itSta->ShipName;
                        ais.ShipType = l_itSta->ShipType;
                        ais.DimA = l_itSta->DimA;
                        ais.DimB = l_itSta->DimB;
                        ais.DimC = l_itSta->DimC;
                        ais.DimD = l_itSta->DimD;
                        ais.Length = l_itSta->Length;
                        ais.Width = l_itSta->Width;
                        ais.SetShipSize = l_itSta->SetShipSize;
                    }
                    ais.CallSign = l_itSta->CallSign;
                    ais.Destination = l_itSta->Destination;
                    ais.EquipmentType = l_itSta->EquipmentType;
                    ais.ETA_Mo = l_itSta->ETA_Mo;
                    ais.ETA_Day = l_itSta->ETA_Day;
                    ais.ETA_Hr = l_itSta->ETA_Hr;
                    ais.ETA_Min = l_itSta->ETA_Min;
                    ais.Draft = l_itSta->Draft;

                    ais.SetShipSize = l_itSta->SetShipSize;

                    ais.ChShipName = l_itSta->ChShipName;
                    ais.Nationality = l_itSta->Nationality;
                    ais.Note = l_itSta->Note;

                } 
                if (l_findCsv == false && l_findStatic == false)
                {
                    ais.IMO = aisData.IMO;
                    ais.ShipName = QString(aisData.ShipName).replace(QRegExp("@"), "");
                    //ais.ShipType = aisData.ShipType;
                    ais.CallSign = QString(aisData.CallSign).replace(QRegExp("@"), "");
                    ais.Destination = QString(aisData.Destination).replace(QRegExp("@"), "");
                    ais.EquipmentType = aisData.EquipmentType;
                    ais.DimA = hgConfigManager::m_sSysConfig->m_dShipLength * 0.75;
                    ais.DimB = hgConfigManager::m_sSysConfig->m_dShipLength * 0.25;
                    ais.DimC = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.25;
                    ais.DimD = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.75;
                    ais.ETA_Mo = aisData.ETA_Mo;
                    ais.ETA_Day = aisData.ETA_Day;
                    ais.ETA_Hr = aisData.ETA_Hr;
                    ais.ETA_Min = aisData.ETA_Min;
                    ais.Draft = aisData.Draft;

                    ais.SetShipSize = true;
                    ais.Length = hgConfigManager::m_sSysConfig->m_dShipLength;
                    ais.Width = hgConfigManager::m_sSysConfig->m_dShipWidth;
                }

                ais.NavStatus = aisData.NavStatus;
                ais.SOG = aisData.SOG;
                ais.PosAccuracy = aisData.PosAccuracy;
                ais.Lon = aisData.Lon;
                ais.Lat = aisData.Lat;
                ais.COG = aisData.COG;
                ais.HDG = aisData.HDG;
                ais.ROTAIS = aisData.ROTAIS;
                ais.utc_sec = aisData.m_utc_sec;
                ais.utc_hour = aisData.m_utc_hour;
                ais.utc_min = aisData.m_utc_min;

                ais.ReportPeriod = 0;
            }

            ais.ID = ais.MMSI;
            hgTargetManager::m_mapAis.insert(ais.ID,ais);
        }

        Assembly(ais,sqlOperator);
        
    } 
    
    assert (ais.HDG < 1000000);
}

void hgTargetManager::Assembly(hgTarget &ais,hgSqlOperator& sqlOperator)
{ 
    ais.Result = AIS_FUSE;
    hgTarget l_aisNow = ais;
    bool l_debug = false;
    if (m_GPSMMSI.contains(ais.MMSI))
    {
        if (m_mapAisRadar.contains(ais.MMSI))
        {
            ais.RadarID = m_mapAisRadar.find(ais.MMSI).value();
            ais.RadarGUID = m_mapAisRadar.find(ais.MMSI).value();
        }
        else
        {
            ais.RadarID = "";
            ais.RadarGUID = "";
        }
        if (m_mapResult.contains(ais.MMSI))
        {
            ais.RadarID = m_mapResult.find(ais.MMSI)->RadarID;
            ais.RadarGUID = m_mapResult.find(ais.MMSI)->RadarID;
        }
    }
//     if (l_debug)
//     {
//         if (m_GPSMMSI.contains(ais.MMSI))
//         {
//             if (m_mapResult.contains(ais.MMSI))
//             {
//                 QMap<QString,hgResult>::iterator l_itRes = m_mapResult.find(ais.MMSI);
//                 qDebug () << "<<<<<<" << ais.MMSI << l_itRes->RadarID << l_itRes->Count;
//                 if (m_mapRadar.find(l_itRes->RadarID) != m_mapRadar.end())
//                 {
//                     hgTarget l_tttt = m_mapRadar.find(l_itRes->RadarID).value();
//                     double l_ss,l_ddd,l_aaa;
//                     SameObject(ais,l_tttt,l_ddd,l_aaa,l_ss);
//                     qDebug () << "          "<< l_ddd << l_aaa << l_ss;
//                 }
//             }
//         }
//     }
    //融合检测
    {
        QMap<QString,hgResult>::iterator l_itRes = m_mapResult.begin();
        bool l_find = false;
        l_itRes = m_mapResult.find(ais.ID);
        if (l_itRes != m_mapResult.end())
        {
            if (l_itRes->MMSI == ais.MMSI)
            {
                l_find = true;

                if (l_itRes->DisCount >= m_DisSuccess 
                 /*   && l_itRes->SogCount >= m_SogSuccess*/
                    && l_itRes->CogCount >= m_CogSuccess)//已融合
                {
                    if (l_itRes->DisCount == m_DisSuccess)
                    {
                        AddFuaeResult(sqlOperator,l_itRes.value(),true,time(NULL));
                        //l_itRes->Count = m_FuseCount+1;
                    }
                    mymap<QString,hgTarget>::iterator l_it = m_mapTarget.find(l_itRes->MMSI);
                    mymap<QString,hgTarget>::iterator l_itRadar = m_mapRadar.find(l_itRes->RadarGUID);
                    bool l_ronghe = true;
                    bool l_cancle = false;
                    if (l_it != m_mapTarget.end())
                    {
                        mymap<QString,hgTarget>::iterator l_itAis = m_mapAis.find(l_itRes->MMSI);
                        if (l_itAis != m_mapAis.end() && ChangeAIS(ais,l_itAis.value()))
                        {
                            l_cancle = true;
                        }
                        if (l_itRadar != m_mapRadar.end())
                        {
                            double l_distance,l_angle,l_speed;
                            if (m_GPSMMSI.contains(ais.MMSI) 
                                && !SameObjectD(ais,l_itRadar.value(),l_distance,l_angle,l_speed))
                            {
                                qDebug () << "<<<<  Cancle" << l_itRes->MMSI << l_itRes->RadarID << l_distance;
                                l_ronghe = false;
                                m_mapResult.erase(l_itRes);
                                if (m_mapAisRadar.contains(ais.MMSI))
                                {
                                    ais.RadarID = m_mapAisRadar.find(ais.MMSI).value();
									ais.RadarGUID = m_mapAisRadar.find(ais.MMSI).value();
									if (m_GPSMMSIHdg.contains(ais.MMSI) && m_GPSMMSIPos.contains(ais.MMSI))
									{

									}
									else if (m_GPSMMSIPos.contains(ais.MMSI) == false)
									{
										ais.Lat = l_itRadar->Lat;
										ais.Lon = l_itRadar->Lon;
									}
									else if (m_GPSMMSIHdg.contains(ais.MMSI) == false)
									{
										ais.HDG = l_itRadar->HDG;
									}
                                }
                                else
                                {
                                    ais.RadarID = "";
                                    ais.RadarGUID = "";
                                }
                            }
                            else
                            {
                                if (m_GPSMMSI.contains(ais.MMSI))
                                {
                                    ais.RadarGUID = l_itRes->RadarGUID;
									ais.RadarID = l_itRes->RadarID;
									if (m_GPSMMSIHdg.contains(ais.MMSI) && m_GPSMMSIPos.contains(ais.MMSI))
									{

									}
									else if (m_GPSMMSIPos.contains(ais.MMSI) == false)
									{
										ais.Lat = l_itRadar->Lat;
										ais.Lon = l_itRadar->Lon;
									}
									else if (m_GPSMMSIHdg.contains(ais.MMSI) == false)
									{
										ais.HDG = l_itRadar->HDG;
									}
                                }
                                else
                                {
                                    double l_distance1,l_angle1,l_speed1;
                                    if (l_cancle == true && !SameObjectD(ais,l_itRadar.value(),l_distance1,l_angle1,l_speed1))
                                    {
                                        l_ronghe = false;
                                        if (hgTargetManager::m_AlgorOwnMMSI.contains(l_itRes->MMSI))
                                        {
                                            qDebug() << "Error Fuse" << l_itRes->MMSI << l_itRes->RadarID << l_distance1;
                                        }
                                        m_mapResult.erase(l_itRes);
                                    }
                                    else
                                    {
                                        ais.RadarGUID = l_itRes->RadarGUID;
                                        ais.RadarID = l_itRes->RadarID;

                                        ais.Lat = l_itRadar->Lat;
                                        ais.Lon = l_itRadar->Lon;
                                        ais.COG = l_itRadar->COG;
                                        ais.SOG = l_itRadar->SOG;
                                        ais.Reserved = l_itRadar->Reserved;
                                        ais.Rng = l_itRadar->Rng;
                                        ais.RadarBrg = l_itRadar->RadarBrg;
                                        ais.Spd = l_itRadar->Spd;
                                        ais.Crs = l_itRadar->Crs;
                                        ais.Scans = l_itRadar->Scans;
                                        ais.Flags = l_itRadar->Flags;
                                        ais.Result = AIS_RADAR_FUSE;
										ais.HDG = l_itRadar->HDG;
										ais.COG = l_itRadar->COG;
										if (ais.SetShipSize == true)
										{
											ais.DimA = l_itRadar->DimA;
											ais.DimB = l_itRadar->DimB;
											ais.DimC = l_itRadar->DimC;
											ais.DimD = l_itRadar->DimD;
											ais.Length = l_itRadar->Length;
											ais.Width = l_itRadar->Width;
											ais.SetShipSize = false;
										}
                                    }
//                                     if (l_cancle == true)
//                                     {
//                                          qDebug() << "Error Fusepp" << l_itRes->MMSI << l_itRes->RadarID << l_distance1;
//                                     }
                                }
                            }
                        }
                        else
                        {
                            l_ronghe = false;
                            if (hgTargetManager::m_AlgorOwnMMSI.contains(l_itRes->MMSI))
                            {
                                qDebug () << "<<<<  Cancle Own  "  << l_itRes->MMSI << l_itRes->RadarID;
                            }
                            if (m_mapAisRadar.contains(ais.MMSI))
                            {
                                ais.RadarID = m_mapAisRadar.find(ais.MMSI).value();
                                ais.RadarGUID = m_mapAisRadar.find(ais.MMSI).value();
                            }
                            else
                            {
                                ais.RadarID = "";
                                ais.RadarGUID = "";
                            }
                            m_mapResult.erase(l_itRes);
                        }

                    }
                    if (l_ronghe == true)
                    {
                        l_it = m_mapTarget.find(l_itRes->RadarGUID);
                        if (l_it != m_mapTarget.end())
                        {
                            m_mapTarget.erase(l_it);
                        }
                    }
                }
                else  //l_itRes->Count < 3 未融合（找到待融合物标）
                {
                    //位置比对
                    ais.Result = AIS_FUSE;
                    double l_distance,l_angle,l_speed,l_AvAngle;
                    bool l_bDist,l_bAngle,l_bSog;
                    mymap<QString,hgTarget>::iterator l_it = m_mapTarget.find(l_itRes->RadarGUID);
                    if (l_it != m_mapTarget.end())
                    {
                        SameObject(ais,l_it.value(),l_distance,l_bDist,l_bAngle,l_bSog);
                        bool l_break = false;
                        if (l_itRes->current < m_FuseCount-1)//当前匹配位置
                        {
                            l_itRes->current++;
                        }
                        else
                        {
                            l_itRes->current = 0;
                        }
                        //距离匹配
                        if ( l_bDist == true && l_bSog == true
                            /*&& l_bAngle == true */)
                        {
                            if (l_itRes->DisSucc[l_itRes->current] == 0)//未赋值
                            {
                                l_itRes->DisCount++;
                            }
                            else if (l_itRes->DisSucc[l_itRes->current] == 1)//失败
                            {
                                l_itRes->DisCount++;
                            }
                            else if (l_itRes->DisSucc[l_itRes->current] == 2)//成功
                            {
                            }
                            l_itRes->DisSucc[l_itRes->current] = 2;
                        }
                        else
                        {
                            if (l_itRes->DisSucc[l_itRes->current] == 0)//未赋值
                            {
                            }
                            else if (l_itRes->DisSucc[l_itRes->current] == 1)//失败
                            {
                            }
                            else if (l_itRes->DisSucc[l_itRes->current] == 2)//成功
                            {
                                l_itRes->DisCount--;
                            }
                            l_itRes->DisSucc[l_itRes->current] = 1;
                            if (l_itRes->DisCount == 0)
                            {
                                l_break = true;
                                m_mapResult.erase(l_itRes);
                            }
                        }
                        //l_break = true;
                        if (l_break == false)
                        {
//                             //速度匹配
//                             if ( l_bSog == true )
//                             {
//                                 if (l_itRes->SogSucc[l_itRes->current] == 0)//未赋值
//                                 {
//                                     l_itRes->SogCount++;
//                                 }
//                                 else if (l_itRes->SogSucc[l_itRes->current] == 1)//失败
//                                 {
//                                     l_itRes->SogCount++;
//                                 }
//                                 else if (l_itRes->SogSucc[l_itRes->current] == 2)//成功
//                                 {
//                                 }
//                                 l_itRes->SogSucc[l_itRes->current] = 2;
//                             }
//                             else
//                             {
//                                 if (l_itRes->SogSucc[l_itRes->current] == 0)//未赋值
//                                 {
//                                 }
//                                 else if (l_itRes->SogSucc[l_itRes->current] == 1)//失败
//                                 {
//                                 }
//                                 else if (l_itRes->SogSucc[l_itRes->current] == 2)//成功
//                                 {
//                                     l_itRes->SogCount--;
//                                 }
//                                 l_itRes->SogSucc[l_itRes->current] = 1;
//                                 if (l_itRes->SogCount < 0)
//                                 {
//                                     l_itRes->SogCount = 0;
//                                 }
//                             }
                            //方向匹配
                            if ( l_bAngle == true )
                            {
                                if (l_itRes->CogSucc[l_itRes->current] == 0)//未赋值
                                {
                                    l_itRes->CogCount++;
                                }
                                else if (l_itRes->CogSucc[l_itRes->current] == 1)//失败
                                {
                                    l_itRes->CogCount++;
                                }
                                else if (l_itRes->CogSucc[l_itRes->current] == 2)//成功
                                {
                                }
                                l_itRes->CogSucc[l_itRes->current] = 2;
                            }
                            else
                            {
                                if (l_itRes->CogSucc[l_itRes->current] == 0)//未赋值
                                {
                                }
                                else if (l_itRes->CogSucc[l_itRes->current] == 1)//失败
                                {
                                }
                                else if (l_itRes->CogSucc[l_itRes->current] == 2)//成功
                                {
                                    l_itRes->CogCount--;
                                }
                                l_itRes->CogSucc[l_itRes->current] = 1;
                                if (l_itRes->CogCount < 0)
                                {
                                    l_itRes->CogCount = 0;
                                }
                            }
                        }
                    }
                }
                ais.Source = FUSE_DATA;
                m_mapTarget.insert(ais.ID,ais);
            }
        }
        if (l_find == false) //id，mmsi未匹配过
        {
            double l_distance,l_angle,l_speed;
            bool l_bDist,l_bAngle,l_bSog;
            QMap<double,hgResult> l_tempMap;
            mymap<QString,hgTarget>::iterator l_it = m_mapRadar.begin();
            for (l_it; l_it != m_mapRadar.end(); ++l_it)
            {
                SameObject(ais,l_it.value(),l_distance,l_bDist,l_bAngle,l_bSog);
                if ( l_bDist == true && l_bSog == true && l_bAngle == true)
                {
                    hgResult l_result;
                    l_result.ID = ais.MMSI;
                    l_result.MMSI = ais.MMSI;
                    l_result.RadarGUID = l_it->RadarGUID;
                    l_result.RadarID = l_it->RadarID;
                    l_result.DisCount = 1;
                    l_result.SogCount = 1;
                    l_result.CogCount = l_bAngle ? 1:0;
                    l_result.current = 0;
                    memset( l_result.DisSucc,0, sizeof(int)*50);
                    memset( l_result.SogSucc,0, sizeof(int)*50);
                    memset( l_result.CogSucc,0, sizeof(int)*50);
                    l_result.DisSucc[0] = 2; // 1匹配失败 2匹配成功 0 初始化
                    l_result.SogSucc[0] = 2;
                    l_result.CogSucc[0] = l_bAngle ? 2:1;
                    l_tempMap.insert(l_distance,l_result); 
                    l_result.AvCog = abs(ais.COG - /*m_mapTarget.find(l_result.RadarGUID)*/l_it->COG);  
                }
            }
            //if (l_tempMap.size() > 0)
            auto l_tempiter = l_tempMap.begin();
            for ( ; l_tempiter != l_tempMap.end(); l_tempiter++)
            {
                hgResult l_result = l_tempiter.value();
                //hgResult l_result = l_tempMap.begin().value();
                double l_dist = l_tempiter.key();
                auto l_iterResult = m_mapResult.begin();
                bool l_RongHe = false;//是否被融合
                QString l_MMSI;
                QMap<QString ,hgResult>::iterator l_iterOld;
                for ( ; l_iterResult != m_mapResult.end(); l_iterResult++)
                {
                    if (l_iterResult->RadarID == l_result.RadarID)///判断此雷达是否被融合
                    {
                        l_RongHe = true;
                        l_MMSI = l_iterResult->MMSI;
                        l_iterOld = l_iterResult;
                    }
                }
                if (l_RongHe == false)
                {
                    m_mapResult.insert(l_result.ID,l_result);
                    break;
                    //m_mapResult.insert(l_tempMap.begin().value().ID,l_tempMap.begin().value());
                }
                else
                {
                    if (l_dist < 50)//距离小于20的话匹配雷达以融合的物标是否还匹配  不是取消融合
                    {
                        double l_distold,l_angleold,l_spdold;
                        if (m_mapAis.find(l_MMSI) != m_mapAis.end()
                            && m_mapRadar.find(l_result.RadarID) != m_mapRadar.end())//雷达链表，AIS链表是否有数据
                        {
                            if (SameObjectD(m_mapAis.find(l_MMSI).value(),m_mapRadar.find(l_result.RadarID).value(),l_distold,l_angleold,l_spdold))//同一物标
                            {
                            }
                            else//不同物标
                            {
                                m_mapResult.erase(l_iterOld);
                                m_mapResult.insert(l_result.ID,l_result);
                                break;
                            }
                        }
                    }
                }
            }
            ais.Source = FUSE_DATA;
            ais.Result = AIS_FUSE; 
            m_mapTarget.insert(ais.ID,ais);
        }

    }
    m_mapAis.insert(l_aisNow.ID,l_aisNow);
}

void hgTargetManager::AssemGPSRadar(hgTarget &ais)
{
	for (auto iter = m_mapRadar.begin(); iter != m_mapRadar.end(); iter++)
	{
		bool l_ret = SameObjectGPSRadar(ais, iter.value());
		if (l_ret == true)
		{
			m_mapGpsRadar.insert(ais.MMSI, iter.value().RadarID);
			return ;
		}
	}
}

bool hgTargetManager::SameObjectGPSRadar(hgTarget ais,hgTarget radar)
{
	double dist = -1;
	bool bDist = false;
	bool bAngle = false;
	bool bSOG = false;
	if (radar.RadarID == "65535" && ais.RadarID != "65535")
	{
		return false;
	}
	hg::utils::PointLL l_aisCenter,l_radarCenter; 
	l_aisCenter = hg::utils::PointLL(ais.Lon,ais.Lat);
	l_radarCenter = hg::utils::PointLL(radar.Lon,radar.Lat);
	dist = hg::utils::navutil::getDistance(l_aisCenter,l_radarCenter)*NM2M;//米
	double l_SOG = abs(ais.SOG - radar.SOG);
	double l_angle = abs(ais.COG - radar.COG);
	if (l_angle > 180)
	{
		l_angle = 360 - l_angle;
	}
	if (l_SOG <= m_SOGDif)
	{
		bSOG = true;
	}
	if (dist < 100)
	{
		bDist = true;
	}
	if (l_angle < m_HDGDif)
	{
		bAngle = true;
	}
	if (bDist == false && bSOG == false)
	{
		bAngle = false;
	}
	if (bAngle == true && bSOG == true && bDist == true)
	{
		return true;
	}
	return false;
}

void hgTargetManager::SameObject(hgTarget ais,hgTarget radar,double &dist,bool &bDist,bool &bAngle,bool &bSOG/*,double &dist,double &angle,double &SOG*/)//根据距离速度判断是否是同一物标
{
    dist = -1;
    bDist = false;
    bAngle = false;
    bSOG = false;
    if (radar.RadarID == "65535" && ais.RadarID != "65535")
    {
        return ;
    }
    hg::utils::PointLL l_aisCenter,l_radarCenter; 
    l_aisCenter = hg::utils::PointLL(ais.Lon,ais.Lat);
    l_radarCenter = hg::utils::PointLL(radar.Lon,radar.Lat);
    hg::utils::PointLL l_Yellow1(hgConfigManager::m_sSysConfig->m_Yellow1Lon,hgConfigManager::m_sSysConfig->m_Yellow1Lat/*119.38402,32.23198*/);
    hg::utils::PointLL l_Yellow2(hgConfigManager::m_sSysConfig->m_Yellow2Lon,hgConfigManager::m_sSysConfig->m_Yellow2Lat/*119.38351,32.23153*/);
    hg::utils::PointLL l_Yellow3(hgConfigManager::m_sSysConfig->m_Yellow3Lon,hgConfigManager::m_sSysConfig->m_Yellow3Lat/*119.38312,32.23084*/);
    hg::utils::PointLL l_112_1(hgConfigManager::m_sSysConfig->m_112_1Lon,hgConfigManager::m_sSysConfig->m_112_1Lat/*119.38154,32.22495*/);
    hg::utils::PointLL l_light(hgConfigManager::m_sSysConfig->m_lightLon,hgConfigManager::m_sSysConfig->m_lightLat);
    if (hg::utils::navutil::getDistance(l_radarCenter,l_Yellow1)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist//雷达时固定点的话 不参与融合
        || hg::utils::navutil::getDistance(l_radarCenter,l_Yellow2)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
        || hg::utils::navutil::getDistance(l_radarCenter,l_Yellow3)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
        || hg::utils::navutil::getDistance(l_radarCenter,l_112_1)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
        || hg::utils::navutil::getDistance(l_radarCenter,l_light)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist)
    {
        if (radar.SOG < hgConfigManager::m_sSysConfig->m_FixedSOG)
        {
            return ;
        }
//         if (ais.RadarID != radar.RadarID)
//         {
//             return ;
//         }
    }
    dist = hg::utils::navutil::getDistance(l_aisCenter,l_radarCenter)*NM2M;//米
    double l_SOG = abs(ais.SOG - radar.SOG);
    double l_angle = abs(ais.COG - radar.COG);
    if (l_angle > 180)
    {
        l_angle = 360 - l_angle;
    }
    if (l_SOG <= m_SOGDif)
    {
        bSOG = true;
    }
    if (dist < m_DisDif)
    {
        bDist = true;
    }
    if (l_angle < m_HDGDif)
    {
        bAngle = true;
    }
    if (bDist == false && bSOG == false)
    {
        bAngle = false;
    }
}

bool hgTargetManager::SameObjectD(hgTarget ais,hgTarget radar,double &dist,double &angle,double &SOG)
{
    if (radar.RadarID == "65535" && ais.RadarID != "65535")
    {
        return false;
    }
    hg::utils::PointLL l_aisCenter,l_radarCenter; 
    l_aisCenter = hg::utils::PointLL(ais.Lon,ais.Lat);
    l_radarCenter = hg::utils::PointLL(radar.Lon,radar.Lat);
//     hg::utils::PointLL l_Yellow1(119.38402,32.23198);
//     hg::utils::PointLL l_Yellow2(119.38351,32.23153);
//     hg::utils::PointLL l_Yellow3(119.38312,32.23084);
//     hg::utils::PointLL l_112_1(119.38154,32.22495);
//     if (hg::utils::navutil::getDistance(l_aisCenter,l_Yellow1)*NM2M < 30
//         || hg::utils::navutil::getDistance(l_aisCenter,l_Yellow2)*NM2M < 30
//         || hg::utils::navutil::getDistance(l_aisCenter,l_Yellow3)*NM2M < 30
//         || hg::utils::navutil::getDistance(l_aisCenter,l_112_1)*NM2M < 30)
//     {
//         if (ais.RadarID != radar.RadarID)
//         {
//             return false;
//         }
//     }
    dist = hg::utils::navutil::getDistance(l_aisCenter,l_radarCenter)*NM2M;//米
    SOG = abs(ais.SOG - radar.SOG);
    angle = abs(ais.COG - radar.COG);
    if (angle > 180)
    {
        angle = 360 - angle;
    }
    if (dist < 100/*m_DisDif*//* && SOG <= m_SOGDif && angle < m_HDGDif*/)
    {
        return true;
    }
    return false;
}

bool hgTargetManager::ChangeAIS(hgTarget newAis,hgTarget oldAis)
{
    hg::utils::PointLL l_newCenter,l_oldCenter; 
    l_newCenter = hg::utils::PointLL(newAis.Lon,newAis.Lat);
    l_oldCenter = hg::utils::PointLL(oldAis.Lon,oldAis.Lat);
    double l_dist = hg::utils::navutil::getDistance(l_newCenter,l_oldCenter)*NM2M;//米
    double l_SOG = abs(newAis.SOG - oldAis.SOG);
    double l_angle = abs(newAis.COG - oldAis.COG);
    if (l_dist < 20 /*&& l_SOG < 0.5 && l_angle == 0*/)
    {
        return false;
    }
    if (m_AlgorOwnMMSI.contains(newAis.MMSI))
    {
        qDebug () << "OwnShip jump " << newAis.MMSI << l_dist;
    }
    return true;
}

// void hgTargetManager::AssemblyTargetGPS(hgTarget &ais,hgSqlOperator& sqlOperator)
// {//融合检测
//     {
//         QMap<QString,hgResult>::iterator l_itRes = m_mapResult.begin();
//         bool l_find = false;
//         l_itRes = m_mapResult.find(ais.ID);
//         if (l_itRes != m_mapResult.end())
//         {
//             if (l_itRes->MMSI == ais.MMSI)
//             {
//                 l_find = true;
// 
//                 if (l_itRes->Count >= 9)
//                 {
//                     if (l_itRes->Count == 9)
//                     {
//                         AddFuaeResult(sqlOperator,l_itRes.value(),true,time(NULL));
//                     }
//                     mymap<QString,hgTarget>::iterator l_it = m_mapTarget.find(l_itRes->MMSI);
//                     mymap<QString,hgTarget>::iterator l_itRadar = m_mapRadar.find(l_itRes->RadarGUID);
//                     if (l_it != m_mapTarget.end())
//                     {
// 
//                         if (l_it->RadarMissing == true)
//                         {
//                             ais.Result = AIS_FUSE;
//                         }
//                         else
//                         {
//                             if (l_itRadar != m_mapRadar.end())
//                             {
//                                 ais.RadarGUID = l_itRes->RadarGUID;
//                                 ais.RadarID = l_itRes->RadarID;
// 
//                                 ais.Lat = l_itRadar->Lat;
//                                 ais.Lon = l_itRadar->Lon;
//                                 ais.COG = l_itRadar->COG;
//                                 ais.SOG = l_itRadar->SOG;
//                                 ais.Reserved = l_itRadar->Reserved;
//                                 ais.Rng = l_itRadar->Rng;
//                                 ais.RadarBrg = l_itRadar->RadarBrg;
//                                 ais.Spd = l_itRadar->Spd;
//                                 ais.Crs = l_itRadar->Crs;
//                                 ais.Scans = l_itRadar->Scans;
//                                 ais.Flags = l_itRadar->Flags;
//                                 ais.Result = AIS_RADAR_FUSE;
//                             }
//                         }
// 
//                     }
//                     {
//                         l_it = m_mapTarget.find(l_itRes->RadarGUID);
//                         if (l_it != m_mapTarget.end())
//                         {
//                             m_mapTarget.erase(l_it);
//                         }
//                     }
//                     l_itRes->Count = 10;
//                 }
//                 else  //l_itRes->Count < 9
//                 {
//                     //位置比对
//                     ais.Result = AIS_FUSE;
//                     hg::utils::PointLL l_aisCenter,l_mapCenter; 
//                     double l_distance,l_angle,l_speed,l_AvAngle;
//                     l_aisCenter.setLat(ais.Lat);
//                     l_aisCenter.setLon(ais.Lon);
//                     mymap<QString,hgTarget>::iterator l_it = m_mapTarget.find(l_itRes->RadarGUID);
//                     if (l_it != m_mapTarget.end())
//                     {
//                         l_mapCenter.setLat(l_it->Lat);
//                         l_mapCenter.setLon(l_it->Lon);
//                         l_distance = hg::utils::navutil::getDistance(l_aisCenter,l_mapCenter)*NM2M;
//                         l_angle = abs(l_it->COG - ais.COG);
//                         l_speed = abs(l_it->SOG - ais.SOG);
//                         l_AvAngle = abs(l_itRes->AvCog - l_angle);
//                         if (l_distance < COM_DISTANCE && l_speed <= COM_SPEED /*&& l_AvAngle <= COM_COG*/)
//                         {
//                             l_itRes->Count++;
//                             l_itRes->AvCog = (l_itRes->AvCog * l_itRes->Count + l_angle) / (l_itRes->Count + 1);
//                         }
//                         else
//                         {
//                             m_mapResult.erase(l_itRes);
//                         }
//                     }
//                 }
//                 ais.Source = FUSE_DATA;
//                 m_mapTarget.insert(ais.ID,ais);
//             }
//         }
//         if (l_find == false) //id，mmsi未匹配过
//         {
//             hg::utils::PointLL l_aisCenter,l_mapCenter; 
//             double l_distance,l_angle,l_speed;
//             QMap<double,hgResult> l_tempMap;
//             l_aisCenter.setLat(ais.Lat);
//             l_aisCenter.setLon(ais.Lon);
//             mymap<QString,hgTarget>::iterator l_it = m_mapTarget.begin();
//             for (l_it; l_it != m_mapTarget.end(); ++l_it)
//             {
//                 if (l_it->MMSI == "UnKnow")
//                 {
//                     l_mapCenter.setLat(l_it->Lat);
//                     l_mapCenter.setLon(l_it->Lon);
//                     l_distance = hg::utils::navutil::getDistance(l_aisCenter,l_mapCenter)*NM2M;
//                     l_angle = abs(l_it->COG - ais.COG);
//                     l_speed = abs(l_it->SOG - ais.SOG);
//                     if (l_distance < 1000 && l_speed <= 2)
//                     {
//                         hgResult l_result;
//                         l_result.ID = ais.MMSI;
//                         l_result.MMSI = ais.MMSI;
//                         l_result.RadarGUID = l_it->RadarGUID;
//                         l_result.RadarID = l_it->RadarID;
//                         l_result.Count = 0;
//                         l_tempMap.insert(l_distance,l_result); 
//                         l_result.AvCog = abs(ais.COG - m_mapTarget.find(l_result.RadarGUID)->COG);
//                     }
//                 }
//             }
//             if (l_tempMap.size() > 0)
//             {
//                 m_mapResult.insert(l_tempMap.begin().value().ID,l_tempMap.begin().value());
//             }
//             ais.Source = FUSE_DATA;
//             ais.Result = AIS_FUSE; 
//             m_mapTarget.insert(ais.ID,ais);
//         }
// 
//     }
// }

void hgTargetManager::AddRadarData(ArpaTargetPack &msg,hgTarget &target)
{

    //mymap<QString,hgTarget>::iterator l_it = m_mapTarget.begin();
    if (msg.number() == -1)
    {
        m_RadarList.clear();
        return ;
    }
    if (msg.number() == -2)
    {
        mymap<QString,hgTarget>::iterator l_itAis = m_mapAis.begin();
        while (l_itAis != m_mapAis.end()  )
        {
            if (!m_RadarList.contains(l_itAis->MMSI))
            {
                if (m_GPSMMSI.contains(l_itAis->MMSI))
                {
                    l_itAis++;
                    continue;
                }
                if (l_itAis->Simulation == true)
                {
                    l_itAis++;
                    continue;
                }
                l_itAis = m_mapAis.erase(l_itAis);
                continue;
            }
            l_itAis++;
        }
        mymap<QString,hgTarget>::iterator l_itRadar = m_mapRadar.begin();
        while (l_itRadar != m_mapRadar.end()  )
        {
            if (m_RadarList.contains(l_itRadar->RadarGUID))
            {
            }
            else
            {
                l_itRadar = m_mapRadar.erase(l_itRadar);
                continue;
            }
            l_itRadar++;
        }
        QMap<QString,hgResult>::iterator l_itRes = m_mapResult.begin();
        while (l_itRes != m_mapResult.end()  )
        {
//             if (m_RadarList.contains(l_itRes->ID) && m_RadarList.contains(l_itRes->MMSI))
//             {
//             }
//             else if (m_RadarList.contains(l_itRes->ID) && m_GPSMMSI.contains(l_itRes->MMSI))
//             {
//             }
            if (m_RadarList.contains(l_itRes->RadarID))
            {
            }
            else
            {
                qDebug () << "Cancle Fuse" << l_itRes->RadarID << "Not Find";
                l_itRes = m_mapResult.erase(l_itRes);
                continue;
            }
            l_itRes++;
        }
        mymap<QString,hgTarget>::iterator l_itTarget = m_mapTarget.begin();
        while (l_itTarget != m_mapTarget.end()  )
        {
            if (l_itTarget->Simulation == true)
            {
                l_itTarget++;
                continue;
            }
            if (m_RadarList.contains(l_itTarget->ID))
            {
            }
            else
            {
                if (m_GPSMMSI.contains(l_itTarget->MMSI))
                {
                }
                else
                {
                    if (l_itTarget->Result == AIS_RADAR_FUSE 
                        && m_mapResult.contains(l_itTarget->ID))
                    {
                    }
                    else
                    {
                        l_itTarget = m_mapTarget.erase(l_itTarget);
                        continue;
                    }
                }
            }
            l_itTarget++;
        }
        QMap<QString,QString>::iterator l_itRadarAis = m_mapRadarAis.begin();
        while ( l_itRadarAis != m_mapRadarAis.end())
        {
            if (m_RadarList.contains(l_itRadarAis.key()))
            {
                l_itRadarAis++;
            }
            else
            {
                l_itRadarAis = m_mapRadarAis.erase(l_itRadarAis);
            }
        }
        return ;
    }

    InitRadarData(msg,target);

    if (target.Spd == -1 || target.Crs == -1 || target.SOG == -1 || target.COG == -1)
    {
        return;
    }

    if (target.Source == RADAR_AIS_DATA)  //RADAR_AIS_DATA
    {
        m_mapAisRadar.insert(target.MMSI,target.RadarID);
        //m_mapAis.insert(target.ID,target);融合结束在插入
        m_RadarList.push_back(target.ID);
        return;
    } 

	UpdateRadarData(msg,target);
    m_RadarList.push_back(target.ID);
    {
        target.Source = FUSE_DATA;
        target.RadarID = target.RadarID;
        target.Result = RADAR_FUSE;
        target.MMSI = "UnKnow";
        target.RadarGUID = target.ID;

        QMap<QString,hgResult>::iterator l_itRes = m_mapResult.begin();
        bool l_find = false;
        for (l_itRes; l_itRes != m_mapResult.end(); ++l_itRes)
        {
            if (target.ID == l_itRes->RadarGUID && l_itRes->DisCount >= m_DisSuccess)
            {
                l_find = true;
                mymap<QString,hgTarget>::iterator l_it = m_mapTarget.find(l_itRes->ID);
                if (l_it != m_mapTarget.end())
                {
                    if (m_GPSMMSI.contains(l_itRes->ID))
                    {
                        l_it->RadarGUID = target.RadarGUID;
                        l_it->RadarID = target.RadarID;
						l_it->Result = AIS_RADAR_FUSE;
						if (m_GPSMMSIHdg.contains(target.MMSI) && m_GPSMMSIPos.contains(target.MMSI))
						{

						}
						else if (m_GPSMMSIPos.contains(target.MMSI) == false)
						{
							l_it->Lat = target.Lat;
							l_it->Lon = target.Lon;
						}
						else if (m_GPSMMSIHdg.contains(target.MMSI) == false)
						{
							l_it->HDG = target.HDG;
						}
                    }
                    else
                    {
                        l_it->RadarGUID = target.RadarGUID;
                        l_it->RadarID = target.RadarID;
                        l_it->Lat = target.Lat;
                        l_it->Lon = target.Lon;
                        l_it->COG = target.COG;
						l_it->HDG = target.HDG;
                        l_it->SOG = target.SOG;
                        l_it->ReportTicks = target.ReportTicks;
                        l_it->ReportPeriod = target.ReportPeriod;
                        l_it->ReportInterval = target.ReportInterval;
                        l_it->RadarInterval = 0;
                        l_it->RadarMissing = target.RadarMissing;
						l_it->Result = AIS_RADAR_FUSE;
						l_it->DimA = target.DimA;
						l_it->DimB = target.DimB;
						l_it->DimC = target.DimC;
						l_it->DimD = target.DimD;
						l_it->Length = target.Length;
						l_it->Width = target.Width;
						l_it->SetShipSize = target.SetShipSize;
                        m_RadarList.push_back(l_it->MMSI);
                    }
                    if (l_it->Result == AIS_RADAR_FUSE && l_it->RadarID.toInt() > 1000)
                    {
                        qDebug () << "+++++" << 1;
                    }
                }
            }
        }
        if (l_find == false)
        {
            m_mapTarget.insert(target.ID,target);
        }
    }

}
void hgTargetManager::AddRadarAISData(ArpaTargetPack &msg,hgTarget &target)
{
    if (msg.number() == -1)
    {
        m_RadarList.clear();
        return ;
    }
    if (msg.number() == -2)
    {
        mymap<QString,hgTarget>::iterator l_itAis = m_mapAis.begin();
        while (l_itAis != m_mapAis.end()  )
        {
            if (!m_RadarList.contains(l_itAis->MMSI))
            {
                if (m_GPSMMSI.contains(l_itAis->MMSI))
                {
                    l_itAis++;
                    continue;
                }
                l_itAis = m_mapAis.erase(l_itAis);
                continue;
            }
            l_itAis++;
        }
        mymap<QString,hgTarget>::iterator l_itRadar = m_mapRadar.begin();
        while (l_itRadar != m_mapRadar.end()  )
        {
            if (m_RadarList.contains(l_itRadar->RadarID))
            {
            }
            else if (m_RadarList.contains(l_itRadar->RadarGUID))
            {
            }
            else
            {
                if (m_GPSMMSI.contains(l_itRadar->MMSI))
                {
                    l_itRadar++;
                    continue;
                }
                l_itRadar = m_mapRadar.erase(l_itRadar);
                continue;
            }
            l_itRadar++;
        }
        mymap<QString,hgTarget>::iterator l_itTarget = m_mapTarget.begin();
        int l_ais = 0;
        int l_radar = 0;
        int l_total = 0;
        int l_error = 0;
        QStringList l_AISGuse;
        QStringList l_RadarGuse;
        QStringList l_Fuse;
        while (l_itTarget != m_mapTarget.end()  )
        {
            if (l_itTarget->Result == AIS_FUSE)
            {
                if (!m_RadarList.contains(l_itTarget->MMSI))
                {
                    if (m_GPSMMSI.contains(l_itTarget->MMSI))
                    {
                        l_itTarget++;
                        l_ais++;
                        continue;
                    }
                    l_itTarget = m_mapTarget.erase(l_itTarget);
                    continue;
                }
                l_ais++;
            }
            else if (l_itTarget->Result == RADAR_FUSE)
            {
                l_radar++;
                if (!m_RadarList.contains(l_itTarget->RadarID))
                {
                    l_itTarget = m_mapTarget.erase(l_itTarget);
                    continue;
                }
            }
            else if (l_itTarget->Result == AIS_RADAR_FUSE)
            {
                l_total++;
            }
            l_itTarget++;
        }
		//qDebug () << m_RadarList.size() << l_radar << l_ais << l_total << m_mapTarget.size() << l_error;
        return ;
    }
    InitRadarAISData(msg,target);

//     if (target.Spd == -1 || target.Crs == -1 || target.SOG == -1 || target.COG == -1)
//     {
//         s_error++;
//         return;
//     }
    //UpdateRadarAISData(msg,target);

    {
        //qDebug  () << target.RadarID;
        if (target.Source == RADAR_AIS_DATA)
        {
            target.Result = AIS_FUSE;
            m_mapAisRadar.insert(target.MMSI,target.RadarID);
            m_RadarList.push_back(target.MMSI);
        }
        else if (target.Source == RADAR_RADAR_DATA)
        {
            target.Result = RADAR_FUSE;
						{
							hg::utils::PointLL l_aisCenter(target.Lon, target.Lat);
							hg::utils::PointLL l_Yellow1(hgConfigManager::m_sSysConfig->m_Yellow1Lon, hgConfigManager::m_sSysConfig->m_Yellow1Lat/*119.38402,32.23198*/);
							hg::utils::PointLL l_Yellow2(hgConfigManager::m_sSysConfig->m_Yellow2Lon, hgConfigManager::m_sSysConfig->m_Yellow2Lat/*119.38351,32.23153*/);
							hg::utils::PointLL l_Yellow3(hgConfigManager::m_sSysConfig->m_Yellow3Lon, hgConfigManager::m_sSysConfig->m_Yellow3Lat/*119.38312,32.23084*/);
							hg::utils::PointLL l_112_1(hgConfigManager::m_sSysConfig->m_112_1Lon, hgConfigManager::m_sSysConfig->m_112_1Lat/*119.38154,32.22495*/);
							hg::utils::PointLL l_light(hgConfigManager::m_sSysConfig->m_lightLon, hgConfigManager::m_sSysConfig->m_lightLat);
							if (hg::utils::navutil::getDistance(l_aisCenter, l_Yellow1)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
								|| hg::utils::navutil::getDistance(l_aisCenter, l_Yellow2)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
								|| hg::utils::navutil::getDistance(l_aisCenter, l_Yellow3)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
								|| hg::utils::navutil::getDistance(l_aisCenter, l_112_1)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
								|| hg::utils::navutil::getDistance(l_aisCenter, l_light)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist)
							{
								if (target.SOG < hgConfigManager::m_sSysConfig->m_FixedSOG)
								{
									vtsInfo << "Find buoy";
									target.DimA = 0;
									target.DimB = 1;
									target.DimC = 0;
									target.DimD = 1;
									target.Length = 1;
									target.Width = 1;
									target.SetShipSize = false;
									target.Result = RADAR_RADAR_DATA;
								}
							}
						}
            m_RadarList.push_back(target.RadarID);
        }
        target.RadarID = target.RadarID;
        if (target.MMSI == "0")
        {
            target.ID = target.RadarID;
        }
//         else if (m_AlgorOwnMMSI.contains(target.MMSI) && target.Source == RADAR_RADAR_DATA)
//         {
//             target.ID = target.RadarID;
//             target.MMSI = "0";
//         }
        else
        {
            target.ID = target.MMSI;
		    }
		for (int i = 0; i < m_GPSMMSI.size(); i++)
		{
			QString l_MMSI = m_GPSMMSI[i];
			mymap<QString,hgTarget>::iterator l_itTar = m_mapTarget.find(l_MMSI);
			if (l_itTar != m_mapTarget.end())
			{
				if (l_itTar->RadarID == target.RadarID && target.MMSI != l_itTar->MMSI)
				{
					l_itTar->RadarID = "";
				}
			}
		}
        if (hgConfigManager::m_sSysConfig->m_GPSOpen == 1 && m_GPSMMSI.contains(target.MMSI))
        {
			if (target.Source == RADAR_AIS_DATA)
			{
				return;
			}
			if (target.Source == RADAR_RADAR_DATA)
			{
				mymap<QString,hgTarget>::iterator l_itTar = m_mapTarget.find(target.MMSI);
				if (l_itTar != m_mapTarget.end())
				{
					l_itTar->RadarID = target.RadarID;
				}
			}
			if (m_GPSMMSIHdg.contains(target.MMSI) && m_GPSMMSIPos.contains(target.MMSI))
			{

			}
			else if (!m_GPSMMSIPos.contains(target.MMSI))
			{
				mymap<QString,hgTarget>::iterator l_it = m_mapAis.find(target.MMSI);
				if (l_it != m_mapAis.end())
				{
					l_it->Lat = target.Lat;
					l_it->Lon = target.Lon;
				}
				mymap<QString,hgTarget>::iterator l_itTar = m_mapTarget.find(target.MMSI);
				if (l_itTar != m_mapTarget.end())
				{
					l_itTar->Lat = target.Lat;
					l_itTar->Lon = target.Lon;
				}
			}
			else if (!m_GPSMMSIHdg.contains(target.MMSI))
			{
				mymap<QString,hgTarget>::iterator l_it = m_mapAis.find(target.MMSI);
				if (l_it != m_mapAis.end())
				{
					l_it->HDG = target.HDG;
					l_it->COG = target.COG;
				}
				mymap<QString,hgTarget>::iterator l_itTar = m_mapTarget.find(target.MMSI);
				if (l_itTar != m_mapTarget.end())
				{
					l_itTar->HDG = target.HDG;
					l_itTar->COG = target.COG;
				}
			}
			{
				mymap<QString,hgTarget>::iterator l_it = m_mapAis.find(target.MMSI);
				if (l_it != m_mapAis.end())
				{
					l_it->SOG = target.SOG;
					l_it->COG = target.COG;
				}
				mymap<QString,hgTarget>::iterator l_itTar = m_mapTarget.find(target.MMSI);
				if (l_itTar != m_mapTarget.end())
				{
					l_itTar->SOG = target.SOG;
					l_itTar->COG = target.COG;
				}
			}

            return ;
        }
        if (target.Source == RADAR_AIS_DATA)//AIS链表
        {
            mymap<QString,hgTarget>::iterator l_it = m_mapAis.find(target.MMSI);
            if (l_it == m_mapAis.end())
            {
                m_mapAis.insert(target.MMSI,target);
            }
            else
            {
                l_it->ID = target.ID;
                l_it->RadarID = target.RadarID;
                l_it->Reserved = target.Reserved;
                l_it->RadarBrg = target.RadarBrg;
                l_it->Rng = target.Rng;
                l_it->Brg = target.Brg;
                l_it->Spd = target.Spd;
                l_it->Crs = target.Crs;
                l_it->Scans = target.Scans;
                l_it->Flags = target.Flags;
                l_it->Lat = target.Lat;
                l_it->Lon = target.Lon;
                l_it->COG = target.COG;
                l_it->SOG = target.SOG;
                l_it->HDG = target.HDG;
                l_it->ReportPeriod = target.ReportTicks - l_it->ReportTicks;
                l_it->ReportTicks = target.ReportTicks;
                l_it->ReportInterval = target.ReportInterval;
                l_it->RadarInterval = 0;
				l_it->DimA = target.DimA;
				l_it->DimB = target.DimB;
				l_it->DimC = target.DimC;
				l_it->DimD = target.DimD;
				l_it->Length = target.Length;
				l_it->Width = target.Width;
				l_it->SetShipSize = target.SetShipSize;
            }
        }
        else if (target.Source == RADAR_RADAR_DATA)//雷达链表
        {
            if (target.MMSI == "0")//未融合
            {
                mymap<QString,hgTarget>::iterator l_itRadar = m_mapRadar.find(target.RadarID);
                if (l_itRadar == m_mapRadar.end())
                {
                    m_mapRadar.insert(target.RadarID, target);
                }
                else
                {
                    l_itRadar->ID = target.ID;
                    l_itRadar->RadarID = target.RadarID;
                    l_itRadar->Reserved = target.Reserved;
                    l_itRadar->RadarBrg = target.RadarBrg;
                    l_itRadar->Rng = target.Rng;
                    l_itRadar->Brg = target.Brg;
                    l_itRadar->Spd = target.Spd;
                    l_itRadar->Crs = target.Crs;
                    l_itRadar->Scans = target.Scans;
                    l_itRadar->Flags = target.Flags;
                    l_itRadar->Lat = target.Lat;
                    l_itRadar->Lon = target.Lon;
                    l_itRadar->COG = target.COG;
                    l_itRadar->SOG = target.SOG;
                    l_itRadar->HDG = target.HDG;
                    l_itRadar->ReportPeriod = target.ReportTicks - l_itRadar->ReportTicks;
                    l_itRadar->ReportTicks = target.ReportTicks;
                    l_itRadar->ReportInterval = target.ReportInterval;
					l_itRadar->RadarInterval = 0;
					l_itRadar->DimA = target.DimA;
					l_itRadar->DimB = target.DimB;
					l_itRadar->DimC = target.DimC;
					l_itRadar->DimD = target.DimD;
					l_itRadar->Length = target.Length;
					l_itRadar->Width = target.Width;
					l_itRadar->SetShipSize = target.SetShipSize;
                }
                l_itRadar = m_mapRadar.begin();
                while ( l_itRadar != m_mapRadar.end() )//删除融合数据
                {
                    if (l_itRadar->RadarGUID == target.RadarID && l_itRadar->RadarID != target.RadarID)
                    {
                        l_itRadar = m_mapRadar.erase(l_itRadar);
                        continue;
                    }
                    l_itRadar++ ;
                }
            }
            else//融合
            {
                mymap<QString,hgTarget>::iterator l_itRadar = m_mapRadar.find(target.MMSI);
                if (l_itRadar == m_mapRadar.end())
                {
                    hgTarget l_target;
                    mymap<QString,hgTarget>::iterator l_itAis = m_mapAis.find(target.MMSI);
                    if (l_itAis != m_mapAis.end())
                    {
                        l_target = l_itAis.value();
                        l_target.RadarGUID = target.RadarID;
                        m_mapRadar.insert(target.MMSI, l_target);
                    }
                    //hgTarget l_target = target;
                }
                else
                {
                    l_itRadar->ID = target.ID;
                    l_itRadar->RadarID = target.RadarID;
                    l_itRadar->Reserved = target.Reserved;
                    l_itRadar->RadarBrg = target.RadarBrg;
                    l_itRadar->RadarGUID = target.RadarID;
                    l_itRadar->Rng = target.Rng;
                    l_itRadar->Brg = target.Brg;
                    l_itRadar->Spd = target.Spd;
                    l_itRadar->Crs = target.Crs;
                    l_itRadar->Scans = target.Scans;
                    l_itRadar->Flags = target.Flags;
                    l_itRadar->Lat = target.Lat;
                    l_itRadar->Lon = target.Lon;
                    l_itRadar->COG = target.COG;
                    l_itRadar->SOG = target.SOG;
                    l_itRadar->HDG = target.HDG;
                    l_itRadar->ReportPeriod = target.ReportTicks - l_itRadar->ReportTicks;
                    l_itRadar->ReportTicks = target.ReportTicks;
                    l_itRadar->ReportInterval = target.ReportInterval;
					l_itRadar->RadarInterval = 0;
					l_itRadar->DimA = target.DimA;
					l_itRadar->DimB = target.DimB;
					l_itRadar->DimC = target.DimC;
					l_itRadar->DimD = target.DimD;
					l_itRadar->Length = target.Length;
					l_itRadar->Width = target.Width;
					l_itRadar->SetShipSize = target.SetShipSize;
                }
                l_itRadar = m_mapRadar.find(target.RadarID);
                if (l_itRadar != m_mapRadar.end())//删除未融合前数据
                {
                    m_mapRadar.erase(l_itRadar);
                }
                l_itRadar = m_mapRadar.begin();
                while ( l_itRadar != m_mapRadar.end() )//删除不同的数据（上次融合MMSI 和这次不同  保留这次删除上次）
                {
                    if (l_itRadar->RadarGUID == target.RadarID && l_itRadar->MMSI != target.MMSI)
                    {
                        //qDebug() << "Radar The last time is different from this time";
                        l_itRadar = m_mapRadar.erase(l_itRadar);
                        continue;
                    }
                    l_itRadar++ ;
                }
            }
        }
        /////总链表
        {
            if (target.Source == RADAR_AIS_DATA)//AIS 数据
            {
                mymap<QString,hgTarget>::iterator l_it = m_mapTarget.find(target.MMSI);
                if (l_it == m_mapTarget.end())//不存在插入
                {
                    hgTarget l_target = target;
                    l_target.Source = FUSE_DATA;
                    l_target.Result = AIS_FUSE;
                    m_mapTarget.insert(target.MMSI, l_target);
                }
                else//存在
                {
                    if (l_it->Result == AIS_RADAR_FUSE)//如果融合了则不刷数据
                    {
                        return;
                    }
                    else//未融合更新数据
                    {
                        l_it->ID = target.ID;
                        l_it->RadarID = target.RadarID;
                        l_it->RadarGUID = target.RadarID;
                        l_it->Reserved = target.Reserved;
                        l_it->RadarBrg = target.RadarBrg;
                        l_it->Rng = target.Rng;
                        l_it->Brg = target.Brg;
                        l_it->Spd = target.Spd;
                        l_it->Crs = target.Crs;
                        l_it->Scans = target.Scans;
                        l_it->Flags = target.Flags;
                        l_it->Lat = target.Lat;
                        l_it->Lon = target.Lon;
                        l_it->COG = target.COG;
                        l_it->SOG = target.SOG;
                        l_it->HDG = target.HDG;
                        l_it->ReportPeriod = target.ReportTicks - l_it->ReportTicks;
                        l_it->ReportTicks = target.ReportTicks;
                        l_it->ReportInterval = target.ReportInterval;
                        l_it->RadarInterval = 0;
                        l_it->Source = FUSE_DATA;
						l_it->Result = AIS_FUSE;
						l_it->DimA = target.DimA;
						l_it->DimB = target.DimB;
						l_it->DimC = target.DimC;
						l_it->DimD = target.DimD;
						l_it->Length = target.Length;
						l_it->Width = target.Width;
						l_it->SetShipSize = target.SetShipSize;
                    }
                }
            }
            else//雷达数据
            {
                if (target.MMSI == "0")//未融合
                {
                    mymap<QString,hgTarget>::iterator l_itTarget = m_mapTarget.find(target.RadarID);
                    if (l_itTarget == m_mapTarget.end())
                    {
                        hgTarget l_target = target;
                        l_target.RadarGUID = target.RadarID;
                        l_target.Source = FUSE_DATA;
                        l_target.Result = RADAR_FUSE;
                        m_mapTarget.insert(target.RadarID, target);
                    }
                    else
                    {
                        l_itTarget->ID = target.ID;
                        l_itTarget->MMSI = target.MMSI;
                        l_itTarget->RadarID = target.RadarID;
                        l_itTarget->RadarGUID = target.RadarID;
                        l_itTarget->Reserved = target.Reserved;
                        l_itTarget->RadarBrg = target.RadarBrg;
                        l_itTarget->Rng = target.Rng;
                        l_itTarget->Brg = target.Brg;
                        l_itTarget->Spd = target.Spd;
                        l_itTarget->Crs = target.Crs;
                        l_itTarget->Scans = target.Scans;
                        l_itTarget->Flags = target.Flags;
                        l_itTarget->Lat = target.Lat;
                        l_itTarget->Lon = target.Lon;
                        l_itTarget->COG = target.COG;
                        l_itTarget->SOG = target.SOG;
                        l_itTarget->HDG = target.HDG;
                        l_itTarget->ReportPeriod = target.ReportTicks - l_itTarget->ReportTicks;
                        l_itTarget->ReportTicks = target.ReportTicks;
                        l_itTarget->ReportInterval = target.ReportInterval;
                        l_itTarget->RadarInterval = 0;
                        l_itTarget->Source = FUSE_DATA;
						l_itTarget->Result = RADAR_FUSE;
						l_itTarget->DimA = target.DimA;
						l_itTarget->DimB = target.DimB;
						l_itTarget->DimC = target.DimC;
						l_itTarget->DimD = target.DimD;
						l_itTarget->Length = target.Length;
						l_itTarget->Width = target.Width;
						l_itTarget->SetShipSize = target.SetShipSize;
                    }
                    l_itTarget = m_mapTarget.begin();
                    while ( l_itTarget != m_mapTarget.end() )//删除融合数据
                    {
                        if (l_itTarget->RadarGUID == target.RadarID && l_itTarget->RadarID != target.RadarID)
                        {
                            l_itTarget = m_mapTarget.erase(l_itTarget);
                            continue;
                        }
                        l_itTarget++ ;
                    }
                }
                else
                {
                    mymap<QString,hgTarget>::iterator l_itTarget = m_mapTarget.find(target.MMSI);
                    if (l_itTarget == m_mapTarget.end())
                    {

                    }
                    else
                    {
                        l_itTarget->ID = target.ID;
                        l_itTarget->RadarID = target.RadarID;
                        l_itTarget->Reserved = target.Reserved;
                        l_itTarget->RadarBrg = target.RadarBrg;
                        l_itTarget->RadarGUID = target.RadarID;
                        l_itTarget->Rng = target.Rng;
                        l_itTarget->Brg = target.Brg;
                        l_itTarget->Spd = target.Spd;
                        l_itTarget->Crs = target.Crs;
                        l_itTarget->Scans = target.Scans;
                        l_itTarget->Flags = target.Flags;
                        l_itTarget->Lat = target.Lat;
                        l_itTarget->Lon = target.Lon;
                        l_itTarget->COG = target.COG;
                        l_itTarget->SOG = target.SOG;
                        l_itTarget->HDG = target.HDG;
                        l_itTarget->ReportPeriod = target.ReportTicks - l_itTarget->ReportTicks;
                        l_itTarget->ReportTicks = target.ReportTicks;
                        l_itTarget->ReportInterval = target.ReportInterval;
                        l_itTarget->RadarInterval = 0;
                        l_itTarget->Source = FUSE_DATA;
						l_itTarget->Result = AIS_RADAR_FUSE;
						l_itTarget->DimA = target.DimA;
						l_itTarget->DimB = target.DimB;
						l_itTarget->DimC = target.DimC;
						l_itTarget->DimD = target.DimD;
						l_itTarget->Length = target.Length;
						l_itTarget->Width = target.Width;
						l_itTarget->SetShipSize = target.SetShipSize;
                    }
                    l_itTarget = m_mapTarget.find(target.RadarID);
                    if (l_itTarget != m_mapTarget.end())//删除未融合前数据
                    {
                        m_mapTarget.erase(l_itTarget);
                    }
                    l_itTarget = m_mapTarget.begin();
                    while ( l_itTarget != m_mapTarget.end() )//删除不同的数据（上次融合MMSI 和这次不同  保留这次删除上次）
                    {
                        if (l_itTarget->RadarGUID == target.RadarID && l_itTarget->MMSI != target.MMSI)
                        {
                            qDebug() << "Target The last time is different from this time";
                            l_itTarget = m_mapTarget.erase(l_itTarget);
                            continue;
                        }
                        l_itTarget++ ;
                    }
                }
            }
        }

        if (target.Source == RADAR_RADAR_DATA )
        {
            m_mapRadarAis.insert(target.RadarID, target.MMSI);
        }
//         if (l_find == false)
//         {
//             m_mapTarget.insert(target.ID,target);
//         }
    }
}

void hgTargetManager::UpdateRadarData(ArpaTargetPack &msg,hgTarget &target)
{ 
    double l_dist,l_angle,l_SOG;
    mymap<QString,hgTarget>::iterator l_it = m_mapRadar.find(target.RadarID);
    if ( l_it != m_mapRadar.end() )
    {
        //target.ID = l_it->ID;
        if (SameObjectD(target, l_it.value(), l_dist, l_angle, l_SOG))
        {
            target.ReportPeriod = target.ReportTicks-l_it->ReportTicks;
        }
        else
        {
            target.ReportPeriod = target.ReportTicks-l_it->ReportTicks;
            auto l_iterResult = m_mapResult.begin();
            for ( ; l_iterResult != m_mapResult.end(); l_iterResult++)
            {
                if (l_iterResult->RadarID == target.RadarID)
                {
                    qDebug () << "<<<<  5   " << l_iterResult->MMSI << l_iterResult->RadarID << l_dist;
                    m_mapResult.erase(l_iterResult);
                    break;
                }
            }
        }
    }
    else
    {

    }
    target.ID = target.RadarID;
    target.RadarGUID = target.RadarID;
    m_mapRadar.insert(target.ID,target);
//     for (auto l_itDel = m_mapRadarDel.begin(); l_itDel != m_mapRadarDel.end();  )
//     {
//         if (target.ReportTicks-l_itDel->ReportTicks > 60)
//         {
//             l_itDel = m_mapRadarDel.erase(l_itDel);
//             continue;
//         }
//         if (SameObject(target, l_itDel.value(), l_dist, l_angle, l_SOG))
//         {
//             if (m_mapTarget.find(l_itDel->MMSI) != m_mapTarget.end())
//             {
//                 if ( !m_mapResult.contains(l_itDel->MMSI) )
//                 {
//                     hgResult l_result;
//                     l_result.ID = l_itDel->MMSI;
//                     l_result.MMSI = l_itDel->MMSI;
//                     l_result.RadarGUID = target.RadarGUID;
//                     l_result.RadarID = target.RadarID;
//                     l_result.Count = m_FuseCount;
// 
// 
//                     auto l_iterResult = m_mapResult.begin();
//                     bool l_RongHe = false;//是否被融合
//                     for ( ; l_iterResult != m_mapResult.end(); l_iterResult++)
//                     {
//                         if (l_iterResult->RadarGUID == l_result.RadarGUID)///判断此雷达是否被融合
//                         {
//                             l_RongHe = true;
//                         }
//                     }
//                     if (l_RongHe == false)
//                     {
//                         m_mapResult.insert(l_itDel->MMSI, l_result);
//                     }
// 
//                     //m_mapResult.insert(l_itDel->MMSI, l_result);
//                     l_itDel = m_mapRadarDel.erase(l_itDel);
//                     continue;
//                 }
//                 else
//                 {
//                     l_itDel = m_mapRadarDel.erase(l_itDel);
//                     continue;
//                 }
//             }
//             else
//             {
//                 l_itDel = m_mapRadarDel.erase(l_itDel);
//                 continue;
//             }
//         }
//         l_itDel++;
//     }
    return ;

    /////////////
    hg::utils::PointLL l_RecPoint;
    l_RecPoint.setLat(target.Lat);
    l_RecPoint.setLon(target.Lon);
    //雷达融合检测
    {
        bool l_findRadarID = false;
        mymap<QString,hgTarget>::iterator l_it = m_mapRadar.begin();
        for (l_it; l_it != m_mapRadar.end(); ++l_it)
        {
            if (l_it->RadarID == target.RadarID)
            {
                l_findRadarID = true;
                hg::utils::PointLL l_PrePoint;
                l_PrePoint.setLon(l_it->Lon/* + (target.ReportTicks-l_it->ReportTicks)*180.0*l_it->SOG/3600.0*sin(l_it->COG*3.14159/180)/(3.14159*3440.067*cos(l_it->Lat*3.14159/180.0))*/);
                l_PrePoint.setLat(l_it->Lat/* + (target.ReportTicks-l_it->ReportTicks)*l_it->SOG/3600.0*cos(l_it->COG*3.14159/180.0)/60.0*/);
                double l_diatance = hg::utils::navutil::getDistance(l_RecPoint,l_PrePoint) * NM2M;
                if (l_diatance < m_DisDif/*DISTANCE*/)
                {
                    target.ID = l_it->ID;
                    target.ReportPeriod = target.ReportTicks-l_it->ReportTicks;
                }
                else
                {
                    m_mapRadarDel.insert(l_it->ID,l_it.value());
                    m_mapRadar.erase(l_it);
                    FindRadarGUID(msg,target);
                    break;
                }
            }
        }

        if (l_findRadarID == false)
        {
            FindRadarGUID(msg,target);
        }
        
        m_mapRadar.insert(target.ID,target);
    }

}

// void hgTargetManager::UpdateRadarAISData(ArpaTargetPack &msg,hgTarget &target)
// {
//     hg::utils::PointLL l_RecPoint;
//     l_RecPoint.setLat(target.Lat);
//     l_RecPoint.setLon(target.Lon);
//     //雷达融合检测
//     {
//         bool l_findRadarID = false;
//         mymap<QString,hgTarget>::iterator l_it = m_mapRadar.begin();
//         for (l_it; l_it != m_mapRadar.end(); ++l_it)
//         {
//             if (l_it->RadarID == target.RadarID)
//             {
//                 l_findRadarID = true;
//                 hg::utils::PointLL l_PrePoint;
//                 l_PrePoint.setLon(l_it->Lon + (target.ReportTicks-l_it->ReportTicks)*180.0*l_it->SOG/3600.0*sin(l_it->COG*3.14159/180)/(3.14159*3440.067*cos(l_it->Lat*3.14159/180.0)));
//                 l_PrePoint.setLat(l_it->Lat + (target.ReportTicks-l_it->ReportTicks)*l_it->SOG/3600.0*cos(l_it->COG*3.14159/180.0)/60.0);
//                 double l_diatance = hg::utils::navutil::getDistance(l_RecPoint,l_PrePoint) * NM2M;
//                 if (l_diatance < DISTANCE)
//                 {
//                     target.ID = l_it->ID;
//                     target.ReportPeriod = target.ReportTicks-l_it->ReportTicks;
//                 }
//                 else
//                 {
//                     m_mapRadarDel.insert(l_it->ID,l_it.value());
//                     m_mapRadar.erase(l_it);
//                     FindRadarGUID(msg,target);
//                     break;
//                 }
//             }
//         }
// 
//         if (l_findRadarID == false)
//         {
//             FindRadarGUID(msg,target);
//         }
// 
//         m_mapRadar.insert(target.ID,target);
//     }
// }

void hgTargetManager::FindRadarGUID(ArpaTargetPack &msg, hgTarget& target)
{
    target.ID = target.RadarID;
    return ;
    hg::utils::PointLL l_RecPoint;
    l_RecPoint.setLat(target.Lat);
    l_RecPoint.setLon(target.Lon);
    QMap<double,hgTarget> l_dis;
    for (auto l_it = m_mapRadarDel.begin(); l_it != m_mapRadarDel.end(); )
    {
        if (target.ReportTicks-l_it->ReportTicks > 20)
        {
            l_it = m_mapRadarDel.erase(l_it);
            continue;
        }
        hg::utils::PointLL l_PrePoint;
        l_PrePoint.setLon(l_it->Lon + (target.ReportTicks-l_it->ReportTicks)*180.0*l_it->SOG/3600.0*sin(l_it->COG*3.14159/180)/(3.14159*3440.067*cos(l_it->Lat*3.14159/180.0)));
        l_PrePoint.setLat(l_it->Lat + (target.ReportTicks-l_it->ReportTicks)*l_it->SOG/3600.0*cos(l_it->COG*3.14159/180.0)/60.0);
        double l_diatance = hg::utils::navutil::getDistance(l_RecPoint,l_PrePoint) * NM2M;
        if (l_diatance < m_DisDif/*DISTANCE*/)
        {
            l_dis.insert(l_diatance,l_it.value());
        }
        ++l_it;
    }
    if (l_dis.size() == 0)
    {
        target.ID = QUuid::createUuid().toString();
        target.ReportPeriod = 0;
    } 
    else if (l_dis.size() == 1)
    {
        target.ID = l_dis.first().ID;
        target.ReportPeriod = 0;
    }
    else
    {
        QMap<double,hgTarget>::iterator l_DisIt = l_dis.begin();
        bool l_find = false;
        for (l_DisIt; l_DisIt != l_dis.end(); ++l_DisIt)
        {
            if (abs(target.COG - l_DisIt->COG) <= m_HDGDif/*DIF_COG*/ && abs(target.SOG - l_DisIt->SOG) <= m_SOGDif/*DIF_SOG*/)
            {
                l_find = true;
                target.ID = l_DisIt->ID;
                target.ReportPeriod = 0;
            }              
        }
        if (l_find == false)
        {
            target.ID = l_dis.first().ID;
            target.ReportPeriod = 0;
        }
    }
}

void hgTargetManager::InitRadarData(ArpaTargetPack &msg,hgTarget &target)
{
    target.RadarID = QString::number(msg.number());
    target.MMSI = "";

    target.ReportTicks = time(NULL);
    target.ReportInterval = 0;
    target.RadarInterval = 0;
    target.RadarMissing = false;
    target.Source = ((quint8)msg.flags() & 128 )? RADAR_AIS_DATA : RADAR_RADAR_DATA;
    if (target.Source == RADAR_AIS_DATA)
    {
		target.ID = QString::number(msg.scans());
        target.MMSI = QString::number(msg.scans());//msg.scans();
    }
    if (target.Source == RADAR_RADAR_DATA)
    {
        m_mapRadarAis.insert(target.RadarID,QString::number(msg.scans()));
    }

    target.Reserved = msg.reserved();
    target.Rng = msg.rng();
	target.RadarBrg = msg.brg()*0.0878;
	int l_WH = msg.orientation_size();
	int l_width,l_len = 0;
	double l_hdg = (l_WH & 0x00000fff)*0.1;
	l_len = (l_WH & 0x003ff000) >> 12;
	l_width = (l_WH & 0xffc00000) >>22;
//     target.Spd = msg.spd() == 0xffff ? -1 : msg.spd()*0.1;
//     target.Crs = msg.crs() == 0xffff ? -1 : msg.crs()*0.1;
    target.Scans = msg.scans();
    target.Flags = msg.flags();
    target.SOG = msg.sog() == 0xffff ? -1 : msg.sog()*0.1;
	target.COG = msg.cog() == 0xffff ? -1 : msg.cog()*0.1;
	target.HDG = (l_hdg == 0 ? target.COG : l_hdg);//msg.cog() == 0xffff ? -1 : msg.cog()*0.1;
    target.Lat = msg.latitude()/600000.0;
    target.Lon = msg.longitude()/600000.0;//  [8/1/2017 LianXinDuan] 模拟器上测试
    target.MID = -1;
    target.ShipName = "";
    target.ChShipName = "";
    target.CallSign = "";
    target.Class = AIS_CLASS_A;
    target.IMO = -1;
    target.ShipType = "";
    target.EquipmentType = -1;
    target.DimA = hgConfigManager::m_sSysConfig->m_dShipLength * 0.75;
    target.DimB = hgConfigManager::m_sSysConfig->m_dShipLength * 0.25;
    target.DimC = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.25;
    target.DimD = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.75;
    target.Length = hgConfigManager::m_sSysConfig->m_dShipLength;
	target.Width = hgConfigManager::m_sSysConfig->m_dShipWidth;
	target.SetShipSize = true;
	if (l_len > 0 && l_width > 0)
	{
		int l_a = l_len /2;
		int l_b = l_len - l_a;
		int l_c  = l_width/2;
		int l_d = l_width - l_c;
		target.DimA = l_a;
		target.DimB = l_b;
		target.DimC = l_c;
		target.DimD = l_d;
		target.Length = l_len;
		target.Width = l_width;
		target.SetShipSize = false;
	}
    target.Destination = "";
    target.ETA_Mo = -1;
    target.ETA_Day = -1;
    target.ETA_Min = -1;
    target.Draft = -1;
    target.Simulation = false;
    target.Note = "";
    target.Nationality = "";
    target.NavStatus = -1;
    target.ROTAIS = -1;
    target.utc_hour = -1;
    target.utc_min = -1;
    target.utc_sec = -1;
    target.Range_NM = -1;
    target.Brg = -1;
    target.SyncState = -1;
    target.SlotTO = -1;
    target.CPA_Valid = false;
    target.TCPA = -1;
    target.CPA = -1;
    target.Missing = false;
	target.OwnShip = false;

    if (target.Source == RADAR_RADAR_DATA)
    {
        hg::utils::PointLL l_aisCenter(target.Lon,target.Lat);
        hg::utils::PointLL l_Yellow1(hgConfigManager::m_sSysConfig->m_Yellow1Lon,hgConfigManager::m_sSysConfig->m_Yellow1Lat/*119.38402,32.23198*/);
        hg::utils::PointLL l_Yellow2(hgConfigManager::m_sSysConfig->m_Yellow2Lon,hgConfigManager::m_sSysConfig->m_Yellow2Lat/*119.38351,32.23153*/);
        hg::utils::PointLL l_Yellow3(hgConfigManager::m_sSysConfig->m_Yellow3Lon,hgConfigManager::m_sSysConfig->m_Yellow3Lat/*119.38312,32.23084*/);
        hg::utils::PointLL l_112_1(hgConfigManager::m_sSysConfig->m_112_1Lon,hgConfigManager::m_sSysConfig->m_112_1Lat/*119.38154,32.22495*/);
        hg::utils::PointLL l_light(hgConfigManager::m_sSysConfig->m_lightLon,hgConfigManager::m_sSysConfig->m_lightLat);
        if (hg::utils::navutil::getDistance(l_aisCenter,l_Yellow1)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
            || hg::utils::navutil::getDistance(l_aisCenter,l_Yellow2)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
            || hg::utils::navutil::getDistance(l_aisCenter,l_Yellow3)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
            || hg::utils::navutil::getDistance(l_aisCenter,l_112_1)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist
            || hg::utils::navutil::getDistance(l_aisCenter,l_light)*NM2M < hgConfigManager::m_sSysConfig->m_FixedDist)
        {
            if (target.SOG < hgConfigManager::m_sSysConfig->m_FixedSOG)
            {
                target.DimA = 0;
                target.DimB = 1;
                target.DimC = 0;
                target.DimD = 1;
                target.Length = 1;
                target.Width = 1;
                target.SetShipSize = false;
            }
        }
     }
//     //if (target.Source == RADAR_AIS_DATA)
//     {
//         if (m_mapTarget.find(target.MMSI) != m_mapTarget.end())
//         {
//             hgTarget l_static = m_mapTarget.find(target.MMSI).value();
//             target.IMO = l_static.IMO;
//             target.CallSign = l_static.CallSign;
//             target.ShipName = l_static.ShipName;
//             target.Destination = l_static.Destination;
//             target.DimA = l_static.DimA;
//             target.DimB = l_static.DimB;
//             target.DimC = l_static.DimC;
//             target.DimD = l_static.DimD;
//             target.Length = l_static.Length;
//             target.Width = l_static.Width;
//             target.SetShipSize = l_static.SetShipSize;
//             target.ReportPeriod = l_static.ReportTicks - target.ReportTicks;
//         }
//     }
	if (target.Source == RADAR_AIS_DATA)
	{
		if (m_mapRadarStatic.contains(target.MMSI) && !m_mapResult.contains(target.MMSI))
		{
			hgTarget l_static = m_mapRadarStatic.find(target.MMSI).value();
			target.IMO = l_static.IMO;
			target.CallSign = l_static.CallSign;
			target.ShipName = l_static.ShipName;
			target.Destination = l_static.Destination;
			target.DimA = l_static.DimA;
			target.DimB = l_static.DimB;
			target.DimC = l_static.DimC;
			target.DimD = l_static.DimD;
			target.Length = l_static.Length;
			target.SetShipSize = l_static.SetShipSize;
		}
	}
    if (target.Source == RADAR_AIS_DATA)
    {
        if (m_mapShipData.contains(target.MMSI))
        {
            hgTarget l_target = m_mapShipData.find(target.MMSI).value();
            target.IMO = l_target.IMO;
            target.ShipName = l_target.ShipName;
            target.DimA = l_target.DimA;
            target.DimB = l_target.DimB;
            target.DimC = l_target.DimC;
            target.DimD = l_target.DimD;
            target.Length = l_target.DimA + l_target.DimB;
            target.Width = l_target.DimC + l_target.DimD; 
            target.SetShipSize = false;


            target.CallSign = l_target.CallSign;
            target.Destination = l_target.Destination;
            target.EquipmentType = l_target.EquipmentType;
            target.ETA_Mo = l_target.ETA_Mo;
            target.ETA_Day = l_target.ETA_Day;
            target.ETA_Hr = l_target.ETA_Hr;
            target.ETA_Min = l_target.ETA_Min;
			target.Draft = l_target.Draft;
        }
        if (m_mapStatic.contains(target.MMSI))
        {
            hgTarget l_target = m_mapStatic.find(target.MMSI).value();
            {
                target.IMO = l_target.IMO;
                target.ShipName = l_target.ShipName;
                target.ShipType = l_target.ShipType;
                target.DimA = l_target.DimA;
                target.DimB = l_target.DimB;
                target.DimC = l_target.DimC;
                target.DimD = l_target.DimD;
                target.Length = l_target.Length;
                target.Width = l_target.Width;
                target.SetShipSize = l_target.SetShipSize;
            }
            target.CallSign = l_target.CallSign;
            target.Destination = l_target.Destination;
            target.EquipmentType = l_target.EquipmentType;
            target.ETA_Mo = l_target.ETA_Mo;
            target.ETA_Day = l_target.ETA_Day;
            target.ETA_Hr = l_target.ETA_Hr;
            target.ETA_Min = l_target.ETA_Min;
            target.Draft = l_target.Draft;

            target.SetShipSize = l_target.SetShipSize;

            target.ChShipName = l_target.ChShipName;
            target.Nationality = l_target.Nationality;
			target.Note = l_target.Note;
        }
	}
}


void hgTargetManager::InitRadarAISData(ArpaTargetPack &msg,hgTarget &target)
{
    target.RadarID = QString::number(msg.number());
    target.MMSI = QString::number(msg.scans());//msg.scans();

    target.ReportTicks = time(NULL);
    target.ReportInterval = 0;
    target.RadarInterval = 0;
    target.RadarMissing = false;
		target.Source = ((int)msg.number() < 10000) ? RADAR_RADAR_DATA : RADAR_AIS_DATA;

    target.Reserved = msg.reserved();
    target.Rng = msg.rng();
	target.RadarBrg = msg.brg()*0.0878;
	//     target.Spd = msg.spd() == 0xffff ? -1 : msg.spd()*0.1;
	//     target.Crs = msg.crs() == 0xffff ? -1 : msg.crs()*0.1;
    target.Scans = msg.scans();
    target.Flags = msg.flags();
    target.SOG = msg.sog() == 0xffff ? -1 : msg.sog()*0.1;
	target.COG = msg.cog() == 0xffff ? -1 : msg.cog()*0.1;
	int l_WH = msg.orientation_size();
	int l_width,l_len = 0;
	double l_hdg = (l_WH & 0x00000fff)*0.1;
	l_len = (l_WH & 0x003ff000) >> 12;
	l_width = (l_WH & 0xffc00000) >>22;
	target.HDG = (l_hdg == 0 ? target.COG : l_hdg);//msg.cog() == 0xffff ? -1 : msg.cog()*0.1;
    target.Lat = msg.latitude()/600000.0;
    target.Lon = msg.longitude()/600000.0;//  [8/1/2017 LianXinDuan] 模拟器上测试
    target.MID = -1;
    target.ShipName = "";
    target.ChShipName = "";
    target.CallSign = "";
    target.Class = AIS_CLASS_A;
    target.IMO = -1;
    target.ShipType = "";
    target.EquipmentType = -1;
    target.DimA = hgConfigManager::m_sSysConfig->m_dShipLength * 0.75;
    target.DimB = hgConfigManager::m_sSysConfig->m_dShipLength * 0.25;
	target.DimC = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.25;
    target.DimD = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.75;
    target.Length = hgConfigManager::m_sSysConfig->m_dShipLength;
	target.Width = hgConfigManager::m_sSysConfig->m_dShipWidth;
	target.SetShipSize = true;
	if (l_len > 0 && l_width > 0)
	{
		int l_a = l_len /2;
		int l_b = l_len - l_a;
		int l_c  = l_width/2;
		int l_d = l_width - l_c;
		target.DimA = l_a;
		target.DimB = l_b;
		target.DimC = l_c;
		target.DimD = l_d;
		target.Length = l_len;
		target.Width = l_width;
		target.SetShipSize = false;
	}
    target.Destination = "";
    target.ETA_Mo = -1;
    target.ETA_Day = -1;
    target.ETA_Min = -1;
    target.Draft = -1;
    target.Simulation =	false;
    target.Note = "";
    target.Nationality = "";
    target.CPA = -1;
    target.Missing = false;
    target.OwnShip = false;
	{
		if (m_mapRadarStatic.contains(target.MMSI))
		{
			hgTarget l_target = m_mapRadarStatic.find(target.MMSI).value();
			target.IMO = l_target.IMO;
			target.CallSign = l_target.CallSign;
			target.ShipName = l_target.ShipName;
// 			target.DimA = l_target.DimA;
// 			target.DimB = l_target.DimB;
// 			target.DimC = l_target.DimC;
// 			target.DimD = l_target.DimD;
// 			target.Length = l_target.DimA + l_target.DimB;
// 			target.Width = l_target.DimC + l_target.DimD; 
// 			target.SetShipSize = false;
		}
	}
    //if (target.Source == RADAR_AIS_DATA)
    {
        bool l_findCsv = false,l_findStatic = false;
        if (m_mapShipData.contains(target.MMSI))
        {
            l_findCsv = true;
            hgTarget l_target = m_mapShipData.find(target.MMSI).value();
            target.IMO = l_target.IMO;
            target.ShipName = l_target.ShipName;
            target.DimA = l_target.DimA;
            target.DimB = l_target.DimB;
            target.DimC = l_target.DimC;
            target.DimD = l_target.DimD;
            target.Length = l_target.DimA + l_target.DimB;
            target.Width = l_target.DimC + l_target.DimD; 
            target.SetShipSize = false;


            target.CallSign = l_target.CallSign;
            target.Destination = l_target.Destination;
            target.EquipmentType = l_target.EquipmentType;
            target.ETA_Mo = l_target.ETA_Mo;
            target.ETA_Day = l_target.ETA_Day;
            target.ETA_Hr = l_target.ETA_Hr;
            target.ETA_Min = l_target.ETA_Min;
            target.Draft = l_target.Draft;
        }
        if (m_mapStatic.contains(target.MMSI))
        {
            l_findStatic = true;
            hgTarget l_target = m_mapStatic.find(target.MMSI).value();
            if (l_findCsv == false)
            {
                target.IMO = l_target.IMO;
                target.ShipName = l_target.ShipName;
                target.ShipType = l_target.ShipType;
                target.DimA = l_target.DimA;
                target.DimB = l_target.DimB;
                target.DimC = l_target.DimC;
                target.DimD = l_target.DimD;
                target.Length = l_target.Length;
                target.Width = l_target.Width;
                target.SetShipSize = l_target.SetShipSize;
            }
            target.CallSign = l_target.CallSign;
            target.Destination = l_target.Destination;
            target.EquipmentType = l_target.EquipmentType;
            target.ETA_Mo = l_target.ETA_Mo;
            target.ETA_Day = l_target.ETA_Day;
            target.ETA_Hr = l_target.ETA_Hr;
            target.ETA_Min = l_target.ETA_Min;
            target.Draft = l_target.Draft;

            target.SetShipSize = l_target.SetShipSize;

            target.ChShipName = l_target.ChShipName;
            target.Nationality = l_target.Nationality;
            target.Note = l_target.Note;
        }
	}
}

void hgTargetManager::AddTarget(hgAisMessage &ais)
{
    hgTarget l_Ais;

    l_Ais.ID = QString::fromStdString(ais.id());
    l_Ais.RadarID = QString::fromStdString(ais.radarid());
    l_Ais.MMSI = QString::fromStdString(ais.mmsi());
    l_Ais.Source = ais.source();
    l_Ais.ShipName = QString::fromStdString(ais.shipname());
    //l_Ais.ShipName.replace(QRegExp("@"), "");

    l_Ais.CallSign = QString::fromStdString(ais.callsign());
    //l_Ais.CallSign.replace(QRegExp("@"), "");
    l_Ais.IMO = ais.imo();
    l_Ais.Class = (hgAisClass)ais.class_();
    l_Ais.ShipType = QString::fromStdString(ais.shiptype());
    l_Ais.DimA = ais.dima();
    l_Ais.DimB = ais.dimb();
    l_Ais.DimC = ais.dimc();
    l_Ais.DimD = ais.dimd();
    l_Ais.Destination = QString::fromStdString(ais.destination());
    //l_Ais.Destination.replace(QRegExp("@"), "");
    l_Ais.ETA_Mo = ais.eta_mo();
    l_Ais.ETA_Day = ais.eta_day();
    l_Ais.ETA_Hr = ais.eta_hr();
    l_Ais.ETA_Min = ais.eta_min();

    l_Ais.Draft = ais.draft();
    l_Ais.NavStatus = ais.navstatus();
    l_Ais.Lon = ais.lon();
    l_Ais.Lat = ais.lat();
    l_Ais.COG = ais.cog();
    l_Ais.SOG = ais.sog();
    l_Ais.HDG = ais.hdg();
    l_Ais.ROTAIS = ais.rotais();
    l_Ais.ReportPeriod = ais.recentperiod();
    l_Ais.ReportTicks = ais.reportticks();
    l_Ais.MID = ais.mid();
    l_Ais.utc_hour = ais.m_utc_hour();
    l_Ais.utc_min = ais.m_utc_min();
    l_Ais.utc_sec = ais.m_utc_sec();
    l_Ais.Range_NM = ais.range_nm();
    l_Ais.Brg = ais.brg();
    l_Ais.SyncState = ais.syncstate();
    l_Ais.SlotTO = ais.slotto();
    l_Ais.Simulation = ais.simulation();
    l_Ais.ReportInterval = 0;
    l_Ais.OwnShip = ais.ownship();

    //qDebug()<<"receive"<<l_Ais.MMSI<<l_Ais.m_dLat<<l_Ais.m_dLon<<l_Ais.m_dSOG;
    mymap<QString,hgTarget>::iterator l_it = m_mapTarget.find(l_Ais.MMSI);
    if (l_it != m_mapTarget.end())
    { 
        l_it->MMSI = l_Ais.MMSI;
        l_it->MID = l_Ais.MID;
        l_it->ReportPeriod = l_Ais.ReportPeriod;
        l_it->ReportTicks = l_Ais.ReportTicks;
        l_it->ReportInterval = 0;
        l_it->Simulation = l_Ais.Simulation;
        if (l_Ais.Lat == NO_VALID_LATLON)
        {
            l_it->Class = l_Ais.Class;
            if (l_Ais.ShipName != NULL)
            {
                l_it->ShipName = l_Ais.ShipName;
            }
            l_it->ShipType = l_Ais.ShipType;
            l_it->CallSign = l_Ais.CallSign;
            l_it->IMO = l_Ais.IMO;
            if (l_Ais.DimA != 0)
            {
                l_it->DimA = l_Ais.DimA;
            }
            if (l_Ais.DimB != 0)
            {
                l_it->DimB = l_Ais.DimB;
            }
            if (l_Ais.DimC != 0)
            {
                l_it->DimC = l_Ais.DimC;
            }
            if (l_Ais.DimD != 0)
            {
                l_it->DimD = l_Ais.DimD;
            }
            l_it->ETA_Mo = l_Ais.ETA_Mo;
            l_it->ETA_Day = l_Ais.ETA_Day;
            l_it->ETA_Hr = l_Ais.ETA_Hr;
            l_it->ETA_Min = l_Ais.ETA_Min;
            l_it->Draft = l_Ais.Draft;
            l_it->Destination = l_Ais.Destination;
        }
        else
        {
            //l_Ais.LastLat = m_mapTarget[QString::fromStdString(ais.mmsi())].Lat;
            //l_Ais.LastLon = m_mapTarget[QString::fromStdString(ais.mmsi())].Lon;
            l_it->NavStatus = l_Ais.NavStatus;
            l_it->Lon = l_Ais.Lon;
            l_it->Lat = l_Ais.Lat;
            l_it->COG = l_Ais.COG;
            l_it->SOG = l_Ais.SOG;
            l_it->HDG = l_Ais.HDG;
            l_it->ROTAIS = l_Ais.ROTAIS;

            l_it->utc_hour = l_Ais.utc_hour;
            l_it->utc_min = l_Ais.utc_min;
            l_it->utc_sec = l_Ais.utc_sec;
            l_it->Range_NM = l_Ais.Range_NM;
            l_it->Brg = l_Ais.Brg;
            l_it->SyncState = l_Ais.SyncState;
            l_it->SlotTO = l_Ais.SlotTO;
        }
    }
    else
    {
        if (l_Ais.Lat != NO_VALID_LATLON)
        {
            //l_Ais.LastLat = 0;
            //l_Ais.LastLon = 0;
            m_mapTarget.insert(l_Ais.MMSI,l_Ais);
        }
    }
}

void hgTargetManager::AddTarget(hgTarget &ais)
{
    mymap<QString,hgTarget>::iterator l_it = m_mapTarget.find(ais.ID);
    if (l_it != m_mapTarget.end())
    {
        l_it->MMSI = ais.MMSI;
        l_it->RadarID = ais.RadarID;
        l_it->Source = ais.Source;
        l_it->Result = ais.Result;
        l_it->IMO = ais.IMO;
        l_it->Length = ais.Length;
        l_it->Width = ais.Width;
        l_it->ShipName = ais.ShipName;
        l_it->ShipType = ais.ShipType;
        l_it->ChShipName = ais.ChShipName;
        l_it->Nationality = ais.Nationality;
        l_it->Note = ais.Note;

        l_it->CallSign = ais.CallSign;
        l_it->EquipmentType = ais.EquipmentType;
        l_it->DimA = ais.DimA;
        l_it->DimB = ais.DimB;
        l_it->DimC = ais.DimC;
        l_it->DimD = ais.DimD;
        l_it->Destination = ais.Destination;
        l_it->ETA_Mo = ais.ETA_Mo;
        l_it->ETA_Hr = ais.ETA_Hr;
        l_it->ETA_Min = ais.ETA_Min;
        l_it->Draft = ais.Draft;

        l_it->NavStatus = ais.NavStatus;
        l_it->SOG = ais.SOG;
        l_it->PosAccuracy = ais.PosAccuracy;
        l_it->Lon = ais.Lon;
        l_it->Lat = ais.Lat;
        l_it->COG = ais.COG;
        l_it->HDG = ais.HDG;
        l_it->ROTAIS = ais.ROTAIS;
        l_it->utc_sec = ais.utc_sec;
        l_it->utc_hour = ais.utc_hour;
        l_it->utc_min = ais.utc_min;
        /*if (ais.MID == 3 || ais.MID == 18 || ais.MID == 19)
        {
            l_it->Prediction.AddPointLL(ais.ReportTicks,hg::utils::PointLL(ais.Lon,ais.Lat));
        }*/
    }
    else
    {
        m_mapTarget.insert(ais.ID,ais);
    }
}

void hgTargetManager::AddAis(hgAisMessage ais)
{
    hgTarget l_Ais;

    l_Ais.ID = QString::fromStdString(ais.id());
    l_Ais.MMSI = QString::fromStdString(ais.mmsi());
    l_Ais.ShipName = QString::fromStdString(ais.shipname());
    l_Ais.ShipName.replace(QRegExp("@"), "");

    l_Ais.CallSign = QString::fromStdString(ais.callsign());
    l_Ais.CallSign.replace(QRegExp("@"), "");
    l_Ais.IMO = ais.imo();
    l_Ais.Class = (hgAisClass)ais.class_();
    l_Ais.ShipType = QString::fromStdString(ais.shiptype());
    l_Ais.DimA = ais.dima();
    l_Ais.DimB = ais.dimb();
    l_Ais.DimC = ais.dimc();
    l_Ais.DimD = ais.dimd();
    l_Ais.Destination = QString::fromStdString(ais.destination());
    l_Ais.Destination.replace(QRegExp("@"), "");
    l_Ais.ETA_Mo = ais.eta_mo();
    l_Ais.ETA_Day = ais.eta_day();
    l_Ais.ETA_Hr = ais.eta_hr();
    l_Ais.ETA_Min = ais.eta_min();

    l_Ais.Draft = ais.draft();
    l_Ais.NavStatus = ais.navstatus();
    l_Ais.Lon = ais.lon();
    l_Ais.Lat = ais.lat();
    l_Ais.COG = ais.cog();
    l_Ais.SOG = ais.sog();
    l_Ais.HDG = ais.hdg();
    l_Ais.ROTAIS = ais.rotais();
    l_Ais.ReportPeriod = ais.recentperiod();
    l_Ais.ReportTicks = ais.reportticks();
    l_Ais.MID = ais.mid();
    l_Ais.utc_hour = ais.m_utc_hour();
    l_Ais.utc_min = ais.m_utc_min();
    l_Ais.utc_sec = ais.m_utc_sec();
    l_Ais.Range_NM = ais.range_nm();
    l_Ais.Brg = ais.brg();
    l_Ais.SyncState = ais.syncstate();
    l_Ais.SlotTO = ais.slotto();
    l_Ais.Simulation = ais.simulation();
    //l_Ais.CalcRot = 0.0;
    //l_Ais.lastHDG = l_Ais.HDG;
    l_Ais.ReportInterval = 0;
    l_Ais.OwnShip = ais.ownship();

    hg::utils::PointLL l_PoinLL(l_Ais.Lon,l_Ais.Lat);


    mymap<QString,hgTarget>::iterator l_it = m_mapAis.find(l_Ais.MMSI);
    if (l_it != m_mapAis.end())
    { 
        int l_iLastTime = l_it->ReportTicks;
        double l_dLastLat = l_it->Lat;
        double l_dLastLon = l_it->Lon;
        double l_LastCOG = l_it->COG;
        double lastSog = l_it->SOG;
        double lastCog = l_it->COG;
        hg::utils::PointLL lastPoint(l_dLastLon,l_dLastLat);

        l_it->MMSI = l_Ais.MMSI;
        l_it->MID = l_Ais.MID;
        l_it->ReportPeriod = l_Ais.ReportPeriod;
        l_it->ReportTicks = l_Ais.ReportTicks;
        l_it->ReportInterval = 0;
        l_it->OwnShip = l_Ais.OwnShip;

        if (l_Ais.Lat == NO_VALID_LATLON)
        {
            l_it->Class = l_Ais.Class;
            if (l_Ais.ShipName != NULL)
            {
                l_it->ShipName = l_Ais.ShipName;
            }
            l_it->ShipType = l_Ais.ShipType;
            l_it->CallSign = l_Ais.CallSign;
            l_it->IMO = l_Ais.IMO;
            l_it->Simulation = l_Ais.Simulation;
            if (l_Ais.DimA != 0)
            {
                l_it->DimA = l_Ais.DimA;
            }
            if (l_Ais.DimB != 0)
            {
                l_it->DimB = l_Ais.DimB;
            }
            if (l_Ais.DimC != 0)
            {
                l_it->DimC = l_Ais.DimC;
            }
            if (l_Ais.DimD != 0)
            {
                l_it->DimD = l_Ais.DimD;
            }
            l_it->ETA_Mo = l_Ais.ETA_Mo;
            l_it->ETA_Day = l_Ais.ETA_Day;
            l_it->ETA_Hr = l_Ais.ETA_Hr;
            l_it->ETA_Min = l_Ais.ETA_Min;
            l_it->Draft = l_Ais.Draft;
            l_it->Destination = l_Ais.Destination;
        }
        else
        {
            //l_Ais.LastLat = m_mapAis[QString::fromStdString(ais.mmsi())].Lat;
            //l_Ais.LastLon = m_mapAis[QString::fromStdString(ais.mmsi())].Lon;
            l_it->NavStatus = l_Ais.NavStatus;
            l_it->Lon = l_Ais.Lon;
            l_it->Lat = l_Ais.Lat;
            l_it->COG = l_Ais.COG;
            l_it->SOG = l_Ais.SOG;
            l_it->HDG = l_Ais.HDG;
            l_it->ROTAIS = l_Ais.ROTAIS;

            l_it->utc_hour = l_Ais.utc_hour;
            l_it->utc_min = l_Ais.utc_min;
            l_it->utc_sec = l_Ais.utc_sec;
            l_it->Range_NM = l_Ais.Range_NM;
            l_it->Brg = l_Ais.Brg;
            l_it->SyncState = l_Ais.SyncState;
            l_it->SlotTO = l_Ais.SlotTO;

        }
    }
    else
    {
        if (l_Ais.Lat != NO_VALID_LATLON)
        {
            m_mapAis.insert(l_Ais.MMSI,l_Ais);
        }
    }
}

void hgTargetManager::AddSim(hgAisMessage ais)
{
    hgTarget l_Ais;

    l_Ais.ID = QString::fromStdString(ais.id());
    l_Ais.RadarID = QString::fromStdString(ais.radarid());
    l_Ais.MMSI = QString::fromStdString(ais.mmsi());
    l_Ais.Source = ais.source();
    l_Ais.ShipName = QString::fromStdString(ais.shipname());

    l_Ais.CallSign = QString::fromStdString(ais.callsign());
    l_Ais.IMO = ais.imo();
    l_Ais.Class = (hgAisClass)ais.class_();
    l_Ais.ShipType = QString::fromStdString(ais.shiptype());
    l_Ais.DimA = ais.dima();
    l_Ais.DimB = ais.dimb();
    l_Ais.DimC = ais.dimc();
    l_Ais.DimD = ais.dimd();
    l_Ais.Destination = QString::fromStdString(ais.destination());
    l_Ais.ETA_Mo = ais.eta_mo();
    l_Ais.ETA_Day = ais.eta_day();
    l_Ais.ETA_Hr = ais.eta_hr();
    l_Ais.ETA_Min = ais.eta_min();

    l_Ais.Draft = ais.draft();
    l_Ais.NavStatus = ais.navstatus();
    l_Ais.Lon = ais.lon();
    l_Ais.Lat = ais.lat();
    l_Ais.COG = ais.cog();
    l_Ais.SOG = ais.sog();
    l_Ais.HDG = ais.hdg();
    l_Ais.ROTAIS = ais.rotais();
    l_Ais.ReportPeriod = ais.recentperiod();
    l_Ais.ReportTicks = ais.reportticks();
    l_Ais.MID = ais.mid();
    l_Ais.utc_hour = ais.m_utc_hour();
    l_Ais.utc_min = ais.m_utc_min();
    l_Ais.utc_sec = ais.m_utc_sec();
    l_Ais.Range_NM = ais.range_nm();
    l_Ais.Brg = ais.brg();
    l_Ais.SyncState = ais.syncstate();
    l_Ais.SlotTO = ais.slotto();
    l_Ais.OwnShip = ais.ownship();


    m_mapRadar.insert(l_Ais.MMSI,l_Ais);
}


void hgTargetManager::DeleteAll()
{
    m_mapTarget.clear();
    m_mapAis.clear();
    m_mapRadar.clear();
}

void hgTargetManager::DeleteSim()
{
    {
        mymap<QString,hgTarget>::iterator l_it;
        l_it = m_mapTarget.begin();
        while (l_it != m_mapTarget.end())
        {
            if (l_it->MMSI.left(1) == "S")
            {
                l_it = m_mapTarget.erase(l_it);
            }
            else
            {
                l_it++;
            }
        }
    }
    {
        mymap<QString,hgTarget>::iterator l_it;
        l_it = m_mapAis.begin();
        while (l_it != m_mapAis.end())
        {
            if (l_it->MMSI.left(1) == "S")
            {
                l_it = m_mapAis.erase(l_it);
            }
            else
            {
                l_it++;
            }
        }
    }
}

void hgTargetManager::DeleteLost()
{
    mymap<QString,hgTarget>::iterator l_it;
    {
        l_it = m_mapTarget.begin();
        while (l_it != m_mapTarget.end())
        {
            if (l_it->Missing == true)
            {
                l_it = m_mapTarget.erase(l_it);
            }
            else
            {
                l_it++;
            }
        }
    }

    mymap<QString,hgTarget>::iterator l_itAis;
    {
        l_itAis = m_mapAis.begin();
        while (l_itAis != m_mapAis.end())
        {
            if (l_itAis->Missing == true)
            {
                l_itAis = m_mapAis.erase(l_it);
            }
            else
            {
                l_itAis++;
            }
        }
    }
}

void hgTargetManager::SetPlayBack(int time)
{
    if (time == 0)
    {
        {

            mymap<QString,hgTarget>::iterator l_it;
            l_it = m_mapTarget.begin();
            while (l_it != m_mapTarget.end())
            {
                if (l_it->Simulation == false)
                {
                    l_it = m_mapTarget.erase(l_it);
                }
                else
                {
                    l_it++;
                }
            }
        }

        {

            mymap<QString,hgTarget>::iterator l_it;
            l_it = m_mapAis.begin();
            while (l_it != m_mapAis.end())
            {
                if (l_it->Simulation == false)
                {
                    l_it = m_mapAis.erase(l_it);
                }
                else
                {
                    l_it++;
                }
            }
        }
    }
    else
    {
        mymap<QString,hgTarget>::iterator l_it;
        {
            l_it = m_mapAis.begin();
            while (l_it != m_mapAis.end())
            {
                if (l_it->ReportTicks > time && l_it->Simulation == false)
                {
                    //m_mapTarget.erase(l_it);
                    l_it = m_mapAis.erase(l_it);
                }
                else
                {
                    l_it++;
                }
            }
        }

        {
            mymap<QString,hgTarget>::iterator l_it;
            l_it = m_mapTarget.begin();
            while (l_it != m_mapTarget.end())
            {
                if (l_it->ReportTicks > time && l_it->Simulation == false)
                {
                    l_it = m_mapTarget.erase(l_it);
                }
                else
                {
                    l_it++;
                }
            }
        }

    }
}


void hgTargetManager::ChangeAisToShip(hgAisMessage ais, hgShipAisMessage &shipais, int hdgtype)
{
    shipais.set_id(ais.id());
    if (ais.radarid() == "-1" || ais.radarid() == "-2")
    {
        shipais.set_id(ais.radarid());
    }
    shipais.set_class_(ais.class_());
    shipais.set_mmsi(ais.mmsi());
    shipais.set_sog(ais.sog());
    shipais.set_lat(ais.lat());
    shipais.set_lon(ais.lon());
    shipais.set_cog(ais.cog());
    shipais.set_hdg(ais.hdg());
    shipais.set_length(ais.length());
    shipais.set_width(ais.width());
    shipais.set_dima(ais.dima());
    shipais.set_dimb(ais.dimb());
    shipais.set_dimc(ais.dimc());
    shipais.set_dimd(ais.dimd());
    shipais.set_recentperiod(ais.recentperiod());
    shipais.set_reportticks(ais.reportticks());
    shipais.set_reportinterval(ais.reportinterval());
    shipais.set_ownship(ais.ownship());
    shipais.set_source(ais.source());
    shipais.set_result(ais.result());
	shipais.set_shipname(ais.shipname());
	shipais.set_hdgtype(hdgtype);
}

void hgTargetManager::SaveAis(hgSqlOperator& sqlOperator, hgAisMessage ais)
{

    if (ais.mid() == 5 || ais.mid() == 24)
    {
//         if (m_mapTarget.find(QString::fromStdString(ais.mmsi())) != m_mapTarget.end())
//         {
//             UpdateStaticAis(sqlOperator,ais);
//         }
//         else
        {
            AddStaticAis(sqlOperator,ais);
        }
    } 
    else if (ais.mid() == 1 || ais.mid() == 2 || ais.mid() == 3 || ais.mid() == 18|| ais.mid() == 19)
    {
        AddDynamicAis(sqlOperator,ais);
    }
}

void hgTargetManager::ReadStaticAis(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("target_static_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgTarget l_data;
        l_data.Class = (hgAisClass)l_record.value("Class").toInt();
        l_data.MMSI = l_record.value("MMSI").toString();
        l_data.ID = l_record.value("ID").toString();
        l_data.RadarID = l_record.value("RadarID").toString();
        l_data.MID = l_record.value("MID").toInt();
        l_data.IMO = l_record.value("IMO").toInt();
        l_data.CallSign = l_record.value("CallSign").toString();
        l_data.ShipName = l_record.value("ShipName").toString();
        l_data.ShipType = l_record.value("ShipType").toString();
        l_data.ETA_Mo = l_record.value("ETA_Mo").toInt();
        l_data.ETA_Day = l_record.value("ETA_Day").toInt();
        l_data.ETA_Hr = l_record.value("ETA_Hr").toInt();
        l_data.ETA_Min = l_record.value("ETA_Min").toInt();
        l_data.DimA = l_record.value("DimA").toInt();
        l_data.DimB = l_record.value("DimB").toInt();
        l_data.DimC = l_record.value("DimC").toInt();
        l_data.DimD = l_record.value("DimD").toInt();
        l_data.Length = l_record.value("Length").toDouble();
        l_data.Width = l_record.value("Width").toDouble();
        l_data.Destination = l_record.value("Destination").toString();
        l_data.Draft = l_record.value("Draft").toDouble();
        //l_data.ReportTicks = l_record.value("ReportTicks").toInt();
        //l_data.ReportTicks = time(NULL);
        l_data.EquipmentType = l_record.value("EquipmentType").toInt();
        l_data.SetShipSize = l_record.value("SetShipSize").toInt();
        l_data.ChShipName = l_record.value("ChShipName").toString();
        l_data.Nationality = l_record.value("Nationality").toString();
        l_data.Note = l_record.value("Note").toString();
        l_data.OwnShip = l_record.value("IsOwnShip").toBool();

		qDebug() << "target static table " << l_data.MMSI;
        m_mapStatic.insert(l_data.MMSI,l_data);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgTargetManager::ReadLloydAis(hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("lloyd_table");

    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        hgTarget l_data;
        l_data.MMSI = l_record.value("MMSI").toString();
        l_data.MID = l_record.value("MID").toInt();
        l_data.ShipName = l_record.value("ShipName").toString();
        l_data.ShipType = l_record.value("ShipType").toString();
        l_data.Length = l_record.value("Length").toDouble();
        l_data.Width = l_record.value("Width").toDouble();
		if (l_data.Length < 20  || l_data.Width < 5 || l_data.MMSI.isEmpty())
		{
			continue;
		}
        l_data.DimA = l_data.Length * 0.75;
        l_data.DimB = l_data.Length * 0.25;
        l_data.DimC = l_data.Width * 0.25;
        l_data.DimD = l_data.Width * 0.75;

        m_mapShipData.insert(l_data.MMSI,l_data);
    }
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void hgTargetManager::AddStaticAis(hgSqlOperator& sqlOperator, hgAisMessage ais)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("target_static_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("Class",ais.class_());
    l_data.insert("ID",QString::fromStdString(ais.id()));
    l_data.insert("MMSI",QString::fromStdString(ais.mmsi()));
    l_data.insert("RadarID",QString::fromStdString(ais.radarid()));
    l_data.insert("MID",ais.mid());
    l_data.insert("IMO",ais.imo());
    l_data.insert("CallSign", QString::fromStdString(ais.callsign()));
    l_data.insert("ShipName", QString::fromStdString(ais.shipname()));
    l_data.insert("ShipType", QString::fromStdString(ais.shiptype()));
    l_data.insert("ETA_Mo",ais.eta_mo());
    l_data.insert("ETA_Day",ais.eta_day());
    l_data.insert("ETA_Hr",ais.eta_hr());
    l_data.insert("ETA_Min",ais.eta_min());
    l_data.insert("DimA",ais.dima());
    l_data.insert("DimB",ais.dimb());
    l_data.insert("DimC",ais.dimc());
    l_data.insert("DimD",ais.dimd());
    l_data.insert("Destination", QString::fromStdString(ais.destination()));
    l_data.insert("Draft",ais.draft());
    l_data.insert("ReportTicks",ais.reportticks());
    l_data.insert("EquipmentType",ais.equipmenttype());
    l_data.insert("Simulation",ais.simulation());
    l_data.insert("IsOwnShip",ais.ownship());

    l_pSqlInsertCmd->SetData(l_data);
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
        if (l_pSqlInsertCmd)
        {
            delete l_pSqlInsertCmd;
            l_pSqlInsertCmd = NULL;
        }
        //std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

void hgTargetManager::AddDynamicAis(hgSqlOperator& sqlOperator, hgAisMessage ais)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("target_dynamic_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",QString::fromStdString(ais.id()));
    l_data.insert("MMSI",QString::fromStdString(ais.mmsi()));
    l_data.insert("RadarID",QString::fromStdString(ais.radarid()));
    l_data.insert("Source",ais.source());
    l_data.insert("Result",ais.result());
    l_data.insert("Reserved",ais.reserved());
    l_data.insert("Rng",ais.rng());
    l_data.insert("Spd",ais.spd());
    l_data.insert("Crs",ais.crs());
    l_data.insert("Scans",ais.scans());
    l_data.insert("Flags",ais.flags());
    l_data.insert("MID",ais.mid());
    l_data.insert("ROTAIS",ais.rotais());
    l_data.insert("SOG",ais.sog());
    l_data.insert("Lon",ais.lon());
    l_data.insert("Lat",ais.lat());
    l_data.insert("COG",ais.cog());
    l_data.insert("HDG",ais.hdg());
    l_data.insert("SyncState",ais.syncstate());
    l_data.insert("SlotTO",ais.slotto());
    l_data.insert("ReportTicks",ais.reportticks());
    l_data.insert("RecentPeriod",ais.recentperiod());
    l_data.insert("PosAccuracy",ais.posaccuracy());
    l_data.insert("m_utc_hour",ais.m_utc_hour());
    l_data.insert("m_utc_min",ais.m_utc_min());
    l_data.insert("m_utc_sec",ais.m_utc_sec());
    l_data.insert("Range_NM",ais.range_nm());
    l_data.insert("Brg",ais.brg());
    l_data.insert("b_active",0);
    l_data.insert("n_alarm_state",0);
    l_data.insert("b_suppress_audio",0);
    l_data.insert("b_positionValid",0);
    l_data.insert("b_nameValid",0);
    l_data.insert("SyncState",0);
    l_data.insert("bCPA_Valid",ais.bcpa_valid());
    l_data.insert("TCPA",ais.tcpa());
    l_data.insert("CPA",ais.cpa());
    l_pSqlInsertCmd->SetData(l_data);
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}

void hgTargetManager::UpdateStaticAis(hgSqlOperator& sqlOperator, hgAisMessage ais)
{
    hgSqlUpdateCmd* l_pSqlUpdateCmd = new hgSqlUpdateCmd;
    l_pSqlUpdateCmd->SetTableName("target_static_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("Class",ais.class_());
    l_data.insert("ID",QString::fromStdString(ais.id()));
    l_data.insert("MMSI",QString::fromStdString(ais.mmsi()));
    l_data.insert("RadarID",QString::fromStdString(ais.radarid()));
    l_data.insert("MID",ais.mid());
    l_data.insert("IMO",ais.imo());
    l_data.insert("CallSign", QString::fromStdString(ais.callsign()));
    l_data.insert("ShipName", QString::fromStdString(ais.shipname()));
    l_data.insert("ShipType", QString::fromStdString(ais.shiptype()));
    l_data.insert("ETA_Mo",ais.eta_mo());
    l_data.insert("ETA_Day",ais.eta_day());
    l_data.insert("ETA_Hr",ais.eta_hr());
    l_data.insert("ETA_Min",ais.eta_min());
    l_data.insert("DimA",ais.dima());
    l_data.insert("DimB",ais.dimb());
    l_data.insert("DimC",ais.dimc());
    l_data.insert("DimD",ais.dimd());  
    l_data.insert("Destination", QString::fromStdString(ais.destination()));
    l_data.insert("Draft",ais.draft());
    l_data.insert("ReportTicks",ais.reportticks());
    l_data.insert("EquipmentType",ais.equipmenttype());
    l_data.insert("Nationality",QString::fromStdString(ais.nationality()));
    l_data.insert("ChShipName",QString::fromStdString(ais.chshipname()));
    l_data.insert("Note",QString::fromStdString(ais.note()));
    l_pSqlUpdateCmd->SetData(l_data);
    l_pSqlUpdateCmd->SetFilter(QString("ID = '%1'").arg(QString::fromStdString(ais.id())));

    if (!sqlOperator.ImplementCmd(l_pSqlUpdateCmd))
    {
		std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
		delete l_pSqlUpdateCmd;
		l_pSqlUpdateCmd = NULL;
        return;
    }
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (l_pSqlUpdateCmd)
    {
        delete l_pSqlUpdateCmd;
        l_pSqlUpdateCmd = NULL;
    }
}

void hgTargetManager::AddFuaeResult(hgSqlOperator& sqlOperator, hgResult result, bool fuse, int time)
{
    hgSqlInsertCmd* l_pSqlInsertCmd = new hgSqlInsertCmd;
    l_pSqlInsertCmd->SetTableName("target_reault_table");
    QMap<QString, QVariant> l_data;
    l_data.insert("ID",result.ID);
    l_data.insert("MMSI",result.MMSI);
    l_data.insert("Fuse",fuse);
    l_data.insert("time",time);
    l_data.insert("RadarGUID",result.RadarGUID);
    l_pSqlInsertCmd->SetData(l_data);
    if (!sqlOperator.ImplementCmd(l_pSqlInsertCmd))
    {
		std::cout << "Open datatabase error:" << sqlOperator.LastError().text().toLatin1().data();
		delete l_pSqlInsertCmd;
		l_pSqlInsertCmd = NULL;
        return;
    }

    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (l_pSqlInsertCmd)
    {
        delete l_pSqlInsertCmd;
        l_pSqlInsertCmd = NULL;
    }
}





