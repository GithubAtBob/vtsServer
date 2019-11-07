#ifndef HG_CHANNELLAYER_H_
#define HG_CHANNELLAYER_H_

#include "hgutils/PolygonLL.h"
// #include "LayerData/hgShipWarningInfo.h"
// #include "LayerData/hgUserLayWarning.h"

// class hgUserLayWarning;
// class hgShipWarningInfo;
#include "message/channelwarinfo.pb.h"

enum hgChannelPointType{//������������˳��
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
    int containsPoint(hg::utils::PointLL pointLL); //Ϊ-1ʱ�����е���  >0ʱ�ڵ� һ��������

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