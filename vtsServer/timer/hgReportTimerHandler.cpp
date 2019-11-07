#include "StdAfx.h"
#include "hgReportTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>

#include "frame/vtsConnectionManager.h"
#include "OverLoad.h"
#include "hgutils/PolygonLL.h"
#include "message/waring.pb.h"
#include "Managers/hgLayerDataManager.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgTargetManager.h"

////////////////
#include "hgutils/NavUtil.h"

extern const char* hgWaringTypeGuid[];

hgReportTimerHandler::hgReportTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgReportTimerHandler::~hgReportTimerHandler(void)
{
}

vtsTimerHandler::WorkMode hgReportTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgReportTimerHandler::handle(const boost::system::error_code& e)
{
	double start = GetTickCount();
    QMap <QString,hgReportLineLayer>::Iterator l_polyiter = hgAlarmManager::m_LayerDataManager.m_pReportLineMap.begin();
    auto l_Targetiter = hgTargetManager::m_mapTarget.begin();
//     if (l_polyiter == hgAlarmManager::m_LayerDataManager.m_pReportLineMap.end() || l_Targetiter == hgTargetManager::m_mapTarget.end())
//     {
//         return;
//     }
    for ( ; l_polyiter != hgAlarmManager::m_LayerDataManager.m_pReportLineMap.end(); l_polyiter++)
    {
        for ( ; l_Targetiter != hgTargetManager::m_mapTarget.end(); ++l_Targetiter )
        {
    //         if (l_Targetiter->Source != AIS_DATA)
    //         {
    //             continue;
    //         }

            hgTarget l_ais = l_Targetiter.value();
            hg::utils::PointLL l_TargetPosition;
            l_TargetPosition.setLat(l_ais.Lat);
            l_TargetPosition.setLon(l_ais.Lon);
            if (l_polyiter.value().m_Info.find(l_ais.ID) == l_polyiter.value().m_Info.end())//此船是否在图形内记录
            {
                hgShipWarningInfo l_SWI;
                l_polyiter.value().m_Info.insert(l_ais.ID,l_SWI);
            }
            hg::utils::PointLL l_Position;
            l_Position.setLat(l_polyiter.value().m_Info.find(l_ais.ID).value().LastLat);
            l_Position.setLon(l_polyiter.value().m_Info.find(l_ais.ID).value().LastLon);
            hg::utils::LineLL l_line(l_Position,l_TargetPosition);
    //         qDebug () << l_polyiter.value().m_Info.find(l_ais.ID).value().LastLat
    //             << l_polyiter.value().m_Info.find(l_ais.ID).value().LastLon
    //             << l_ais.Lat << l_ais.Lon;
            if (l_polyiter.value().m_Info.find(l_ais.ID).value().LastLat != -1
                && ThroughReport(l_polyiter->m_Polygon,l_line))
            {
                hgWarningMes l_mes;
                l_mes.set_warningid(hgWaringTypeGuid[ThroughLine]);
                l_mes.set_warningguid(QUuid::createUuid().toString().toStdString());
                l_mes.set_warningpriority(PriorityRed);
                l_mes.set_warningname("Through");
                l_mes.set_mmsi(l_ais.ID.toStdString());
                l_mes.set_userlayguid(l_polyiter.key().toStdString());
                l_mes.set_userlayid(UserLayerType::UReprotLine);
                l_mes.set_warningtime(hgTargetManager::GetWarnTime());
                hgAlarmManager::SendMessage(l_mes,"hgWarningMes",this);
            }
            l_polyiter.value().m_Info.find(l_ais.ID).value().LastLat = l_ais.Lat;
            l_polyiter.value().m_Info.find(l_ais.ID).value().LastLon = l_ais.Lon;
        }
    }
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgReportTimerHandler TimeDiff: " << diff;
		}
}

bool hgReportTimerHandler::ThroughReport(hg::utils::PolygonLL ploygon, hg::utils::LineLL line)
{
    for ( int i = 1; i < ploygon.size(); i++ )
    {
        hg::utils::LineLL l_line(ploygon.at(i-1),ploygon.at(i));
        hg::utils::PointLL l_point;
//         int a = l_line.intersect(line,&l_point);
//         qDebug() << "i = "<<i <<l_line.intersect(line,&l_point);
//         double l_dist = hg::utils::navutil::getDistance(line.p1(),line.p2());
        if (l_line.intersect(line,&l_point) == QLineF::BoundedIntersection)
        {
            //qDebug() << true << line.lat1() << line.lon1() << line.lat2() << line.lon2() << l_line.lat1() << l_line.lon1() << l_line.lat2() << l_line.lon2();
            return true;
        }
    }
    return false;
}