#include "StdAfx.h"
#include "hgComManager.h"


hgComManager::hgComManager(void)
{
	m_pSerialPort = new QSerialPort;
	m_nBaudRate = 9600;
	m_strComName = "";
}


hgComManager::~hgComManager(void)
{
	if (m_pSerialPort != NULL)
	{
		CloseCom();
		delete m_pSerialPort;
		m_pSerialPort = NULL;
	}
}

QSerialPort::BaudRate hgComManager::GetBaudRate(int baudRate)
{
	switch (baudRate)
	{
	case 1200:
		return QSerialPort::Baud1200;
	case 2400:
		return QSerialPort::Baud2400;
	case 4800:
		return QSerialPort::Baud4800;
	case 9600:
		return QSerialPort::Baud9600;
	case 19200:
		return QSerialPort::Baud19200;
	case 38400:
		return QSerialPort::Baud38400;
	case 57600:
		return QSerialPort::Baud57600;
	case 115200:
		return QSerialPort::Baud115200;
	}

	return QSerialPort::UnknownBaud;
}

void hgComManager::SetBaudRate(int baudRate)
{
	m_nBaudRate = baudRate;
}

void hgComManager::SetComName(QString strComName)
{
	m_strComName = strComName;
}

bool hgComManager::OpenCom()
{
	if (m_pSerialPort->isOpen())
	{
		return true;
	}

	m_pSerialPort->setPortName(m_strComName);
	m_pSerialPort->setBaudRate(GetBaudRate(m_nBaudRate));
	m_pSerialPort->setParity(QSerialPort::NoParity);
	m_pSerialPort->setDataBits(QSerialPort::Data8);
	m_pSerialPort->setStopBits(QSerialPort::OneStop);
	m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);
	//m_pSerialPort->setReadBufferSize(1024);
	return m_pSerialPort->open(QSerialPort::ReadWrite);
}

void hgComManager::CloseCom()
{
	if (m_pSerialPort->isOpen())
	{
		m_pSerialPort->close();
	}
}

bool hgComManager::ClearCom()
{
	if (m_pSerialPort->isOpen())
	{
		m_pSerialPort->clear();
		CloseCom();
		return OpenCom();
	}

	return false;
}

int hgComManager::ReadData(QByteArray& qa,int timeout)
{
	qa = m_pSerialPort->readLine();

	if (qa.size() == 0 && !m_pSerialPort->waitForReadyRead(timeout))
	{
		return -1;
	}
	return qa.size();
}