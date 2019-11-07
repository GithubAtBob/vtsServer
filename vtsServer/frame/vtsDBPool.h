#pragma once

#include <boost/noncopyable.hpp>
#include <QString>
#include <QQueue>
#include <QSqlDatabase>
#include <QMutex>
#include <QWaitCondition>


/*
 * openConnection() 用于从连接池里获取连接。 
 * closeConnection(QSqlDatabase connection) 并不会真正的关闭连接，
 * 而是把连接放回连接池复用。连接的底层是通过 Socket 来通讯的，建立 Socket 
 * 连接是非常耗时的，如果每个连接都在使用完后就给断开 Socket 连接，
 * 需要的时候再重新建立 Socket连接是非常浪费的，所以要尽量的复用以提高效率。
 * release() 真正的关闭所有的连接，一般在程序结束的时候才调用，在 main() 函数的 return 语句前。
 * usedConnectionNames 保存正在被使用的连接的名字，用于保证同一个连接不会同时被多个线程使用。 
 * unusedConnectionNames 保存没有被使用的连接的名字，它们对应的连接在调用 openConnection() 时返回。
 * 如果 testOnBorrow 为 true，则连接断开后会自动重新连接（例如数据库程序崩溃了，网络的原因等导致连接断开了）。
 * 但是每次获取连接的时候都会先查询一下数据库，如果发现连接无效则重新建立连接。
 * testOnBorrow 为 true 时，需要提供一条 SQL 语句用于测试查询，
 * 例如 MySQL 下可以用 SELECT 1。如果 testOnBorrow 为 false，
 * 则连接断开后不会自动重新连接。
 * 需要注意的是，Qt 里已经建立好的数据库连接当连接断开后调用 QSqlDatabase::isOpen() 返回的值仍然是 true，
 * 因为先前的时候已经建立好了连接，Qt 里没有提供判断底层连接断开的方法或者信号，
 * 所以 QSqlDatabase::isOpen() 返回的仍然是先前的状态 true。
 * testOnBorrowSql 为测试访问数据库的 SQL，一般是一个非常轻量级的 SQL，如 SELECT 1。
 * 获取连接的时候，如果没有可用连接，我们的策略并不是直接返回一个无效的连接，而是等待 waitInterval 毫秒，
 * 如果期间有连接被释放回连接池里就返回这个连接，没有就继续等待 waitInterval 毫秒，
 * 再看看有没有可用连接，直到等待 maxWaitTime 毫秒仍然没有可用连接才返回一个无效的连接。
 * 因为我们不能在程序里无限制的创建连接，用 maxConnectionCount 来控制创建连接的最大数量。
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

        bool    testOnBorrow;    // 取得连接的时候验证连接是否有效
        QString testOnBorrowSql; // 测试访问数据库的 SQL
        int     testTime;        // 测试的间隔时间，单位秒

        int maxWaitTime;  // 获取连接最大等待时间
        int waitInterval; // 尝试获取连接时等待间隔时间
        int maxConnectionCount; // 最大连接数
    };

    vtsDBPool(DBPoolConfig& config);

    ~vtsDBPool(void);

    QSqlDatabase openConnection();

    void closeConnection(QSqlDatabase connection);

private:

    QSqlDatabase createConnection(const QString& connectionName);

    QQueue<QString> _usedConnectionNames;   // 已使用的数据库连接名

    QQueue<QString> _unusedConnectionNames; // 未使用的数据库连接名

    // 数据库信息
    QString _hostName;
    QString _databaseName;
    QString _username;
    QString _password;
    QString _databaseType;

    bool    _testOnBorrow;    // 取得连接的时候验证连接是否有效
    QString _testOnBorrowSql; // 测试访问数据库的 SQL
    int     _testTime;          // 测试的间隔时间，单位秒;默认60秒

    int _maxWaitTime;  // 获取连接最大等待时间
    int _waitInterval; // 尝试获取连接时等待间隔时间
    int _maxConnectionCount; // 最大连接数

    QMutex _mutex;
    QWaitCondition _waitConnection;

    QMap<QString, time_t> _testTimeMap;
};

