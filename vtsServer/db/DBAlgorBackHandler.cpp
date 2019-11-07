
#include "StdAfx.h"
#include "DBAlgorBackHandler.h"

#include <QSqlQuery>
#include <QVariant>

#include "hgSqlInsertCmd.h"
#include "hgSqlUpdateCmd.h"
#include "hgSqlRemoveCmd.h"
#include "hgSqlSelectCmd.h"
#include "hgSqlOperator.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgConfigManager.h"
#include "Config/hgSysConfig.h"


DBAlgorBackHandler::DBAlgorBackHandler(void)
{
    Sql = false;
}


DBAlgorBackHandler::~DBAlgorBackHandler(void)
{
}

void DBAlgorBackHandler::handle(boost::asio::io_service &s, hgSqlOperator& sqlOperator)
{
    hgSqlSelectCmd* l_pSqlSelectCmd = new hgSqlSelectCmd;
    l_pSqlSelectCmd->SetTableName("arpaall_target_table_min");
    QString l_filter;
    for (int i = 0; i < Request.begintime().size(); i++)
    {
        if (i != 0)
        {
            l_filter.append(" or ");
        }
        l_filter.append(QString("(time >= '%1' and time <= '%2')").arg(Request.begintime(i)-hgConfigManager::m_sSysConfig->m_backSec).arg(Request.endtime(i)+hgConfigManager::m_sSysConfig->m_backSec));
    }
    //l_pSqlSelectCmd->SetFilter(QString("time >= '%1' and time <= '%2'").arg(Request.begintime()).arg(Request.endtime()));
    l_pSqlSelectCmd->SetFilter(l_filter);
    QList<QSqlRecord>* l_pSqlRecord = sqlOperator.Records();
    if (!sqlOperator.ImplementCmd(l_pSqlSelectCmd))
    {
        Sql = false;
        std::cout << "Open datatabase error(arpaall_target_table_min Read):" << sqlOperator.LastError().text().toLatin1().data() << endl;
        if (l_pSqlSelectCmd)
        {
            delete l_pSqlSelectCmd;
            l_pSqlSelectCmd = NULL;
        }
        return;
    }
    Sql = true;
    for (int i = 0; i < l_pSqlRecord->count(); i++)
    {
        QSqlRecord l_record = l_pSqlRecord->at(i);
        QByteArray l_Mess = l_record.value("alldata").toByteArray();
        time_t l_time = l_record.value("time").toInt();
        size_t l_allSize = l_Mess.size();
        size_t l_packetSize = sizeof(ARPA_TARGET_PACKET);
        int l_PacketCount = l_allSize / l_packetSize;
        ARPA_TARGET_PACKET* l_OwnArpa = NULL;
        ARPA_TARGET_PACKET* l_OwnArpaR = NULL;
        ARPA_TARGET_PACKET* l_TargetArpa = NULL;
        ARPA_TARGET_PACKET* l_TargetArpaR = NULL;
        for (int j = 0; j < l_PacketCount; j++)
        {
            ARPA_TARGET_PACKET* l_Packet = (ARPA_TARGET_PACKET*)(l_Mess.data() + l_packetSize * j);
            int l_Source = ((quint8)l_Packet->flags & 128 )? RADAR_AIS_DATA : RADAR_RADAR_DATA;
            if (l_Source == RADAR_AIS_DATA)
            {
                if (QString::number(l_Packet->scans) == Request.ownmmsi().c_str())
                {
                    l_OwnArpa = l_Packet;
                }
                if (QString::number(l_Packet->scans) == Request.targetmmsi().c_str())
                {
                    l_TargetArpa = l_Packet;
                }
            }
            else if (l_Source == RADAR_RADAR_DATA)
            {
                if (QString::number(l_Packet->number) == Request.ownradarid().c_str())
                {
                    l_OwnArpaR = l_Packet;
                }
                if (QString::number(l_Packet->number) == Request.targetradarid().c_str())
                {
                    l_TargetArpaR= l_Packet;
                }
            }
        }
        if (l_OwnArpa == NULL && l_OwnArpaR == NULL)
        {
            continue;
        }
        if (l_TargetArpa == NULL && l_TargetArpaR == NULL)
        {
            continue;
        }


        Repsone.add_time(l_time);
        hgAisMessage* l_own = Repsone.add_own();
        hgAisMessage* l_target = Repsone.add_target();
        GetAisMess(l_own, l_OwnArpa, l_OwnArpaR);
        l_own->set_result(AIS_FUSE);
        GetAisMess(l_target, l_TargetArpa, l_TargetArpaR);
        l_own->set_reportticks(l_time);
        l_target->set_reportticks(l_time);
    }
    Repsone.set_guid(Request.guid());
    if (l_pSqlSelectCmd)
    {
        delete l_pSqlSelectCmd;
        l_pSqlSelectCmd = NULL;
    }
}

void DBAlgorBackHandler::GetAisMess(hgAisMessage* message, ARPA_TARGET_PACKET* ais, ARPA_TARGET_PACKET* radar)
{
    if (ais != NULL)
    {
        message->set_radarid( QString::number(ais->number).toStdString() );
        message->set_mmsi( QString::number(ais->scans).toStdString() );
        message->set_reserved( ais->reserved );
        message->set_rng( ais->rng );
        message->set_brg( ais->brg);
        message->set_radarbrg( ais->brg*0.0878 );
//         message->set_spd( (ais->spd == 0xffff ? -1 : ais->spd*0.1) );
//         message->set_crs( (ais->crs == 0xffff ? -1 : ais->crs*0.1) );
        message->set_scans( ais->scans );
        message->set_flags( ais->flags );
        message->set_sog( (ais->sog == 0xffff ? -1 : ais->sog*0.1) );
        message->set_cog( (ais->cog == 0xffff ? -1 : ais->cog*0.1) );
        message->set_hdg( (ais->cog == 0xffff ? -1 : ais->cog*0.1) );
        message->set_lat( ais->latitude/600000.0 );
        message->set_lon( ais->longitude/600000.0 );


        message->set_id(message->mmsi());
    }
    
    {
        message->set_reportinterval(0);
        message->set_mid(-1);
        message->set_shipname("");
        message->set_chshipname("");
        message->set_class_(AIS_CLASS_A);
        message->set_imo(-1);
        message->set_shiptype("");
        message->set_equipmenttype(-1);
        message->set_dima(hgConfigManager::m_sSysConfig->m_dShipLength * 0.75);
        message->set_dimb(hgConfigManager::m_sSysConfig->m_dShipLength * 0.25);
        message->set_dimc(hgConfigManager::m_sSysConfig->m_dShipWidth * 0.25);
        message->set_dimd(hgConfigManager::m_sSysConfig->m_dShipWidth * 0.75);
        message->set_length(hgConfigManager::m_sSysConfig->m_dShipLength);
        message->set_width(hgConfigManager::m_sSysConfig->m_dShipWidth);
        message->set_setshipsize(true);
        message->set_destination("");
        message->set_eta_mo(-1);
        message->set_eta_day(-1);
        message->set_eta_min(-1);
        message->set_draft(-1);
        message->set_simulation(false);
        message->set_note("");
        message->set_nationality("");
        message->set_navstatus(-1);
        message->set_rotais(-1);
        message->set_m_utc_hour(-1);
        message->set_m_utc_min(-1);
        message->set_m_utc_sec(-1);
        message->set_range_nm(-1);
        message->set_brg(-1);
        message->set_syncstate(-1);
        message->set_slotto(-1);
        message->set_bcpa_valid(false);
        message->set_tcpa(-1);
        message->set_cpa(-1);
        message->set_eta_mo(-1);
        message->set_ownship(false);
        if (ais != NULL)
        {
            if (hgTargetManager::m_mapTarget.find(message->mmsi().c_str()) != hgTargetManager::m_mapTarget.end())
            {
                hgTarget l_static = hgTargetManager::m_mapTarget.find(message->mmsi().c_str()).value();
                message->set_imo(l_static.IMO);
                message->set_callsign(l_static.CallSign.toStdString());
                message->set_shipname(l_static.ShipName.toStdString());
                message->set_destination(l_static.Destination.toStdString());
                message->set_dima(l_static.DimA);
                message->set_dimb(l_static.DimB);
                message->set_dimc(l_static.DimC);
                message->set_dimd(l_static.DimD);
                message->set_length(l_static.Length);
                message->set_width(l_static.Width);
                message->set_setshipsize(l_static.SetShipSize);
            }
            if (hgTargetManager::m_mapRadarStatic.contains(message->mmsi().c_str()))
            {
                hgTarget l_static = hgTargetManager::m_mapRadarStatic.find(message->mmsi().c_str()).value();
                message->set_imo(l_static.IMO);
                message->set_callsign(l_static.CallSign.toStdString());
                message->set_shipname(l_static.ShipName.toStdString());
                message->set_destination(l_static.Destination.toStdString());
                message->set_dima(l_static.DimA);
                message->set_dimb(l_static.DimB);
                message->set_dimc(l_static.DimC);
                message->set_dimd(l_static.DimD);
                message->set_length(l_static.Length);
                message->set_width(l_static.Width);
                message->set_setshipsize(l_static.SetShipSize);
            }
            bool l_findCsv = false,l_findStatic = false;
            if (hgTargetManager::m_mapShipData.contains(message->mmsi().c_str()))
            {
                l_findCsv = true;
                hgTarget l_target = hgTargetManager::m_mapStatic.find(message->mmsi().c_str()).value();
                message->set_imo(l_target.IMO);
                message->set_shipname(l_target.ShipName.toStdString());
                message->set_dima(l_target.DimA);
                message->set_dimb(l_target.DimB);
                message->set_dimc(l_target.DimC);
                message->set_dimd(l_target.DimD);
                message->set_length(l_target.Length);
                message->set_width(l_target.Width);
                message->set_setshipsize(l_target.SetShipSize);

                message->set_callsign(l_target.CallSign.toStdString());
                message->set_destination(l_target.Destination.toStdString());
                message->set_equipmenttype(l_target.EquipmentType);
                message->set_eta_mo(l_target.ETA_Mo);
                message->set_eta_day(l_target.ETA_Day);
                message->set_eta_hr(l_target.ETA_Hr);
                message->set_eta_min(l_target.ETA_Min);
                message->set_draft(l_target.Draft);
            }
            if (hgTargetManager::m_mapStatic.contains(message->mmsi().c_str()))
            {
                l_findStatic = true;
                hgTarget l_target = hgTargetManager::m_mapStatic.find(message->mmsi().c_str()).value();
                if (l_findCsv == false)
                {
                    message->set_imo(l_target.IMO);
                    message->set_shipname(l_target.ShipName.toStdString());
                    message->set_shiptype(l_target.ShipType.toStdString());
                    message->set_dima(l_target.DimA);
                    message->set_dimb(l_target.DimB);
                    message->set_dimc(l_target.DimC);
                    message->set_dimd(l_target.DimD);
                    message->set_length(l_target.Length);
                    message->set_width(l_target.Width);
                }

                message->set_callsign(l_target.CallSign.toStdString());
                message->set_destination(l_target.Destination.toStdString());
                message->set_equipmenttype(l_target.EquipmentType);
                message->set_eta_mo(l_target.ETA_Mo);
                message->set_eta_day(l_target.ETA_Day);
                message->set_eta_hr(l_target.ETA_Hr);
                message->set_eta_min(l_target.ETA_Min);
                message->set_draft(l_target.Draft);

                message->set_setshipsize(l_target.SetShipSize);

                message->set_chshipname(l_target.ChShipName.toStdString());
                message->set_nationality(l_target.Nationality.toStdString());
                message->set_note(l_target.Note.toStdString());
            }
        }
    }
    
    if (radar != NULL && ais == NULL)
    {
        message->set_radarid( QString::number(radar->number).toStdString() );
        if (ais == NULL)
        {
            message->set_mmsi( "UnKnow" );
            message->set_id(message->radarid());
        }
        message->set_reserved( radar->reserved );
        message->set_rng( radar->rng );
        message->set_brg( radar->brg);
        message->set_radarbrg( radar->brg*0.0878 );
//         message->set_spd( (radar->spd == 0xffff ? -1 : radar->spd*0.1) );
//         message->set_crs( (radar->crs == 0xffff ? -1 : radar->crs*0.1) );
        message->set_scans( radar->scans );
        message->set_flags( radar->flags );
        message->set_sog( (radar->sog == 0xffff ? -1 : radar->sog*0.1) );
        message->set_cog( (radar->cog == 0xffff ? -1 : radar->cog*0.1) );
        message->set_hdg( (radar->cog == 0xffff ? -1 : radar->cog*0.1) );
        message->set_lat( radar->latitude/600000.0 );
        message->set_lon( radar->longitude/600000.0 );
    }
    message->set_source(FUSE_DATA);
    if (ais == NULL && radar != NULL)
    {
        message->set_result(RADAR_FUSE);
    }
    if (ais != NULL && radar == NULL)
    {
        message->set_result(AIS_FUSE);
    }
    if (ais != NULL && radar != NULL)
    {
        message->set_result(AIS_RADAR_FUSE);
    }
}
