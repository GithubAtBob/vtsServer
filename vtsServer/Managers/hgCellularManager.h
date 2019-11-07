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
    Engine = 0,     //发动机使用中
    Mooring,        //锚泊
    Control,        //未操纵
    Limited,        //有限适航性
    Draught,        //受船舶吃水限制
    Wharf,          //系泊
    Stranding,      //搁浅
    Fishing,        //从事捕捞
    Underway,       //航行中
    Num,             //未知
};

typedef struct
{
	hg::utils::PointLL m_LeftBegin;//航道最左边90
	hg::utils::PointLL m_LeftEnd;
	hg::utils::PointLL m_MidBegin;//航道中心
	hg::utils::PointLL m_MidEnd;//航道中心
	hg::utils::PointLL m_RightBegin;//航道最右边270
	hg::utils::PointLL m_RightEnd;

    hg::utils::LineLL m_LineLL;
    double m_dLength;   //航道段长度m
    double m_dAllLength; //前面航道段长度m
    double m_dWidthBegin;
    double m_dWidthEnd;
    double m_dAngle;  //航道中心线角度
    hg::utils::PolygonLL m_PolygonLL;

}hgSimChannelData;

//正常航行船舶
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

    int m_iCellularCount; //占据元胞个数
    int m_cellularFirst[Row]; //首元胞编号
    int m_cellularLast[Row]; //尾元胞编号

    int m_iOvertakingNum;  //追越次数
    int m_iAcrossNum;      //穿越次数 
    int m_iHeadonNum;     //对遇次数
    int m_iIntersectNum;  //交叉次数
    int m_iObstructNum;  //遇碍次数

    time_t m_tStartTime;  //起始模拟时间步
    time_t m_tSTopTime;   //终止模拟时间步

    int m_iEndPoint; //默认0——东渡航道； 1——进入3号锚地； 2——进入4号锚地； 3——进入海沧航道

  
}hgNormalShip;


//碍航物
typedef struct
{
    QString m_strMMSI;
    double m_dLat;
    double m_dLon;
    int m_iShipLength;

    int m_iCellularCount; //占据元胞个数
    int m_cellularFirst[Row]; //首元胞编号
    int m_cellularLast[Row]; //尾元胞编号

    time_t m_tStartTime;  //起始模拟时间步
    time_t m_tSTopTime;   //终止模拟时间步

}hgBarrierShip;

//穿越船舶
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

    int m_iCellularCount; //占据元胞个数
    int m_cellularFirst[Row]; //首元胞编号
    int m_cellularLast[Row]; //尾元胞编号

    time_t m_tStartTime;  //起始模拟时间步
    time_t m_tSTopTime;   //终止模拟时间步

}hgThroughShip;

//会遇局面
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
    int m_iMeetType;  //会遇类型 : 1——追越  2——穿越  3——对遇  4——交叉

    time_t m_tStartTime;  //起始模拟时间步
    time_t m_tSTopTime;   //终止模拟时间步
}hgMeetShip;

//虚拟船舶
typedef struct
{
    QString m_strMMSI;
    double m_dSOG;
    double m_iShipLength;
    QString m_strGoodsType;
    bool m_bPutIn; //是否进港
    int m_iEndType; //终点
    QString m_strID;
    double m_dLat;
    double m_dLon;
    time_t m_tStartTime;  //起始模拟时间步
    time_t m_tSTopTime;   //终止模拟时间步

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

    QMap<QString,hgNormalShip> m_mapNormalShip; //正常航行船舶
    QMap<QString,hgThroughShip> m_mapThroughShip; //穿越船舶
    QMap<QString,hgBarrierShip> m_mapBarrierShip;  //碍航物
    QMap<QString,hgVirtualShip> m_mapVirtualShip;  //虚拟船舶
};

#endif //HG_CELLULARMANAGER_H_