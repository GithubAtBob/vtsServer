
#pragma once

#include "hgPlaneProjection.h"
#include "hgutils/Pointll.h"
#include "hgAisDecoder.h"

struct hgTarget;

class hgAisDeadReckoning
{
public:

    hgAisDeadReckoning();

    void setMMSI(int MMSI);

    int getMMSI()
    {
        return _mmsi;
    }

    void update(int dt);

    void updateAis(const hgTarget& aisdata, time_t reportTick);

    void reset();

    hg::utils::PointLL getDRPos()
    {
        return _last.DRPos;
    }

    bool isUpdateAis();
protected:

    int getReportPeriod(double sog, double truerot);

    double getTrueRot(int aisrot, double nowcog, double lastcog, double dt);

    QPointF calcNextRecvMsgPosXY(const QPointF& nowxy, const QPointF& speedXY, int period);

    QPointF calcSpeedXY(double aissog, double aiscog, double truerot, int period);

    double getBestSog(double aissog);

    enum
    {
        state_not_begin = -1,
        state_ship_stop = 0,
        state_ship_move = 1,
    };

    // -1: 没有推算
    // 0: 推算中,但ais船停止
    // 1: 推算中
    int _state;

    int _mmsi;

    int _limitedPeriod;

    int _lapsedTick;

    struct
    {
        double aissog;
        double aiscog;
        double truerot;
        QPointF DR_vxy;
        hg::utils::PointLL DRPos;
        hg::utils::PointLL aispos;
        time_t reportTick;
    }_last;

    CPlaneProjection    _projector;

    QVector<double> _aisHistorySog;

    bool _updateAis;
};
