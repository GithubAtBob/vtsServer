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
    void GetWarningData(hgPolygonLayer &polygon);//��ͼ�ξ������� ����polygon

public:
    ///ͼ�λ�������
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
    hgUserLayWarning m_ULWaring;//������Ϣ����
    //ͼ�ξ�������
    QMap <QString,hgShipWarningInfo> m_Info;//key����MMSI��value�����������Ϣ
    QMap <QString,QString> m_InsideMMSI;//�������ڵĴ���
    QMap <QString,QMap <QString,bool> > m_CollisionData;// ��1����2���Ƿ���ײ���Դ�1Ϊ����
    bool m_IsSendCongestion;//ӵ��
    time_t m_CongesTime;//ӵ����ʼʱ��
};

#endif //HG_DATAMANAGER_H_