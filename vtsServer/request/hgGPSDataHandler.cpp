
#include "StdAfx.h"
#include "hgGPSDataHandler.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgSendManager.h"
#include "Managers/hgConfigManager.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"
#include "LayerData/hgPolygonLayer.h"
#include "message/hgGPSData.pb.h"
#include <QSqlDatabase>
#include "frame/vtsServer.h"
#include "message/IdentityPack.pb.h"

hgGPSDataHandler::hgGPSDataHandler()
{

}

hgGPSDataHandler::~hgGPSDataHandler(void)
{
}

vtsRequestHandler::WorkMode hgGPSDataHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgGPSDataHandler::handle(boost::asio::const_buffer& data)
{
    bool l_qdbug = false;
    hgGPSData msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));
    //qDebug() << msg.state() << msg.type();
    if (msg.state() == false)
    {
        return ;
    }
    if ( !hgTargetManager::m_GPSMMSI.contains(msg.mmsi().c_str()) )
    {
        vtsInfo << "Begin Receive GPS " << msg.mmsi().c_str();
        hgTargetManager::m_GPSMMSI.push_back(msg.mmsi().c_str());
        qDebug () << "<<<<<<<<<" << hgTargetManager::m_GPSMMSI;
        std::string l_name = "s_GPS" + msg.mmsi();
        //this->connection()->setChannel(l_name);
        IdentityPack l_imsg;
        l_imsg.set_name(l_name);
        l_imsg.set_type(IdentityType::ServerLogin);
		hgSendManager::SendClientMessage("Identity",l_imsg,this->connection());
	}
	if ( !hgTargetManager::m_GPSMMSIPos.contains(msg.mmsi().c_str()) )
	{
		if (GPSRMC == msg.type() || GPSGGA == msg.type())
		{
			hgTargetManager::m_GPSMMSIPos.push_back(msg.mmsi().c_str());
			std::string l_name = "s_PosGPS" + msg.mmsi();
			IdentityPack l_imsg;
			l_imsg.set_name(l_name);
			l_imsg.set_type(IdentityType::ServerLogin);
			hgSendManager::SendShipMessage("Identity",l_imsg,this->connection());
			qDebug () << "<<<<<<<<< s_PosGPS" << msg.mmsi().c_str();
		}
	}
	if ( !hgTargetManager::m_GPSMMSIHdg.contains(msg.mmsi().c_str()) )
	{
		if (msg.type() == GPSHDT || msg.type() == GPSHDM)
		{
			hgTargetManager::m_GPSMMSIHdg.push_back(msg.mmsi().c_str());
			std::string l_name = "s_HdgGPS" + msg.mmsi();
			IdentityPack l_imsg;
			l_imsg.set_name(l_name);
			l_imsg.set_type(IdentityType::ServerLogin);
			hgSendManager::SendShipMessage("Identity",l_imsg,this->connection());
			qDebug () << "<<<<<<<<< s_HdgGPS" << msg.mmsi().c_str();
		}
	}
    bool l_NorthArea = false;
    bool l_SouthArea = false;
//     hgPolygonLayer l_NorthLayer;
//     hgPolygonLayer l_SouthLayer;
    hg::utils::PolygonLL l_NorthAreaLL;
    hg::utils::PolygonLL l_SouthAreaLL;
    if (hgAlarmManager::m_LayerDataManager.m_pPloygonMap.contains("{637F13FE-2E48-40B6-8327-68583E209BFE}"))
    {
        l_NorthArea = true;
        l_NorthAreaLL = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find("{637F13FE-2E48-40B6-8327-68583E209BFE}").value().m_Polygon;
    }
    if (hgAlarmManager::m_LayerDataManager.m_pPloygonMap.contains("{5F81AA11-DA37-450C-A1FB-C0B52D5AE632}"))
    {
        l_SouthArea = true;
        l_SouthAreaLL = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find("{5F81AA11-DA37-450C-A1FB-C0B52D5AE632}").value().m_Polygon;
    }
	mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapTarget.find(msg.mmsi().c_str());
	mymap<QString,hgTarget>::iterator l_itAIS = hgTargetManager::m_mapAis.find(msg.mmsi().c_str());
    if (l_it != hgTargetManager::m_mapTarget.end())
    {
        //hg::utils::PointLL l_Point(l_it->Lon,l_it->Lat);
        l_it->ReportInterval = 0;
        if (GPSRMC == msg.type() || GPSGGA == msg.type())
        {
            l_it->ReportPeriod = msg.time() - l_it->ReportTicks;
        }
        hg::utils::PointLL l_GPPoint(l_it->Lon,l_it->Lat);
        bool l_Add180 = false;//hdg 是否加180
        bool l_UseCog = false;//hdg是否用COG代替
        if (l_NorthArea == true && l_SouthArea == true)
        {
            int l_CurPos;//当前位置
            if (l_NorthAreaLL.containsPoint(l_GPPoint, Qt::WindingFill))
            {
                l_CurPos = SPNorthArea;
                l_UseCog = true;
            }
            else if (l_SouthAreaLL.containsPoint(l_GPPoint, Qt::WindingFill))
            {
                l_CurPos = SPSouthArea;
                l_UseCog = true;
            }
            else
            {
                l_CurPos = SPUnknow;
            }
			static int s_time = 0;
			static bool s_debug = false;
			s_debug = false;
			if (time(NULL) - s_time > 2)
			{
				s_debug = true;
				s_time = time(NULL);
			}
			//当前 South  ， North to South  转向
			//     North  ， south to north 不转向
            if (hgAlarmManager::m_ShipPosition.contains(msg.mmsi().c_str()))
            {
                int l_position = hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()];//原来船位
                if (l_position == SPUnknow)
                {
                    if (l_CurPos == SPNorthArea)
                    {
                        hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()] = SPNorthArea;
                    }
                    else if (l_CurPos == SPSouthArea)
                    {
                        hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()] = SPSouthArea;
                    }
                }
                else if (l_position == SPNorthArea)
                {
                    if (l_CurPos == SPUnknow)
                    {
                        hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()] = SPNorthToSouth;
                        l_Add180 = true;
                    }
                }
                else if (l_position == SPSouthArea)
                {
                    if (l_CurPos == SPUnknow)
                    {
                        hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()] = SPSouthToNorth;
                    }
					else
					{
						l_Add180 = true;
					}
                }
                else if (l_position == SPNorthToSouth)
                {
                    if (l_CurPos == SPSouthArea)
                    {
						hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()] = SPSouthArea;
						l_Add180 = true;
                    }
                    else
                    {
                        l_Add180 = true;
                    }
                }
                else if (l_position == SPSouthToNorth)
                {
                    if (l_CurPos == SPNorthArea)
                    {
                        hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()] = SPNorthArea;
                        //l_Add180 = true;
                    }
                }
            }
            else
            {
                hgAlarmManager::m_ShipPosition.insert(msg.mmsi().c_str(),l_CurPos);
            }
			//qDebug() << msg.mmsi().c_str() << hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()] << l_Add180;
        }
		if (hgTargetManager::m_GPSHdg.contains(msg.mmsi().c_str()))
		{
			l_Add180 = (hgTargetManager::m_GPSHdg[msg.mmsi().c_str()] == 0 ? false : true);
		}
        if (msg.type() == GPSHDT || msg.type() == GPSHDM)
        {
//             if (l_UseCog == true)
//             {
//                 l_it->HDG = msg.hdg();
//             }
//             else
			{
				//根据船舶运行方向（根据收到消息判断）
				if (hgTargetManager::m_GPSHdg.contains(msg.mmsi().c_str()))
				{
					int _hdg = hgTargetManager::m_GPSHdg[msg.mmsi().c_str()];

					if (_hdg == 0)//往扬州方向开   0~90   90~270
					{
						if (msg.hdg() > 270 || msg.hdg() < 90)
						{
							l_it->HDG = msg.hdg();
						}
						else
						{
							l_it->HDG = msg.hdg() > 180 ? (msg.hdg()-180) : (msg.hdg()+180);
						}
					}
					//往镇江方向  90~270
					else
					{
						if (msg.hdg() > 90 && msg.hdg() < 270)
						{
							l_it->HDG = msg.hdg();
						}
						else
						{
							l_it->HDG = msg.hdg() > 180 ? (msg.hdg()-180) : (msg.hdg()+180);
						}
					}
				}
				//根据船舶运行轨迹判断（本程序判断）
				else
				{
					if (l_Add180 == true)
					{
						l_it->HDG = msg.hdg() > 180 ? (msg.hdg()-180) : (msg.hdg()+180);
					}
					else
					{
						l_it->HDG = msg.hdg();
					}
				}
			}
			if (l_itAIS != hgTargetManager::m_mapAis.end())
			{
				l_itAIS->HDG = l_it->HDG;
			}
            if (l_qdbug)
            {
                qDebug() << "GPSHDM" << msg.hdg() << "  " << QDateTime::fromTime_t(time(NULL)).toString("hh-mm-ss");
            }
        }
        else if (msg.type() == GPSRMC)
        {
            l_it->Lat = msg.lat();
            l_it->Lon = msg.lon();
            l_it->ReportTicks = msg.time();
            l_it->SOG = msg.speed();
			l_it->COG = msg.course();
			if (l_itAIS != hgTargetManager::m_mapAis.end())
			{
				l_itAIS->Lat = msg.lat();
				l_itAIS->Lon = msg.lon();
				l_itAIS->ReportTicks = msg.time();
				l_itAIS->SOG = msg.speed();
				l_itAIS->COG = msg.course();
			}

            if (l_qdbug)
            {
                qDebug() << "GPSRMC" << msg.lat() << "  " << msg.lon() << "  " << QDateTime::fromTime_t(msg.time()).toString("hh-mm-ss") << "  "  << msg.speed() << "  " << QDateTime::fromTime_t(time(NULL)).toString("hh-mm-ss");
            } 
        }
        else if (msg.type() == GPSGGA)
        {
            l_it->Lat = msg.lat();
            l_it->Lon = msg.lon();
            l_it->ReportTicks = msg.time();
			if (l_itAIS != hgTargetManager::m_mapAis.end())
			{
				l_itAIS->Lat = msg.lat();
				l_itAIS->Lon = msg.lon();
				l_itAIS->ReportTicks = msg.time();
			}
            if (l_qdbug)
            {
                qDebug() << "GPSGGA" << msg.lat() << "  " << msg.lon() << "  " << QDateTime::fromTime_t(msg.time()).toString("hh-mm-ss") << "  " << QDateTime::fromTime_t(time(NULL)).toString("hh-mm-ss");
            }
        }
//         if (l_it->COG < 360 && l_UseCog == true)
//         {
//             l_it->HDG = l_it->COG;
        //         }

        if (hgConfigManager::m_sSysConfig->m_FuseType == 2)
        {
            l_it = hgTargetManager::m_mapTarget.find(msg.mmsi().c_str());
            if (l_it != hgTargetManager::m_mapTarget.end())
            {
                QSqlDatabase database = this->connection()->server().openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                hgTargetManager::Assembly(l_it.value(),l_sqlOperator);
                this->connection()->server().closeDBConnection(database);
            }
        }
		else if (hgConfigManager::m_sSysConfig->m_FuseType == 1)
		{
			l_it = hgTargetManager::m_mapTarget.find(msg.mmsi().c_str());
			if (l_it != hgTargetManager::m_mapTarget.end())
			{
				hgTargetManager::AssemGPSRadar(l_it.value());
			}
		}

        l_it = hgTargetManager::m_mapTarget.find(msg.mmsi().c_str());
        if (l_it != hgTargetManager::m_mapTarget.end())
        {
            hgAisMessage l_AisMessage;

            l_AisMessage.set_id(l_it->ID.toStdString());
            l_AisMessage.set_radarid(l_it->RadarID.toStdString());
            l_AisMessage.set_radarguid(l_it->RadarGUID.toStdString());
            l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
            l_AisMessage.set_source(FUSE_DATA);
            l_AisMessage.set_result(AIS_FUSE);
            l_AisMessage.set_reserved(l_it->Reserved);
            l_AisMessage.set_rng(l_it->Rng);
            l_AisMessage.set_radarbrg(l_it->RadarBrg);
            l_AisMessage.set_spd(l_it->Spd);
            l_AisMessage.set_crs(l_it->Crs);
            l_AisMessage.set_scans(l_it->Scans);
            l_AisMessage.set_flags(l_it->Flags);
            l_AisMessage.set_mid(l_it->MID);
            l_AisMessage.set_class_(l_it->Class);
            l_AisMessage.set_imo(l_it->IMO);
            l_AisMessage.set_length(l_it->Length);
            l_AisMessage.set_width(l_it->Width);
            l_AisMessage.set_recentperiod(l_it->ReportPeriod);
            l_AisMessage.set_navstatus(l_it->NavStatus);
            l_AisMessage.set_rotais(l_it->ROTAIS);
            l_AisMessage.set_sog(l_it->SOG);
            l_AisMessage.set_lon(l_it->Lon);
            l_AisMessage.set_lat(l_it->Lat);
            l_AisMessage.set_cog(l_it->COG);
            l_AisMessage.set_hdg(l_it->HDG);
            l_AisMessage.set_imo(l_it->IMO);
            l_AisMessage.set_callsign(l_it->CallSign.toStdString());
            l_AisMessage.set_shipname(l_it->ShipName.toStdString());
            l_AisMessage.set_shiptype(l_it->ShipType.toStdString());
            l_AisMessage.set_posaccuracy(l_it->PosAccuracy);
            l_AisMessage.set_equipmenttype(l_it->EquipmentType);
            l_AisMessage.set_eta_mo(l_it->ETA_Mo);
            l_AisMessage.set_eta_day(l_it->ETA_Day);
            l_AisMessage.set_eta_hr(l_it->ETA_Hr);
            l_AisMessage.set_eta_min(l_it->ETA_Min);
            l_AisMessage.set_draft(l_it->Draft);
            l_AisMessage.set_destination(l_it->Destination.toStdString());
            l_AisMessage.set_syncstate(l_it->SyncState);
            l_AisMessage.set_slotto(l_it->SlotTO);
            l_AisMessage.set_dima(l_it->DimA);
            l_AisMessage.set_dimb(l_it->DimB);
            l_AisMessage.set_dimc(l_it->DimC);
            l_AisMessage.set_dimd(l_it->DimD);
            l_AisMessage.set_length(l_it->Length);
            l_AisMessage.set_width(l_it->Width);
            l_AisMessage.set_setshipsize(l_it->SetShipSize);
            l_AisMessage.set_reportticks(l_it->ReportTicks);
            l_AisMessage.set_simulation(l_it->Simulation);
            l_AisMessage.set_reportinterval(l_it->ReportInterval);
            l_AisMessage.set_ownship(/*l_it->OwnShip*/true);
            l_AisMessage.set_recentperiod(l_it->ReportPeriod);
            l_AisMessage.set_m_utc_hour(l_it->utc_hour);
            l_AisMessage.set_m_utc_min(l_it->utc_min);
            l_AisMessage.set_m_utc_sec(l_it->utc_sec);
            l_AisMessage.set_range_nm(l_it->Range_NM);
            l_AisMessage.set_brg(l_it->Brg);
            l_AisMessage.set_bcpa_valid(l_it->CPA_Valid);
            l_AisMessage.set_tcpa(l_it->TCPA);
            l_AisMessage.set_cpa(l_it->CPA);
            l_AisMessage.set_chshipname(l_it->ChShipName.toStdString());
            l_AisMessage.set_nationality(l_it->Nationality.toStdString());
            l_AisMessage.set_note(l_it->Note.toStdString());

//             hg::utils::PointLL l_point(l_AisMessage.lon(),l_AisMessage.lat());
//             if (hgConfigManager::m_sSysConfig->m_AreaLL.size() > 2
//                 && !hgConfigManager::m_sSysConfig->m_AreaLL.containsPoint(l_point,Qt::WindingFill))
//             {
//                 return ;
//             }


            if ( abs(l_AisMessage.lat()) > 90 || abs(l_AisMessage.lon() > 180) )
            {
                return;
            }
            assert (l_AisMessage.hdg() < 1000000);
//             if (hgConfigManager::m_sSysConfig->m_iTrackPredict == 0)
//             {
                hgShipAisMessage l_shipais;
                if (l_qdbug)
                {
                    qDebug () << "++++++++++++++++" << l_AisMessage.mmsi().c_str();
				}
				if (l_Add180 == true)
				{
					hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 1);
				}
				else
				{
					hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 0);
				}
                hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
				hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
/*            }*/
        }   

        //ais 目标
        {
            mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapAis.find(msg.mmsi().c_str());
            QMap<QString,hgResult>::iterator l_itResult;
            if (l_it != hgTargetManager::m_mapAis.end())
            {
                hgAisMessage l_AisMessage;

                l_AisMessage.set_id(l_it->ID.toStdString());
                l_AisMessage.set_radarid(l_it->RadarID.toStdString());
                l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
                l_AisMessage.set_source(AIS_DATA);
                l_AisMessage.set_result(AIS_FUSE);
                l_AisMessage.set_reserved(l_it->Reserved);
                l_AisMessage.set_rng(l_it->Rng);
                l_AisMessage.set_radarbrg(l_it->RadarBrg);
                l_AisMessage.set_spd(l_it->Spd);
                l_AisMessage.set_crs(l_it->Crs);
                l_AisMessage.set_scans(l_it->Scans);
                l_AisMessage.set_flags(l_it->Flags);
                l_AisMessage.set_mid(l_it->MID);
                l_AisMessage.set_class_(l_it->Class);
                l_AisMessage.set_imo(l_it->IMO);
                l_AisMessage.set_length(l_it->Length);
                l_AisMessage.set_width(l_it->Width);
                l_AisMessage.set_recentperiod(l_it->ReportPeriod);
                l_AisMessage.set_navstatus(l_it->NavStatus);
                l_AisMessage.set_rotais(l_it->ROTAIS);
                l_AisMessage.set_sog(l_it->SOG);
                l_AisMessage.set_lon(l_it->Lon);
                l_AisMessage.set_lat(l_it->Lat);
                l_AisMessage.set_cog(l_it->COG);
                l_AisMessage.set_hdg(l_it->HDG);
                l_AisMessage.set_imo(l_it->IMO);
                l_AisMessage.set_callsign(l_it->CallSign.toStdString());
                l_AisMessage.set_shipname(l_it->ShipName.toStdString());
                l_AisMessage.set_shiptype(l_it->ShipType.toStdString());
                l_AisMessage.set_posaccuracy(l_it->PosAccuracy);
                l_AisMessage.set_equipmenttype(l_it->EquipmentType);
                l_AisMessage.set_eta_mo(l_it->ETA_Mo);
                l_AisMessage.set_eta_day(l_it->ETA_Day);
                l_AisMessage.set_eta_hr(l_it->ETA_Hr);
                l_AisMessage.set_eta_min(l_it->ETA_Min);
                l_AisMessage.set_draft(l_it->Draft);
                l_AisMessage.set_destination(l_it->Destination.toStdString());
                l_AisMessage.set_syncstate(l_it->SyncState);
                l_AisMessage.set_slotto(l_it->SlotTO);
                l_AisMessage.set_dima(l_it->DimA);
                l_AisMessage.set_dimb(l_it->DimB);
                l_AisMessage.set_dimc(l_it->DimC);
                l_AisMessage.set_dimd(l_it->DimD);
                l_AisMessage.set_length(l_it->Length);
                l_AisMessage.set_width(l_it->Width);
                l_AisMessage.set_setshipsize(l_it->SetShipSize);
                l_AisMessage.set_reportticks(l_it->ReportTicks);
                l_AisMessage.set_simulation(l_it->Simulation);
                l_AisMessage.set_reportinterval(l_it->ReportInterval);
                l_AisMessage.set_ownship(l_it->OwnShip);
                l_AisMessage.set_recentperiod(l_it->ReportPeriod);
                l_AisMessage.set_m_utc_hour(l_it->utc_hour);
                l_AisMessage.set_m_utc_min(l_it->utc_min);
                l_AisMessage.set_m_utc_sec(l_it->utc_sec);
                l_AisMessage.set_range_nm(l_it->Range_NM);
                l_AisMessage.set_brg(l_it->Brg);
                l_AisMessage.set_bcpa_valid(l_it->CPA_Valid);
                l_AisMessage.set_tcpa(l_it->TCPA);
                l_AisMessage.set_cpa(l_it->CPA);
                l_AisMessage.set_chshipname(l_it->ChShipName.toStdString());
                l_AisMessage.set_nationality(l_it->Nationality.toStdString());
                l_AisMessage.set_note(l_it->Note.toStdString());


//                 hg::utils::PointLL l_point(l_AisMessage.lon(),l_AisMessage.lat());
//                 if (hgConfigManager::m_sSysConfig->m_AreaLL.size() > 2
//                     && !hgConfigManager::m_sSysConfig->m_AreaLL.containsPoint(l_point,Qt::WindingFill))
//                 {
//                     return ;
//                 }


                if ( abs(l_AisMessage.lat()) > 90 || abs(l_AisMessage.lon() > 180) )
                {
                    return;
                }
                assert (l_AisMessage.hdg() < 1000000);
//                 if (hgConfigManager::m_sSysConfig->m_iTrackPredict == 0)
//                 {
                    hgShipAisMessage l_shipais;
                    if (l_qdbug)
                    {
                        qDebug () << "---------------" << l_AisMessage.mmsi().c_str();
					}
					if (l_Add180 == true)
					{
						hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 1);
					}
					else
					{
						hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 0);
					}
                    hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
                    hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
/*                }*/

            }
        }
    }
    else
    {
        hgTarget ais;
        if (msg.type() == GPSHDT || msg.type() == GPSHDM)
        {
            ais.HDG = msg.hdg();
        }
        else if (msg.type() == GPSRMC)
        {
            ais.Lat = msg.lat();
            ais.Lon = msg.lon();
            ais.ReportTicks = msg.time();
            ais.Spd = msg.speed();
            ais.COG = msg.course();
            //qDebug() << "GPSRMC" << msg.lat() << "  " << msg.lon() << "  " << msg.time() << "  "  << msg.speed() << "  " << QDateTime::fromTime_t(time(NULL)).toString("hh-mm-ss");
        }
        else if (msg.type() == GPSGGA)
        {
            ais.Lat = msg.lat();
            l_it->Lon = msg.lon();
            l_it->ReportTicks = msg.time();
            if (l_qdbug)
            {
                qDebug() << "GPSGGA" << msg.lat() << "  " << msg.lon() << "  " << msg.time() << "  " << QDateTime::fromTime_t(time(NULL)).toString("hh-mm-ss");
            }
        }


        ais.Source = AIS_DATA;
        ais.Result = AIS_FUSE;
        ais.Reserved = 0;
        ais.Rng = 0;
        ais.RadarBrg = 0;
        ais.Spd = 0;
        ais.Crs = 0;
        ais.Scans = 0;
        ais.Flags = 0;

        ais.MMSI = msg.mmsi().c_str();
        ais.ID = msg.mmsi().c_str();
        ais.Class = AIS_CLASS_A;
        ais.ReportTicks = msg.time();
        ais.Simulation = false;
        ais.Missing = false;
        ais.OwnShip = true;
        ais.ReportInterval = 0;
        ais.DimA = 0;
        ais.DimB = 0;
        ais.DimC = 0;
        ais.DimD = 0;
        ais.Range_NM = 0;
        ais.Brg = 0;
        ais.TCPA = 0;
        ais.CPA = 0;
        ais.SyncState = 0;
        ais.SlotTO = 0;
        ais.COG = 0;
        ais.HDG = 0;
        ais.SOG = 0;
        ais.Draft = 0;
        ais.ROTAIS = 0;
        ais.ChShipName = "Unknow";
        ais.ShipName = "Unknow";
        ais.IMO = 0;
        ais.CallSign = "Unknow";
        ais.Destination = "Unknow";
        ais.EquipmentType = -1;
        ais.ETA_Mo = -1;
        ais.ETA_Day = -1;
        ais.ETA_Hr = -1;
        ais.ETA_Min = -1;
        ais.Nationality = "Unknow";
        ais.Note = "Unknow";

        QMap<QString,hgTarget>::iterator l_itSta = hgTargetManager::m_mapStatic.find(ais.MMSI);
        QMap<QString,hgTarget>::iterator l_itCsv = hgTargetManager::m_mapShipData.find(ais.MMSI);
        //std::clock_t t2 = clock();
        //qDebug() << "find(...............)" << t2-t1 << m_mapStatic.size();
        bool l_findCsv = false,l_findStatic = false;
        if (l_itCsv != hgTargetManager::m_mapShipData.end())
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


//             ais.CallSign = aisData.CallSign;
//             ais.Destination = aisData.Destination;
//             ais.EquipmentType = aisData.EquipmentType;
//             ais.ETA_Mo = aisData.ETA_Mo;
//             ais.ETA_Day = aisData.ETA_Day;
//             ais.ETA_Hr = aisData.ETA_Hr;
//             ais.ETA_Min = aisData.ETA_Min;
//             ais.Draft = aisData.Draft;
        }
        if (l_itSta != hgTargetManager::m_mapStatic.end())
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
//             ais.IMO = aisData.IMO;
//             ais.ShipName = QString(aisData.ShipName).replace(QRegExp("@"), "");
//             //ais.ShipType = aisData.ShipType;
//             ais.CallSign = QString(aisData.CallSign).replace(QRegExp("@"), "");
//             ais.Destination = QString(aisData.Destination).replace(QRegExp("@"), "");
//             ais.EquipmentType = aisData.EquipmentType;
            ais.DimA = hgConfigManager::m_sSysConfig->m_dShipLength * 0.75;
            ais.DimB = hgConfigManager::m_sSysConfig->m_dShipLength * 0.25;
            ais.DimC = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.25;
            ais.DimD = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.75;
//             ais.ETA_Mo = aisData.ETA_Mo;
//             ais.ETA_Day = aisData.ETA_Day;
//             ais.ETA_Hr = aisData.ETA_Hr;
//             ais.ETA_Min = aisData.ETA_Min;
//             ais.Draft = aisData.Draft;

            ais.SetShipSize = true;
            ais.Length = hgConfigManager::m_sSysConfig->m_dShipLength;
            ais.Width = hgConfigManager::m_sSysConfig->m_dShipWidth;
        }
        hgTargetManager::m_mapTarget.insert(ais.ID,ais);

    }
    hgTargetManager::m_mapAis.UnLockAll();
    hgTargetManager::m_mapTarget.UnLockAll();
}

void hgGPSDataHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

// void hgGPSDataHandler::afterDb(DBArpaTargetHandler* db)
// {
//     delete db;
//     delete this;
// }

void hgGPSDataHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
