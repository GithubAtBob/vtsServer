#ifndef HG_POLYGONLAYER_H_
#define HG_POLYGONLAYER_H_

#include "hgutils/PolygonLL.h"
#include "LayerData/hgShipWarningInfo.h"
#include "LayerData/hgUserLayWarning.h"

class hgUserLayWarning;
class hgShipWarningInfo;

class hgPolygonLayer
{
public:
	hgPolygonLayer(void);
    ~hgPolygonLayer(void);
    void GetWarningData(hgPolygonLayer &polygon);//将图形警报参数 传给polygon

public:
    ///图形基本属性
    QString m_Name;
    int m_LineStyle;
    int m_FullStyle;
    int m_LineWidth;
    QString m_DrawMan;
    bool m_IsNew;
    QString m_LineColor;
    QString m_FullColor;
    QList <QString> m_WaringID;
    hg::utils::PolygonLL m_Polygon;
    hgUserLayWarning m_ULWaring;//警告信息参数
    //图形警报参数
    QMap <QString,hgShipWarningInfo> m_Info;//key船号MMSI，value触发警告的信息
    QMap <QString,QString> m_InsideMMSI;//在区域内的船号
    QMap <QString,QMap <QString,bool> > m_CollisionData;// 船1，船2，是否相撞，以船1为参数
    bool m_IsSendCongestion;//拥挤
    time_t m_CongesTime;//拥挤开始时刻
};

#endif //HG_DATAMANAGER_H_