
#include "StdAfx.h"
#include "hgRadarImageHandler.h"

#include "message/RadarImagePack.pb.h"
#include "frame/vtsServer.h"
#include "db/DBRadarImageHandler.h"
#include <QImage>
#include "Managers/hgTargetManager.h"
#include "Managers/hgSendManager.h"
#include "Managers/hgConfigManager.h"
#include "Managers/hgDataManager.h"
#include "Config/hgSysConfig.h"
#include "timer/hgPortTimerHandler.h"

hgRadarImageHandler::hgRadarImageHandler()
{

}

hgRadarImageHandler::~hgRadarImageHandler(void)
{
}

vtsRequestHandler::WorkMode hgRadarImageHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgRadarImageHandler::handle(boost::asio::const_buffer& data)
{
    bool l_debug = false;;
    if (hgConfigManager::m_sSysConfig->m_radarServer != TurnOn)
    {
        delete this;
        return;
    }
    RadarImagePack msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    if (l_debug)
        qDebug () << "Imgage  Begin" << clock() << time(NULL) << msg.clientname().c_str() << hgDataManager::m_radarCenter.contains(msg.clientname().c_str());
    //msg.ParseFromString(boost::asio::buffer_cast<const char*>(data));
    if (hgDataManager::m_radarCenter.contains(msg.clientname().c_str()))
    {
        RadarImageCenter l_center = hgDataManager::m_radarCenter.find(msg.clientname().c_str()).value();
        if (l_debug)
        {
            vtsInfo << "+++++ " << msg.view_center_y() << " "  << msg.view_center_x() << " "  << l_center.lat << " "  << l_center.lon << " "  << time(NULL);
        }
        if (l_center.lat != msg.view_center_y() || l_center.lon != msg.view_center_x())
        {
            if (l_debug)
            {
                vtsInfo << "+++++ERROR " << " " << msg.view_center_y() << " "  << msg.view_center_x() << " "  << l_center.lat << " "  << l_center.lon;
            }
            delete this;
            return ;
        }
    }
    std::string l_image = msg.image();
    QImage l_QImage;
    bool b = l_QImage.loadFromData(QByteArray::fromStdString(l_image));
    //QString l_URL = QString("data/RadarImage/%1.png").arg(time(NULL));
    QString l_URL = QString("data/RadarImage/%1.png").arg(hgTargetManager::GetWarnTime());
    if (hgConfigManager::m_sSysConfig->m_SaveFile == 1)
	{
		if ( !l_QImage.save(l_URL) )
		{
			delete this;
			return;
		}
        //SaveFile(msg);
    }
    if (this->connection()->channel() == "s_PlayBack")
    {
        if (l_debug)
            qDebug () << "Imgage  Save" << clock() << time(NULL);
        static int count = 0;
        count ++;
        msg.add_reserved0(QString::number(count).toStdString());
        hgSendManager::SendClientMessage("RadarImage",msg,this->connection());
        delete this;
    } 
    else
    {
        if (l_debug)
            qDebug () << "Imgage  Save" << clock() << time(NULL);
        DBRadarImageHandler *dbHandler = new DBRadarImageHandler();
        dbHandler->RadarImage = msg;
        dbHandler->URL = l_URL;
        postToDB(dbHandler, boost::bind(&hgRadarImageHandler::afterDb, this, dbHandler));
    }
}

void hgRadarImageHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

void hgRadarImageHandler::afterDb(DBRadarImageHandler* db)
{
    bool l_debug = false;
    //RadarImagePack result;
    static int count = 0;
    count ++;
    if (l_debug)
        qDebug () << "Imgage  End" << clock() << time(NULL) << count;
    db->RadarImage.add_reserved0(QString::number(count).toStdString());
    hgSendManager::SendSpecifyMessage("RadarImage",db->RadarImage,this->connection(),db->RadarImage.clientname());
    //this->connection()->server().connectionManager().multicast(db->RadarImage.clientname(),"RadarImage",db->RadarImage);
//     this->connection()->server().connectionManager().for_each
//         ([&](ConnectionPtr p){
//             if (p != this->connection())//自己不要发送
//             {
//                 boost::system::error_code error;
//                 p->write("RadarImage",db->RadarImage,error);
//             }
//     });
    //responseAsync(result, boost::bind(&hgRadarImageHandler::afterResponse, this, boost::asio::placeholders::error));
    delete db;
    delete this;
}

void hgRadarImageHandler::SaveFile(RadarImagePack msg)
{
    if (hgConfigManager::m_sSysConfig->m_SaveFile == 1)
    {
        time_t l_now = time(NULL);
        QSettings l_set(QString("./Data/RadarImgPack/%1/%2.ini").arg(hgConfigManager::m_sSysConfig->m_filename).arg(l_now),QSettings::IniFormat);
        l_set.setValue("Image/time",l_now);
        l_set.setValue("Image/packettype",msg.packettype());
        l_set.setValue("Image/utc",msg.utc());
        l_set.setValue("Image/view_center_x",msg.view_center_x());
        l_set.setValue("Image/view_center_y",msg.view_center_y());
        l_set.setValue("Image/view_scale",msg.view_scale());
        l_set.setValue("Image/clientname",msg.clientname().c_str());
        l_set.setValue("Image/image",QByteArray::fromStdString(msg.image()));
    }
}

void hgRadarImageHandler::afterResponse(const boost::system::error_code& e)
{
    delete this;
}
