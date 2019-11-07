#include "StdAfx.h"
#include "hgEllipseTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>

#include "frame/vtsConnectionManager.h"
#include "OverLoad.h"
#include "hgutils/PolygonLL.h"
#include "hgutils/NavUtil.h"
#include "message/waring.pb.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"

#include "Managers/hgSendManager.h"
extern QList <AIS *> AISTestList;

hgEllipseTimerHandler::hgEllipseTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgEllipseTimerHandler::~hgEllipseTimerHandler(void)
{
}

vtsTimerHandler::WorkMode hgEllipseTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgEllipseTimerHandler::handle(const boost::system::error_code& e)
{
    return ;
     for ( int i = 0; i < AISTestList.size() ; i++ )
     {
         AIS* l_test = AISTestList.at(i);
         hg::utils::PointLL l_testpoint;
         l_testpoint.setLat(l_test->lat);
         l_testpoint.setLon(l_test->lon);
         QMap <QString,vtsEllipse>::Iterator iter = hgAlarmManager::m_LayerDataManager.m_pEllipseMap.find(this->name().c_str());
         if (iter != hgAlarmManager::m_LayerDataManager.m_pEllipseMap.end())
         {
             QString l_ID = iter.key();
             vtsEllipse l_vtsEllipse = iter.value();
             hg::utils::PointLL l_center;
             l_center.setLat(l_vtsEllipse.Lat);
             l_center.setLon(l_vtsEllipse.Lon);
             hg::utils::PointLL l_begin(0,0);
             hg::utils::PointLL l_latend(0,l_center.lat()-l_testpoint.lat());
             hg::utils::PointLL l_lonend(l_center.lon()-l_testpoint.lon(),0);
             double l_latdist = hg::utils::navutil::getDistance(l_begin,l_latend);
             double l_londist = hg::utils::navutil::getDistance(l_begin,l_lonend);
             double l_distance = (l_latdist * l_latdist) / (l_vtsEllipse.ShortAxis * l_vtsEllipse.ShortAxis)
                 + (l_londist * l_londist) / (l_vtsEllipse.LongAxis * l_vtsEllipse.LongAxis);
             if ( l_distance <= 1 )     //到圆心距离小于半径 入侵警报
             {
                 //vtsInfo << "\ntest ok";
                 WaringRepsone respon;
                 WaringRequest* wa = respon.add_waring();
                 wa->set_name(l_vtsEllipse.Name.toStdString());
                 wa->set_id(l_ID.toStdString());
                 wa->set_type(2);
                 wa->set_time(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString());

                 hgSendManager::SendClientMessage("waring",respon,this->server());
//                  this->server()->connectionManager().for_each
//                      ([&](ConnectionPtr p){
//                          p->write("waring",respon);
//                  });
             }
         }
     }
}
