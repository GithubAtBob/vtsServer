#ifndef HG_CELLULARMANAGER_H_
#define HG_CELLULARMANAGER_H_

#define CELLULAR_WIDTH 4
#define CELLULAR_HIGH 1294

#define Line 0
#define Row 1

#define CHANNEL_WIDTH_A 450
#define CHANNEL_WIDTH_C 600
#define CHANNEL_WIDTH_D 410
#define CHANNEL_WIDTH_E 410


#define CHANNEL_LENGTH_CC1 5900
#define CHANNEL_LENGTH_C1C2 500

#define CELLULAR_LENGTH 30.

#include <QVector>
#include "hgutils/PointLL.h"
#include "hgutils/PolygonLL.h"
#include "hgTargetManager.h"

namespace hg
{
	namespace utils
	{
		class PointLL;
        class LineLL;
	}
}

enum Line_F
{
    Non = 0,
    Line_F1,
    Line_F2,
    Line_F3,
    Line_F4,
    Line_F5,
    Line_F6,
};

enum NavStatusNum
{
    Engine = 0,     //������ʹ����
    Mooring,        //ê��
    Control,        //δ����
    Limited,        //�����ʺ���
    Draught,        //�ܴ�����ˮ����
    Wharf,          //ϵ��
    Stranding,      //��ǳ
    Fishing,        //���²���
    Underway,       //������
    Num,             //δ֪
};

typedef struct
{
	hg::utils::PointLL m_LeftBegin;//���������90
	hg::utils::PointLL m_LeftEnd;
	hg::utils::PointLL m_MidBegin;//��������
	hg::utils::PointLL m_MidEnd;//��������
	hg::utils::PointLL m_RightBegin;//�������ұ�270
	hg::utils::PointLL m_RightEnd;

    hg::utils::LineLL m_LineLL;
    double m_dLength;   //�����γ���m
    double m_dAllLength; //ǰ�溽���γ���m
    double m_dWidthBegin;
    double m_dWidthEnd;
    double m_dAngle;  //���������߽Ƕ�
    hg::utils::PolygonLL m_PolygonLL;

}hgSimChannelData;

//�������д���
typedef struct
{
    QString m_strMMSI;
    double m_dLat;
    double m_dLon;
    int m_iShipLength;
    QString m_strShipType;
    double m_dSOG;
    double m_dCOG;
    QString m_strGoodsType;
    int m_iNavStatus;

    int m_iCellularCount; //ռ��Ԫ������
    int m_cellularFirst[Row]; //��Ԫ�����
    int m_cellularLast[Row]; //βԪ�����

    int m_iOvertakingNum;  //׷Խ����
    int m_iAcrossNum;      //��Խ���� 
    int m_iHeadonNum;     //��������
    int m_iIntersectNum;  //�������
    int m_iObstructNum;  //��������

    time_t m_tStartTime;  //��ʼģ��ʱ�䲽
    time_t m_tSTopTime;   //��ֹģ��ʱ�䲽

    int m_iEndPoint; //Ĭ��0�������ɺ����� 1��������3��ê�أ� 2��������4��ê�أ� 3�������뺣�׺���

  
}hgNormalShip;


//������
typedef struct
{
    QString m_strMMSI;
    double m_dLat;
    double m_dLon;
    int m_iShipLength;

    int m_iCellularCount; //ռ��Ԫ������
    int m_cellularFirst[Row]; //��Ԫ�����
    int m_cellularLast[Row]; //βԪ�����

    time_t m_tStartTime;  //��ʼģ��ʱ�䲽
    time_t m_tSTopTime;   //��ֹģ��ʱ�䲽

}hgBarrierShip;

//��Խ����
typedef struct
{
    QString m_strMMSI;
    double m_dLat;
    double m_dLon;
    int m_iShipLength;
    QString m_strShipType;
    double m_dSOG;
    double m_dCOG;
    QString m_strGoodsType;
    int m_iNavStatus;

    int m_iCellularCount; //ռ��Ԫ������
    int m_cellularFirst[Row]; //��Ԫ�����
    int m_cellularLast[Row]; //βԪ�����

    time_t m_tStartTime;  //��ʼģ��ʱ�䲽
    time_t m_tSTopTime;   //��ֹģ��ʱ�䲽

}hgThroughShip;

//��������
typedef struct
{
    QString m_strMMSIOwn;
    QString m_strMMSITarget;
    double m_dLat;
    double m_dLon;
    double m_dSOGOwn;
    double m_dSOGTarget;
    QString m_strGoodsTypeOwn;
    QString m_strGoodsTypeTarget;
    int m_iMeetType;  //�������� : 1����׷Խ  2������Խ  3��������  4��������

    time_t m_tStartTime;  //��ʼģ��ʱ�䲽
    time_t m_tSTopTime;   //��ֹģ��ʱ�䲽
}hgMeetShip;

//���⴬��
typedef struct
{
    QString m_strMMSI;
    double m_dSOG;
    double m_iShipLength;
    QString m_strGoodsType;
    bool m_bPutIn; //�Ƿ����
    int m_iEndType; //�յ�
    QString m_strID;
    double m_dLat;
    double m_dLon;
    time_t m_tStartTime;  //��ʼģ��ʱ�䲽
    time_t m_tSTopTime;   //��ֹģ��ʱ�䲽

}hgVirtualShip;

class hgCellularManager
{
public:
	hgCellularManager(void);
	~hgCellularManager(void);

	void InitCellular();
	void InitSimChannel();

    void GetLineParamet(hg::utils::PointLL &start, hg::utils::PointLL &end, double* k, double* b);

    double GetDitance(hg::utils::PointLL &target, double &k, double &b);

    int WithinChannel(hg::utils::PointLL &target);

    void AddToMap(hgTarget& ais);

    int Round(double count);

    void AddVirtualShip(hgVirtualShip& ship);

    void ChangeVirtualShip(hgVirtualShip& ship);

protected:
	int m_arrayCellular[CELLULAR_WIDTH][CELLULAR_HIGH];
	QVector<hgSimChannelData*> m_vecSimChannelDataList;

    QMap<QString,hgNormalShip> m_mapNormalShip; //�������д���
    QMap<QString,hgThroughShip> m_mapThroughShip; //��Խ����
    QMap<QString,hgBarrierShip> m_mapBarrierShip;  //������
    QMap<QString,hgVirtualShip> m_mapVirtualShip;  //���⴬��
};

#endif //HG_CELLULARMANAGER_H_