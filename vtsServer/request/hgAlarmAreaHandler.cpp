
#include "StdAfx.h"
#include "hgAlarmAreaHandler.h"

#include "message/hgAlarmArea.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgAlarmManager.h"
#include "db/DBAlarmAreaHandler.h"

#include "Managers/hgSendManager.h"
hgAlarmAreaHandler::hgAlarmAreaHandler()
{

}

hgAlarmAreaHandler::~hgAlarmAreaHandler(void)
{
}

vtsRequestHandler::WorkMode hgAlarmAreaHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgAlarmAreaHandler::handle(boost::asio::const_buffer& data)
{
    hgAlarmArea msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    if (msg.type() == 1)//修改
    {
        hgAlarmManager::m_listArea.clear();
        for (int i = 0; i < msg.mmsi_size(); i++)
        {
            hgAlarmManager::m_listArea.push_back(msg.mmsi(i).c_str());
        }
        hgSendManager::SendClientMessageUOwn("AlarmArea",msg,this->connection());
        hgSendManager::SendSpecifyMessage("AlarmArea",msg,this->connection(),"s_AlgorithServer");
//         this->connection()->server().connectionManager().for_each
//             ([&](ConnectionPtr p){
//                 if (p != this->connection())//自己不要发送
//                 {
//                     p->write("AlarmArea",msg);
//                 }
//         });
        DBAlarmAreaHandler* dbHandler = new DBAlarmAreaHandler();
        dbHandler->m_type = msg.type();
        dbHandler->m_List = hgAlarmManager::m_listArea;
        postToDB(dbHandler, boost::bind(&hgAlarmAreaHandler::afterDb, this, dbHandler));
        //this->connection()->server().connectionManager().multicast("s_RadarServer","RadarAsk",msg);
//         delete this;
//         return ;
    }
    else if (msg.type() == 2)//请求数据
    {
        DBAlarmAreaHandler* dbHandler = new DBAlarmAreaHandler();
        dbHandler->m_type = msg.type();
        postToDB(dbHandler, boost::bind(&hgAlarmAreaHandler::afterDb, this, dbHandler));
    }
}

void hgAlarmAreaHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgAlarmAreaHandler::afterDb(DBAlarmAreaHandler* db)
{
    if (db->m_type == 2)
    {
        hgAlarmArea msg;
        msg.set_type(db->m_type);
        for (int i = 0; i < db->m_List.size(); i++)
        {
            QString l_mmsi = db->m_List.at(i);
            auto l_polygon = hgAlarmManager::m_LayerDataManager.m_pPloygonMap.find(l_mmsi);
            if (l_polygon == hgAlarmManager::m_LayerDataManager.m_pPloygonMap.end())
            {
                vtsWarning << "AlarmArea No Such Area";
                continue;
            }
            msg.add_mmsi(db->m_List.at(i).toStdString());
            hgPolygonMes* l_polygonMes = msg.add_polygon();
            for (int j = 0; j < l_polygon->m_Polygon.size(); j++)
            {
                PointMes* l_point = l_polygonMes->add_point();
                l_point->set_lat(l_polygon->m_Polygon.at(j).lat());
                l_point->set_lon(l_polygon->m_Polygon.at(j).lon());
            }
        }
        response(msg, boost::bind(&hgAlarmAreaHandler::afterResponse, this, boost::asio::placeholders::error));
        delete db;
    }
    else if (db->m_type == 1)
    {
        delete db;
        delete this;
        return ;
    }
}

void hgAlarmAreaHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
