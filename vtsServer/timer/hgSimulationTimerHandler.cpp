#include "StdAfx.h"
#include "hgSimulationTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgTargetManager.h"
#include "Managers/hgConfigManager.h"
#include "timer/hgPortTimerHandler.h"
#include "hgutils/NavUtil.h"
#include "hgutils/PointLL.h"

#include "Managers/hgSendManager.h"
vtsSETUP_TIMER("Simulation", 1, hgSimulationTimerHandler);

hgSimulationTimerHandler::hgSimulationTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgSimulationTimerHandler::~hgSimulationTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgSimulationTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_main;
}

void hgSimulationTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    mymap<QString,hgTarget>::iterator l_it;
    for (l_it = hgTargetManager::m_mapAis.begin(); l_it != hgTargetManager::m_mapAis.end(); ++l_it)
    {
        if (l_it->Simulation == false)
        {
            continue;
        }

        hg::utils::PointLL l_CenterPointLL;
        l_CenterPointLL.setLat(l_it->Lat);
        l_CenterPointLL.setLon(l_it->Lon);

        hg::utils::PointLL l_NewPointLL;
        l_NewPointLL = hg::utils::navutil::getPoint(l_CenterPointLL, l_it->SOG/3600, l_it->HDG);//ÐÂÎ»ÖÃ
        l_it->Lat = l_NewPointLL.lat();
        l_it->Lon = l_NewPointLL.lon();
        {
            mymap<QString,hgTarget>::iterator l_itTarget = hgTargetManager::m_mapTarget.find(l_it->MMSI);
            if (l_itTarget != hgTargetManager::m_mapTarget.end())
            { 
                l_itTarget->Lat = l_it->Lat;
                l_itTarget->Lon = l_it->Lon;
            }
        }
        l_it->ReportTicks = time(NULL);
        l_it->ReportInterval  = 1;
        l_it->ReportPeriod = 1;
        hgAisMessage l_AisMessage;
        l_AisMessage.set_id(l_it->ID.toStdString());
        l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
        l_AisMessage.set_source(FUSE_DATA);
        l_AisMessage.set_result(AIS_FUSE);
        l_AisMessage.set_mid(l_it->MID);
        l_AisMessage.set_class_(l_it->Class);
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
        l_AisMessage.set_reportticks(l_it->ReportTicks);
        l_AisMessage.set_reportinterval(l_it->ReportInterval);
        l_AisMessage.set_recentperiod(l_it->ReportPeriod);
        l_AisMessage.set_chshipname(l_it->ChShipName.toStdString());
        l_AisMessage.set_nationality(l_it->Nationality.toStdString());
        l_AisMessage.set_note(l_it->Note.toStdString());
        l_AisMessage.set_simulation(true);
        l_AisMessage.set_ownship(l_it->OwnShip);
        l_AisMessage.set_setshipsize(false);

        hgShipAisMessage l_shipais;
        hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
        hgSendManager::SendExceptShipMessage("Simulation",l_AisMessage,this->server());
        hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->server());
//         this->server()->connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 p->write("Simulation",l_AisMessage);
//                 p->write("ShipAisMessage",l_shipais);
//         });


        l_AisMessage.set_source(AIS_DATA);
        hgSendManager::SendExceptShipMessage("Simulation",l_AisMessage,this->server());

        QSqlDatabase database = this->server()->openDBConnection();
        hgSqlOperator l_sqlOperator(database);
        {
            hgTargetManager::SaveAis(l_sqlOperator,l_AisMessage);
        }
        this->server()->closeDBConnection(database);
    }


    hgTargetManager::m_mapTarget.UnLockAll();
    hgTargetManager::m_mapAis.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgSimulationTimerHandler TimeDiff: " << diff;
		}
}
