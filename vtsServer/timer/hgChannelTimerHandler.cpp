#include "StdAfx.h"
#include "hgChannelTimerHandler.h"

#include "frame/vtsLog.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"

#include <boost/thread.hpp>

#include "frame/vtsConnectionManager.h"
#include "OverLoad.h"
#include "hgutils/PolygonLL.h"
#include "message/waring.pb.h"
#include "Managers/hgAlarmManager.h"
#include "Managers/hgLayerDataManager.h"

#include "Managers/hgSendManager.h"
extern QList <AIS *> AISTestList;

hgChannelTimerHandler::hgChannelTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgChannelTimerHandler::~hgChannelTimerHandler(void)
{
}

vtsTimerHandler::WorkMode hgChannelTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgChannelTimerHandler::handle(const boost::system::error_code& e)
{
    return ;
    for ( int i = 0; i < AISTestList.size() ; i++ )
    {
        AIS* l_test = AISTestList.at(i);
        hg::utils::PointLL po;
        po.setLat(l_test->lat);
        po.setLon(l_test->lon);
        QMap <QString,hgChannelLayer>::Iterator iter = hgAlarmManager::m_LayerDataManager.m_pChannelMap.find(this->name().c_str());
        if (iter != hgAlarmManager::m_LayerDataManager.m_pChannelMap.end())
        {
            QString l_ID = iter.key();
            hgChannelLayer l_vtsChannel = iter.value();
            if (l_vtsChannel.containsPoint(po) == -1)     //在多边形内  入侵警报
            {
                //vtsInfo << "\ntest ok";
                WaringRepsone respon;
                WaringRequest* wa = respon.add_waring();
                wa->set_name(l_vtsChannel.m_Name.toStdString());
                wa->set_id(l_ID.toStdString());
                wa->set_type(2);
                wa->set_time(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString());

                hgSendManager::SendClientMessage("waring",respon,this->server());
//                 this->server()->connectionManager().for_each
//                     ([&](ConnectionPtr p){
//                         p->write("waring",respon);
//                 });
            }
        }
    }
}
