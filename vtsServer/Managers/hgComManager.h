#ifndef HG_COMMANAGER_H_
#define HG_COMMANAGER_H_


#include <QtSerialPort/QtSerialPort>

class hgComManager
{
public:
	hgComManager(void);
	~hgComManager(void);

	bool OpenCom();
	void CloseCom();
	bool ClearCom();

	void SetBaudRate(int baudRate);
	void SetComName(QString strComName);

	int ReadData(QByteArray& qa, int timeout);
	int WriteData();

protected:
	static QSerialPort::BaudRate GetBaudRate(int baudRate);

protected:
	QSerialPort* m_pSerialPort;
	int m_nBaudRate;
	QString m_strComName;

};

#endif //HG_COMMANAGER_H_