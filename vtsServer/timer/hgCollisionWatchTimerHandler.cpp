#include "StdAfx.h"
#include "hgCollisionWatchTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>
#include "Managers/hgTargetManager.h"
#include "hgutils/NavUtil.h"
#include "hgutils/MathUtil.h"
#include "message/hgWarningMes.pb.h"
#include "Managers/hgAlarmManager.h"
//vtsSETUP_TIMER("Domain", 1, hgDomainTimerHandler);

extern const char* hgWaringTypeGuid[];
hgCollisionWatchTimerHandler::hgCollisionWatchTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgCollisionWatchTimerHandler::~hgCollisionWatchTimerHandler(void)
{
    
}

vtsTimerHandler::WorkMode hgCollisionWatchTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgCollisionWatchTimerHandler::handle(const boost::system::error_code& e)
{
	  double start = GetTickCount();
    QMap<QString,CollisionWatch>::iterator l_itCollisionWatch;
    mymap<QString,hgTarget>::iterator l_itAisLoop;
    QMap<QString,hgTarget>::iterator l_itCollisionAis;
    for (l_itCollisionWatch = hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.begin(); l_itCollisionWatch != hgAlarmManager::m_WarningSetManager.m_mapCollisionWatch.end(); l_itCollisionWatch++)
    {

        if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itCollisionWatch->TargetID) != hgAlarmManager::m_WarningSetManager.m_mapAuthorized.end())
        {
            if (hgAlarmManager::m_WarningSetManager.m_mapAuthorized.find(l_itCollisionWatch->TargetID)->Authorize == true)
            {
                continue;
            }   
        }

        if (l_itCollisionWatch->b_CollisionWatch == false)
        {
            continue;
        }
        for (l_itAisLoop = hgTargetManager::m_mapTarget.begin(); l_itAisLoop != hgTargetManager::m_mapTarget.end(); ++l_itAisLoop)
        {
           hgTarget l_collisionValue;
           l_itCollisionAis = hgTargetManager::m_mapTarget.find(l_itCollisionWatch->TargetID);
           if (l_itCollisionAis != hgTargetManager::m_mapTarget.end())
           {
               l_collisionValue = l_itCollisionAis.value();
           }
           else
           {
               continue;
           }
           hgWarningMes l_CollisionMes,l_CancelMes;
           switch (hgAlarmManager::CollisionWatching(l_itCollisionWatch.value(),l_itAisLoop.value(),l_collisionValue))
           {
           case IsSendWarn:
               l_CollisionMes.set_warningid(hgWaringTypeGuid[COLLISIONWATCH]);
               l_CollisionMes.set_warningguid(QUuid::createUuid().toString().toStdString());
               l_CollisionMes.set_warningpriority(PriorityRed);
               l_CollisionMes.set_warningname(l_itCollisionWatch->TargetID.toStdString());
               l_CollisionMes.set_mmsi(l_itCollisionWatch->TargetID.toStdString());
               l_CollisionMes.set_warningtime(hgTargetManager::GetWarnTime());
               l_CollisionMes.set_warningtype(CollisionWatchWarn);
               hgAlarmManager::SendMessage(l_CollisionMes,"hgWarningMes",this);
               break;
           case UnSendWarn:
               break;
           case CancelWarn:
               l_CancelMes.set_warningid(hgWaringTypeGuid[COLLISIONWATCH]);
               l_CancelMes.set_warningguid(QUuid::createUuid().toString().toStdString());
               l_CancelMes.set_warningpriority(NoRisk);
               l_CancelMes.set_warningname(l_itCollisionWatch->TargetID.toStdString());
               l_CancelMes.set_mmsi(l_itCollisionWatch->TargetID.toStdString());
               l_CancelMes.set_warningtime(hgTargetManager::GetWarnTime());
               l_CancelMes.set_warningtype(CollisionWatchWarn);
               hgAlarmManager::SendMessage(l_CancelMes,"hgWarningMes",this);
               break;
           }   
        }
    }
		hgTargetManager::m_mapTarget.UnLockAll();
		double end = GetTickCount();
		double diff = end - start;
		if (diff > 500.0)
		{
			vtsInfo << "hgCollisionWatchTimerHandler TimeDiff: " << diff;
		}
}
