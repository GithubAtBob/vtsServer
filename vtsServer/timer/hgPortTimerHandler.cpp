#include "StdAfx.h"
#include "hgPortTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgComManager.h"
#include "Managers/hgTargetManager.h"
#include "hgAisDecoder.h"
#include "message/hgAisMessage.pb.h"
#include "message/deviceinfo.pb.h"
#include <QDebug>
#include "Managers/hgConfigManager.h"
#include "Managers/hgSendManager.h"
using boost::asio::ip::udp;
vtsSETUP_TIMER("port", 0.1, hgPortTimerHandler);

hgPortTimerHandler::hgPortTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
    m_bRead = false;
    m_bInitCom = false;
    m_Wait = 0;
 

}

hgPortTimerHandler::~hgPortTimerHandler(void)
{
    m_pComManager->CloseCom();
    m_pComManager->ClearCom();
}

vtsTimerHandler::WorkMode hgPortTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_main;
}

void hgPortTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    if (hgConfigManager::m_sSysConfig->m_aisServer != TurnOn || hgConfigManager::m_sSysConfig->m_comMode != TurnOn)
    {
        return;
    }

    m_Wait++;
    if (m_bInitCom == false)
    {
        m_pComManager = new hgComManager();
        m_pComManager->SetBaudRate(hgConfigManager::m_sSysConfig->m_comBaud);
        m_pComManager->SetComName(hgConfigManager::m_sSysConfig->m_comName);
        m_bOpen = m_pComManager->OpenCom();
        if (m_bOpen == false)
        {
            std::cout << "Open SerialPort error.";
        }
        m_bInitCom = true;
    }


    if (m_Wait > hgConfigManager::m_sSysConfig->m_AISMaxTime*10)
        {
            Device l_DeviceInfo;
            l_DeviceInfo.set_type(DeviceType::DeviceAIS);
            l_DeviceInfo.set_status(false);
            hgSendManager::SendClientMessage("Device",l_DeviceInfo,this->server());
//             this->server()->connectionManager().for_each
//                 ([&](ConnectionPtr p){
//                     p->write("Device",l_DeviceInfo);
//             });
        }
        if (m_bOpen == false)
        {
            Device l_DeviceInfo;
            l_DeviceInfo.set_type(DeviceType::DeviceAIS);
            l_DeviceInfo.set_status(false);
            hgSendManager::SendClientMessage("Device",l_DeviceInfo,this->server());
//             this->server()->connectionManager().for_each
//                 ([&](ConnectionPtr p){
//                     p->write("Device",l_DeviceInfo);
//             });
            return;
        }
        if (m_pComManager->ReadData(m_RequestData,0) == 0)
        {
            return;
        }

        m_Wait = 0;
        Device l_DeviceInfo;
        l_DeviceInfo.set_type(DeviceType::DeviceAIS);
        l_DeviceInfo.set_status(true);
        hgSendManager::SendClientMessage("Device",l_DeviceInfo,this->server());
//         this->server()->connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 p->write("Device",l_DeviceInfo);
//         });
        /* if (m_RequestData.count("!AIVDM") == 0)
        {  
        return;
        }*/
        //qDebug()<<"RequestData"<<m_RequestData;

        hgAisData l_AisData;
        hgAisDecodeError l_error = hgTargetManager::m_AisDecoder->Decode(m_RequestData,l_AisData);
        if (l_error != AIS_NOERROR)
        {
            return;
        }
        //l_AisData.ShipType = (unsigned char)l_AisDecoder.GetVesselType(false, l_AisData);
//         if (l_AisData.Lat == 91 || l_AisData.Lon == 181 || l_AisData.MMSI == NO_VALID_MMSI)
//         {
//             return;
//         }


        if (((abs(l_AisData.Lat) > 90 || abs(l_AisData.Lon > 180)) && (l_AisData.Lat != NO_VALID_LATLON && l_AisData.Lon != NO_VALID_LATLON)) || l_AisData.MMSI == NO_VALID_MMSI)
        {
            return;
        }
        if (abs(l_AisData.Lat) == 0 || abs(l_AisData.Lon) == 0)
        {
            return;
        }
        if (l_AisData.MID != 1 && l_AisData.MID != 2 && l_AisData.MID != 3 && l_AisData.MID != 4 && l_AisData.MID != 5 && 
            l_AisData.MID != 18 && l_AisData.MID != 19 && l_AisData.MID != 21 && l_AisData.MID != 24)
        {
            return;
        }

        hgTarget l_ais;
        l_ais.ShipType = hgTargetManager::m_AisDecoder->GetVesselType(false, l_AisData);


        mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapTarget.begin();
        mymap<QString,hgTarget>::iterator l_itAis = hgTargetManager::m_mapAis.begin();
        mymap<QString,hgTarget>::iterator l_itRadar = hgTargetManager::m_mapRadar.begin();

        QSqlDatabase database = this->server()->openDBConnection();
        hgSqlOperator l_sqlOperator(database);
        hgTargetManager::AssemblyTarget(l_AisData,l_ais,l_sqlOperator);
        this->server()->closeDBConnection(database);

        l_it = hgTargetManager::m_mapTarget.find(l_ais.ID);
        if (l_it != hgTargetManager::m_mapTarget.end())
        {
            hgAisMessage l_AisMessage;

            l_AisMessage.set_id(l_it->ID.toStdString());
            l_AisMessage.set_radarid(l_it->RadarID.toStdString());
            l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
            l_AisMessage.set_source(FUSE_DATA);
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

            hg::utils::PointLL l_point(l_AisMessage.lon(),l_AisMessage.lat());
            if (hgConfigManager::m_sSysConfig->m_AreaLL.size() > 2
                && !hgConfigManager::m_sSysConfig->m_AreaLL.containsPoint(l_point,Qt::WindingFill))
            {
                return ;
            }


            if (hgConfigManager::m_sSysConfig->m_iTrackPredict == 0)
            {
                hgShipAisMessage l_shipais;
                hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
                hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->server());
                hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->server());
                //             this->server()->connectionManager().for_each
                //                 ([&](ConnectionPtr p){
                //                     p->write("AisMessage",l_AisMessage);
                //             });
            }


        }


        //ais Ä¿±ê
        {
            mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapAis.find(l_ais.ID);
            QMap<QString,hgResult>::iterator l_itResult;
            if (l_it != hgTargetManager::m_mapAis.end())
            {
                hgAisMessage l_AisMessage;

                l_AisMessage.set_id(l_it->ID.toStdString());
                l_AisMessage.set_radarid(l_it->RadarID.toStdString());
                l_AisMessage.set_radarguid(l_it->RadarGUID.toStdString());
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
                    hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
                    hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->server());
                    hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->server());
                    //                  this->connection()->server().connectionManager().for_each
                    //                     ([&](ConnectionPtr p){
                    //                     p->write("AisMessage",l_AisMessage);
                    //                     p->write("ShipAisMessage",l_shipais);
                    // 
                    //                    });
                }

                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgTargetManager::SaveAis(l_sqlOperator,l_AisMessage);
                }
                this->server()->closeDBConnection(database);

            }
        }

    hgTargetManager::m_mapRadar.UnLockAll();
    hgTargetManager::m_mapAis.UnLockAll();
    hgTargetManager::m_mapTarget.UnLockAll();

		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgPortTimerHandler TimeDiff: " << diff;
		}
}
