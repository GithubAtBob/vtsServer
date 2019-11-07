
#include "StdAfx.h"
#include "hgArpaAllHandler.h"

#include "message/RadarImagePack.pb.h"
#include "message/hgArpaAll.pb.h"
#include "frame/vtsServer.h"
#include "db/DBArpaAllHandler.h"
#include "Managers/hgTargetManager.h"
#include "Config/hgSysConfig.h"
#include "Managers/hgConfigManager.h"
#include "timer/hgPortTimerHandler.h"
#include "Managers/hgSendManager.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"
#include "LayerData/hgPolygonLayer.h"

//#define OnlySendFuse

hgArpaAllHandler::hgArpaAllHandler()
{

}

hgArpaAllHandler::~hgArpaAllHandler(void)
{
}

vtsRequestHandler::WorkMode hgArpaAllHandler::workMode()
{
	return Work_Delete_Manual;
}

void hgArpaAllHandler::handle(boost::asio::const_buffer& data)
{
	if (hgConfigManager::m_sSysConfig->m_radarServer != TurnOn)
	{
		delete this;
		return;
	}

	hgArpaAllPack l_Packet;
	l_Packet.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
	//msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));
	QByteArray l_AllPacket = QByteArray::fromStdString(l_Packet.arpadata());
	size_t l_allSize = l_AllPacket.size();
	size_t l_packetSize = sizeof(ARPA_TARGET_PACKET);
	int l_PacketCount = l_allSize / l_packetSize;
	{
		ArpaTargetPack l_mess;
		l_mess.set_number(-1);
		if (hgConfigManager::m_sSysConfig->m_FuseType == 1)
		{
			RadarFuseType(l_mess);
		}
		else if (hgConfigManager::m_sSysConfig->m_FuseType == 2)
		{
			OwnFuseType(l_mess);
		}
	}

	QMap<int ,ARPA_TARGET_PACKET*> l_textmap;
	for (int i = 0; i < l_PacketCount; i++)
	{
		ARPA_TARGET_PACKET* l_targetPacket = (ARPA_TARGET_PACKET*)(l_AllPacket.data() + l_packetSize * i);
		ArpaTargetPack msg;
		msg.set_number(l_targetPacket->number);
		msg.set_reserved(l_targetPacket->reserved);
		msg.set_rng(l_targetPacket->rng);
		msg.set_brg(l_targetPacket->brg);
		msg.set_orientation_size(l_targetPacket->orientation_size);
		msg.set_sog(l_targetPacket->sog);
		msg.set_cog(l_targetPacket->cog);
		msg.set_scans(l_targetPacket->scans);
		msg.set_flags(l_targetPacket->flags);
		msg.set_longitude(l_targetPacket->longitude);
		msg.set_latitude(l_targetPacket->latitude);

		if (l_targetPacket->sog == 65535)
		{
			continue;
		}
		if (l_targetPacket->cog == 65535)
		{
			continue;
		}

		int l_Source = ((quint8)l_targetPacket->flags & 128 )? RADAR_AIS_DATA : RADAR_RADAR_DATA;

		if (hgConfigManager::m_sSysConfig->m_useRadarAis == false)
		{
			if (l_Source == RADAR_AIS_DATA)
			{
				// 				QString l_MMSI = QString::number(l_targetPacket->scans);
				// 				if (hgTargetManager::m_mapRadarStatic.contains(l_MMSI))
				// 				{
				// 
				// 				}
				// 				else
				// 				{
				// 					RadarRequst msg;
				// 					msg.set_name("s_RadarServerOwn");
				// 					msg.set_mess(QString("info:tgt=%1").arg(l_targetPacket->number).toStdString());
				// 					hgTargetManager::m_mapAisRadar[l_MMSI] = QString::number(l_targetPacket->number);
				// 					hgSendManager::SendSpecifyMessage("RadarAsk",msg,this->connection(),"s_RadarServer");
				// 				}
				continue;
			}
			if (l_Source == RADAR_RADAR_DATA)
			{
				l_textmap[l_targetPacket->number] = l_targetPacket;
			}
		}
		if (hgConfigManager::m_sSysConfig->m_FuseType == 1)
		{
			RadarFuseType(msg);
		}
		else if (hgConfigManager::m_sSysConfig->m_FuseType == 2)
		{
			OwnFuseType(msg);
		}
	}
	{
		ArpaTargetPack l_mess;
		l_mess.set_number(-2);
		if (hgConfigManager::m_sSysConfig->m_FuseType == 1)
		{
			RadarFuseType(l_mess);
		}
		else if (hgConfigManager::m_sSysConfig->m_FuseType == 2)
		{
			OwnFuseType(l_mess);
		}
	}

	if (0/*hgConfigManager::m_sSysConfig->m_useRadarAis == false*/)
	{
		QFile l_File;
		l_File.setFileName(QString("./Data/ArpaTarget/info.txt"));
		if (l_File.open(QIODevice::Append))
		{
			QString l_line = "|--------------------------------|\n";
			l_File.write(l_line.toLatin1());
			for (auto iter = l_textmap.begin(); iter != l_textmap.end(); iter++)
			{
				ARPA_TARGET_PACKET* l_pa = iter.value();
				QString l_MMSI = QString::number(l_pa->scans);
				double l_aisLen = 0;
				double l_aisWidth = 0;
				if (hgTargetManager::m_mapRadarStatic.contains(l_MMSI))
				{
					hgTarget l_ais = hgTargetManager::m_mapRadarStatic.find(l_MMSI).value();
					l_aisLen = l_ais.Length;
					l_aisWidth = l_ais.Width;
					//continue;
				}
				else
				{
					continue;
				}
				int l_WH = l_pa->orientation_size;
				int l_width,l_len = 0;
				double l_hdg = (l_WH & 0x00000fff)*0.1;
				l_len = (l_WH & 0x003ff000) >> 12;
				l_width = (l_WH & 0xffc00000) >>22;
				l_line = QString("ID:%1, length %2, width %3, MMSI %4, Length %5, Width %6\n")
					.arg(l_pa->number).arg(l_len).arg(l_width)
					.arg(l_pa->scans).arg(l_aisLen).arg(l_aisWidth);
				l_File.write(l_line.toLatin1());
			}
			l_File.close();
		}
	}
	DBArpaAllHandler* dbHandler = new DBArpaAllHandler();
	dbHandler->pack = l_Packet;
	postToDB(dbHandler, boost::bind(&hgArpaAllHandler::afterDb, this, dbHandler));
}

void hgArpaAllHandler::timeout(time_t last)
{
	time_t now = time(NULL);
	std::cout << now-last << std::endl;
}

void hgArpaAllHandler::afterDb(DBArpaAllHandler* db)
{
	delete db;
	delete this;
}

void hgArpaAllHandler::WriteToFile(ArpaTargetPack msg)
{
	//return;
	if (hgConfigManager::m_sSysConfig->m_SaveFile == 1)
	{
		QFile l_File;
		l_File.setFileName(QString("./Data/ArpaTarget/%1").arg(hgConfigManager::m_sSysConfig->m_filename));
		if (l_File.open(QIODevice::Append))
		{
			QString l_line = QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13\n").arg(time(NULL))
				.arg(msg.number()).arg(msg.reserved()).arg(msg.rng())
				.arg(msg.brg()).arg(msg.orientation_size())
				.arg(msg.sog()).arg(msg.cog()).arg(msg.scans())
				.arg(msg.flags()).arg(msg.longitude()).arg(msg.latitude());
			l_File.write(l_line.toLatin1());
			l_File.close();
		}
	}
}

void hgArpaAllHandler::RadarFuseType(ArpaTargetPack msg)
{
	WriteToFile(msg);
	hgTarget l_target;

	mymap<QString,hgTarget>::iterator l_it;// = hgTargetManager::m_mapTarget.begin();
	mymap<QString,hgTarget>::iterator l_itRadar;// = hgTargetManager::m_mapRadar.begin();

	hgTargetManager::AddRadarAISData(msg,l_target);
	if (msg.number() == -1 || msg.number() == -2)
	{
		hgAisMessage l_AisMessage;
		l_AisMessage.set_radarid(QString::number(msg.number()).toStdString());
		hgShipAisMessage l_shipais;
		hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
		hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
		hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
		//delete this;
		return ;
	}
	if (hgTargetManager::m_mapShipData.contains(l_target.MMSI))
	{

	}
	else if (hgTargetManager::m_mapStatic.contains(l_target.MMSI))
	{
	}
// 	else if (hgTargetManager::m_mapRadarStatic.contains(l_target.MMSI))
// 	{
// 	}
	else
	{
		if (hgTargetManager::m_mapAisRadar.contains(l_target.MMSI))
		{
			RadarRequst msg;
			msg.set_name("s_RadarServerOwn");
			QString l_ID = hgTargetManager::m_mapAisRadar.find(l_target.MMSI).value();
			msg.set_mess(QString("info:tgt=%1").arg(l_ID).toStdString());
			hgSendManager::SendSpecifyMessage("RadarAsk",msg,this->connection(),"s_RadarServer");
		}
	}
	if (hgConfigManager::m_sSysConfig->m_GPSOpen == 1 && hgTargetManager::m_GPSMMSI.contains(l_target.MMSI))
	{
		//delete this;
		return ;
	}
	if (l_target.Result == AIS_FUSE /*&& !hgTargetManager::m_AlgorOwnMMSI.contains(l_target.MMSI)*/)
	{
		//delete this;
		return ;
	}
	if (l_target.Result == RADAR_FUSE && hgTargetManager::m_mapGpsRadar.contains(l_target.RadarID))
	{
		return ;
	}
	hgAisMessage l_SaveAis;
	//融合
	{
		if (l_target.MMSI == "0")
		{
			l_it = hgTargetManager::m_mapTarget.find(l_target.RadarID);
		}
		else
		{
			l_it = hgTargetManager::m_mapTarget.find(l_target.MMSI);
		}

		if (l_it != hgTargetManager::m_mapTarget.end())
		{
			hgAisMessage l_AisMessage;
			l_AisMessage.set_id(l_it->ID.toStdString());
			l_AisMessage.set_radarid(l_it->RadarID.toStdString());
			l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
			l_AisMessage.set_source(l_it->Source);
			l_AisMessage.set_result(l_it->Result);
			if (hgTargetManager::m_AlgorOwnMMSI.contains(l_it->MMSI))
			{
				l_AisMessage.set_result(AIS_FUSE);
			}
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
			if (!hgTargetManager::m_mapShipData.contains(l_it->MMSI)
				&& !hgTargetManager::m_mapStatic.contains(l_it->MMSI)
				&& hgTargetManager::m_mapRadarStatic.contains(l_it->MMSI))
			{
				hgTarget l_targetss = hgTargetManager::m_mapRadarStatic.find(l_it->MMSI).value();
				l_AisMessage.set_shipname(l_targetss.ShipName.toStdString());
				l_AisMessage.set_shiptype(l_targetss.ShipType.toStdString());
			}
			else
			{
				l_AisMessage.set_shipname(l_it->ShipName.toStdString());
				l_AisMessage.set_shiptype(l_it->ShipType.toStdString());
			}
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
			hgShipAisMessage l_shipais;
			bool l_turn = false;
			if (hgTargetManager::m_AlgorOwnMMSI.contains(l_AisMessage.mmsi().c_str()))
			{
				l_turn = OwnShipTurnDir(l_AisMessage);
			}
			if (l_turn == true)
			{
				hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 1);
			}
			else
			{
				hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
			}
			hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
			hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
			//qDebug () << l_it->MMSI << "  " << l_it->RadarID << "  " << l_it->Source << "  " << l_it->Result << l_it->RadarGUID;
		}
		else
		{
			//qDebug () << l_target.RadarID << l_target.MMSI;
		}
	}

	//雷达
	{
		bool l_send = false;
		if (l_target.Source == RADAR_AIS_DATA)
		{
			l_it = hgTargetManager::m_mapAis.find(l_target.MMSI);
			if (l_it != hgTargetManager::m_mapAis.end())
			{
				l_send = true;
			}
		}
		else if (l_target.Source == RADAR_RADAR_DATA)
		{
			if (l_target.MMSI == "0")
			{
				l_it = hgTargetManager::m_mapRadar.find(l_target.ID);
				if (l_it != hgTargetManager::m_mapRadar.end())
				{
					l_send = true;
				}
			}
			else
			{
				l_it = hgTargetManager::m_mapRadar.find(l_target.MMSI);
				if (l_it != hgTargetManager::m_mapRadar.end())
				{
					l_send = true;
				}
			}
		}
		if (l_send)
		{
			hgAisMessage l_AisMessage;
			l_AisMessage.set_id(l_it->ID.toStdString());
			l_AisMessage.set_radarid(l_it->RadarID.toStdString());
			l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
			l_AisMessage.set_source(l_it->Source);
			l_AisMessage.set_result(l_it->Result);
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
			hgShipAisMessage l_shipais;
			bool l_turn = false;
			if (hgTargetManager::m_AlgorOwnMMSI.contains(l_AisMessage.mmsi().c_str()))
			{
				l_turn = OwnShipTurnDir(l_AisMessage);
			}
			if (l_turn == true)
			{
				hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 1);
			}
			else
			{
				hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
			}
			hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
			hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
			l_SaveAis = l_AisMessage;

		}
	}

	hgTargetManager::m_mapAis.UnLockAll();
	hgTargetManager::m_mapRadar.UnLockAll();
	hgTargetManager::m_mapTarget.UnLockAll();

	//     DBArpaTargetHandler* dbHandler = new DBArpaTargetHandler();
	//     dbHandler->ArpaTarget = l_SaveAis;
	//     postToDB(dbHandler, boost::bind(&hgArpaTargetHandler::afterDb, this, dbHandler));
}

void hgArpaAllHandler::OwnFuseType(ArpaTargetPack msg)
{
	//         if (msg.number() == -1 || msg.number() == -2)
	//         {
	//             delete this;
	//             return ;
	//         }
	WriteToFile(msg);
	hgTarget l_target;

	mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapTarget.begin();
	mymap<QString,hgTarget>::iterator l_itRadar = hgTargetManager::m_mapRadar.begin();

	hgTargetManager::AddRadarData(msg,l_target);
	if (msg.number() == -1 || msg.number() == -2)
	{
		hgAisMessage l_AisMessage;
		l_AisMessage.set_radarid(QString::number(msg.number()).toStdString());
		hgShipAisMessage l_shipais;
		hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
		hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
		hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
		//delete this;
		return ;
	}
	hgAisMessage l_SaveAis;
	if (l_target.Source == RADAR_AIS_DATA)
	{
		if (hgTargetManager::m_GPSMMSI.contains(l_target.MMSI))
		{
			return ;
			QSqlDatabase database = this->connection()->server().openDBConnection();
			hgSqlOperator l_sqlOperator(database);
			hgTargetManager::Assembly(l_target,l_sqlOperator);
			this->connection()->server().closeDBConnection(database);
			//delete this;
			return ;
		}
		if (hgTargetManager::m_mapShipData.contains(l_target.MMSI))
		{

		}
		else if (hgTargetManager::m_mapStatic.contains(l_target.MMSI))
		{
		}
// 		else if (hgTargetManager::m_mapRadarStatic.contains(l_target.MMSI))
// 		{
// 		}
		else
		{

// 			if (hgTargetManager::m_mapAisRadar.contains(l_target.MMSI))
// 			{
// 				RadarRequst msg;
// 				msg.set_name("s_RadarServerOwn");
// 				QString l_ID = hgTargetManager::m_mapAisRadar.find(l_target.MMSI).value();
// 				msg.set_mess(QString("info:tgt=%1").arg(l_ID).toStdString());
// 				hgSendManager::SendSpecifyMessage("RadarAsk",msg,this->connection(),"s_RadarServer");
// 			}
		}
		QSqlDatabase database = this->connection()->server().openDBConnection();
		hgSqlOperator l_sqlOperator(database);
		hgTargetManager::Assembly(l_target,l_sqlOperator);
		this->connection()->server().closeDBConnection(database);
		//hgTargetManager::m_mapTarget.insert(l_target.ID,l_target);

		if (hgTargetManager::m_mapRadar.find(l_target.RadarID) != hgTargetManager::m_mapRadar.end()
			&& !hgTargetManager::m_mapStatic.contains(l_target.MMSI)
			&& !hgTargetManager::m_mapShipData.contains(l_target.MMSI))
		{
			if (hgTargetManager::m_AlgorOwnMMSI.contains(l_target.MMSI))
			{
				qDebug() << "????" << hgTargetManager::m_mapStatic.contains(l_target.MMSI) << l_target.MMSI;
			}
			else
			{
				hgTarget l_r = hgTargetManager::m_mapRadar.find(l_target.RadarID).value();
				l_target.DimA = l_r.DimA;
				l_target.DimB = l_r.DimB;
				l_target.DimC = l_r.DimC;
				l_target.DimD = l_r.DimD;
				l_target.Length = l_r.Length;
				l_target.Width = l_r.Width;
				l_target.SetShipSize = false;
			}
		}

		mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapTarget.begin();
		mymap<QString,hgTarget>::iterator l_itAis = hgTargetManager::m_mapAis.begin();
		mymap<QString,hgTarget>::iterator l_itRadar = hgTargetManager::m_mapRadar.begin();
		/////融合数据
		l_it = hgTargetManager::m_mapTarget.find(l_target.ID);
		if (l_it != hgTargetManager::m_mapTarget.end())
		{
			if (l_it->Result == AIS_FUSE && !hgTargetManager::m_AlgorOwnMMSI.contains(l_target.MMSI))
			{
				return ;
			}
			hgAisMessage l_AisMessage;

			l_AisMessage.set_id(l_it->ID.toStdString());
			l_AisMessage.set_radarid(l_it->RadarID.toStdString());
			l_AisMessage.set_radarguid(l_it->RadarGUID.toStdString());
			l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
			l_AisMessage.set_source(FUSE_DATA);
			l_AisMessage.set_result(l_it->Result);
			if (hgTargetManager::m_AlgorOwnMMSI.contains(l_it->MMSI))
			{
				l_AisMessage.set_result(AIS_FUSE);
			}
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

			hg::utils::PointLL l_point(l_AisMessage.lon(),l_AisMessage.lat());
			if (hgConfigManager::m_sSysConfig->m_AreaLL.size() > 2
				&& !hgConfigManager::m_sSysConfig->m_AreaLL.containsPoint(l_point,Qt::WindingFill))
			{
				return ;
			}


			if ( abs(l_AisMessage.lat()) > 90 || abs(l_AisMessage.lon() > 180) )
			{
				return;
			}
			assert (l_AisMessage.hdg() < 1000000);
			if (hgConfigManager::m_sSysConfig->m_iTrackPredict == 0)
			{
				hgShipAisMessage l_shipais;
				bool l_turn = false;
				if (hgTargetManager::m_AlgorOwnMMSI.contains(l_AisMessage.mmsi().c_str()))
				{
					l_turn = OwnShipTurnDir(l_AisMessage);
					if (l_AisMessage.mmsi() == "413796235")
					{
						qDebug() << "413796235" << l_turn;
					}
				}
				if (l_turn == true)
				{
					hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 1);
				}
				else
				{
					hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
				}

				//融合物标强制使用 雷达数据
				if (l_AisMessage.result() == AIS_RADAR_FUSE)
				{
					if (hgTargetManager::m_mapRadar.find(l_AisMessage.radarid().c_str()) != hgTargetManager::m_mapRadar.end()
						&& !hgTargetManager::m_AlgorOwnMMSI.contains(l_AisMessage.mmsi().c_str()))
					{
						auto l_test = hgTargetManager::m_mapRadar.find(l_AisMessage.radarid().c_str());
						l_AisMessage.set_dima(l_test->DimA);
						l_AisMessage.set_dimb(l_test->DimB);
						l_AisMessage.set_dimc(l_test->DimC);
						l_AisMessage.set_dimd(l_test->DimD);
					}
				}
				hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
				hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
			}
		}   
#ifndef OnlySendFuse
		//ais 目标
		{
			mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapAis.find(l_target.ID);
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


				hg::utils::PointLL l_point(l_AisMessage.lon(),l_AisMessage.lat());
				if (hgConfigManager::m_sSysConfig->m_AreaLL.size() > 2
					&& !hgConfigManager::m_sSysConfig->m_AreaLL.containsPoint(l_point,Qt::WindingFill))
				{
					return ;
				}


				if ( abs(l_AisMessage.lat()) > 90 || abs(l_AisMessage.lon() > 180) )
				{
					return;
				}
				assert (l_AisMessage.hdg() < 1000000);
				if (hgConfigManager::m_sSysConfig->m_iTrackPredict == 0)
				{
					hgShipAisMessage l_shipais;
					bool l_turn = false;
					if (hgTargetManager::m_AlgorOwnMMSI.contains(l_AisMessage.mmsi().c_str()))
					{
						l_turn = OwnShipTurnDir(l_AisMessage);
// 						if (l_AisMessage.mmsi() == "413796235")
// 						{
// 							qDebug() << "413796235 +++ " << l_turn;
// 						}
					}
					if (l_turn == true)
					{
						hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 1);
					}
					else
					{
						hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
					}
					hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
					hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
				}
				l_SaveAis = l_AisMessage;

			}
		}
#endif
	}
	else
	{
		//融合
		{
			l_it = hgTargetManager::m_mapTarget.find(l_target.ID);
			QMap<QString,hgResult>::iterator l_itResult;
			if (l_it == hgTargetManager::m_mapTarget.end())
			{
				for (l_itResult = hgTargetManager::m_mapResult.begin(); l_itResult != hgTargetManager::m_mapResult.end(); ++l_itResult)
				{
					if (l_itResult->RadarGUID == l_target.ID)
					{
						l_it = hgTargetManager::m_mapTarget.find(l_itResult->ID);
						break;
					}
				}
			}
			if (l_it != hgTargetManager::m_mapTarget.end())
			{
				//                 for (int g = 0; g < hgTargetManager::m_GPSMMSI.size(); g++)
				//                 {
				//                     QString l_gMMSI = hgTargetManager::m_GPSMMSI.at(g);
				//                     if (hgTargetManager::m_mapResult.contains(l_gMMSI))
				//                     {
				//                         qDebug () << "111";
				//                         hgResult l_gResult = hgTargetManager::m_mapResult.find(l_gMMSI).value();
				//                         qDebug () << "222";
				//                         if (l_gResult.Count >= hgTargetManager::m_FuseSuccess)
				//                         {
				//                             if (l_gResult.RadarID == l_it->RadarID || l_itResult->ID == l_gMMSI)
				//                             {
				//                                 return ;
				//                             }
				//                         }
				//                     }
				//                 }

// 				if (hgTargetManager::m_mapRadarStatic.contains(l_it->MMSI) && !hgTargetManager::m_mapResult.contains(l_it->MMSI))
// 				{
// 					hgTarget l_static = hgTargetManager::m_mapRadarStatic.find(l_it->MMSI).value();
// 					l_it->IMO = l_static.IMO;
// 					l_it->CallSign = l_static.CallSign;
// 					l_it->ShipName = l_static.ShipName;
// 					l_it->Destination = l_static.Destination;
// 					l_it->DimA = l_static.DimA;
// 					l_it->DimB = l_static.DimB;
// 					l_it->DimC = l_static.DimC;
// 					l_it->DimD = l_static.DimD;
// 					l_it->Length = l_static.Length;
// 					l_it->SetShipSize = l_static.SetShipSize;
// 				}
				if (hgTargetManager::m_mapShipData.contains(l_it->MMSI))
				{
					hgTarget l_target = hgTargetManager::m_mapShipData.find(l_it->MMSI).value();
					l_it->IMO = l_target.IMO;
					l_it->ShipName = l_target.ShipName;
					l_it->DimA = l_target.DimA;
					l_it->DimB = l_target.DimB;
					l_it->DimC = l_target.DimC;
					l_it->DimD = l_target.DimD;
					l_it->Length = l_target.DimA + l_target.DimB;
					l_it->Width = l_target.DimC + l_target.DimD; 
					l_it->SetShipSize = false;


					l_it->CallSign = l_target.CallSign;
					l_it->Destination = l_target.Destination;
					l_it->EquipmentType = l_target.EquipmentType;
					l_it->ETA_Mo = l_target.ETA_Mo;
					l_it->ETA_Day = l_target.ETA_Day;
					l_it->ETA_Hr = l_target.ETA_Hr;
					l_it->ETA_Min = l_target.ETA_Min;
					l_it->Draft = l_target.Draft;
				}
				if (hgTargetManager::m_mapStatic.contains(l_it->MMSI))
				{
					hgTarget l_target = hgTargetManager::m_mapStatic.find(l_it->MMSI).value();
					{
						l_it->IMO = l_target.IMO;
						l_it->ShipName = l_target.ShipName;
						l_it->ShipType = l_target.ShipType;
						l_it->DimA = l_target.DimA;
						l_it->DimB = l_target.DimB;
						l_it->DimC = l_target.DimC;
						l_it->DimD = l_target.DimD;
						l_it->Length = l_target.Length;
						l_it->Width = l_target.Width;
						l_it->SetShipSize = l_target.SetShipSize;
					}
					l_it->CallSign = l_target.CallSign;
					l_it->Destination = l_target.Destination;
					l_it->EquipmentType = l_target.EquipmentType;
					l_it->ETA_Mo = l_target.ETA_Mo;
					l_it->ETA_Day = l_target.ETA_Day;
					l_it->ETA_Hr = l_target.ETA_Hr;
					l_it->ETA_Min = l_target.ETA_Min;
					l_it->Draft = l_target.Draft;

					l_it->SetShipSize = l_target.SetShipSize;

					l_it->ChShipName = l_target.ChShipName;
					l_it->Nationality = l_target.Nationality;
					l_it->Note = l_target.Note;
				}
				if (hgTargetManager::m_GPSMMSI.contains(l_it->MMSI))
				{
					return ;
				}
				hgAisMessage l_AisMessage;
				l_AisMessage.set_id(l_it->ID.toStdString());
				l_AisMessage.set_radarid(l_it->RadarID.toStdString());
				l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
				l_AisMessage.set_source(l_it->Source);
				l_AisMessage.set_result(l_it->Result);
				if (hgTargetManager::m_AlgorOwnMMSI.contains(l_it->MMSI))
				{
					l_AisMessage.set_result(AIS_FUSE);
				}
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
				hgShipAisMessage l_shipais;
				bool l_turn = false;
				if (hgTargetManager::m_AlgorOwnMMSI.contains(l_AisMessage.mmsi().c_str()))
				{
					l_turn = OwnShipTurnDir(l_AisMessage);
// 					if (l_AisMessage.mmsi() == "413796235")
// 					{
// 						qDebug() << l_turn;
// 					}
				}
				if (l_turn == true)
				{
					hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 1);
				}
				else
				{
					hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
				}

				//融合物标强制使用 雷达数据
				if (l_AisMessage.result() == AIS_RADAR_FUSE)
				{
					if (hgTargetManager::m_mapRadar.find(l_AisMessage.radarid().c_str()) != hgTargetManager::m_mapRadar.end()
						&& !hgTargetManager::m_AlgorOwnMMSI.contains(l_AisMessage.mmsi().c_str()))
					{
						auto l_test = hgTargetManager::m_mapRadar.find(l_AisMessage.radarid().c_str());
						l_AisMessage.set_dima(l_test->DimA);
						l_AisMessage.set_dimb(l_test->DimB);
						l_AisMessage.set_dimc(l_test->DimC);
						l_AisMessage.set_dimd(l_test->DimD);
					}
				}
				hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
				hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
			}
		}

#ifndef OnlySendFuse
		//雷达
		{
			mymap<QString,hgTarget>::iterator l_itRadar = hgTargetManager::m_mapRadar.find(l_target.ID);
			if (l_itRadar != hgTargetManager::m_mapRadar.end())
			{
				hgAisMessage l_AisMessage;
				l_AisMessage.set_id(l_itRadar->ID.toStdString());
				l_AisMessage.set_radarid(l_itRadar->RadarID.toStdString());
				l_AisMessage.set_mmsi(l_itRadar->MMSI.toStdString());
				l_AisMessage.set_source(l_itRadar->Source);
				l_AisMessage.set_result(l_itRadar->Result);
				l_AisMessage.set_reserved(l_itRadar->Reserved);
				l_AisMessage.set_rng(l_itRadar->Rng);
				l_AisMessage.set_radarbrg(l_itRadar->RadarBrg);
				l_AisMessage.set_spd(l_itRadar->Spd);
				l_AisMessage.set_crs(l_itRadar->Crs);
				l_AisMessage.set_scans(l_itRadar->Scans);
				l_AisMessage.set_flags(l_itRadar->Flags);
				l_AisMessage.set_mid(l_itRadar->MID);
				l_AisMessage.set_class_(l_itRadar->Class);
				l_AisMessage.set_imo(l_itRadar->IMO);
				l_AisMessage.set_length(l_itRadar->Length);
				l_AisMessage.set_width(l_itRadar->Width);
				l_AisMessage.set_recentperiod(l_itRadar->ReportPeriod);
				l_AisMessage.set_navstatus(l_itRadar->NavStatus);
				l_AisMessage.set_rotais(l_itRadar->ROTAIS);
				l_AisMessage.set_sog(l_itRadar->SOG);
				l_AisMessage.set_lon(l_itRadar->Lon);
				l_AisMessage.set_lat(l_itRadar->Lat);
				l_AisMessage.set_cog(l_itRadar->COG);
				l_AisMessage.set_hdg(l_itRadar->HDG);
				l_AisMessage.set_imo(l_itRadar->IMO);
				l_AisMessage.set_callsign(l_itRadar->CallSign.toStdString());
				l_AisMessage.set_shipname(l_itRadar->ShipName.toStdString());
				l_AisMessage.set_shiptype(l_itRadar->ShipType.toStdString());
				l_AisMessage.set_posaccuracy(l_itRadar->PosAccuracy);
				l_AisMessage.set_equipmenttype(l_itRadar->EquipmentType);
				l_AisMessage.set_eta_mo(l_itRadar->ETA_Mo);
				l_AisMessage.set_eta_day(l_itRadar->ETA_Day);
				l_AisMessage.set_eta_hr(l_itRadar->ETA_Hr);
				l_AisMessage.set_eta_min(l_itRadar->ETA_Min);
				l_AisMessage.set_draft(l_itRadar->Draft);
				l_AisMessage.set_destination(l_itRadar->Destination.toStdString());
				l_AisMessage.set_syncstate(l_itRadar->SyncState);
				l_AisMessage.set_slotto(l_itRadar->SlotTO);
				l_AisMessage.set_dima(l_itRadar->DimA);
				l_AisMessage.set_dimb(l_itRadar->DimB);
				l_AisMessage.set_dimc(l_itRadar->DimC);
				l_AisMessage.set_dimd(l_itRadar->DimD);
				l_AisMessage.set_length(l_itRadar->Length);
				l_AisMessage.set_width(l_itRadar->Width);
				l_AisMessage.set_setshipsize(l_itRadar->SetShipSize);
				l_AisMessage.set_reportticks(l_itRadar->ReportTicks);
				l_AisMessage.set_simulation(l_itRadar->Simulation);
				l_AisMessage.set_reportinterval(l_itRadar->ReportInterval);
				l_AisMessage.set_ownship(l_itRadar->OwnShip);
				l_AisMessage.set_recentperiod(l_itRadar->ReportPeriod);
				l_AisMessage.set_m_utc_hour(l_itRadar->utc_hour);
				l_AisMessage.set_m_utc_min(l_itRadar->utc_min);
				l_AisMessage.set_m_utc_sec(l_itRadar->utc_sec);
				l_AisMessage.set_range_nm(l_itRadar->Range_NM);
				l_AisMessage.set_brg(l_itRadar->Brg);
				l_AisMessage.set_bcpa_valid(l_itRadar->CPA_Valid);
				l_AisMessage.set_tcpa(l_itRadar->TCPA);
				l_AisMessage.set_cpa(l_itRadar->CPA);
				l_AisMessage.set_chshipname(l_itRadar->ChShipName.toStdString());
				l_AisMessage.set_nationality(l_itRadar->Nationality.toStdString());
				l_AisMessage.set_note(l_itRadar->Note.toStdString());
				hgShipAisMessage l_shipais;
				bool l_turn = false;
				if (hgTargetManager::m_AlgorOwnMMSI.contains(l_AisMessage.mmsi().c_str()))
				{
					l_turn = OwnShipTurnDir(l_AisMessage);
// 					if (l_AisMessage.mmsi() == "413796235")
// 					{
// 						qDebug() << l_turn;
// 					}
				}
				if (l_turn == true)
				{
					hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais, 1);
				}
				else
				{
					hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
				}
				hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
				hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
				l_SaveAis = l_AisMessage;

			}
		}
#endif
		hgTargetManager::m_mapRadar.UnLockAll();
		hgTargetManager::m_mapTarget.UnLockAll();
	}

	//     DBArpaTargetHandler* dbHandler = new DBArpaTargetHandler();
	//     dbHandler->ArpaTarget = l_SaveAis;
	//     postToDB(dbHandler, boost::bind(&hgArpaTargetHandler::afterDb, this, dbHandler));
}

bool hgArpaAllHandler::OwnShipTurnDir(hgAisMessage msg)
{
	bool l_NorthArea = false;
	bool l_SouthArea = false;
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

	if (l_NorthArea == true && l_SouthArea == true)
	{
	}
	else
	{
		return false;
	}

	mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapTarget.find(msg.mmsi().c_str());
	if (l_it != hgTargetManager::m_mapTarget.end())
	{
		hg::utils::PointLL l_GPPoint(l_it->Lon,l_it->Lat);
		int l_CurPos;//当前位置
		if (l_NorthAreaLL.containsPoint(l_GPPoint, Qt::WindingFill))
		{
			l_CurPos = SPNorthArea;
		}
		else if (l_SouthAreaLL.containsPoint(l_GPPoint, Qt::WindingFill))
		{
			l_CurPos = SPSouthArea;
		}
		else
		{
			l_CurPos = SPUnknow;
		}
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
					
					return true;
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
					return true;
				}
			}
			else if (l_position == SPNorthToSouth)
			{
				if (l_CurPos == SPSouthArea)
				{
					hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()] = SPSouthArea;
					return true;
				}
				else
				{
					return true;
				}
			}
			else if (l_position == SPSouthToNorth)
			{
				if (l_CurPos == SPNorthArea)
				{
					hgAlarmManager::m_ShipPosition[msg.mmsi().c_str()] = SPNorthArea;

					//return true;
				}
			}
		}
		else
		{
			hgAlarmManager::m_ShipPosition.insert(msg.mmsi().c_str(),l_CurPos);
		}
	}

	return false;
}

void hgArpaAllHandler::afterResponse(const boost::system::error_code& e)
{
	delete this;
}
