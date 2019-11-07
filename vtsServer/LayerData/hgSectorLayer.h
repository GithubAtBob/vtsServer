#ifndef HG_SECTORLAYER_H_
#define HG_SECTORLAYER_H_

#include "hgutils/PolygonLL.h"
#include "LayerData/hgShipWarningInfo.h"
#include "LayerData/hgUserLayWarning.h"

class hgUserLayWarning;
class hgShipWarningInfo;

class hgSectorLayer
{
public:
	hgSectorLayer(void);
    ~hgSectorLayer(void);
    void GetWarningData(hgSectorLayer &sector);//��ͼ�ξ������� ����polygon

public:
    ///ͼ�λ�������
    QString m_Name;
    double m_Lat;
    double m_Lon;
    double m_Radius;
    double m_BeginAngle;
    double m_EndAngle;
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