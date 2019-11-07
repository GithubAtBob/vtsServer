
#include "StdAfx.h"
#include "hgArpaTargetHandler.h"

#include "message/RadarImagePack.pb.h"
#include "frame/vtsServer.h"
#include "db/DBArpaTargetHandler.h"
#include "Managers/hgTargetManager.h"
#include "Config/hgSysConfig.h"
#include "Managers/hgConfigManager.h"
#include "timer/hgPortTimerHandler.h"
#include "Managers/hgSendManager.h"

hgArpaTargetHandler::hgArpaTargetHandler()
{

}

hgArpaTargetHandler::~hgArpaTargetHandler(void)
{
}

vtsRequestHandler::WorkMode hgArpaTargetHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgArpaTargetHandler::handle(boost::asio::const_buffer& data)
{
    if (hgConfigManager::m_sSysConfig->m_radarServer != TurnOn)
    {
        delete this;
        return;
    }

    ArpaTargetPack msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));
    if (hgConfigManager::m_sSysConfig->m_FuseType == 1)
    {
        RadarFuseType(msg);
    }
    else if (hgConfigManager::m_sSysConfig->m_FuseType == 2)
    {
        OwnFuseType(msg);
    }
}

void hgArpaTargetHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgArpaTargetHandler::afterDb(DBArpaTargetHandler* db)
{
    delete db;
    delete this;
}

void hgArpaTargetHandler::WriteToFile(ArpaTargetPack& msg)
{
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

void hgArpaTargetHandler::RadarFuseType(ArpaTargetPack& msg)
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
        delete this;
        return ;
    }
    if (hgConfigManager::m_sSysConfig->m_GPSOpen == 1 && hgTargetManager::m_GPSMMSI.contains(l_target.MMSI))
    {
        delete this;
        return ;
    }
    if (l_target.Result == AIS_FUSE && !hgTargetManager::m_AlgorOwnMMSI.contains(l_target.MMSI))
    {
        delete this;
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
            hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
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
            hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
            hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
            hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
            l_SaveAis = l_AisMessage;

        }
    }

    hgTargetManager::m_mapAis.UnLockAll();
    hgTargetManager::m_mapRadar.UnLockAll();
    hgTargetManager::m_mapTarget.UnLockAll();

    DBArpaTargetHandler* dbHandler = new DBArpaTargetHandler();
    dbHandler->ArpaTarget = l_SaveAis;
    postToDB(dbHandler, boost::bind(&hgArpaTargetHandler::afterDb, this, dbHandler));
}

void hgArpaTargetHandler::OwnFuseType(ArpaTargetPack& msg)
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
        delete this;
        return ;
    }
    hgAisMessage l_SaveAis;
    if (l_target.Source == RADAR_AIS_DATA)
    {
        if (hgTargetManager::m_GPSMMSI.contains(l_target.MMSI))
        {
            delete this;
            return ;
        }
        if (hgTargetManager::m_mapShipData.contains(l_target.MMSI))
        {

        }
        else if (hgTargetManager::m_mapStatic.contains(l_target.MMSI))
        {
        }
        else if (hgTargetManager::m_mapRadarStatic.contains(l_target.MMSI))
        {
        }
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
        QSqlDatabase database = this->connection()->server().openDBConnection();
        hgSqlOperator l_sqlOperator(database);
        hgTargetManager::Assembly(l_target,l_sqlOperator);
        this->connection()->server().closeDBConnection(database);
        //hgTargetManager::m_mapTarget.insert(l_target.ID,l_target);

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
                hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
                hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
                hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
            }
        }   
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
                    hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
                    hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
                    hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
                }
                l_SaveAis = l_AisMessage;

            }
        }
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
                hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
                hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
                hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
            }
        }

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
                hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
                hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->connection());
                hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->connection());
                l_SaveAis = l_AisMessage;

            }
        }

        hgTargetManager::m_mapRadar.UnLockAll();
        hgTargetManager::m_mapTarget.UnLockAll();
    }
     
    DBArpaTargetHandler* dbHandler = new DBArpaTargetHandler();
    dbHandler->ArpaTarget = l_SaveAis;
    postToDB(dbHandler, boost::bind(&hgArpaTargetHandler::afterDb, this, dbHandler));
}

void hgArpaTargetHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
