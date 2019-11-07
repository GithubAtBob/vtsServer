#pragma once

#include "frame/vtsTimerHandler.h"
#include <QtSerialPort/QSerialPort>

#define PORT 39421 //udp½ÓÊÕais¶Ë¿ÚºÅ 
class hgComManager;
class QUdpSocket;
enum DataModeType
{
    TurnOff = 0,
    TurnOn,
};

class hgPortTimerHandler : public vtsTimerHandler
{
public:
    hgPortTimerHandler(const std::string& name);
    ~hgPortTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

    QSerialPort *m_pSerialPort;

protected:
    hgComManager* m_pComManager;
    QByteArray m_RequestData;
    bool m_bOpen;
    bool m_bRead;
    bool m_bInitCom;
    int m_Wait;
};
