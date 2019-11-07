#include "StdAfx.h"
#include "Config/hgCPAConfig.h"

hgCPAConfig::hgCPAConfig(const QString& path, QSettings::Format format /*= QSettings::IniFormat*/, QObject* parent /*= NULL*/) : hgConfigBase(path, format, parent)
{
}


hgCPAConfig::~hgCPAConfig(void)
{
}

void hgCPAConfig::ReadSysConfig()
{
	QString str = GetPath();
    ReadDayCPA();
    ReadNightCPA();
}



void hgCPAConfig::WriteSysConfig()
{

}

void hgCPAConfig::ReadDayCPA()
{
    ShipCPAData l_ShipCPAData;

    GetValue("/Day/FishingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/FishingTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Vessel Towing",l_ShipCPAData);

    GetValue("/Day/TowingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/TowingTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Vessel Fishing",l_ShipCPAData);

    GetValue("/Day/TowingLongDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/TowingLongTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Vessel Towing, Long",l_ShipCPAData);

    GetValue("/Day/DredgingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/DredgingTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Vessel Dredging",l_ShipCPAData);

    GetValue("/Day/DivingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/DivingTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Vessel Diving",l_ShipCPAData);

    GetValue("/Day/MilitaryDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/MilitaryTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Military Vessel",l_ShipCPAData);

    GetValue("/Day/SailingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/SailingTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Sailing Vessel",l_ShipCPAData);

    GetValue("/Day/PleasureCraftDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/PleasureCraftTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Pleasure craft",l_ShipCPAData);

    GetValue("/Day/HighSpeedCraftDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/HighSpeedCraftTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("High Speed Craft",l_ShipCPAData);

    GetValue("/Day/PilotVesselDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/PilotVesselTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Pilot Vessel",l_ShipCPAData);

    GetValue("/Day/SearchAndRescueDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/SearchAndRescueTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Search and Rescue Vessel",l_ShipCPAData);

    GetValue("/Day/TugDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/TugTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Tug",l_ShipCPAData);

    GetValue("/Day/PortTenderDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/PortTenderTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Port Tender",l_ShipCPAData);

    GetValue("/Day/PollutionControlDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/PollutionControlTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Pollution Control Vessel",l_ShipCPAData);

    GetValue("/Day/LawEnforcementDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/LawEnforcementFishingTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Law Enforcement Vessel",l_ShipCPAData);

    GetValue("/Day/MedicalTransportDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/MedicalTransportTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Medical Transport",l_ShipCPAData);

    GetValue("/Day/PassengerShipDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/PassengerShipTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Passenger Ship",l_ShipCPAData);

    GetValue("/Day/CargoShipDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/CargoShipTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Cargo Ship",l_ShipCPAData);

    GetValue("/Day/TankerDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/TankerTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Tanker",l_ShipCPAData);

    GetValue("/Day/UnknownDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Day/UnknownTCPA", l_ShipCPAData.m_dTCPA);
    m_DayCPAMap.insert("Unknown",l_ShipCPAData);
}

void hgCPAConfig::ReadNightCPA()
{
    ShipCPAData l_ShipCPAData;

    GetValue("/Night/FishingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/FishingTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Vessel Towing",l_ShipCPAData);

    GetValue("/Night/TowingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/TowingTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Vessel Fishing",l_ShipCPAData);

    GetValue("/Night/TowingLongDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/TowingLongTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Vessel Towing, Long",l_ShipCPAData);

    GetValue("/Night/DredgingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/DredgingTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Vessel Dredging",l_ShipCPAData);

    GetValue("/Night/DivingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/DivingTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Vessel Diving",l_ShipCPAData);

    GetValue("/Night/MilitaryDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/MilitaryTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Military Vessel",l_ShipCPAData);

    GetValue("/Night/SailingDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/SailingTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Sailing Vessel",l_ShipCPAData);

    GetValue("/Night/PleasureCraftDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/PleasureCraftTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Pleasure craft",l_ShipCPAData);

    GetValue("/Night/HighSpeedCraftDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/HighSpeedCraftTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("High Speed Craft",l_ShipCPAData);

    GetValue("/Night/PilotVesselDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/PilotVesselTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Pilot Vessel",l_ShipCPAData);

    GetValue("/Night/SearchAndRescueDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/SearchAndRescueTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Search and Rescue Vessel",l_ShipCPAData);

    GetValue("/Night/TugDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/TugTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Tug",l_ShipCPAData);

    GetValue("/Night/PortTenderDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/PortTenderTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Port Tender",l_ShipCPAData);

    GetValue("/Night/PollutionControlDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/PollutionControlTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Pollution Control Vessel",l_ShipCPAData);

    GetValue("/Night/LawEnforcementDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/LawEnforcementFishingTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Law Enforcement Vessel",l_ShipCPAData);

    GetValue("/Night/MedicalTransportDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/MedicalTransportTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Medical Transport",l_ShipCPAData);

    GetValue("/Night/PassengerShipDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/PassengerShipTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Passenger Ship",l_ShipCPAData);

    GetValue("/Night/CargoShipDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/CargoShipTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Cargo Ship",l_ShipCPAData);

    GetValue("/Night/TankerDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/TankerTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Tanker",l_ShipCPAData);

    GetValue("/Night/UnknownDCPA", l_ShipCPAData.m_dDCPA);
    GetValue("/Night/UnknownTCPA", l_ShipCPAData.m_dTCPA);
    m_NightCPAMap.insert("Unknown",l_ShipCPAData);
}
