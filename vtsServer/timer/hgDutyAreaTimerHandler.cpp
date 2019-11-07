#include "StdAfx.h"
#include "hgDutyAreaTimerHandler.h"

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
vtsSETUP_TIMER("hgDutyAreaTimerHandler", 1.0, hgDutyAreaTimerHandler);
extern QList <AIS *> AISTestList;

hgDutyAreaTimerHandler::hgDutyAreaTimerHandler(const std::string& name)
    : vtsTimerHandler(name)
{
}

hgDutyAreaTimerHandler::~hgDutyAreaTimerHandler(void)
{
}

vtsTimerHandler::WorkMode hgDutyAreaTimerHandler::workMode()
{
    return vtsTimerHandler::WorkMode_thread;
}

void hgDutyAreaTimerHandler::handle(const boost::system::error_code& e)
{
    return ;
    for ( int i = 0; i < AISTestList.size() ; i++ )
    {
        AIS* l_test = AISTestList.at(i);
        hg::utils::PointLL po;
        po.setLat(l_test->lat);
        po.setLon(l_test->lon);
        QMap <QString,hgDutyAreaLayer>::Iterator iter = hgAlarmManager::m_LayerDataManager.m_pDutyAreaMap.begin();
        for ( ; iter != hgAlarmManager::m_LayerDataManager.m_pDutyAreaMap.end(); iter++ )
        {
            QString l_ID = iter.key();
            hgDutyAreaLayer l_vtsDutyArea = iter.value();
            hg::utils::PolygonLL poly = l_vtsDutyArea.m_Polygon;
            if (poly.containsPoint(po,Qt::WindingFill))     //在责任区内  入侵警报
            {
                //vtsInfo << "\ntest ok";
                WaringRepsone respon;
                WaringRequest* wa = respon.add_waring();
                wa->set_name(l_vtsDutyArea.m_Name.toStdString());
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
