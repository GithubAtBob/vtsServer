#ifndef HG_ELEMENTMANAGER_H_
#define HG_ELEMENTMANAGER_H_

#include "hgutils/PolygonLL.h"
#include <QMap>

#include "LayerData/hgPolygonLayer.h"
#include "LayerData/hgCricleLayer.h"
#include "LayerData/hgSectorLayer.h"
#include "LayerData/hgReportLineLayer.h"
#include "LayerData/hgDutyAreaLayer.h"
#include "LayerData/hgNotesLayer.h"
#include "LayerData/hgAidSailLayer.h"
#include "LayerData/hgFixedObjectLayer.h"
#include "LayerData/hgChannelLayer.h"
enum VtsShipInfoPosType{
    InsidePos = 1,
    OutSidePos
};

enum VtsWaringType{
    ENTERWATCH = 0,
    LEAVINGWATCH,
    INSIDEWATCH,
    OUTSIDEWATCH,
    APPROACHINGWATCH,
    HIGHSPEEDWATCH,
    LOWSPEEDWATCH,
    REPORTINGAREA,
    PROHIBITEDANCHORAGE,
    ANCHORAGE,
    ACCELERATIONWATCH,
    COLLISIONWATCH,
    STRIKINGWATCH,
    CONGESTIONWATCH,
    GROUNDINGWATCH,
    GROUNDINGSUPPLEMENT,
    COURSECHANGEWATCH,
    LOSTTRACK,
    LOSTTRACKWARINGSUPPRESSION,
    NEWTRACK,
    NEWTRACKWARINGSUPPRESSION,
    FoggyArea,
    ANCHORWATCH,
    BERTHINGWATCH,
    DOMAINWATCH,
    TURNINGCIRCLE,
    MOVEMENTEND,
    HISTORY,
    ThroughLine
};


struct vtsEllipse{
    QString Name;
    double Lat;
    double Lon;
    double LongAxis;
    double ShortAxis;
    int LineStyle;
    int FullStyle;
    int LineWidth;
    QList <int> WaringID;
    QString DrawMan;
    bool IsNew;
    QString LineColor;
    QString FullColor;
};

class hgLayerDataManager
{
public:
	hgLayerDataManager(void);
    ~hgLayerDataManager(void);
    void ReadAll(hgSqlOperator& sqlOperator);
    void ReadPloygon(hgSqlOperator& sqlOperator);
    void CreateArea(hgSqlOperator& sqlOperator);//判断是否有报警抑制区域 若无则创建
    void ReadEllipse(hgSqlOperator& sqlOperator);
    void ReadCricle(hgSqlOperator& sqlOperator);
    void ReadSector(hgSqlOperator& sqlOperator);
    void ReadDutyArea(hgSqlOperator& sqlOperator);
    void ReadReportLine(hgSqlOperator& sqlOperator);
    void ReadChannel(hgSqlOperator& sqlOperator);
    void ReadNotes(hgSqlOperator& sqlOperator);
    void ReadAidSail(hgSqlOperator& sqlOperator);
    void ReadFixedObject(hgSqlOperator& sqlOperator);

    void StartReportLineTimer();

public:
    QMap <QString, hgPolygonLayer> m_pPloygonMap;        //Guid,数据
    /*static */QMap <QString, vtsEllipse> m_pEllipseMap;
    QMap <QString, hgCricleLayer> m_pCricleMap;
    QMap <QString, hgSectorLayer> m_pSectorMap;
    QMap <QString, hgDutyAreaLayer> m_pDutyAreaMap;
    QMap <QString, hgReportLineLayer> m_pReportLineMap;
    QMap <QString, hgChannelLayer> m_pChannelMap;
    QMap <QString, hgNotesLayer> m_pNotesMap;
    QMap <QString, hgAidSailLayer> m_pAidSailMap;
    QMap <QString, hgFixedObjectLayer> m_pFixedObjectMap;
    QMap <QString, QString> m_ShipMap;


protected:

public:
};

#endif //HG_DATAMANAGER_H_