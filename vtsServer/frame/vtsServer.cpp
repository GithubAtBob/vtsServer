
#include "stdafx.h"

#include "vtsServer.h"

#include <boost/bind.hpp>

#include "vtsLog.h"
#include "vtsDBPool.h"
#include "vtsServicePool.h"
#include "vtsTimerHandler.h"
#include "vtsPreprocessHandler.h"


vtsServer::vtsServer(const std::string& address, const std::string& port,
    vtsDBPool& dbpool, vtsServicePool& servicePool)
    : _mainService(),
    _signals(_mainService),
    _acceptor(_mainService),
    _newConnection(),
    _connectionManager(),
    _dbPool(dbpool),
    _servicePool(servicePool)
{

    // Register to handle the signals that indicate when the server should exit.
    // It is safe to register for the same signal multiple times in a program,
    // provided all registration for the specified signal is made through Asio.
    _signals.add(SIGINT);
    _signals.add(SIGTERM);
#if defined(SIGQUIT)
    _signals.add(SIGQUIT);
#endif // defined(SIGQUIT)
    _signals.async_wait(boost::bind(&vtsServer::handleStop, this));

    auto &l = vtsPreprocessHandler::handlerList();
    for (auto iter=l.begin(); iter!=l.end(); ++iter)
    {
        (*iter)->beforeServerListen(this, address, port);
    }

    boost::asio::ip::tcp::resolver resolver(_mainService);
    boost::asio::ip::tcp::resolver::query query(address, port);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();

    vtsInfo << "listen: " << address << "@" << port;

    startAccept();
}

vtsServer::~vtsServer(void)
{
    // handleStop();
}

void vtsServer::run()
{
    vtsInfo << "server run.";

    _servicePool.run();

    _mainService.dispatch([this](){
        auto &l = vtsPreprocessHandler::handlerList();
        for (auto iter=l.begin(); iter!=l.end(); ++iter)
        {
            (*iter)->afterServerRun(this);
        }
    });

    setupTimer();

    auto &l = vtsPreprocessHandler::handlerList();
    for (auto iter=l.begin(); iter!=l.end(); ++iter)
    {
        (*iter)->beforeServerRun(this);
    }

    // boost::asio::io_service::work work(_mainService);
    _mainService.run();
}

void vtsServer::startAccept()
{
    _newConnection.reset(new vtsConnection(*this, _connectionManager));
    _acceptor.async_accept(_newConnection->socket(),
        boost::bind(&vtsServer::handleAccept, this, boost::asio::placeholders::error));
}

void vtsServer::handleAccept(const boost::system::error_code &e)
{
    if (!_acceptor.is_open())
        return;

    if (!e)
    {
        auto &remote = _newConnection->socket().remote_endpoint();
        vtsInfo << "new connect:" << _newConnection->socket().native_handle() << 
            " from: " << remote.address().to_string() << "@" << remote.port();
        _connectionManager.start(_newConnection);
    }
    else
    {
        vtsError << e.message();
    }

    startAccept();
}

void vtsServer::handleStop()
{
    auto &l = vtsPreprocessHandler::handlerList();
    for (auto iter=l.begin(); iter!=l.end(); ++iter)
    {
        (*iter)->beforeServerStop(this);
    }

    destroyTimer();

    _acceptor.close();
    _connectionManager.stop_all();
    _servicePool.stop();

    _mainService.stop();

    for (auto iter=l.begin(); iter!=l.end(); ++iter)
    {
        (*iter)->afterServerStop(this);
    }

    vtsInfo << "server stop.";

    for (auto iter=l.begin(); iter!=l.end(); ++iter)
    {
        delete (*iter);
    }
    l.clear();
}

boost::asio::io_service& vtsServer::mainService()
{
    return _mainService;
}

boost::asio::io_service& vtsServer::threadService()
{
    return _servicePool.getService();
}

QSqlDatabase vtsServer::openDBConnection()
{
    return _dbPool.openConnection();
}

void vtsServer::closeDBConnection(QSqlDatabase connection)
{
    _dbPool.closeConnection(connection);
}

void vtsServer::setupTimer()
{
    auto &handlerMap = vtsTimerHandler::handlerMap();
    for (auto it=handlerMap.begin(); it!=handlerMap.end(); ++it)
    {
        it->second->init(this);
        it->second->run();
    }
}

void vtsServer::destroyTimer()
{
    auto &handlerMap = vtsTimerHandler::handlerMap();
    for (auto it=handlerMap.begin(); it!=handlerMap.end(); ++it)
    {
        it->second->cancel(true);
    }
    handlerMap.clear();
}

vtsSession & vtsServer::session()
{
    return _session;
}

vtsConnectionManager & vtsServer::connectionManager()
{
    return _connectionManager;
}

void vtsServer::setLimitKbs(int kbs)
{
    vtsInfo << "set limit kbs:" << kbs;
    _connectionManager.setLimitKbs(kbs);
}

void vtsServer::setLimitQps(int qps)
{
    vtsInfo << "set limit qps:" << qps;
    _connectionManager.setLimitQps(qps);
}
