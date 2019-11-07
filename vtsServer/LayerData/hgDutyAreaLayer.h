#ifndef HG_DUTYAREALAYER_H_
#define HG_DUTYAREALAYER_H_

#include "hgutils/PolygonLL.h"
#include "LayerData/hgShipWarningInfo.h"
#include "LayerData/hgUserLayWarning.h"

class hgUserLayWarning;
class hgShipWarningInfo;

class hgDutyAreaLayer
{
public:
	hgDutyAreaLayer(void);
    ~hgDutyAreaLayer(void);

public:
    QString m_Name;
    int m_LineStyle;
    int m_FullStyle;
    int m_LineWidth;
    QString m_DutyMan;
    QString m_DrawMan;
    bool m_IsNew;
    QString m_LineColor;
    QString m_FullColor;
    hg::utils::PolygonLL m_Polygon;
};

#endif //HG_DATAMANAGER_H_