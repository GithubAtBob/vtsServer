#include "StdAfx.h"
#include "hgTrackPredictTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgTargetManager.h"
#include "hgutils/NavUtil.h"
#include "hgutils/PointLL.h"
#include "Managers/hgConfigManager.h"

#include "Managers/hgSendManager.h"
vtsSETUP_TIMER("TrackPredict", 2, hgTrackPredictTimerHandler);

hgTrackPredictTimerHandler::hgTrackPredictTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgTrackPredictTimerHandler::~hgTrackPredictTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgTrackPredictTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
    //return vtsTimerHandler::WorkMode_main;
}

void hgTrackPredictTimerHandler::handle(const boost::system::error_code& e)
{
    return;
    mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapTarget.begin();

    if (hgTargetManager::GetPredict() == true)
    {
        SimHandle(e);
    }


    if (hgConfigManager::m_sSysConfig->m_iTrackPredict == 0)
    {
        //return;
    }

    for (l_it; l_it != hgTargetManager::m_mapTarget.end(); ++l_it)
    {
/*
        double l_SOG = 0;
        QMap<int,double>::iterator l_itSOG;
        for (l_itSOG = l_it->m_mapHistorySOG.begin(); l_itSOG != l_it->m_mapHistorySOG.end(); ++l_itSOG)
        {
            l_SOG = l_SOG + l_itSOG.value();
        }

        l_SOG = l_SOG/(l_it->m_mapHistorySOG.size()*1.0);

        l_it->Lon = l_it->Lon + 180*l_SOG/3600*sin(l_it->COG*3.14159/180)/(3.14159*3440.067*cos(l_it->Lat*3.14159/180));
        l_it->Lat = l_it->Lat + l_SOG/3600*cos(l_it->COG*3.14159/180)/60;*/

      /*  if (l_it->Class == AIS_CLASS_A)
        {
            if (l_it->SOG <= ClassMediumSOG)
            {
                if (hgConfigManager::m_sSysConfig->m_iclassASmall * 3 < l_it->ReportInterval)
                {
                    return;
                }
            }
            else if (l_it->SOG > ClassMediumSOG && l_it->SOG <= ClassBigSOG)
            {
                if (hgConfigManager::m_sSysConfig->m_iclassAMedium * 3 < l_it->ReportInterval)
                {
                    return;
                }
            }
            else if (l_it->SOG > ClassBigSOG)
            {
                if (hgConfigManager::m_sSysConfig->m_iclassABig * 3 < l_it->ReportInterval)
                {
                    return;
                }
            }
  
        }
        else if (l_it->Class == AIS_CLASS_B)
        {
            if (l_it->SOG <= ClassSmallSOG)
            {
                if (hgConfigManager::m_sSysConfig->m_iclassBLowest * 3 < l_it->ReportInterval)
                {
                    return;
                }
            }
            else if (l_it->SOG > ClassSmallSOG && l_it->SOG <= ClassMediumSOG)
            {
                if (hgConfigManager::m_sSysConfig->m_iclassBSmall * 3 < l_it->ReportInterval)
                {
                    return;
                }
            }
            else if (l_it->SOG > ClassMediumSOG && l_it->SOG <= ClassBigSOG)
            {
                if (hgConfigManager::m_sSysConfig->m_iclassBMedium * 3 < l_it->ReportInterval)
                {
                    return;
                }
            }
            else if (l_it->SOG > ClassBigSOG)
            {
                if (hgConfigManager::m_sSysConfig->m_iclassBBig * 3 < l_it->ReportInterval)
                {
                    return;
                }
            }
        }
        else
        {
            return;
        }*/

        //l_it->AisDeadReckoning.update(1);
        //hg::utils::PointLL l_newPointLL = l_it->AisDeadReckoning.getDRPos();
        //l_it->Lat = l_newPointLL.lat();
        //l_it->Lon = l_newPointLL.lon();
        //l_it->ReportTicks = l_it->ReportTicks+1;

        //if (l_it->Result == AIS_FUSE && l_it->Prediction.GetStart() == true)
        {
            hg::utils::PointLL l_pointLL;
            l_it->ReportTicks = l_it->ReportTicks + 2;
            //bool suc = l_it->Prediction.GetLatLonByTime(l_it->ReportTicks,l_pointLL);
            //if (suc == false)
            {
                continue;
            }

            l_it->Lat = l_pointLL.lat();
            l_it->Lon = l_pointLL.lon();

            hgAisMessage l_AisMessage;
            l_AisMessage.set_id(l_it->ID.toStdString());
            l_AisMessage.set_source(l_it->Source);
            l_AisMessage.set_result(l_it->Result);
            l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
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
            l_AisMessage.set_simulation(false);
            l_AisMessage.set_ownship(l_it->OwnShip);
            l_AisMessage.set_reportinterval(l_it->ReportInterval);
            l_AisMessage.set_recentperiod(l_it->ReportPeriod);


            hgShipAisMessage l_shipais;
            hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
            hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->server());
            hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->server());
        }

        
//         this->server()->connectionManager().for_each
//         ([&](ConnectionPtr p){
//         p->write("AisMessage",l_AisMessage);
//         });
    }

    hgTargetManager::m_mapTarget.UnLockAll(); 
}




void hgTrackPredictTimerHandler::SimHandle(const boost::system::error_code& e)
{
    mymap<QString,hgTarget>::iterator l_it;
    //qDebug()<<"size....."<<l_mapAis.size();
    for (l_it = hgTargetManager::m_mapAis.begin(); l_it != hgTargetManager::m_mapAis.end(); l_it++)
    {
        l_it->Lon = l_it->Lon + 180*l_it->SOG/3600*sin(l_it->COG*3.14159/180)/(3.14159*3440.067*cos(l_it->Lat*3.14159/180));
        l_it->Lat = l_it->Lat + l_it->SOG/3600*cos(l_it->COG*3.14159/180)/60;


        l_it->ReportTicks = l_it->ReportTicks+1;
        l_it->ReportTicks = 1;
        l_it->ReportPeriod = 1;

        hgAisMessage l_AisMessage;
        l_AisMessage.set_mmsi(l_it->MMSI.toStdString());
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
        l_AisMessage.set_simulation(false);
        l_AisMessage.set_ownship(l_it->OwnShip);
        l_AisMessage.set_reportinterval(l_it->ReportInterval);
        l_AisMessage.set_recentperiod(l_it->ReportPeriod);


        hgShipAisMessage l_shipais;
        hgTargetManager::ChangeAisToShip(l_AisMessage,l_shipais);
        hgSendManager::SendExceptShipMessage("AisMessage",l_AisMessage,this->server());
        hgSendManager::SendShipMessage("ShipAisMessage",l_shipais,this->server());
//         this->server()->connectionManager().for_each
//         ([&](ConnectionPtr p){
//         p->write("AisMessage",l_AisMessage);
//         });
    }
        
}
