#include "stdafx.h"

#include "hgAisDeadReckoning.h"

#include "hgutils/NavUtil.h"
#include "hgutils/MathUtil.h"
#include "Managers/hgTargetManager.h"

#include <numeric>

using namespace hg::utils;

namespace
{
    void projector_set_origin(CPlaneProjection& proj, const PointLL& p)
    {
        double latlon[2] = {mathutil::DegToRad(p.lat()), mathutil::DegToRad(p.lon())};
        proj.set_origin(latlon);
    }
    QPointF projector_llxy(CPlaneProjection& proj, const PointLL& p)
    {
        double latlon[2] = {mathutil::DegToRad(p.lat()), mathutil::DegToRad(p.lon())};
        double xy[2];
        proj.llxy(latlon, xy);
        return QPointF(xy[0], xy[1]);
    }

    PointLL projector_xyll(CPlaneProjection& proj, const QPointF& p)
    {
        double xy[2] = {p.x(), p.y()};
        double latlon[2];
        proj.xyll(xy, latlon);
        return PointLL(mathutil::RadToDeg(latlon[1]), mathutil::RadToDeg(latlon[0]));
    }
}

hgAisDeadReckoning::hgAisDeadReckoning()
{
    _lapsedTick = 0;
    _limitedPeriod = 0;
    _last.aiscog = 0.;
    _last.aissog = 0.;
    _last.truerot = 0.;
    _last.reportTick = 0;
    _state = -1;
    _updateAis = false;
}


void hgAisDeadReckoning::setMMSI(int MMSI)
{
    _mmsi = MMSI;
}

void hgAisDeadReckoning::reset()
{
    _state = -1;
    _aisHistorySog.clear();
}


bool hgAisDeadReckoning::isUpdateAis()
{
    return _updateAis;
}

double hgAisDeadReckoning::getBestSog(double aissog)
{
    if (_aisHistorySog.size() ==0 )
        return aissog;

    double sum = std::accumulate(_aisHistorySog.begin(), _aisHistorySog.end(), 0.0);
    double avgSog = sum / _aisHistorySog.size();
    avgSog = qMin(avgSog, aissog);
    // ais从静止开始的话
    if (aissog > 1.0 && avgSog <= 0.01)
    {
        _aisHistorySog.clear();
        avgSog = aissog;
    }
    return avgSog;
}

int hgAisDeadReckoning::getReportPeriod(double sog, double truerot)
{
    int period = 0;
    if (sog <= 14.0)
    {
        if (fabs(truerot) > 1e-3)
            period = 10;
        else
            period = 4;
    }
    else if (sog <= 23.0)
    {
        if (fabs(truerot) > 1e-3)
            period = 6;
        else
            period = 2;
    }
    else
    {
        if (fabs(truerot) > 1e-3)
            period = 3;
        else
            period = 2;
    }
    return period;
}

double hgAisDeadReckoning::getTrueRot(int aisrot, double nowcog, double lastcog, double dt)
{
    double truerot = 0.0;
    if (aisrot == -128)
        return truerot;
    if (abs(aisrot) == 127)
    {
        truerot = (nowcog-lastcog)/dt*60.0;
        if (aisrot > 0)
            truerot = fabs(truerot);
        else
            truerot = -fabs(truerot);
    }
    else
    {
        truerot = pow(aisrot/4.733, 2);
        if (aisrot < 0)
            truerot = -truerot;
    }
    return truerot;
}

/*
QPointF hgAisDeadReckoning::calcNextRecvMsgPosXY(QPointF& nowxy, double aissog, double aiscog, double truerot, int period)
{
    double nextcog = aiscog + truerot*period;
    double v = mathutil::KnToMsec(aissog);
    double theta = mathutil::DegToRad(nextcog);
    double next_vx = v * cos(theta);
    double next_vy = v * sin(theta);

    return nowxy + QPointF(next_vx*period, next_vy*period);
}
*/

QPointF hgAisDeadReckoning::calcNextRecvMsgPosXY(const QPointF& nowxy, const QPointF& speedXY, int period)
{
    return nowxy + speedXY*period;
}

QPointF hgAisDeadReckoning::calcSpeedXY(double aissog, double aiscog, double truerot, int period)
{
    double nextcog = aiscog + truerot*period/60.0;
    double v = mathutil::KnToMsec(aissog);
    double theta = mathutil::DegToRad(nextcog);
    double next_vx = v * cos(theta);
    double next_vy = v * sin(theta);
    return QPointF(next_vx, next_vy);
}

void hgAisDeadReckoning::update(int dt)
{
    if (_state == state_not_begin)
        return;
    do 
    {
        if (_state == state_ship_stop)
        {
            _last.DRPos = _last.aispos;
            break;
        }

        // 时间到了，但没有收到新的ais消息，继续推算
        if (_limitedPeriod > 0 && _lapsedTick >= _limitedPeriod)
        {
            double aissog = _last.aissog;
            double aiscog = _last.aiscog;
            double truerot = _last.truerot;
            int period = getReportPeriod(aissog, truerot);
            int usedperiod = _limitedPeriod + period;
            double bestSog = getBestSog(aissog);
            QPointF nowAisXY = projector_llxy(_projector, _last.aispos);
            QPointF next_vxy = calcSpeedXY(bestSog, aiscog, truerot, usedperiod);
            QPointF nextxy = calcNextRecvMsgPosXY(nowAisXY, next_vxy, usedperiod);
            QPointF DRxy = projector_llxy(_projector, _last.DRPos);
            _last.DR_vxy = (nextxy-DRxy)/(period*1.0);
            _limitedPeriod = usedperiod;
        }

        QPointF nowxy = projector_llxy(_projector, _last.DRPos);
        nowxy = nowxy + _last.DR_vxy*dt;
        _last.DRPos = projector_xyll(_projector, nowxy);
    } while (false);

    _lapsedTick += dt;
}

void hgAisDeadReckoning::updateAis(const hgTarget& aisdata, time_t reportTick)
{
    if (aisdata.MMSI.toInt() != _mmsi)
        return;

    _updateAis = true;

    PointLL aispos(aisdata.Lon, aisdata.Lat);
    double aiscog = aisdata.COG;
    double aissog = aisdata.SOG;
    int aisrot = aisdata.ROTAIS;
    double truerot = 0.0;
    bool update_state = true;

    do {
        if (_state = state_not_begin)
        {
            projector_set_origin(_projector, aispos);
            double v = mathutil::KnToMsec(aissog);
            double theta = mathutil::DegToRad(aiscog);
            _last.DR_vxy.rx() = v*cos(theta);
            _last.DR_vxy.ry() = v*sin(theta);
            _last.DRPos = PointLL(aisdata.Lon, aisdata.Lat);

            _aisHistorySog.push_back(aissog);

            if (aissog == 0.0)
                _state = state_ship_stop;
            else
                _state = state_ship_move;
            break;
        }


        double dt = reportTick - _last.reportTick;
        QPointF nowAisXY = projector_llxy(_projector, aispos);
        QPointF lastAisXY = projector_llxy(_projector, _last.aispos);
        QPointF dXY = nowAisXY - lastAisXY;
        if (dt < 1.0)
        {
            update_state = false;
            break;
        }

        if ((fabs(dXY.x()) < 1e-3 && fabs(dXY.y()) < 1e-3 ))
        {
            if (aissog == 0.0)
            {
                // ais停船
                _state = state_ship_stop;
                break;
            }
            else
            {
                update_state = false;
                break;
            }
        }

        // 上一次是停止状态，需要清空sog
        if (_state == state_ship_stop)
            _aisHistorySog.clear();

        _state = state_ship_move;
        _aisHistorySog.push_back(aissog);
        if (_aisHistorySog.size() > 5)
            _aisHistorySog.pop_front();
        double bestSog = getBestSog(aissog);
        truerot = getTrueRot(aisrot, aiscog, _last.aiscog, dt);
        int period = getReportPeriod(aissog, truerot);

        int usedperiod = period;
        QPointF next_vxy = calcSpeedXY(bestSog, aiscog, truerot, usedperiod);
        QPointF nextxy = calcNextRecvMsgPosXY(nowAisXY, next_vxy, usedperiod);

        PointLL nextpos = projector_xyll(_projector, nextxy);
        double brg = navutil::getBearing(_last.DRPos, nextpos);
        // nextpos可能在当前推算位置的后面，最多进行3次过滤
        for (int i=0; i<3; i++)
        {
            if (fabs(brg-aiscog) < 60.0)
                break;
            usedperiod += period;
            next_vxy = calcSpeedXY(aissog, aiscog, truerot, usedperiod);
            nextxy = calcNextRecvMsgPosXY(nowAisXY, next_vxy, usedperiod);
            nextpos = projector_xyll(_projector, nextxy);
            brg = navutil::getBearing(_last.DRPos, nextpos);
        }

        QPointF DRxy = projector_llxy(_projector, _last.DRPos);
        QPointF dr_vxy = (nextxy - DRxy) / (usedperiod*1.0);

        _last.DR_vxy = dr_vxy;
        _lapsedTick = 0;
        _limitedPeriod = usedperiod;

    } while(false);

    if (!update_state)
        return;

    _last.reportTick = reportTick;
    _last.aissog = aissog;
    _last.aiscog = aiscog;
    _last.truerot = truerot;
    _last.aispos = aispos;
}
