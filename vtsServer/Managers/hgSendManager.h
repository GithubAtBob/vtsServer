#ifndef HG_SENDMANAGER_H_
#define HG_SENDMANAGER_H_

// class QProcess;
// #include <QApplication>
#include <string>
#include <vector>

class hgSendManager
{
public:
	hgSendManager(void);
	~hgSendManager(void);

public://连接channel无设置视为客服端
    static void SendShipMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//仅发送至船端
    static void SendClientMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//仅发送至客服端（除船端）
    static void SendClientMessageUOwn(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//仅发送至客服端（除船端）自己不发
    static void SendAllMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//慎用船端需要的数据少基本不用
    static void SendExceptShipMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//发送至除船端以外的连接
    static void SendSpecifyMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect,std::string channel);//发送指定连接
    static void SendCurrentMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//当前连接


    static void SendShipMessage(std::string type,google::protobuf::Message& msg,vtsServer* server);//仅发送至船端
    static void SendClientMessage(std::string type,google::protobuf::Message& msg,vtsServer* server);//仅发送至客服端（除船端）
    static void SendExceptShipMessage(std::string type,google::protobuf::Message& msg,vtsServer* server);//发送至除船端以外的连接
	static void SendSpecifyMessage(std::string type,google::protobuf::Message& msg,vtsServer* server,std::string channel);//发送指定连接
	static void SendAllMessage(std::string type,google::protobuf::Message& msg,vtsServer* server);//仅发送至船端

protected:

public:
};

#endif //HG_DATAMANAGER_H_