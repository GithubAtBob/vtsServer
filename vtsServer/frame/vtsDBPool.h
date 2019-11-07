#pragma once

#include <boost/noncopyable.hpp>
#include <QString>
#include <QQueue>
#include <QSqlDatabase>
#include <QMutex>
#include <QWaitCondition>


/*
 * openConnection() ���ڴ����ӳ����ȡ���ӡ� 
 * closeConnection(QSqlDatabase connection) �����������Ĺر����ӣ�
 * ���ǰ����ӷŻ����ӳظ��á����ӵĵײ���ͨ�� Socket ��ͨѶ�ģ����� Socket 
 * �����Ƿǳ���ʱ�ģ����ÿ�����Ӷ���ʹ�����͸��Ͽ� Socket ���ӣ�
 * ��Ҫ��ʱ�������½��� Socket�����Ƿǳ��˷ѵģ�����Ҫ�����ĸ��������Ч�ʡ�
 * release() �����Ĺر����е����ӣ�һ���ڳ��������ʱ��ŵ��ã��� main() ������ return ���ǰ��
 * usedConnectionNames �������ڱ�ʹ�õ����ӵ����֣����ڱ�֤ͬһ�����Ӳ���ͬʱ������߳�ʹ�á� 
 * unusedConnectionNames ����û�б�ʹ�õ����ӵ����֣����Ƕ�Ӧ�������ڵ��� openConnection() ʱ���ء�
 * ��� testOnBorrow Ϊ true�������ӶϿ�����Զ��������ӣ��������ݿ��������ˣ������ԭ��ȵ������ӶϿ��ˣ���
 * ����ÿ�λ�ȡ���ӵ�ʱ�򶼻��Ȳ�ѯһ�����ݿ⣬�������������Ч�����½������ӡ�
 * testOnBorrow Ϊ true ʱ����Ҫ�ṩһ�� SQL ������ڲ��Բ�ѯ��
 * ���� MySQL �¿����� SELECT 1����� testOnBorrow Ϊ false��
 * �����ӶϿ��󲻻��Զ��������ӡ�
 * ��Ҫע����ǣ�Qt ���Ѿ������õ����ݿ����ӵ����ӶϿ������ QSqlDatabase::isOpen() ���ص�ֵ��Ȼ�� true��
 * ��Ϊ��ǰ��ʱ���Ѿ������������ӣ�Qt ��û���ṩ�жϵײ����ӶϿ��ķ��������źţ�
 * ���� QSqlDatabase::isOpen() ���ص���Ȼ����ǰ��״̬ true��
 * testOnBorrowSql Ϊ���Է������ݿ�� SQL��һ����һ���ǳ��������� SQL���� SELECT 1��
 * ��ȡ���ӵ�ʱ�����û�п������ӣ����ǵĲ��Բ�����ֱ�ӷ���һ����Ч�����ӣ����ǵȴ� waitInterval ���룬
 * ����ڼ������ӱ��ͷŻ����ӳ���ͷ���������ӣ�û�оͼ����ȴ� waitInterval ���룬
 * �ٿ�����û�п������ӣ�ֱ���ȴ� maxWaitTime ������Ȼû�п������Ӳŷ���һ����Ч�����ӡ�
 * ��Ϊ���ǲ����ڳ����������ƵĴ������ӣ��� maxConnectionCount �����ƴ������ӵ����������
 */

class vtsDBPool :
    private boost::noncopyable
{
public:

    struct DBPoolConfig
    {
        QString hostName;
        QString databaseName;
        QString username;
        QString password;
        QString databaseType;

        bool    testOnBorrow;    // ȡ�����ӵ�ʱ����֤�����Ƿ���Ч
        QString testOnBorrowSql; // ���Է������ݿ�� SQL
        int     testTime;        // ���Եļ��ʱ�䣬��λ��

        int maxWaitTime;  // ��ȡ�������ȴ�ʱ��
        int waitInterval; // ���Ի�ȡ����ʱ�ȴ����ʱ��
        int maxConnectionCount; // ���������
    };

    vtsDBPool(DBPoolConfig& config);

    ~vtsDBPool(void);

    QSqlDatabase openConnection();

    void closeConnection(QSqlDatabase connection);

private:

    QSqlDatabase createConnection(const QString& connectionName);

    QQueue<QString> _usedConnectionNames;   // ��ʹ�õ����ݿ�������

    QQueue<QString> _unusedConnectionNames; // δʹ�õ����ݿ�������

    // ���ݿ���Ϣ
    QString _hostName;
    QString _databaseName;
    QString _username;
    QString _password;
    QString _databaseType;

    bool    _testOnBorrow;    // ȡ�����ӵ�ʱ����֤�����Ƿ���Ч
    QString _testOnBorrowSql; // ���Է������ݿ�� SQL
    int     _testTime;          // ���Եļ��ʱ�䣬��λ��;Ĭ��60��

    int _maxWaitTime;  // ��ȡ�������ȴ�ʱ��
    int _waitInterval; // ���Ի�ȡ����ʱ�ȴ����ʱ��
    int _maxConnectionCount; // ���������

    QMutex _mutex;
    QWaitCondition _waitConnection;

    QMap<QString, time_t> _testTimeMap;
};

