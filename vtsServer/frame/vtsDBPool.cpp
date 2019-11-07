
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
    // 销毁连接池的时候删除所有的连接
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

    // 已创建连接数
    int connectionCount = _unusedConnectionNames.size() + _usedConnectionNames.size();

    // 如果连接已经用完，等待 waitInterval 毫秒看看是否有可用连接，最长等待 maxWaitTime 毫秒
    for (int i = 0;
        i < _maxWaitTime
        && _unusedConnectionNames.size() == 0 && connectionCount == _maxConnectionCount;
        i += _waitInterval)
    {
        _waitConnection.wait(&_mutex, _waitInterval);

        // 重新计算已创建连接数
        connectionCount = _unusedConnectionNames.size() + _usedConnectionNames.size();
    }

    if (_unusedConnectionNames.size() > 0)
    {
        // 有已经回收的连接，复用它们
        connectionName = _unusedConnectionNames.dequeue();
    }
    else if (connectionCount < _maxConnectionCount)
    {
        // 没有已经回收的连接，但是没有达到最大连接数，则创建新的连接
        connectionName = QString("Connection-%1").arg(connectionCount + 1);
    }
    else
    {
        // 已经达到最大连接数
        vtsWarning << "Cannot create more connections."; 
        return QSqlDatabase();
    }

    // 创建连接
    QSqlDatabase db = createConnection(connectionName);

    // 有效的连接才放入 usedConnectionNames
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
    // 如果是我们创建的连接，从 used 里删除，放入 unused 里
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
    // 连接已经创建过了，复用它，而不是重新创建
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

            // 返回连接前访问数据库，如果连接断开，重新建立连接
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

    // 创建一个新的连接
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
