
#include "StdAfx.h"
#include "hgAisTextHandler.h"

#include "message/hgAisMessage.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgTargetManager.h"
#include "timer/hgPortTimerHandler.h"
#include "Managers/hgConfigManager.h"
#include "message/hgPlayBack.pb.h"
#include "message/deviceinfo.pb.h"
#include "message/hgShipAisMessage.pb.h"
#include "Managers/hgSendManager.h"
//#include "AisAnalysis/hgMyAisDecoder.h"

//AIS_DECODER decoder;

hgAisTextHandler::hgAisTextHandler()
{
}

hgAisTextHandler::~hgAisTextHandler(void)
{
}

vtsRequestHandler::WorkMode hgAisTextHandler::workMode()
{
    return Work_Delete_Manual;
}


void hgAisTextHandler::handle(boost::asio::const_buffer& data)
{
    static int l_iStart = 0;

    if (hgConfigManager::m_sSysConfig->m_aisServer != TurnOn || hgConfigManager::m_sSysConfig->m_netMode != TurnOn)
    {
        delete this;
        return;
    }

    if (l_iStart == 0)
    {
        vtsInfo << "### Start Receive Ais Data !!!";
        l_iStart = 1;
    }

    //this->postToThread(boost::bind(&hgAisTextHandler::aisTextReceive, this, data));  
    aisTextReceive(data);

}




void hgAisTextHandler::aisTextReceive(boost::asio::const_buffer& data)
{
    hgAisData l_AisData;
    char buf[256];
    size_t len = boost::asio::buffer_size(data);
    memcpy(buf, boost::asio::buffer_cast<const char*>(data), len);
    buf[len] = '\0';
    QString l_str = QString(buf);

    hgTargetManager::SetWarnTime(l_str.left(l_str.indexOf(",")).toInt()); //刷新当前回放时间


    if (l_str.right(l_str.length() - l_str.indexOf(",") - 1) == "NULL")
    {
        if (l_str.left(l_str.indexOf(",")).toInt() == Stop)
        {
            hgTargetManager::SetPredict(false);
            return;
        }
        else if (l_str.left(l_str.indexOf(",")).toInt() == Start)
        {
            hgTargetManager::SetPredict(true);
            return;
        }

        hgPlayBack l_PlayBackMsg;
        l_PlayBackMsg.set_time(l_str.left(l_str.indexOf(",")).toInt());

        hgTargetManager::SetPlayBack(l_str.left(l_str.indexOf(",")).toInt());

        hgSendManager::SendExceptShipMessage("PlayBack",l_PlayBackMsg,this->connection());
//         this->connection()->server().connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 p->write("PlayBack",l_PlayBackMsg);
//         });
    }
    else
    {
        hgAisDecodeError l_error = hgTargetManager::m_AisDecoder->Decode(l_str.right(l_str.length() - l_str.indexOf(",") - 1).toLatin1().data(),l_AisData);


        if (l_error != AIS_NOERROR)
        {
            return;
        }
        //QString l_ShipType = hgTargetManager::m_AisDecoder->GetVesselType(false, l_AisData);
        l_AisData.ReportTicks = (l_str.left(l_str.indexOf(",")).toInt());


        if (l_AisData.OwnShip == true)
        {
            if (hgTargetManager::m_OwnMMSI.indexOf(QString::number(l_AisData.MMSI)) == -1)
            {
                hgTargetManager::m_OwnMMSI.push_back(QString::number(l_AisData.MMSI));
            }
        }
        if (hgTargetManager::m_OwnMMSI.indexOf(QString::number(l_AisData.MMSI)) != -1)
        {
            l_AisData.OwnShip = true;
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

        if (l_str.right(l_str.length() - l_str.indexOf(",") - 1).mid(3,3) == "VDO")
        {
            //qDebug()<< "VDO" << l_AisData.MMSI;
        } 

        if (hgTargetManager::m_GPSMMSI.contains(QString::number(l_AisData.MMSI)))
        {
            return ;
        }


        hgTarget l_ais;
        l_ais.ShipType = hgTargetManager::m_AisDecoder->GetVesselType(false, l_AisData);
   
        //融合目标
        {

            mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapTarget.begin();
            mymap<QString,hgTarget>::iterator l_itAis = hgTargetManager::m_mapAis.begin();
            mymap<QString,hgTarget>::iterator l_itRadar = hgTargetManager::m_mapRadar.begin();

            QSqlDatabase database = this->connection()->server().openDBConnection();
            hgSqlOperator l_sqlOperator(database);
            hgTargetManager::AssemblyTarget(l_AisData,l_ais,l_sqlOperator);
            this->connection()->server().closeDBConnection(database);

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


                if ( abs(l_AisMessage.lat()) > 90 || abs(l_AisMessage.lon() > 180) )
                {
                    return;
                }
                assert (l_AisMessage.hdg() < 1000000);
                if (hgConfigManager::m_sSysConfig->m_iTrackPredict == 0)
                {
                    hgShipAisMessage l_shipais;
                    hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
            	    hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
            	    hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
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
            	    hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
            	    hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
                }

            }
        }


//                 QSqlDatabase database = this->connection()->server().openDBConnection();
//                 hgSqlOperator l_sqlOperator(database);
//                 {
//                     hgTargetManager::SaveAis(l_sqlOperator,l_AisMessage);
//                 }
//                 this->connection()->server().closeDBConnection(database);
            }

    hgTargetManager::m_mapRadar.UnLockAll();
    hgTargetManager::m_mapAis.UnLockAll();
    hgTargetManager::m_mapTarget.UnLockAll();
    delete this;
}


