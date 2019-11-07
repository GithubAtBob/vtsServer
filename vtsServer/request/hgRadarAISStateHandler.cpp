
#include "StdAfx.h"
#include "hgRadarAISStateHandler.h"

#include "message/RadarImagePack.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgTargetManager.h"
#include "Config/hgSysConfig.h"
#include "Managers/hgConfigManager.h"
#include "timer/hgPortTimerHandler.h"
#include "Managers/hgSendManager.h"

hgRadarAISStateHandler::hgRadarAISStateHandler()
{

}

hgRadarAISStateHandler::~hgRadarAISStateHandler(void)
{
}

vtsRequestHandler::WorkMode hgRadarAISStateHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgRadarAISStateHandler::handle(boost::asio::const_buffer& data)
{
    if (hgConfigManager::m_sSysConfig->m_radarServer != TurnOn)
    {
        delete this;
        return;
    }

	//return ;
    RadarAISStatePack msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));
    unsigned int l_WH = msg.dimensions();
    int a,b,c,d;
//     d = (l_WH & 0xFC000000) >> 26;//6
//     c = (l_WH & 0x03F00000) >> 20;//6
//     b = (l_WH & 0x000FF800) >> 11;//9
//     a = (l_WH & 0x000007FC) >> 2;//9
    d = (l_WH & 0x0000003F)/* >> 26*/;//6
    c = (l_WH & 0x00000FC0) >> 6/* >> 20*/;//6
    b = (l_WH & 0x001FF000) >>12/*>> 11*/;//9
	a = (l_WH & 0x7FE00000) >>21/*>> 2*/;//9
	if ( a == 0 || b == 0 || c == 0 || d == 0)
	{
		delete this;
		return ;
	}
    QMap<QString,QString>::iterator l_iter = hgTargetManager::m_mapAisRadar.begin();
    for ( l_iter; l_iter != hgTargetManager::m_mapAisRadar.end(); l_iter++ )
    {
        if (l_iter.value().toInt() == msg.number())
        {
            QString l_MMSI = l_iter.key();

            {
                hgTarget l_static;
                l_static.MMSI = l_MMSI;
                l_static.IMO = msg.imo();
                l_static.CallSign = msg.callsign().c_str();
                l_static.ShipName = msg.name().c_str();
                l_static.Destination = msg.destination().c_str();
                if ( a == 0 || b == 0 || c == 0 || d == 0)
                {
                    l_static.DimA = hgConfigManager::m_sSysConfig->m_dShipLength * 0.75;
                    l_static.DimB = hgConfigManager::m_sSysConfig->m_dShipLength * 0.25;
                    l_static.DimC = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.25;
                    l_static.DimD = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.75;
                    l_static.Length = hgConfigManager::m_sSysConfig->m_dShipLength;
                    l_static.Width = hgConfigManager::m_sSysConfig->m_dShipWidth;
                    l_static.SetShipSize = true;
                }
//                 else if (a+b < 20
//                     || a+b > 250
//                     || c+d < 2 
//                     || c+d > 50)
//                 {
//                     l_static.DimA = hgConfigManager::m_sSysConfig->m_dShipLength * 0.75;
//                     l_static.DimB = hgConfigManager::m_sSysConfig->m_dShipLength * 0.25;
//                     l_static.DimC = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.25;
//                     l_static.DimD = hgConfigManager::m_sSysConfig->m_dShipWidth * 0.75;
//                     l_static.Length = hgConfigManager::m_sSysConfig->m_dShipLength;
//                     l_static.Width = hgConfigManager::m_sSysConfig->m_dShipWidth;
//                     l_static.SetShipSize = true;
//                 }
                else
                {
                    l_static.DimA = a;
                    l_static.DimB = b;
                    l_static.DimC = c;
                    l_static.DimD = d;
                    l_static.Length = a+b;
                    l_static.Width = c+d;
                    l_static.SetShipSize = false;
                }
                hgTargetManager::m_mapRadarStatic.insert(l_MMSI,l_static);
			}

// 			if (hgTargetManager::m_mapStatic.contains(l_MMSI))
// 			{
// 				//qDebug () << "have static";
// 				return ;
// 			}
// 
//             mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapTarget.find(l_MMSI);
//             if (l_it != hgTargetManager::m_mapTarget.end() )
//             {
//                 l_it->IMO = msg.imo();
//                 l_it->CallSign = msg.callsign().c_str();
//                 l_it->ShipName = msg.name().c_str();
//                 l_it->Destination = msg.destination().c_str();
//                 if ( a == 0 || b == 0 || c == 0 || d == 0)
//                 {
//                 }
//                 else if (hgConfigManager::m_sSysConfig->m_radarStatic == 0)
//                 {
//                 }
//                 else
//                 {
//                     l_it->DimA = a;
//                     l_it->DimB = b;
//                     l_it->DimC = c;
//                     l_it->DimD = d;
//                     l_it->Length = a+b;
//                     l_it->Width = c+d;
//                     l_it->SetShipSize = false;
//                 }
//                 hgAisMessage l_AisMessage;
//                 l_AisMessage.set_id(l_it->ID.toStdString());
//                 l_AisMessage.set_radarid(l_it->RadarID.toStdString());
//                 l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
//                 l_AisMessage.set_source(l_it->Source);
//                 l_AisMessage.set_result(l_it->Result);
//                 if (hgTargetManager::m_AlgorOwnMMSI.contains(l_it->MMSI))
//                 {
//                     l_AisMessage.set_result(AIS_FUSE);
//                 }
//                 l_AisMessage.set_reserved(l_it->Reserved);
//                 l_AisMessage.set_rng(l_it->Rng);
//                 l_AisMessage.set_radarbrg(l_it->RadarBrg);
//                 l_AisMessage.set_spd(l_it->Spd);
//                 l_AisMessage.set_crs(l_it->Crs);
//                 l_AisMessage.set_scans(l_it->Scans);
//                 l_AisMessage.set_flags(l_it->Flags);
//                 l_AisMessage.set_mid(l_it->MID);
//                 l_AisMessage.set_class_(l_it->Class);
//                 l_AisMessage.set_imo(l_it->IMO);
//                 l_AisMessage.set_length(l_it->Length);
//                 l_AisMessage.set_width(l_it->Width);
//                 l_AisMessage.set_recentperiod(l_it->ReportPeriod);
//                 l_AisMessage.set_navstatus(l_it->NavStatus);
//                 l_AisMessage.set_rotais(l_it->ROTAIS);
//                 l_AisMessage.set_sog(l_it->SOG);
//                 l_AisMessage.set_lon(l_it->Lon);
//                 l_AisMessage.set_lat(l_it->Lat);
//                 l_AisMessage.set_cog(l_it->COG);
//                 l_AisMessage.set_hdg(l_it->HDG);
//                 l_AisMessage.set_imo(l_it->IMO);
//                 l_AisMessage.set_callsign(l_it->CallSign.toStdString());
//                 l_AisMessage.set_shipname(l_it->ShipName.toStdString());
//                 l_AisMessage.set_shiptype(l_it->ShipType.toStdString());
//                 l_AisMessage.set_posaccuracy(l_it->PosAccuracy);
//                 l_AisMessage.set_equipmenttype(l_it->EquipmentType);
//                 l_AisMessage.set_eta_mo(l_it->ETA_Mo);
//                 l_AisMessage.set_eta_day(l_it->ETA_Day);
//                 l_AisMessage.set_eta_hr(l_it->ETA_Hr);
//                 l_AisMessage.set_eta_min(l_it->ETA_Min);
//                 l_AisMessage.set_draft(l_it->Draft);
//                 l_AisMessage.set_destination(l_it->Destination.toStdString());
//                 l_AisMessage.set_syncstate(l_it->SyncState);
//                 l_AisMessage.set_slotto(l_it->SlotTO);
//                 l_AisMessage.set_dima(l_it->DimA);
//                 l_AisMessage.set_dimb(l_it->DimB);
//                 l_AisMessage.set_dimc(l_it->DimC);
//                 l_AisMessage.set_dimd(l_it->DimD);
//                 l_AisMessage.set_length(l_it->Length);
//                 l_AisMessage.set_width(l_it->Width);
//                 l_AisMessage.set_setshipsize(l_it->SetShipSize);
//                 l_AisMessage.set_reportticks(l_it->ReportTicks);
//                 l_AisMessage.set_simulation(l_it->Simulation);
//                 l_AisMessage.set_reportinterval(l_it->ReportInterval);
//                 l_AisMessage.set_ownship(l_it->OwnShip);
//                 l_AisMessage.set_recentperiod(l_it->ReportPeriod);
//                 l_AisMessage.set_m_utc_hour(l_it->utc_hour);
//                 l_AisMessage.set_m_utc_min(l_it->utc_min);
//                 l_AisMessage.set_m_utc_sec(l_it->utc_sec);
//                 l_AisMessage.set_range_nm(l_it->Range_NM);
//                 l_AisMessage.set_brg(l_it->Brg);
//                 l_AisMessage.set_bcpa_valid(l_it->CPA_Valid);
//                 l_AisMessage.set_tcpa(l_it->TCPA);
//                 l_AisMessage.set_cpa(l_it->CPA);
//                 l_AisMessage.set_chshipname(l_it->ChShipName.toStdString());
//                 l_AisMessage.set_nationality(l_it->Nationality.toStdString());
//                 l_AisMessage.set_note(l_it->Note.toStdString());
//                 hgShipAisMessage l_shipais;
//                 hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
//                 hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
//                 hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
//             }
//             l_it = hgTargetManager::m_mapAis.find(l_MMSI);
//             if (l_it != hgTargetManager::m_mapAis.end())
//             {
//                 l_it->IMO = msg.imo();
//                 l_it->CallSign = msg.callsign().c_str();
//                 l_it->ShipName = msg.name().c_str();
//                 l_it->Destination = msg.destination().c_str();
//                 if ( a == 0 && b == 0 && c == 0 & d == 0)
//                 {
//                 }
//                 else if (hgConfigManager::m_sSysConfig->m_radarStatic == 0)
//                 {
//                 }
//                 else
//                 {
//                     l_it->DimA = a;
//                     l_it->DimB = b;
//                     l_it->DimC = c;
//                     l_it->DimD = d;
//                     l_it->Length = a+b;
//                     l_it->Width = c+d;
//                     l_it->SetShipSize = false;
//                 }
//                 hgAisMessage l_AisMessage;
//                 l_AisMessage.set_id(l_it->ID.toStdString());
//                 l_AisMessage.set_radarid(l_it->RadarID.toStdString());
//                 l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
//                 l_AisMessage.set_source(l_it->Source);
//                 l_AisMessage.set_result(l_it->Result);
//                 l_AisMessage.set_reserved(l_it->Reserved);
//                 l_AisMessage.set_rng(l_it->Rng);
//                 l_AisMessage.set_radarbrg(l_it->RadarBrg);
//                 l_AisMessage.set_spd(l_it->Spd);
//                 l_AisMessage.set_crs(l_it->Crs);
//                 l_AisMessage.set_scans(l_it->Scans);
//                 l_AisMessage.set_flags(l_it->Flags);
//                 l_AisMessage.set_mid(l_it->MID);
//                 l_AisMessage.set_class_(l_it->Class);
//                 l_AisMessage.set_imo(l_it->IMO);
//                 l_AisMessage.set_length(l_it->Length);
//                 l_AisMessage.set_width(l_it->Width);
//                 l_AisMessage.set_recentperiod(l_it->ReportPeriod);
//                 l_AisMessage.set_navstatus(l_it->NavStatus);
//                 l_AisMessage.set_rotais(l_it->ROTAIS);
//                 l_AisMessage.set_sog(l_it->SOG);
//                 l_AisMessage.set_lon(l_it->Lon);
//                 l_AisMessage.set_lat(l_it->Lat);
//                 l_AisMessage.set_cog(l_it->COG);
//                 l_AisMessage.set_hdg(l_it->HDG);
//                 l_AisMessage.set_imo(l_it->IMO);
//                 l_AisMessage.set_callsign(l_it->CallSign.toStdString());
//                 l_AisMessage.set_shipname(l_it->ShipName.toStdString());
//                 l_AisMessage.set_shiptype(l_it->ShipType.toStdString());
//                 l_AisMessage.set_posaccuracy(l_it->PosAccuracy);
//                 l_AisMessage.set_equipmenttype(l_it->EquipmentType);
//                 l_AisMessage.set_eta_mo(l_it->ETA_Mo);
//                 l_AisMessage.set_eta_day(l_it->ETA_Day);
//                 l_AisMessage.set_eta_hr(l_it->ETA_Hr);
//                 l_AisMessage.set_eta_min(l_it->ETA_Min);
//                 l_AisMessage.set_draft(l_it->Draft);
//                 l_AisMessage.set_destination(l_it->Destination.toStdString());
//                 l_AisMessage.set_syncstate(l_it->SyncState);
//                 l_AisMessage.set_slotto(l_it->SlotTO);
//                 l_AisMessage.set_dima(l_it->DimA);
//                 l_AisMessage.set_dimb(l_it->DimB);
//                 l_AisMessage.set_dimc(l_it->DimC);
//                 l_AisMessage.set_dimd(l_it->DimD);
//                 l_AisMessage.set_length(l_it->Length);
//                 l_AisMessage.set_width(l_it->Width);
//                 l_AisMessage.set_setshipsize(l_it->SetShipSize);
//                 l_AisMessage.set_reportticks(l_it->ReportTicks);
//                 l_AisMessage.set_simulation(l_it->Simulation);
//                 l_AisMessage.set_reportinterval(l_it->ReportInterval);
//                 l_AisMessage.set_ownship(l_it->OwnShip);
//                 l_AisMessage.set_recentperiod(l_it->ReportPeriod);
//                 l_AisMessage.set_m_utc_hour(l_it->utc_hour);
//                 l_AisMessage.set_m_utc_min(l_it->utc_min);
//                 l_AisMessage.set_m_utc_sec(l_it->utc_sec);
//                 l_AisMessage.set_range_nm(l_it->Range_NM);
//                 l_AisMessage.set_brg(l_it->Brg);
//                 l_AisMessage.set_bcpa_valid(l_it->CPA_Valid);
//                 l_AisMessage.set_tcpa(l_it->TCPA);
//                 l_AisMessage.set_cpa(l_it->CPA);
//                 l_AisMessage.set_chshipname(l_it->ChShipName.toStdString());
//                 l_AisMessage.set_nationality(l_it->Nationality.toStdString());
//                 l_AisMessage.set_note(l_it->Note.toStdString());
//                 hgShipAisMessage l_shipais;
//                 hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
//                 hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
//                 hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
//             }
         }
    }
    hgTargetManager::m_mapTarget.UnLockAll();
}

void hgRadarAISStateHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}