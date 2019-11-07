#pragma once

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <string>

#include <QString>
#include <QVariant>
#include <QMap>

#include "vtsConnection.h"
#include "vtsConnectionManager.h"

class vtsDBPool;
class vtsServer;
class vtsServicePool;

/*
 * 目前采用的模式是: 主线程处理业务以及网络i/o；数据库处理由专门的子线程处理
 * 性能优化方向：使用线程池，每个线程处理不同的网络i/o
 */
class vtsServer :
    private boost::noncopyable
{
public:
    explicit vtsServer(const std::string& address, const std::string& port,
        vtsDBPool& dbpool, vtsServicePool& servicePool);
    ~vtsServer(void);

    void run();

    boost::asio::io_service& mainService();

    boost::asio::io_service& threadService();

    QSqlDatabase openDBConnection();

    void closeDBConnection(QSqlDatabase connection);

    vtsSession &session();

    vtsConnectionManager &connectionManager();

    void setLimitKbs(int kbs);

    void setLimitQps(int qps);

private:

    void setupTimer();

    void destroyTimer();

    void startAccept();

    void handleAccept(const boost::system::error_code &e);

    void handleStop();

    boost::asio::io_service _mainService;

    /// The signal_set is used to register for process termination notifications.
    boost::asio::signal_set _signals;

    boost::asio::ip::tcp::acceptor _acceptor;

    vtsConnectionManager _connectionManager;

    ConnectionPtr   _newConnection;

    vtsDBPool& _dbPool;

    vtsServicePool& _servicePool;

    vtsSession _session;

};

