#ifndef HG_CHANNELLAYER_H_
#define HG_CHANNELLAYER_H_

#include "hgutils/PolygonLL.h"
// #include "LayerData/hgShipWarningInfo.h"
// #include "LayerData/hgUserLayWarning.h"

// class hgUserLayWarning;
// class hgShipWarningInfo;
#include "message/channelwarinfo.pb.h"

enum hgChannelPointType{//点存放在容器的顺序
    ChannelLeftBegin = 0,
    ChannelLeftEnd,
    ChannelMidBegin,
    ChannelMidEnd,
    ChannelRightBegin,
    ChannelRightEnd,
    ChannelLefMidBegin,
    ChannelLefMidEnd,
    ChannelRigMidBegin,
    ChannelRigMidEnd,
};

class hgChannelLayer
{
public:
	hgChannelLayer(void);
    ~hgChannelLayer(void);
    int containsPoint(hg::utils::PointLL pointLL); //为-1时不再行道上  >0时在第 一个航段上

public:
    QString m_Name;
    QString m_Annotation;
    int m_ChannelType;
    double m_Width;
    QVector < hg::utils::PolygonLL > m_AllPoint;
    int m_LineStyle;
    QString m_LineColor;
    QString m_DrawMan;
    bool m_IsNew;
    ChannelWarInfo m_Info;
};

#endif //HG_DATAMANAGER_H_