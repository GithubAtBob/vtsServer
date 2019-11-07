#ifndef HG_REPORTLINELAYER_H_
#define HG_REPORTLINELAYER_H_

#include "hgutils/PolygonLL.h"
#include "LayerData/hgShipWarningInfo.h"

class hgReportLineLayer
{
public:
	hgReportLineLayer(void);
    ~hgReportLineLayer(void);

public:
    QString m_Name;
    int m_LineStyle;
    int m_FullStyle;
    int m_LineWidth;
    QString m_DrawMan;
    bool m_IsNew;
    QString m_LineColor;
    QString m_FullColor;
    //QList <QString> m_WaringID;
    hg::utils::PolygonLL m_Polygon;
    QMap <QString,hgShipWarningInfo> m_Info;//key船号MMSI，value触发警告的信息
};

#endif //HG_DATAMANAGER_H_