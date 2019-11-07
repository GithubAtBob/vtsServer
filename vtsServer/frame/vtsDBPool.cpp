
#include "StdAfx.h"

#include "vtsDBPool.h"
#include "vtsLog.h"

#include <QSqlQuery>
#include <QSqlError>


vtsDBPool::vtsDBPool(vtsDBPool::DBPoolConfig& config)
{
    _hostName = config.hostName;
    _databaseName = config.databaseName;
    _username = config.username;
    _password = config.password;
    _databaseType = config.databaseType;

    _testOnBorrow = config.testOnBorrow;
    _testOnBorrowSql = config.testOnBorrowSql;

    _maxWaitTime = config.maxWaitTime;
    _waitInterval = config.waitInterval;
    _maxConnectionCount = config.maxConnectionCount;

    _testTime = config.testTime;

    vtsInfo << "DBPool config: " << _username << "@" << _hostName << ";" << _databaseName;
}

vtsDBPool::~vtsDBPool(void)
{
    // �������ӳص�ʱ��ɾ�����е�����
    foreach(QString connectionName, _usedConnectionNames) {
        QSqlDatabase::removeDatabase(connectionName);
    }

    foreach(QString connectionName, _unusedConnectionNames) {
        QSqlDatabase::removeDatabase(connectionName);
    }
}

QSqlDatabase vtsDBPool::openConnection()
{
    QString connectionName;

    QMutexLocker locker(&_mutex);

    // �Ѵ���������
    int connectionCount = _unusedConnectionNames.size() + _usedConnectionNames.size();

    // ��������Ѿ����꣬�ȴ� waitInterval ���뿴���Ƿ��п������ӣ���ȴ� maxWaitTime ����
    for (int i = 0;
        i < _maxWaitTime
        && _unusedConnectionNames.size() == 0 && connectionCount == _maxConnectionCount;
        i += _waitInterval)
    {
        _waitConnection.wait(&_mutex, _waitInterval);

        // ���¼����Ѵ���������
        connectionCount = _unusedConnectionNames.size() + _usedConnectionNames.size();
    }

    if (_unusedConnectionNames.size() > 0)
    {
        // ���Ѿ����յ����ӣ���������
        connectionName = _unusedConnectionNames.dequeue();
    }
    else if (connectionCount < _maxConnectionCount)
    {
        // û���Ѿ����յ����ӣ�����û�дﵽ������������򴴽��µ�����
        connectionName = QString("Connection-%1").arg(connectionCount + 1);
    }
    else
    {
        // �Ѿ��ﵽ���������
        vtsWarning << "Cannot create more connections."; 
        return QSqlDatabase();
    }

    // ��������
    QSqlDatabase db = createConnection(connectionName);

    // ��Ч�����Ӳŷ��� usedConnectionNames
    if (db.isOpen())
    {
        _usedConnectionNames.enqueue(connectionName);
    }

    // vtsInfo << "openConnection: " << connectionName;

    return db;
}

void vtsDBPool::closeConnection(QSqlDatabase connection)
{
    QString connectionName = connection.connectionName();

    QMutexLocker locker(&_mutex);
    // ��������Ǵ��������ӣ��� used ��ɾ�������� unused ��
    if (_usedConnectionNames.contains(connectionName))
    {
        _usedConnectionNames.removeOne(connectionName);
        _unusedConnectionNames.enqueue(connectionName);
        _waitConnection.wakeOne();
    }

    // vtsInfo << "closeConnection: " << connectionName;
}

QSqlDatabase vtsDBPool::createConnection(const QString& connectionName)
{
    // �����Ѿ��������ˣ������������������´���
    if (QSqlDatabase::contains(connectionName))
    {
        QSqlDatabase db1 = QSqlDatabase::database(connectionName);

        if (_testOnBorrow)
        {
            time_t now = time(NULL);
            auto it = _testTimeMap.find(connectionName);
            bool do_it = false;
            if (it == _testTimeMap.end())
            {
                do_it = true;
            }
            else
            {
                do_it = now - it.value() >= _testTime;
            }

            // ��������ǰ�������ݿ⣬������ӶϿ������½�������
            // vtsDebug << "Test connection on borrow, execute:" << _testOnBorrowSql << ", for" << connectionName;
            if (do_it)
            {
                _testTimeMap[connectionName] = now;
                QSqlQuery query(_testOnBorrowSql, db1);

                if (query.lastError().type() != QSqlError::NoError && !db1.open())
                {
                    vtsError << "Open datatabase error:" << db1.lastError().text();
                    return QSqlDatabase();
                }
            }
        }

        return db1;
    }

    // ����һ���µ�����
    QSqlDatabase db = QSqlDatabase::addDatabase(_databaseType, connectionName);
    db.setHostName(_hostName);
    db.setDatabaseName(_databaseName);
    db.setUserName(_username);
    db.setPassword(_password);

    if (!db.open())
    {
        vtsError << "Open datatabase error:" << db.lastError().text();
        return QSqlDatabase();
    }

    // vtsInfo << "Create connection: " << connectionName;

    return db;
}
