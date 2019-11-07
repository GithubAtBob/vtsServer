#ifndef HG_NOTESLAYER_H_
#define HG_NOTESLAYER_H_

#include "hgutils/PolygonLL.h"
// #include "LayerData/hgShipWarningInfo.h"
// #include "LayerData/hgUserLayWarning.h"

// class hgUserLayWarning;
// class hgShipWarningInfo;

class hgNotesLayer
{
public:
	hgNotesLayer(void);
    ~hgNotesLayer(void);

public:
    QString m_Name;
    double m_Lat;
    double m_Lon;
    QString m_Notes;
    QString m_Color;
    QString m_DrawMan;
    bool m_IsNew;
};

#endif //HG_DATAMANAGER_H_