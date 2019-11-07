#include "StdAfx.h"
#include "hgDownLineHandler.h"
#include "message/IdentityPack.pb.h"
#include "Managers/hgDataManager.h"
#include "Managers/hgAlarmManager.h"
#include "message/AlgorithmMode.pb.h"
#include "frame/vtsServer.h"

#include "Managers/hgSendManager.h"
void hgDownLineHandler::whenConnectionDisconnected(ConnectionPtr c)
{
    vtsError  << "++++++++++++++" << c->channel();
    if (c->channel().size() > 0)
    {
        if (c->channel() == "s_AlgorithServer")
        {
            hgAlarmManager::m_AlgorithmMode = NoneModel;
        }
        IdentityPack msg;
        std::string name = c->channel();
        msg.set_name(name);
        QString l_GPS = name.c_str();
        //if (l_GPS.startsWith("s_GPS"))
		if (l_GPS.startsWith("g"))
        {
            //QString l_GPS2 = l_GPS.right(l_GPS.size() - 5);
			QString l_GPS2 = l_GPS.right(l_GPS.size() - 2);
            if (hgTargetManager::m_GPSMMSI.contains(l_GPS2))
            {
                hgTargetManager::m_GPSMMSI.removeAll(l_GPS2);
			}
			if (hgTargetManager::m_GPSMMSIPos.contains(l_GPS2))
			{
				hgTargetManager::m_GPSMMSIPos.removeAll(l_GPS2);
			}
			if (hgTargetManager::m_GPSMMSIHdg.contains(l_GPS2))
			{
				hgTargetManager::m_GPSMMSIHdg.removeAll(l_GPS2);
			}
            qDebug () << "End Receive GPS " << l_GPS2;
            qDebug () << "<<<<<<<<<" << hgTargetManager::m_GPSMMSI;
        }
        if (name[0] == 's')
        {
            msg.set_type(ServerLogout);
        }
        else if (name[0] == 'c')
        {
            msg.set_type(UserLogout);
        }
        else if (name[0] == 'g')
        {
            msg.set_type(ShipLogout);
        }
        hgSendManager::SendClientMessage("Identity",msg,c);
//         c->server().connectionManager().for_each
//             ([&](ConnectionPtr p)
//         {  
//             if (p->channel()[0] != 's')
//             {
//                 p->write("Identity",msg);
//             }
		//         });
		if (l_GPS.startsWith("s_GPS"))
		{
			qDebug() << msg.name().c_str();
			hgSendManager::SendShipMessage("Identity",msg,c);
		}
        hgSendManager::SendSpecifyMessage("Identity",msg,&c->server(),"s_RadarServer");
        //c->server().connectionManager().multicast("s_RadarServer","Identity",msg);
    }
}
