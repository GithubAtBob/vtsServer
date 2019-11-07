#include "StdAfx.h"
#include "hgRadarAisTimerHandler.h"
#include <boost/thread.hpp>
#include <QDebug>

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include "Managers/hgTargetManager.h"
#include "hgAisDecoder.h"
#include "message/hgAisMessage.pb.h"
#include "message/deviceinfo.pb.h"
#include "Managers/hgConfigManager.h"
#include "Managers/hgSendManager.h"
#include "Managers/hgAlarmManager.h"
#include "hgPortTimerHandler.h"

vtsSETUP_TIMER("RadarAis", 0.1, hgRadarAisTimerHandler);

hgRadarAisTimerHandler::hgRadarAisTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
    m_bConnect = false;
    m_iCount = 0;

    io_service_ = new io_service();     
    socket_ = new tcp::socket(*io_service_); 

    //Connection();
}

hgRadarAisTimerHandler::~hgRadarAisTimerHandler(void)
{
}

vtsTimerHandler::WorkMode hgRadarAisTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgRadarAisTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    if (hgConfigManager::m_sSysConfig->m_aisServer != TurnOn || hgConfigManager::m_sSysConfig->m_netMode != TurnOn || hgConfigManager::m_sSysConfig->m_transpondMode != TurnOn)
    {
        return;
    }


    m_iCount++;

    if (m_iCount == 1)
    {
        m_iCount++;
        Connection();
    }

    if (m_bConnect == false && m_iCount > 30)
    {
        //m_iCount = 0;
        //Connection();
        return;
    } 
    //qDebug() << m_buffer;

    if (m_str.size() < 1024)
    {
        try
        {
            char buffTemp[100];
            memset(buffTemp,0,sizeof(buffTemp));
            size_t tempSize = socket_->read_some(boost::asio::buffer(buffTemp));
            m_str += buffTemp;
        }
        catch (std::exception& e)
        {
            m_bConnect = false;
        	//cout << e.what() << endl;
        }
    }
    int first = m_str.indexOf("!AI");
    int end = m_str.indexOf("\r\n");
    QString data;
    if (first != -1 && end != -1 && first < end)
    {
        data = m_str.mid(first,end-first);
        m_str = m_str.mid(end+2,m_str.size()-(end+3));
        //qDebug() << data;
        //m_iCount = 0;
    }
    if (first != -1 && end != -1 && first > end)
    {
        m_str = m_str.mid(end+2,m_str.size()-(end+3));
    }
    
    
    if (data.size() > 0)
    {
        hgAisData l_AisData;
        hgAisDecoder l_AisDecoder;
        hgAisDecodeError l_error = l_AisDecoder.Decode(data.toLatin1().data(),l_AisData);
        if (l_error != AIS_NOERROR)
        {
            return;
        }

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
        l_ais.ShipType = l_AisDecoder.GetVesselType(false, l_AisData);
        //融合目标
        {
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
                l_AisMessage.set_radarguid(l_it->RadarGUID.toStdString());
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
                }


            }   
        }


        //ais 目标
        {
            mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapAis.find(l_ais.ID);
            QMap<QString,hgResult>::iterator l_itResult;
            if (l_it != hgTargetManager::m_mapAis.end())
            {
                hgAisMessage l_AisMessage;

                l_AisMessage.set_id(l_it->ID.toStdString());
                l_AisMessage.set_radarid(l_it->RadarID.toStdString());
                l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
                l_AisMessage.set_source(RADAR_AIS_DATA);
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


                if (hgConfigManager::m_sSysConfig->m_iTrackPredict == 0)
                {
                    hgShipAisMessage l_shipais;
                    hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
                    hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->server());
                    hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->server());
//                     this->server()->connectionManager().for_each
//                         ([&](ConnectionPtr p){
//                             p->write("AisMessage",l_AisMessage);
//                     });
                }


                QSqlDatabase database = this->server()->openDBConnection();
                hgSqlOperator l_sqlOperator(database);
                {
                    hgTargetManager::SaveAis(l_sqlOperator,l_AisMessage);
                }
                this->server()->closeDBConnection(database);

            }
        }
   }

   hgTargetManager::m_mapRadar.UnLockAll();
   hgTargetManager::m_mapAis.UnLockAll();
   hgTargetManager::m_mapTarget.UnLockAll();
	 double l_end = GetTickCount();
	 double diff = l_end - start;
	 if (diff > 500.0)
	 {
		 vtsInfo << "hgRadarAisTimerHandler TimeDiff: " << diff;
	 }
}

void hgRadarAisTimerHandler::Connection()
{
    if (io_service_ != NULL)
    {
        delete socket_;
        socket_ = NULL;
        delete io_service_;
        io_service_ = NULL;
        io_service_ = new io_service();
        socket_ = new tcp::socket(*io_service_); 
    }
     

    try
    {
        tcp::resolver resolver(*io_service_);     
        tcp::resolver::query query(hgConfigManager::m_sSysConfig->m_RadarAisIP.toStdString(), boost::lexical_cast<string, unsigned short>(hgConfigManager::m_sSysConfig->m_RadarAisPort)); 

        boost::system::error_code ec;     
        tcp::resolver::iterator iter = resolver.resolve(query, ec);     
        tcp::resolver::iterator end;     

        // pick the first endpoint     
        if (iter != end && ec == 0)     
        {     
            tcp::endpoint endpoint = *iter;     
            std::cout << "Connecting to: " << endpoint << std::endl;     
            socket_->connect(endpoint, ec);     
            if (ec)     
            {     
                m_bConnect = false;
                std::cerr << "Error: " << ec.message() << std::endl;
                throw ec; 
            } 
            else
            {
                m_bConnect = true;
            }
        } 
    }
    catch (boost::system::error_code& e)
    {
    	cout << e.message() << endl;
    }
}
