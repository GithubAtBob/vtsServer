#include "StdAfx.h"
#include "Managers/hgSendManager.h"

#include "frame/vtsConnection.h"
#include "frame/vtsConnectionManager.h"
#include "frame/vtsServer.h"
#include "Managers/hgDataManager.h"
#include "message/hgShipAisMessage.pb.h"

/*************************************
    g_MMSI��ʽ Ϊ ����_MMSI
    s_Name��ʽ Ϊ ������_��������
    s_GPSMMSI��ʽ Ϊ ����GPS����_MMSI
    c_ID��ʽ Ϊ �ͷ���_�˺�
*************************************/
hgSendManager::hgSendManager(void)
{
}


hgSendManager::~hgSendManager(void)
{
}

void hgSendManager::SendShipMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect)
{
    connect->server().connectionManager().for_each
        ([&](ConnectionPtr p){
            if (p->channel().size() > 0 && p->channel()[0] == 'g')//������������
            {
                bool Send = true;
                if (type == "ShipAisMessage")
                {
                    hgShipAisMessage& l_mes = (hgShipAisMessage&)msg;
                    if (l_mes.id() == "-1" || l_mes.id() == "-2")
                    {
                        Send = true;
                    }
                    else
                    {
                        hg::utils::PointLL l_PointLL(l_mes.lon(),l_mes.lat());
                        if (hgDataManager::m_ShipAreaMap.contains(p->channel().c_str()))
                        {
                            if (!hgDataManager::m_ShipAreaMap[p->channel().c_str()].containsPoint(l_PointLL,Qt::WindingFill))
                            {
                                Send = false;
                            }
                        }
                    }
                }
                if (Send)
                {
                    p->write(type,msg);
                }
            }
    });
}

void hgSendManager::SendShipMessage(std::string type,google::protobuf::Message& msg,vtsServer* server)
{
    server->connectionManager().for_each
        ([&](ConnectionPtr p){
            if (p->channel().size() > 0 && p->channel()[0] == 'g')//������������
            {
                bool Send = true;
                if (type == "ShipAisMessage")
                {
                    hgShipAisMessage& l_mes = (hgShipAisMessage&)msg;
                    if (l_mes.id() == "-1" || l_mes.id() == "-2")
                    {
                        Send = true;
                    }
                    else
                    {
                        hg::utils::PointLL l_PointLL(l_mes.lon(),l_mes.lat());
                        if (hgDataManager::m_ShipAreaMap.contains(p->channel().c_str()))
                        {
                            if (!hgDataManager::m_ShipAreaMap[p->channel().c_str()].containsPoint(l_PointLL,Qt::WindingFill))
                            {
                                Send = false;
                            }
                        }
                    }
                }
                if (Send)
                {
                    p->write(type,msg);
                }
            }
    });
}

void hgSendManager::SendClientMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect)
{
    connect->server().connectionManager().for_each
        ([&](ConnectionPtr p){
            /*if (p->channel().size() == 0)
            {
                p->write(type,msg); //δ��¼����������
            }*/
            
            if (p->channel().size() > 0 && p->channel()[0] == 'c')
            {
                p->write(type,msg);
            }
    });
}

void hgSendManager::SendClientMessage(std::string type,google::protobuf::Message& msg,vtsServer* server)
{
    server->connectionManager().for_each
        ([&](ConnectionPtr p){
//             if (p->channel().size() == 0)
//             {
//                 p->write(type,msg); //δ��¼����������
//             }

            if (p->channel().size() > 0 && p->channel()[0] == 'c')
            {
                p->write(type,msg);
            }
    });
}

void hgSendManager::SendClientMessageUOwn(std::string type,google::protobuf::Message& msg,ConnectionPtr connect)
{
    connect->server().connectionManager().for_each
        ([&](ConnectionPtr p){
//             if (p->channel().size() == 0 && p != connect)
//             {
//                 p->write(type,msg);
//             }

            if (p->channel().size() > 0 && p->channel()[0] == 'c' && p != connect)
            {
                p->write(type,msg);
            }
    });
}

void hgSendManager::SendAllMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect)
{
    connect->server().connectionManager().broadcast(type,msg);
}

void hgSendManager::SendAllMessage(std::string type,google::protobuf::Message& msg,vtsServer* server)
{
	server->connectionManager().broadcast(type,msg);
}

void hgSendManager::SendExceptShipMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect)
{
    connect->server().connectionManager().for_each
        ([&](ConnectionPtr p){
            if (p->channel().size() > 0 && p->channel()[0] == 'g')
            {
            }
            else
            {
                if (p->channel().size() > 0)
                {
                    p->write(type,msg);
                }
            }
    });
}

void hgSendManager::SendExceptShipMessage(std::string type,google::protobuf::Message& msg,vtsServer* server)
{
    server->connectionManager().for_each
        ([&](ConnectionPtr p){
            if (p->channel().size() > 0 && p->channel()[0] == 'g')
            {
            }
            else
            {
                if (p->channel().size() > 0)
                {
                    p->write(type,msg);
                }
            }
    });
}

void hgSendManager::SendSpecifyMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect,std::string channel)
{
    connect->server().connectionManager().multicast(channel,type,msg);
}

void hgSendManager::SendSpecifyMessage(std::string type,google::protobuf::Message& msg,vtsServer* server,std::string channel)
{
    server->connectionManager().multicast(channel,type,msg);
}

void hgSendManager::SendCurrentMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect)
{
    connect->write(type,msg);
}
