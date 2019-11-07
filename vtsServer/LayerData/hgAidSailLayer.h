#ifndef HG_AIDSAILLAYER_H_
#define HG_AIDSAILLAYER_H_

#include "hgutils/PolygonLL.h"
// #include "LayerData/hgShipWarningInfo.h"
// #include "LayerData/hgUserLayWarning.h"

// class hgUserLayWarning;
// class hgShipWarningInfo;

class hgAidSailLayer
{
public:
	hgAidSailLayer(void);
    ~hgAidSailLayer(void);

public:
    QString m_Name;
    double m_Lat;
    double m_Lon;
    QString m_Remarks;
    QString m_IconURL;
    QString m_DrawMan;
    bool m_IsNew;
};

#endif //HG_DATAMANAGER_H_