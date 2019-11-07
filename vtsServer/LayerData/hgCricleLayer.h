#ifndef HG_CRICLELAYER_H_
#define HG_CRICLELAYER_H_

#include "hgutils/PolygonLL.h"
#include "LayerData/hgShipWarningInfo.h"
#include "LayerData/hgUserLayWarning.h"

class hgUserLayWarning;
class hgShipWarningInfo;

class hgCricleLayer
{
public:
	hgCricleLayer(void);
    ~hgCricleLayer(void);
    void GetWarningData(hgCricleLayer &cricle);

public:
    ///ͼ�λ�������
    QString m_Name;
    double m_Lat;
    double m_Lon;
    double m_Radius;
    int m_LineStyle;
    int m_FullStyle;
    int m_LineWidth;
    QString m_DrawMan;
    bool m_IsNew;
    QString m_LineColor;
    QString m_FullColor;
    QList <QString> m_WaringID;
    hgUserLayWarning m_ULWaring;//������Ϣ����
    //ͼ�ξ�������
    QMap <QString,hgShipWarningInfo> m_Info;//key����MMSI��value�����������Ϣ
    QMap <QString,QString> m_InsideMMSI;//�������ڵĴ���
    QMap <QString,QMap <QString,bool> > m_CollisionData;// ��1����2���Ƿ���ײ���Դ�1Ϊ����
    bool m_IsSendCongestion;//ӵ��
    time_t m_CongesTime;//ӵ����ʼʱ��
};

#endif //HG_DATAMANAGER_H_