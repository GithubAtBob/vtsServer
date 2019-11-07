#include "StdAfx.h"
#include "LayerData/hgUserLayWarning.h"

const char* hgAnchorageTypeName[] = //船舶类型
{
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Unknown"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Vessel Fishing"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Vessel Towing"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Vessel Dredging"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Military Vessel"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Sailing Vessel"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Pleasure craft"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Tug"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Passenger Ship"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Passenger Launch"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Ferry Boat"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Spare"),
    QT_TRANSLATE_NOOP("hgBottomSpecifyPolygonWidget", "Tanker"),
};
const char* hgAnchorageTypeGuid[] = //船舶类型对应GUID
{
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{E392E781-B7C5-42FE-9C1C-29645FE9B12E}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{9627F620-B96C-4DBF-B300-AF02898D3203}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{F773CE59-9EE9-4211-986C-2E7024792E24}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{E6DEEF6E-B4B7-4282-B985-B433AA1AAC02}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{E369234D-1DD2-410D-BFC2-A1B67F18501B}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{D31BF885-DDAA-45D9-A72D-F91601C7EE27}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{A4A66AAE-00EB-4519-8194-AFBB53E4EC14}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{D155445D-ED40-49E8-BFEF-9114D13C1B2F}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{B6184D9E-79ED-410E-BFE6-392EB6E3ECE3}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{2C462ADA-E888-4952-9CC8-EDDCCD97DB9B}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{1F498939-FF6A-46BF-B7CF-E882FE84F470}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{86F6A6AB-3855-42FF-9A3F-3FBA249F8EFF}"),
    QT_TRANSLATE_NOOP("hgAnchorageTypeGuid", "{01FE77C8-1664-4625-9D47-AF1D7207405B}"),
};

hgUserLayWarning::hgUserLayWarning(void)
{
    InitAllData();
}

hgUserLayWarning::~hgUserLayWarning(void)
{

}

void hgUserLayWarning::InitAllData()
{
    enter_time = 0;
    enter_speed = 0;
    leave_time = 0;
    leave_speed = 0;
    inside_time = 0;
    inside_speed = 0;
    outside_time = 0;
    outside_speed = 0;
    high_duration = 0;
    high_speed = 0;
    low_duration = 0;
    low_speed = 0;
    pro_duration = 0;
    pro_lat = 0;
    pro_lon = 0;
    anc_type.clear();
    add_max = 0;
    add_min = 0;
    add_duration = 0;
    col_cpa = 0;
    col_tcpa = 0;
    col_dcpa = 0;
    col_dist = 0;
    con_time = 0;
    con_total = 0;
    gro_depth = 0;
    gro_time = 0;
    app_time = 0;
    cou_change = 0;
    cou_time = 0;
    m_FogBeginTime = 0;
    m_FogEndTime = 0;
    m_FogTime = 0;
    m_FogMMSI.clear();
}
