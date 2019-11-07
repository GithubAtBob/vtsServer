#ifndef HG_DATAMANAGER_H_
#define HG_DATAMANAGER_H_

// class QProcess;
// #include <QApplication>
#include <string>
#include <vector>
#include <QMap>
#include "hgutils/PolygonLL.h"

struct RadarVoltages
{
	int flags;//0Î´Á¬ÉÏ  1 radar1  2 radar2 3 ÈÚºÏ
	int error;
};

struct RadarImageCenter 
{
    double lat;
    double lon;
};
class hgDataManager
{
public:
	hgDataManager(void);
	~hgDataManager(void);

public:
	static void CreateAllData();

    static void DeleteAllData();

    static QProcess* m_sCellularProcess;
    
    static std::vector<std::string> m_restServer;

    static QMap <QString, hg::utils::PolygonLL> m_ShipAreaMap;

    static QMap <QString, RadarImageCenter> m_radarCenter;

	static RadarVoltages m_radarState;


protected:

public:
};

#endif //HG_DATAMANAGER_H_