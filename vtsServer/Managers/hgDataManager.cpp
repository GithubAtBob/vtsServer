#include "StdAfx.h"
#include "Managers/hgDataManager.h"

// #include <QApplication>
// #include <QDesktopWidget>

#include "Managers/hgConfigManager.h"

QProcess* hgDataManager::m_sCellularProcess = NULL;
std::vector<std::string> hgDataManager::m_restServer(0);
QMap <QString, hg::utils::PolygonLL> hgDataManager::m_ShipAreaMap;

QMap <QString, RadarImageCenter> hgDataManager::m_radarCenter;
RadarVoltages hgDataManager::m_radarState;

hgDataManager g_DataManager;

hgDataManager::hgDataManager(void)
{
}


hgDataManager::~hgDataManager(void)
{
    DeleteAllData();
}

void hgDataManager::CreateAllData()
{
	//读取配置文件
	hgConfigManager::ReadAllConfig();
	hgDataManager::m_radarState.flags = 0;

    //启动hgCellularServer
    if (hgConfigManager::m_sSysConfig->m_iCellularMode == 1)
    {
        m_sCellularProcess = new QProcess();
        //m_sCellularProcess->start(hgConfigManager::m_sSysConfig->m_strCellularName);
        //m_sCellularProcess->start("C:/project/HgProject/branches/HongWuHan/vtsServer/bin/data/Appendix/hgCellularServer.exe");
    }
}

void hgDataManager::DeleteAllData()
{
	hgConfigManager::ReleaseAllConfig();
}