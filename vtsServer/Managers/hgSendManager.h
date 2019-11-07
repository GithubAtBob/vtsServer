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

public://����channel��������Ϊ�ͷ���
    static void SendShipMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//������������
    static void SendClientMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//���������ͷ��ˣ������ˣ�
    static void SendClientMessageUOwn(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//���������ͷ��ˣ������ˣ��Լ�����
    static void SendAllMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//���ô�����Ҫ�������ٻ�������
    static void SendExceptShipMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//���������������������
    static void SendSpecifyMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect,std::string channel);//����ָ������
    static void SendCurrentMessage(std::string type,google::protobuf::Message& msg,ConnectionPtr connect);//��ǰ����


    static void SendShipMessage(std::string type,google::protobuf::Message& msg,vtsServer* server);//������������
    static void SendClientMessage(std::string type,google::protobuf::Message& msg,vtsServer* server);//���������ͷ��ˣ������ˣ�
    static void SendExceptShipMessage(std::string type,google::protobuf::Message& msg,vtsServer* server);//���������������������
	static void SendSpecifyMessage(std::string type,google::protobuf::Message& msg,vtsServer* server,std::string channel);//����ָ������
	static void SendAllMessage(std::string type,google::protobuf::Message& msg,vtsServer* server);//������������

protected:

public:
};

#endif //HG_DATAMANAGER_H_