
#include "StdAfx.h"
#include "hgIdentityHandler.h"

#include "message/IdentityPack.pb.h"
#include "message/hgAlgorOwnShip.pb.h"
#include "frame/vtsServer.h"
#include "Managers/hgDataManager.h"
#include "Managers/hgTargetManager.h"
#include "Managers/hgSendManager.h"
hgIdentityHandler::hgIdentityHandler()
{

}

hgIdentityHandler::~hgIdentityHandler(void)
{
}

vtsRequestHandler::WorkMode hgIdentityHandler::workMode()
{
    return Work_Delete_Manual;
}

void hgIdentityHandler::handle(boost::asio::const_buffer& data)
{
    IdentityPack msg;
    msg.ParseFromArray(boost::asio::buffer_cast<const char*>(data), boost::asio::buffer_size(data));
    

    if (msg.type() == IdentityType::ServerLogin)
    {
        this->connection()->setChannel(msg.name());
        hgSendManager::SendClientMessage("Identity",msg,this->connection());
        if (msg.name() == "s_AlgorithServer")
        {
            hgAlgorOwnShip l_hgAlgorOwnShip;
            for (int i = 0; i < hgTargetManager::m_AlgorOwnMMSI.size(); i++)
            {
                l_hgAlgorOwnShip.add_mmsi(hgTargetManager::m_AlgorOwnMMSI.at(i).toStdString());
            }
            hgSendManager::SendCurrentMessage("AlgorOwnShip",l_hgAlgorOwnShip,this->connection());
        }
    }
    else if (msg.type() == IdentityType::UserLogin)
    {
        this->connection()->setChannel(msg.name());
        this->connection()->server().connectionManager().for_each
            ([&](ConnectionPtr p){
                if (p->channel().size() > 0 && p->channel()[0] == 's')//自己不要发送
                {
                    IdentityPack l_msg;
                    l_msg.set_type(IdentityType::ServerLogin);
                    l_msg.set_name(p->channel());
                    hgSendManager::SendCurrentMessage("Identity",l_msg,this->connection());
                }
                if (p->channel().size() > 0 && p->channel()[0] == 'c')
                {//发送在线客服端信息至当前登入账号
                    auto &remote = p->socket().remote_endpoint();
                    IdentityPack l_msg;
                    l_msg.set_type(IdentityType::UserLogin);
                    l_msg.set_name(p->channel());
                    l_msg.set_ip(remote.address().to_string());
                    l_msg.set_port(QString::number(remote.port()).toStdString());
                    hgSendManager::SendCurrentMessage("Identity",l_msg,this->connection());
                }
                if (p->channel().size() > 0 && p->channel()[0] == 'g')
                {//发送在线客服端信息至当前登入账号
                    auto &remote = p->socket().remote_endpoint();
                    IdentityPack l_msg;
                    l_msg.set_type(IdentityType::ShipLogin);
                    l_msg.set_name(p->channel());
                    l_msg.set_ip(remote.address().to_string());
                    l_msg.set_port(QString::number(remote.port()).toStdString());
                    hgSendManager::SendCurrentMessage("Identity",l_msg,this->connection());
                }
        });
        {//发送至客服端上线消息
            auto &remote = this->connection()->socket().remote_endpoint();
            IdentityPack l_msg;
            l_msg.set_type(IdentityType::UserLogin);
            l_msg.set_name(msg.name());
            l_msg.set_ip(remote.address().to_string());
            l_msg.set_port(QString::number(remote.port()).toStdString());
            hgSendManager::SendClientMessage("Identity",l_msg,this->connection());
        }
    }
    else if (msg.type() == IdentityType::UserLogout)
    {
        IdentityPack msg;
        msg.set_name(this->connection()->channel());
        msg.set_type(UserLogout);
        hgSendManager::SendSpecifyMessage("Identity",msg,this->connection(),"s_RadarServer");
        hgSendManager::SendClientMessage("Identity",msg,this->connection());
        //this->connection()->server().connectionManager().multicast("s_RadarServer","Identity",msg);
        this->connection()->setChannel("");
    }
    else if (msg.type() == IdentityType::ShipLogin)
    {
        this->connection()->setChannel(msg.name());
        this->connection()->server().connectionManager().for_each
            ([&](ConnectionPtr p){
                if (p->channel().size() > 0 && p->channel()[0] == 'c')
                {
                    auto &remote = this->connection()->socket().remote_endpoint();
                    IdentityPack l_msg;
                    l_msg.set_type(IdentityType::ShipLogin);
                    l_msg.set_name(msg.name());
                    l_msg.set_ip(remote.address().to_string());
                    l_msg.set_port(QString::number(remote.port()).toStdString());
                    hgSendManager::SendClientMessage("Identity",l_msg,this->connection());
                }
		});
		std::string l_name = msg.name();
		QString l_NameMMSI = l_name.c_str();
		QString l_MMSI = l_NameMMSI.right(l_NameMMSI.size() - 2);
		if (hgTargetManager::m_GPSMMSIPos.contains(l_MMSI))
		{
			std::string l_PosGPSname = "s_PosGPS" + l_MMSI.toStdString();
			IdentityPack l_imsg;
			l_imsg.set_name(l_PosGPSname);
			l_imsg.set_type(IdentityType::ServerLogin);
			hgSendManager::SendCurrentMessage("Identity",l_imsg,this->connection());
		}
		if (hgTargetManager::m_GPSMMSIHdg.contains(l_MMSI))
		{
			std::string l_HdgGPSname = "s_HdgGPS" + l_MMSI.toStdString();
			IdentityPack l_imsg;
			l_imsg.set_name(l_HdgGPSname);
			l_imsg.set_type(IdentityType::ServerLogin);
			hgSendManager::SendCurrentMessage("Identity",l_imsg,this->connection());
		}
		//发送本船 信息
		hgAlgorOwnShip l_hgAlgorOwnShip;
		for (int i = 0; i < hgTargetManager::m_AlgorOwnMMSI.size(); i++)
		{
			l_hgAlgorOwnShip.add_mmsi(hgTargetManager::m_AlgorOwnMMSI.at(i).toStdString());
		}
		hgSendManager::SendCurrentMessage("AlgorOwnShip",l_hgAlgorOwnShip,this->connection());
    }
	else if (msg.type() == IdentityType::ShipLogout)
	{
		std::string l_name = msg.name();
		QString l_MMSI = l_name.c_str();
		hgTargetManager::m_GPSMMSI.removeAll(l_MMSI);
		hgTargetManager::m_GPSMMSIHdg.removeAll(l_MMSI);
		hgTargetManager::m_GPSMMSIPos.removeAll(l_MMSI);
	}
    delete this;
    return ;
}

void hgIdentityHandler::timeout(time_t last)
{
    time_t now = time(NULL);
    std::cout << now-last << std::endl;
}

// void hgIdentityHandler::afterDb(DBWaringHandler* db)
// {
//     WaringRepsone result;
//     result.set_result(db->Result.toStdString());
//     result.set_type(db->Type);
//     responseAsync(result, boost::bind(&hgIdentityHandler::afterResponse, this, boost::asio::placeholders::error));
//     delete db;
// }
// 
// void hgIdentityHandler::afterResponse(const boost::system::error_code& e)
// {
//     delete this;
// }
