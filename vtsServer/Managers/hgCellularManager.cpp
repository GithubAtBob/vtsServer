#include "StdAfx.h"
#include "hgCellularManager.h"
#include "hgutils/NavUtil.h"
#include "hgutils/LineLL.h"

hgCellularManager::hgCellularManager(void)
{
}


hgCellularManager::~hgCellularManager(void)
{
}

void hgCellularManager::InitCellular()
{
	for (int i = 0; i < CELLULAR_WIDTH; i++)
	{
		for (int j = 0; j < CELLULAR_HIGH; j++)
		{
			m_arrayCellular[i][j] = 0;
		}
	}
}

void hgCellularManager::InitSimChannel()
{
    //计算A到C航段的坐标
    double l_dDisanceAC = 0;
    double l_dAngleA = 0;
    hgSimChannelData* l_sSimChannelDataA = new hgSimChannelData;
    l_sSimChannelDataA->m_MidBegin = hg::utils::PointLL(118.2934,24.2054);       //A点坐标
    l_sSimChannelDataA->m_MidEnd = hg::utils::PointLL(118.1825,24.3211);         //C点坐标

    hg::utils::navutil::getDistanceBearing(l_sSimChannelDataA->m_MidBegin, l_sSimChannelDataA->m_MidEnd, &l_dDisanceAC, &l_dAngleA);

    l_sSimChannelDataA->m_LeftBegin = hg::utils::navutil::getPoint(l_sSimChannelDataA->m_MidBegin, CHANNEL_WIDTH_A / 1852. / 2., l_dAngleA - 90);
    l_sSimChannelDataA->m_LeftEnd = hg::utils::navutil::getPoint(l_sSimChannelDataA->m_MidEnd, CHANNEL_WIDTH_A / 1852. / 2., l_dAngleA - 90);
    l_sSimChannelDataA->m_RightBegin = hg::utils::navutil::getPoint(l_sSimChannelDataA->m_MidBegin, CHANNEL_WIDTH_A / 1852. / 2., l_dAngleA + 90);
    l_sSimChannelDataA->m_RightEnd = hg::utils::navutil::getPoint(l_sSimChannelDataA->m_MidEnd, CHANNEL_WIDTH_A / 1852. / 2., l_dAngleA + 90);

    l_sSimChannelDataA->m_dLength = 17700;
    l_sSimChannelDataA->m_dWidthBegin = CHANNEL_WIDTH_A;
    l_sSimChannelDataA->m_dWidthEnd = CHANNEL_WIDTH_A;
    l_sSimChannelDataA->m_dAllLength = 0;
    l_sSimChannelDataA->m_dAngle = l_dAngleA;
    l_sSimChannelDataA->m_LineLL.setPoints(l_sSimChannelDataA->m_LeftBegin,l_sSimChannelDataA->m_RightBegin);

    l_sSimChannelDataA->m_PolygonLL.push_back(l_sSimChannelDataA->m_LeftBegin);
    l_sSimChannelDataA->m_PolygonLL.push_back(l_sSimChannelDataA->m_LeftEnd);
    l_sSimChannelDataA->m_PolygonLL.push_back(l_sSimChannelDataA->m_RightBegin);
    l_sSimChannelDataA->m_PolygonLL.push_back(l_sSimChannelDataA->m_RightEnd);


    m_vecSimChannelDataList.append(l_sSimChannelDataA);

    //计算C到C1航段的坐标
    double l_dDistanceCD = 0;
    double l_dAngleC = 0;
    hg::utils::PointLL l_pointLLD(118.1021,24.4028);
    hgSimChannelData* l_sSimChannelDataC = new hgSimChannelData;
    l_sSimChannelDataC->m_MidBegin = hg::utils::PointLL(118.1825,24.3211);   //C点坐标
    hg::utils::navutil::getDistanceBearing(l_sSimChannelDataC->m_MidBegin, l_pointLLD, &l_dDistanceCD, &l_dAngleC);
    l_sSimChannelDataC->m_MidEnd = hg::utils::navutil::getPoint(l_sSimChannelDataC->m_MidBegin, CHANNEL_LENGTH_CC1 / 1852., l_dAngleC); //C1点坐标
    l_sSimChannelDataC->m_LeftBegin = hg::utils::navutil::getPoint(l_sSimChannelDataC->m_MidBegin,CHANNEL_WIDTH_C / 1852. / 2., l_dAngleC - 90);
    l_sSimChannelDataC->m_LeftEnd = hg::utils::navutil::getPoint(l_sSimChannelDataC->m_MidEnd,CHANNEL_WIDTH_C / 1852. / 2., l_dAngleC - 90);
    l_sSimChannelDataC->m_RightBegin = hg::utils::navutil::getPoint(l_sSimChannelDataC->m_MidBegin,CHANNEL_WIDTH_C / 1852. / 2., l_dAngleC + 90);
    l_sSimChannelDataC->m_RightEnd = hg::utils::navutil::getPoint(l_sSimChannelDataC->m_MidEnd,CHANNEL_WIDTH_C / 1852. / 2., l_dAngleC + 90);

    l_sSimChannelDataC->m_dLength = 5900;
    l_sSimChannelDataC->m_dWidthBegin = CHANNEL_WIDTH_C;
    l_sSimChannelDataC->m_dWidthEnd = CHANNEL_WIDTH_C;
    l_sSimChannelDataC->m_dAllLength = 17700;
    l_sSimChannelDataC->m_dAngle = l_dAngleC;
    l_sSimChannelDataA->m_LineLL.setPoints(l_sSimChannelDataA->m_LeftBegin,l_sSimChannelDataA->m_RightBegin);

    l_sSimChannelDataC->m_PolygonLL.push_back(l_sSimChannelDataC->m_LeftBegin);
    l_sSimChannelDataC->m_PolygonLL.push_back(l_sSimChannelDataC->m_LeftEnd);
    l_sSimChannelDataC->m_PolygonLL.push_back(l_sSimChannelDataC->m_RightBegin);
    l_sSimChannelDataC->m_PolygonLL.push_back(l_sSimChannelDataC->m_RightEnd);

    m_vecSimChannelDataList.append(l_sSimChannelDataC);

    //计算C1到C2航段的坐标
    hgSimChannelData* l_sSimChannelDataC1 = new hgSimChannelData;
    l_sSimChannelDataC1->m_MidBegin = l_sSimChannelDataC->m_MidEnd;  //C1
    l_sSimChannelDataC1->m_MidEnd = hg::utils::navutil::getPoint(l_sSimChannelDataC1->m_MidBegin,CHANNEL_LENGTH_C1C2 / 1852.,l_dAngleC); //C2
    l_sSimChannelDataC1->m_LeftBegin = hg::utils::navutil::getPoint(l_sSimChannelDataC1->m_MidBegin,CHANNEL_WIDTH_C / 1852. / 2., l_dAngleC - 90);
    l_sSimChannelDataC1->m_LeftEnd = hg::utils::navutil::getPoint(l_sSimChannelDataC1->m_MidEnd,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleC - 90);
    l_sSimChannelDataC1->m_RightBegin = hg::utils::navutil::getPoint(l_sSimChannelDataC1->m_MidBegin,CHANNEL_WIDTH_C / 1852. / 2., l_dAngleC + 90);
    l_sSimChannelDataC1->m_RightEnd = hg::utils::navutil::getPoint(l_sSimChannelDataC1->m_MidEnd,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleC + 90);

    l_sSimChannelDataC1->m_dLength = 500;
    l_sSimChannelDataC1->m_dWidthBegin = CHANNEL_WIDTH_C;
    l_sSimChannelDataC1->m_dWidthEnd = CHANNEL_WIDTH_D;
    l_sSimChannelDataC1->m_dAngle = l_dAngleC;
    l_sSimChannelDataC1->m_LineLL.setPoints(l_sSimChannelDataC1->m_LeftBegin,l_sSimChannelDataC1->m_RightBegin);

    l_sSimChannelDataC1->m_PolygonLL.push_back(l_sSimChannelDataC1->m_LeftBegin);
    l_sSimChannelDataC1->m_PolygonLL.push_back(l_sSimChannelDataC1->m_LeftEnd);
    l_sSimChannelDataC1->m_PolygonLL.push_back(l_sSimChannelDataC1->m_RightBegin);
    l_sSimChannelDataC1->m_PolygonLL.push_back(l_sSimChannelDataC1->m_RightEnd);

    m_vecSimChannelDataList.append(l_sSimChannelDataC1);

    //计算C2到D航段的坐标
    hgSimChannelData* l_sSimChannelDataC2 = new hgSimChannelData;
    l_sSimChannelDataC2->m_MidBegin = l_sSimChannelDataC1->m_MidEnd;
    l_sSimChannelDataC2->m_MidEnd = hg::utils::PointLL(118.1021,24.4028); //D
    l_sSimChannelDataC2->m_LeftBegin = hg::utils::navutil::getPoint(l_sSimChannelDataC2->m_MidBegin,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleC - 90);
    l_sSimChannelDataC2->m_LeftEnd = hg::utils::navutil::getPoint(l_sSimChannelDataC2->m_MidEnd,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleC - 90);
    l_sSimChannelDataC2->m_RightBegin = hg::utils::navutil::getPoint(l_sSimChannelDataC2->m_MidBegin,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleC + 90);
    l_sSimChannelDataC2->m_RightEnd = hg::utils::navutil::getPoint(l_sSimChannelDataC2->m_MidEnd,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleC + 90);

    l_sSimChannelDataC2->m_dLength = hg::utils::navutil::getDistance(l_sSimChannelDataC2->m_MidBegin,l_sSimChannelDataC2->m_MidEnd) * 1852.;
    l_sSimChannelDataC2->m_dWidthBegin = CHANNEL_WIDTH_D;
    l_sSimChannelDataC2->m_dWidthEnd = CHANNEL_WIDTH_D;
    l_sSimChannelDataC2->m_dAngle = l_dAngleC;
    l_sSimChannelDataC2->m_LineLL.setPoints(l_sSimChannelDataC2->m_LeftBegin,l_sSimChannelDataC2->m_RightBegin);

    l_sSimChannelDataC2->m_PolygonLL.push_back(l_sSimChannelDataC2->m_LeftBegin);
    l_sSimChannelDataC2->m_PolygonLL.push_back(l_sSimChannelDataC2->m_LeftEnd);
    l_sSimChannelDataC2->m_PolygonLL.push_back(l_sSimChannelDataC2->m_RightBegin);
    l_sSimChannelDataC2->m_PolygonLL.push_back(l_sSimChannelDataC2->m_RightEnd);

    m_vecSimChannelDataList.append(l_sSimChannelDataC2);

    //计算D到E1航段的坐标
    hgSimChannelData* l_sSimChannelDataD = new hgSimChannelData;
    l_sSimChannelDataD->m_MidBegin = l_sSimChannelDataC2->m_MidEnd;  //D
    l_sSimChannelDataD->m_MidEnd = hg::utils::PointLL(118.0469,24.4344); //E1

    double l_dDistanceDE1 = 0;
    double l_dAngleD = 0;
    hg::utils::navutil::getDistanceBearing(l_sSimChannelDataD->m_MidBegin, l_sSimChannelDataD->m_MidEnd, &l_dDistanceDE1, &l_dAngleD);

    l_sSimChannelDataD->m_LeftBegin = hg::utils::navutil::getPoint(l_sSimChannelDataD->m_MidBegin,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleD - 90);
    l_sSimChannelDataD->m_LeftEnd = hg::utils::navutil::getPoint(l_sSimChannelDataD->m_MidEnd,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleD - 90);
    l_sSimChannelDataD->m_RightBegin = hg::utils::navutil::getPoint(l_sSimChannelDataD->m_MidBegin,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleD + 90);
    l_sSimChannelDataD->m_RightEnd = hg::utils::navutil::getPoint(l_sSimChannelDataD->m_MidEnd,CHANNEL_WIDTH_D / 1852. / 2., l_dAngleD + 90);

    l_sSimChannelDataD->m_dLength = hg::utils::navutil::getDistance(l_sSimChannelDataD->m_MidBegin,l_sSimChannelDataD->m_MidEnd) * 1852.;
    l_sSimChannelDataD->m_dWidthBegin = CHANNEL_WIDTH_D;
    l_sSimChannelDataD->m_dWidthEnd = CHANNEL_WIDTH_D;
    l_sSimChannelDataD->m_dAngle = l_dAngleD;
    l_sSimChannelDataD->m_LineLL.setPoints(l_sSimChannelDataD->m_LeftBegin,l_sSimChannelDataD->m_RightBegin);

    l_sSimChannelDataD->m_PolygonLL.push_back(l_sSimChannelDataD->m_LeftBegin);
    l_sSimChannelDataD->m_PolygonLL.push_back(l_sSimChannelDataD->m_LeftEnd);
    l_sSimChannelDataD->m_PolygonLL.push_back(l_sSimChannelDataD->m_RightBegin);
    l_sSimChannelDataD->m_PolygonLL.push_back(l_sSimChannelDataD->m_RightEnd);

    m_vecSimChannelDataList.append(l_sSimChannelDataD);

    //计算E1到E2航段的坐标
    hgSimChannelData* l_sSimChannelDataE1 = new hgSimChannelData;
    l_sSimChannelDataE1->m_MidBegin = l_sSimChannelDataD->m_MidEnd;  //E1
    l_sSimChannelDataE1->m_MidEnd = hg::utils::PointLL(118.0453,24.4536); //E2

    double l_dDistanceE1E2 = 0;
    double l_dAngleE1 = 0;
    hg::utils::navutil::getDistanceBearing(l_sSimChannelDataE1->m_MidBegin, l_sSimChannelDataE1->m_MidEnd, &l_dDistanceE1E2, &l_dAngleE1);

    l_sSimChannelDataE1->m_LeftBegin = hg::utils::navutil::getPoint(l_sSimChannelDataE1->m_MidBegin,CHANNEL_WIDTH_E / 1852. / 2., l_dAngleE1 - 90);
    l_sSimChannelDataE1->m_LeftEnd = hg::utils::navutil::getPoint(l_sSimChannelDataE1->m_MidEnd,CHANNEL_WIDTH_E / 1852. / 2., l_dAngleE1 - 90);
    l_sSimChannelDataE1->m_RightBegin = hg::utils::navutil::getPoint(l_sSimChannelDataE1->m_MidBegin,CHANNEL_WIDTH_E / 1852. / 2., l_dAngleE1 + 90);
    l_sSimChannelDataE1->m_RightEnd = hg::utils::navutil::getPoint(l_sSimChannelDataE1->m_MidEnd,CHANNEL_WIDTH_E / 1852. / 2., l_dAngleE1 + 90);

    l_sSimChannelDataE1->m_dLength = hg::utils::navutil::getDistance(l_sSimChannelDataE1->m_MidBegin,l_sSimChannelDataE1->m_MidEnd) * 1852.;
    l_sSimChannelDataE1->m_dWidthBegin = CHANNEL_WIDTH_D;
    l_sSimChannelDataE1->m_dWidthEnd = CHANNEL_WIDTH_D;
    l_sSimChannelDataE1->m_dAngle = l_dAngleE1;
    l_sSimChannelDataE1->m_LineLL.setPoints(l_sSimChannelDataE1->m_LeftBegin,l_sSimChannelDataE1->m_RightBegin);

    l_sSimChannelDataE1->m_PolygonLL.push_back(l_sSimChannelDataE1->m_LeftBegin);
    l_sSimChannelDataE1->m_PolygonLL.push_back(l_sSimChannelDataE1->m_LeftEnd);
    l_sSimChannelDataE1->m_PolygonLL.push_back(l_sSimChannelDataE1->m_RightBegin);
    l_sSimChannelDataE1->m_PolygonLL.push_back(l_sSimChannelDataE1->m_RightEnd);

    m_vecSimChannelDataList.append(l_sSimChannelDataE1);


}

void hgCellularManager::GetLineParamet(hg::utils::PointLL &start, hg::utils::PointLL &end, double* k, double* b)
{
    *k = - (end.lat() - start.lat()) / (end.lon() - start.lon());
    *b = *k * start.lon() - start.lat();
}

double hgCellularManager::GetDitance(hg::utils::PointLL &target, double &k, double &b)
{
    return k * target.lon() + target.lat() + b;
}

int hgCellularManager::WithinChannel(hg::utils::PointLL &target)
{
    for (int i = 0; i < m_vecSimChannelDataList.size(); i++)
    {
        if (m_vecSimChannelDataList[i]->m_PolygonLL.containsPoint(target,Qt::OddEvenFill))
        {
            return i+1;
        }
    }
    return 0;
}

int hgCellularManager::Round(double count)
{
    int l_iCount = count;
    if(int((count * 10)) % (l_iCount * 10) <= 4)
    {
        return l_iCount;
    }
    else
    {
        return l_iCount + 1;
    }
}

void hgCellularManager::AddVirtualShip(hgVirtualShip& ship)
{
    m_mapVirtualShip.insert(ship.m_strMMSI,ship);
}

void hgCellularManager::ChangeVirtualShip(hgVirtualShip& ship)
{
    QMap<QString,hgVirtualShip>::iterator l_it = m_mapVirtualShip.find(ship.m_strMMSI);
    if (l_it != m_mapVirtualShip.end())
    {
        l_it->m_dSOG = ship.m_dSOG;
        l_it->m_iShipLength = ship.m_iShipLength;
        l_it->m_strGoodsType = ship.m_strGoodsType;
        l_it->m_bPutIn = ship.m_bPutIn; 
        l_it->m_iEndType = ship.m_iEndType; 
        l_it->m_strID = ship.m_strID;
        l_it->m_dLat = ship.m_dLat;
        l_it->m_dLon = ship.m_dLon;
        l_it->m_tStartTime = ship.m_tStartTime;
        l_it->m_tSTopTime = ship.m_tSTopTime;
    }
}

void hgCellularManager::AddToMap(hgTarget& ais)
{
    hg::utils::PointLL l_TargetPointLL(ais.Lat,ais.Lon);
    hg::utils::PointLL l_ExtendPointLL,l_IntersectPointLL;
    hg::utils::LineLL l_ExtendLineLL;
    double l_distance = 0.,l_Angle = 0;
    switch(WithinChannel(l_TargetPointLL))  //航段
    {
    case Non:
        return;
    case Line_F1:
        l_ExtendPointLL = hg::utils::navutil::getPoint(l_TargetPointLL,CELLULAR_WIDTH,m_vecSimChannelDataList[Non]->m_dAngle);
        l_ExtendLineLL.setPoints(l_TargetPointLL,l_ExtendPointLL);
        m_vecSimChannelDataList[Non]->m_LineLL.intersect(l_ExtendLineLL,&l_IntersectPointLL);
        l_distance = hg::utils::navutil::getDistance(l_TargetPointLL,l_IntersectPointLL);
        l_Angle = ais.COG - m_vecSimChannelDataList[Non]->m_dAngle;
        break;
    case Line_F2:
        l_ExtendPointLL = hg::utils::navutil::getPoint(l_TargetPointLL,CELLULAR_WIDTH,m_vecSimChannelDataList[Line_F1]->m_dAngle);
        l_ExtendLineLL.setPoints(l_TargetPointLL,l_ExtendPointLL);
        m_vecSimChannelDataList[Line_F1]->m_LineLL.intersect(l_ExtendLineLL,&l_IntersectPointLL);
        l_distance = hg::utils::navutil::getDistance(l_TargetPointLL,l_IntersectPointLL) + m_vecSimChannelDataList[Non]->m_dLength;
        l_Angle = ais.COG - m_vecSimChannelDataList[Line_F1]->m_dAngle;
        break;
    case Line_F3:
        l_ExtendPointLL = hg::utils::navutil::getPoint(l_TargetPointLL,CELLULAR_WIDTH,m_vecSimChannelDataList[Line_F2]->m_dAngle);
        l_ExtendLineLL.setPoints(l_TargetPointLL,l_ExtendPointLL);
        m_vecSimChannelDataList[Line_F2]->m_LineLL.intersect(l_ExtendLineLL,&l_IntersectPointLL);
        l_distance = hg::utils::navutil::getDistance(l_TargetPointLL,l_IntersectPointLL) + m_vecSimChannelDataList[Non]->m_dLength + m_vecSimChannelDataList[Line_F1]->m_dLength;
        l_Angle = ais.COG - m_vecSimChannelDataList[Line_F2]->m_dAngle;
        break;
    case Line_F4:
        l_ExtendPointLL = hg::utils::navutil::getPoint(l_TargetPointLL,CELLULAR_WIDTH,m_vecSimChannelDataList[Line_F3]->m_dAngle);
        l_ExtendLineLL.setPoints(l_TargetPointLL,l_ExtendPointLL);
        m_vecSimChannelDataList[Line_F3]->m_LineLL.intersect(l_ExtendLineLL,&l_IntersectPointLL);
        l_distance = hg::utils::navutil::getDistance(l_TargetPointLL,l_IntersectPointLL) + m_vecSimChannelDataList[Non]->m_dLength + m_vecSimChannelDataList[Line_F1]->m_dLength
            + m_vecSimChannelDataList[Line_F2]->m_dLength;
        l_Angle = ais.COG - m_vecSimChannelDataList[Line_F3]->m_dAngle;
        break;
    case Line_F5:
        l_ExtendPointLL = hg::utils::navutil::getPoint(l_TargetPointLL,CELLULAR_WIDTH,m_vecSimChannelDataList[Line_F4]->m_dAngle);
        l_ExtendLineLL.setPoints(l_TargetPointLL,l_ExtendPointLL);
        m_vecSimChannelDataList[Line_F4]->m_LineLL.intersect(l_ExtendLineLL,&l_IntersectPointLL);
        l_distance = hg::utils::navutil::getDistance(l_TargetPointLL,l_IntersectPointLL) + m_vecSimChannelDataList[Non]->m_dLength + m_vecSimChannelDataList[Line_F1]->m_dLength
            + m_vecSimChannelDataList[Line_F2]->m_dLength + m_vecSimChannelDataList[Line_F3]->m_dLength;
        l_Angle = ais.COG - m_vecSimChannelDataList[Line_F4]->m_dAngle;
        break;
    case Line_F6:
        l_ExtendPointLL = hg::utils::navutil::getPoint(l_TargetPointLL,CELLULAR_WIDTH,m_vecSimChannelDataList[Line_F5]->m_dAngle);
        l_ExtendLineLL.setPoints(l_TargetPointLL,l_ExtendPointLL);
        m_vecSimChannelDataList[Line_F5]->m_LineLL.intersect(l_ExtendLineLL,&l_IntersectPointLL);
        l_distance = hg::utils::navutil::getDistance(l_TargetPointLL,l_IntersectPointLL) + m_vecSimChannelDataList[Non]->m_dLength + m_vecSimChannelDataList[Line_F1]->m_dLength
            + m_vecSimChannelDataList[Line_F2]->m_dLength + m_vecSimChannelDataList[Line_F3]->m_dLength + m_vecSimChannelDataList[Line_F4]->m_dLength;
        l_Angle = ais.COG - m_vecSimChannelDataList[Line_F5]->m_dAngle;
        break;
    }
    int l_iLine = int(l_distance/CELLULAR_LENGTH);  //元胞号
    
    //航行状态
    if (ais.NavStatus == Mooring || ais.NavStatus == Wharf || ais.NavStatus == Stranding)
    {
        hgBarrierShip l_BarrierShip;
        l_BarrierShip.m_strMMSI = ais.MMSI;
        l_BarrierShip.m_dLat = ais.Lat;
        l_BarrierShip.m_dLon = ais.Lon;
        l_BarrierShip.m_iShipLength = ais.DimA + ais.DimB;

        m_mapBarrierShip.insert(l_BarrierShip.m_strMMSI,l_BarrierShip);
    } 
    else
    {
        //与航道夹角
        if (abs(l_Angle) < 10 || abs(l_Angle) > 170)
        {
            int l_line = 0;
            hgNormalShip l_NormalShip;

            if (abs(l_Angle) < 10)
            {
                l_line = 1; //进港
                l_NormalShip.m_cellularFirst[Line] = l_line;
                l_NormalShip.m_cellularFirst[Row] = l_iLine + int(ais.DimA/CELLULAR_LENGTH);
                l_NormalShip.m_cellularLast[Line] = l_line;
                l_NormalShip.m_cellularLast[Row] = l_iLine - int(ais.DimB/CELLULAR_LENGTH);
            } 
            else
            {
                l_line = 4; //出港
                l_NormalShip.m_cellularFirst[Line] = l_line;
                l_NormalShip.m_cellularFirst[Row] = l_iLine - int(ais.DimA/CELLULAR_LENGTH);
                l_NormalShip.m_cellularLast[Line] = l_line;
                l_NormalShip.m_cellularLast[Row] = l_iLine + int(ais.DimB/CELLULAR_LENGTH);
            }
            l_NormalShip.m_strMMSI = ais.MMSI;
            l_NormalShip.m_dLat = ais.Lat;
            l_NormalShip.m_dLon = ais.Lon;
            l_NormalShip.m_iShipLength = ais.DimA + ais.DimB;
            l_NormalShip.m_strShipType = ais.ShipType;
            l_NormalShip.m_dSOG =ais.SOG;
            l_NormalShip.m_dCOG = ais.COG;
            //l_NormalShip.m_strGoodsType = ;
            l_NormalShip.m_iNavStatus = ais.NavStatus;
            l_NormalShip.m_iCellularCount = int (l_NormalShip.m_iShipLength/CELLULAR_LENGTH) + 1;
            l_NormalShip.m_iOvertakingNum = 0;  
            l_NormalShip.m_iAcrossNum = 0;       
            l_NormalShip.m_iHeadonNum = 0;    
            l_NormalShip.m_iIntersectNum = 0;  
            l_NormalShip.m_iObstructNum = 0; 
            //l_NormalShip.m_tStartTime;
            //l_NormalShip.m_tSTopTime;

            m_mapNormalShip.insert(l_NormalShip.m_strMMSI,l_NormalShip);        
        }
        else
        {
            int l_line = 0;
            hgThroughShip l_ThroughShip;

            if (abs(l_Angle) < 90)
            {
                l_line = 1; //进港
                l_ThroughShip.m_cellularFirst[Line] = l_line;
                l_ThroughShip.m_cellularFirst[Row] = l_iLine + int(ais.DimA/CELLULAR_LENGTH);
                l_ThroughShip.m_cellularLast[Line] = l_line;
                l_ThroughShip.m_cellularLast[Row] = l_iLine - int(ais.DimB/CELLULAR_LENGTH);
            } 
            else
            {
                l_line = 4; //出港
                l_ThroughShip.m_cellularFirst[Line] = l_line;
                l_ThroughShip.m_cellularFirst[Row] = l_iLine - int(ais.DimA/CELLULAR_LENGTH);
                l_ThroughShip.m_cellularLast[Line] = l_line;
                l_ThroughShip.m_cellularLast[Row] = l_iLine + int(ais.DimB/CELLULAR_LENGTH);
            }
            l_ThroughShip.m_strMMSI = ais.MMSI;
            l_ThroughShip.m_dLat = ais.Lat;
            l_ThroughShip.m_dLon = ais.Lon;
            l_ThroughShip.m_iShipLength = ais.DimA + ais.DimB;
            l_ThroughShip.m_strShipType = ais.ShipType;
            l_ThroughShip.m_dSOG =ais.SOG;
            l_ThroughShip.m_dCOG = ais.COG;
            //l_ThroughShip.m_strGoodsType = ;
            l_ThroughShip.m_iNavStatus = ais.NavStatus;
            //l_ThroughShip.m_tStartTime;
            //l_ThroughShip.m_tSTopTime;

            m_mapThroughShip.insert(l_ThroughShip.m_strMMSI,l_ThroughShip);
        }
    }
}


