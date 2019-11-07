#ifndef HG_CONFIGMANAGER_H_
#define HG_CONFIGMANAGER_H_

#include "Config/hgSysConfig.h"
#include "Config/hgCPAConfig.h"

class hgConfigManager
{
public:
	hgConfigManager(void);
	~hgConfigManager(void);

public:
	static void ReadAllConfig();
	static void WriteAllConfig();
	static void ReleaseAllConfig();

protected:
	static void InitConfig();

public:
	static hgSysConfig* m_sSysConfig;
    static hgCPAConfig* m_sCPAConfig;
};

#endif //HG_CONFIGMANAGER_H_