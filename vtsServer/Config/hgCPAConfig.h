#ifndef HG_CPACONFIG_H_
#define HG_CPACONFIG_H_

#include "Config/hgConfigBase.h"
#include "hgutils/PolygonLL.h"

struct ShipCPAData 
{
    double m_dDCPA;
    double m_dTCPA;
};

class hgCPAConfig : public hgConfigBase
{
public:
	hgCPAConfig(const QString& path, QSettings::Format format = QSettings::IniFormat, QObject* parent = NULL);
	~hgCPAConfig(void);

public:
    void ReadSysConfig();
	void WriteSysConfig();
    void ReadDayCPA();
    void ReadNightCPA();

public:

    QMap<QString,ShipCPAData> m_DayCPAMap;
    QMap<QString,ShipCPAData> m_NightCPAMap;
};

#endif //HG_CPACONFIG_H_