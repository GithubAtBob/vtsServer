
#include "StdAfx.h"
#include "hgAisChangeHandler.h"

#include "message/hgAisMessage.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgTargetManager.h"
#include "timer/hgPortTimerHandler.h"
#include "Managers/hgConfigManager.h"
#include "message/hgAisChange.pb.h"
#include "db/DBAisChangeHandler.h"
//#include "AisAnalysis/hgMyAisDecoder.h"

//AIS_DECODER decoder;

#include "Managers/hgSendManager.h"
hgAisChangeHandler::hgAisChangeHandler()
{

}

hgAisChangeHandler::~hgAisChangeHandler(void)
{
}

vtsRequestHandler::WorkMode hgAisChangeHandler::workMode()
{
    return Work_Delete_Manual;
}


void hgAisChangeHandler::handle(boost::asio::const_buffer& data)
{
    hgAisChange msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));

    DBAisChangeHandler *dbHandler = new DBAisChangeHandler();
    dbHandler->m_MMSI = QString::fromStdString(msg.mmsi());
    dbHandler->m_ShipNameEN = QString::fromStdString(msg.enshipname());
    dbHandler->m_ShipNameCH = QString::fromStdString(msg.chshipname());
    dbHandler->m_Callsign = QString::fromStdString(msg.callsign());
    dbHandler->m_Nationality = QString::fromStdString(msg.nationality());
    dbHandler->m_ShipType = QString::fromStdString(msg.shiptype());
    dbHandler->m_Note = QString::fromStdString(msg.note());

    dbHandler->m_IMO = msg.imo();
    dbHandler->m_DimA = msg.dima();
    dbHandler->m_DimB = msg.dimb();
    dbHandler->m_DimC = msg.dimc();
    dbHandler->m_DimD = msg.dimd();
    dbHandler->m_Class = msg.class_();

    postToDB(dbHandler, boost::bind(&hgAisChangeHandler::afterDb, this, dbHandler));
}



void hgAisChangeHandler::afterDb(DBAisChangeHandler* db)
{
    bool l_sim = false;

    if (hgTargetManager::m_mapStatic.contains(db->m_MMSI))
    {
        QMap <QString,hgTarget>::iterator l_it = hgTargetManager::m_mapStatic.find(db->m_MMSI);
        l_it->ShipName = db->m_ShipNameEN;
        l_it->ChShipName = db->m_ShipNameCH;
        l_it->CallSign = db->m_Callsign;
        l_it->Nationality = db->m_Nationality;
        l_it->IMO = db->m_IMO;
        l_it->Class = (hgAisClass)db->m_Class;
        l_it->ShipType = db->m_ShipType;
        l_it->DimA = db->m_DimA;
        l_it->DimB = db->m_DimB;
        l_it->DimC = db->m_DimC;
        l_it->DimD = db->m_DimD;
        l_it->Note = db->m_Note;
        l_it->SetShipSize = false;
    }
    else
    {
        hgTarget l_target;
        l_target.MMSI = db->m_MMSI;
        l_target.ShipName = db->m_ShipNameEN;
        l_target.ChShipName = db->m_ShipNameCH;
        l_target.CallSign = db->m_Callsign;
        l_target.Nationality = db->m_Nationality;
        l_target.IMO = db->m_IMO;
        l_target.Class = (hgAisClass)db->m_Class;
        l_target.ShipType = db->m_ShipType;
        l_target.DimA = db->m_DimA;
        l_target.DimB = db->m_DimB;
        l_target.DimC = db->m_DimC;
        l_target.DimD = db->m_DimD;
        l_target.Note = db->m_Note;
        l_target.SetShipSize = false;
        hgTargetManager::m_mapStatic.insert(db->m_MMSI,l_target);
    }

    {
        mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapTarget.begin();
        for (l_it; l_it != hgTargetManager::m_mapTarget.end(); ++l_it)
        {
            if (l_it->MMSI == db->m_MMSI)
            {
                l_sim = l_it->Simulation;

                l_it->ShipName = db->m_ShipNameEN;
                l_it->ChShipName = db->m_ShipNameCH;
                l_it->CallSign = db->m_Callsign;
                l_it->Nationality = db->m_Nationality;
                l_it->IMO = db->m_IMO;
                l_it->Class = (hgAisClass)db->m_Class;
                l_it->ShipType = db->m_ShipType;
                l_it->DimA = db->m_DimA;
                l_it->DimB = db->m_DimB;
                l_it->DimC = db->m_DimC;
                l_it->DimD = db->m_DimD;
                l_it->Note = db->m_Note;
                l_it->SetShipSize = false;
                break;
            }
        }
        hgTargetManager::m_mapTarget.UnLockAll();
    }


    {
        mymap<QString,hgTarget>::iterator l_it = hgTargetManager::m_mapAis.find(db->m_MMSI);
        if (l_it != hgTargetManager::m_mapAis.end())
        {
            l_it->ShipName = db->m_ShipNameEN;
            l_it->ChShipName = db->m_ShipNameCH;
            l_it->CallSign = db->m_Callsign;
            l_it->Nationality = db->m_Nationality;
            l_it->IMO = db->m_IMO;
            l_it->Class = (hgAisClass)db->m_Class;
            l_it->ShipType = db->m_ShipType;
            l_it->DimA = db->m_DimA;
            l_it->DimB = db->m_DimB;
            l_it->DimC = db->m_DimC;
            l_it->DimD = db->m_DimD;
            l_it->Note = db->m_Note;
            l_it->SetShipSize = false;
        }
        hgTargetManager::m_mapAis.UnLockAll();
    } 
    



    hgAisChange msg;
    msg.set_mmsi(db->m_MMSI.toStdString());
    msg.set_enshipname(db->m_ShipNameEN.toStdString());
    msg.set_chshipname(db->m_ShipNameCH.toStdString());
    msg.set_callsign(db->m_Callsign.toStdString());
    msg.set_nationality(db->m_Nationality.toStdString());
    msg.set_imo(db->m_IMO);
    msg.set_class_(db->m_Class);
    msg.set_dima(db->m_DimA);
    msg.set_dimb(db->m_DimB);
    msg.set_dimc(db->m_DimC);
    msg.set_dimd(db->m_DimD);
    msg.set_shiptype(db->m_ShipType.toStdString());
    msg.set_note(db->m_Note.toStdString());

    hgSendManager::SendExceptShipMessage("AisChange",msg,this->connection());
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             p->write("AisChange",msg);
//     });
    delete db;
    delete this;
}

