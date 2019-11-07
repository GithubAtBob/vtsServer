#include "StdAfx.h"
#include "Managers/hgConfigManager.h"

hgSysConfig *hgConfigManager::m_sSysConfig = NULL;
hgCPAConfig* hgConfigManager::m_sCPAConfig = NULL;

const char* g_hgConfigMan_SysConfigPath = "./Data/Config/SysConfig.ini";
const char* g_hgConfigMan_CPAConfigPath = "./Data/Config/CPAConfig.ini";

hgConfigManager::hgConfigManager(void)
{
}


hgConfigManager::~hgConfigManager(void)
{
}

void hgConfigManager::InitConfig()
{
	if (m_sSysConfig == NULL)
	{
		m_sSysConfig = new hgSysConfig(g_hgConfigMan_SysConfigPath);
	}
    if (m_sCPAConfig == NULL)
    {
        m_sCPAConfig = new hgCPAConfig(g_hgConfigMan_CPAConfigPath);
    }
}

void hgConfigManager::ReadAllConfig()
{
	InitConfig();
	m_sSysConfig->ReadSysConfig();
    m_sCPAConfig->ReadSysConfig();
}

void hgConfigManager::WriteAllConfig()
{

}

void hgConfigManager::ReleaseAllConfig()
{
	if (m_sSysConfig != NULL)
	{
		delete m_sSysConfig;
		m_sSysConfig = NULL;
	}
    if (m_sCPAConfig != NULL)
    {
        delete m_sCPAConfig;
        m_sCPAConfig = NULL;
    }
}