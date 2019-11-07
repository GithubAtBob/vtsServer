#include "StdAfx.h"
#include "hgFuseTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgComManager.h"
#include "Managers/hgConfigManager.h"
#include "Managers/hgTargetManager.h"
#include "hgutils/NavUtil.h"

vtsSETUP_TIMER("fuse", 300, hgFuseTimerHandler);

hgFuseTimerHandler::hgFuseTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
    
}

hgFuseTimerHandler::~hgFuseTimerHandler(void)
{
   
}

vtsTimerHandler::WorkMode hgFuseTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_main;
}

void hgFuseTimerHandler::handle(const boost::system::error_code& e)
{
    return;
    QMap<QString,hgResult>::iterator it = hgTargetManager::m_mapResult.begin();
    while (it != hgTargetManager::m_mapResult.end())
    {
        hg::utils::PointLL radarPoint,aisPoint;
        {
            mymap<QString,hgTarget>::iterator itTarget = hgTargetManager::m_mapTarget.find(it->MMSI);
            if (itTarget != hgTargetManager::m_mapTarget.end())
            {
                radarPoint.setLat(itTarget->Lat);
                radarPoint.setLon(itTarget->Lon);
            }
        }
        {
            mymap<QString,hgTarget>::iterator itRadar = hgTargetManager::m_mapAis.find(it->MMSI);
            if (itRadar != hgTargetManager::m_mapRadar.end())
            {
                aisPoint.setLat(itRadar->Lat);
                aisPoint.setLon(itRadar->Lon);
            }
        }
        double l_dis = hg::utils::navutil::getDistance(radarPoint,aisPoint);
        if (l_dis > 0.3)
        {
            {
                QMap<QString,hgTarget>::iterator itTarget = hgTargetManager::m_mapTarget.find(it->ID);
                if (itTarget != hgTargetManager::m_mapTarget.end())
                {
                    itTarget->Result = AIS_FUSE;
                }
            }

            QSqlDatabase database = this->server()->openDBConnection();
            hgSqlOperator l_sqlOperator(database);
            hgTargetManager::AddFuaeResult(l_sqlOperator,it.value(),false,time(NULL));
            this->server()->closeDBConnection(database);
            it = hgTargetManager::m_mapResult.erase(it);
            continue;
        }
        ++it;
    }
    hgTargetManager::m_mapTarget.UnLockAll();
}
