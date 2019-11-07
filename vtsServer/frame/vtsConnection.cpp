
#include "stdafx.h"

#include "vtsConnection.h"

#include <iostream>
#include <boost/bind.hpp>

#include "vtsLog.h"
#include "vtsMessage.h"
#include "vtsServer.h"
#include "vtsConnectionManager.h"
#include "vtsRequestHandler.h"
#include "vtsPreprocessHandler.h"

vtsConnection::vtsConnection(vtsServer& s, vtsConnectionManager& manager)
    :
    _buffer(8192),
    _server(s),
    _socket(s.mainService()),
    _manager(manager)
{
    _used = 0;
    _asyncWriting = false;
    _qps = 0;
    _kbs = 0.0;
    _lastClock = clock();
	_lastTick = time(NULL);
}

vtsConnection::~vtsConnection(void)
{
    for (auto it=_cachedRequestMap.begin(); it!=_cachedRequestMap.end(); ++it)
    {
        delete it->second;
    }
	_cachedRequestMap.clear();

	for (auto it=_asyncWriteQueue.begin(); it!=_asyncWriteQueue.end(); ++it)
	{
		delete it->data;
	}
	_asyncWriteQueue.clear();
}

boost::asio::ip::tcp::socket& vtsConnection::socket()
{
    return _socket;
}

void vtsConnection::start()
{
    auto &l = vtsPreprocessHandler::handlerList();
    for (auto iter=l.begin(); iter!=l.end(); ++iter)
    {
        (*iter)->whenConnectionConnected(shared_from_this());
    }
    _socket.async_read_some(boost::asio::buffer(_buffer), 
        boost::bind(&vtsConnection::handleRead, shared_from_this(), 
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
	_lastTick = time(NULL);
}

void vtsConnection::stop()
{
    auto &l = vtsPreprocessHandler::handlerList();
    for (auto iter=l.begin(); iter!=l.end(); ++iter)
    {
        (*iter)->whenConnectionDisconnected(shared_from_this());
    }
    _socket.close();
}

void vtsConnection::handleRead(const boost::system::error_code& e, std::size_t bytesTransferred)
{
    if (!e)
    {
		if (bytesTransferred == 0)
		{
			vtsWarning << "recv bytes == 0, disconnect!";
			_manager.stop(shared_from_this());
			return;
		}
        _used += bytesTransferred;

		_lastTick = time(NULL);

        unpackMessage();

        _kbs += bytesTransferred;
        clock_t now = clock();
        if (now - _lastClock >= 1000)
        {
            if (_limitKbs > 0 && _kbs/1024.0 >= _limitKbs)
            {
                vtsWarning << "disconnect! out of the limit of kbs: " << _limitKbs << " actual: " << _kbs/1024.0 \
                    << "\tfrom:" << socket().remote_endpoint().address();
                _manager.stop(shared_from_this());
            }

            if (_limitQps > 0 && _qps >= _limitQps)
            {
                vtsWarning << "disconnect! out of the limit of qps: " << _limitQps << " actual: " << _qps \
                    << "\tfrom:" << socket().remote_endpoint().address();
                _manager.stop(shared_from_this());
            }

            _lastClock = clock();
            _kbs = 0;
            _qps = 0;
        }

        if (_used >= _buffer.size())
            _buffer.resize(_used*2);

        _socket.async_read_some(boost::asio::buffer(_buffer.data()+_used, _buffer.size()-_used),
            boost::bind(&vtsConnection::handleRead, shared_from_this(), 
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));

    }
    else
    {
        vtsError << "read error: " << e.message();
        if (e != boost::asio::error::operation_aborted)
        {
            _manager.stop(shared_from_this());
        }
    }
}

void vtsConnection::unpackMessage()
{
    // 如断包的话,包含上次断包结果
    // 缓存都是从索引0开始处理
    int handledCount = 0;
    int remainedCount = _used;
    // 断包、粘包处理
    while (remainedCount >= MESSAGE_HEAD_LEN && handledCount < _used)
    {
        char *data = _buffer.data() + handledCount;
        vtsMessageHead *head = (vtsMessageHead*)data;
        // 兼容旧版本
        if(head->minorVer == 0)
        {
            vtsMessageHead_minv0 *head0 = (vtsMessageHead_minv0*)data;
            head->contentSize = head0->contentSize;
            head->minorVer = MESSAGE_MINOR;
        }
        if (head->head1 == MESSAGE_HEAD1
            && head->head2 == MESSAGE_HEAD2)
        {
            if (head->majorVer == MESSAGE_MAJOR 
                && head->minorVer == MESSAGE_MINOR)
            {
                // 是否断包
                if (head->contentSize <= remainedCount-MESSAGE_HEAD_LEN)
                {
                    // 根据type类型,pb解析并创建request_handler
                    char type[MESSAGE_TYPE_LEN+1];
                    int offset = MESSAGE_HEAD_LEN;
                    memcpy(type, data+offset, MESSAGE_TYPE_LEN);
                    type[MESSAGE_TYPE_LEN] = '\0';
                    offset += MESSAGE_TYPE_LEN;
										double start = GetTickCount();
                    doRequestHandler(type,
                        boost::asio::const_buffer(data+offset, head->contentSize-MESSAGE_TYPE_LEN));
										double end = GetTickCount();
										double diff = end - start;
										if (diff > 100.0)
										{
											vtsInfo << type << " TimeDiff: " << diff;
										}

                    _qps++;

                    handledCount += MESSAGE_HEAD_LEN;
                    handledCount += head->contentSize;
                    remainedCount = _used - handledCount;
                }
                else
                {
                    // 断包,等待上次结果
                    _used = handledCount;
                    break;
                }
            }
            else
            {
                vtsWarning << "version error, clear buffer. total: " << remainedCount;
                _used = 0;
                remainedCount = 0;
                break;
            }
        }
        // 开始的数据不是包头,清空
        else
        {
            vtsWarning << "data error, clear buffer. total: " << remainedCount;
            _used = 0;
            remainedCount = 0;
            break;
        }
    }

    // 缓冲中的数据全部处理完毕
    if (remainedCount == 0)
    {
        _used = 0;
    }
    else
    {
        // 对于断包,用memmove移动到最前面
        memmove(_buffer.data(), _buffer.data()+handledCount, remainedCount);
        _used = remainedCount;
    }
    // vtsInfo << "package count: " << package_count;
}

void vtsConnection::doRequestHandler(const std::string& type, boost::asio::const_buffer& data)
{
    // 从缓存中先获取
    {
        auto cachedFound = _cachedRequestMap.find(type);
        if (cachedFound != _cachedRequestMap.end())
        {
            cachedFound->second->reset();
            cachedFound->second->handle(data);
            return;
        }
    }

    auto &handlerMap = vtsRequestHandler::requestHandlerMap();
    auto found = handlerMap.find(type);
    if (found != handlerMap.end())
    {
        auto handler = found->second(type, shared_from_this());
        handler->reset();
        // 先获取workmode
        // 避免在manual方式handle函数里delete this造成崩溃
        // 但,这也失去了灵活(无法在handle函数中动态决定workmode)
        auto mode = handler->workMode();
        handler->handle(data);
        if (mode == vtsRequestHandler::Work_Delete_Auto)
            delete handler;
        else if (mode == vtsRequestHandler::Work_Cached)
            _cachedRequestMap[type] = handler;
    }
    else
    {
        vtsWarning << "no request handler for: " << type;
    }
}

vtsSession& vtsConnection::session()
{
    return _session;
}

boost::asio::io_service& vtsConnection::mainService()
{
    return _server.mainService();
}

boost::asio::io_service& vtsConnection::threadService()
{
    return _server.threadService();
}

void vtsConnection::finishWriting(const boost::system::error_code& e, std::size_t bytesTransferred)
{

    // 主线程的锁粒度粗,尽量让主线程多处理网络收发
    boost::mutex::scoped_lock lock(_asynWriteMutex);
    AsyncWriteData *d1 = nullptr;

    d1 = &_asyncWriteQueue.front();

    if (d1->f)
        d1->f(e);
    delete d1->data;

    _asyncWriteQueue.pop_front();

    bool stop = false;
    if (e)
    {
        vtsError << "write error: " << e.message();
        if (e != boost::asio::error::operation_aborted)
        {
            for (auto it=_asyncWriteQueue.begin(); it!=_asyncWriteQueue.end(); ++it)
            {
                if (it->f)
                    it->f(e);
                delete it->data;
            }
            _asyncWriteQueue.clear();
            _manager.stop(shared_from_this());
            stop = true;
        }
    }

    _asyncWriting = false;
    if (!stop && _asyncWriteQueue.size() > 0)
    {
        auto &d2 = _asyncWriteQueue.front();
        boost::asio::async_write(socket(), boost::asio::buffer(d2.data, d2.len),
            boost::asio::transfer_at_least(d2.len),
            boost::bind(&vtsConnection::finishWriting, shared_from_this(), 
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        _asyncWriting = true;
    }
}

vtsServer& vtsConnection::server()
{
    return _server;
}

vtsConnectionManager& vtsConnection::connectionManager()
{
    return _manager;
}

void vtsConnection::dispatchToDB(vtsDatabaseHandler* db)
{
    QSqlDatabase database = openDBConnection();
#ifdef USE_HG_SQL_OPERATOR
    hgSqlOperator l_sqlOperator(database);
    db->handle(mainService(), l_sqlOperator);
#else
    db->handle(mainService(), database);
#endif
    closeDBConnection(database);
}

QSqlDatabase vtsConnection::openDBConnection()
{
    return server().openDBConnection();
}

void vtsConnection::closeDBConnection(QSqlDatabase connection)
{
    server().closeDBConnection(connection);
}

void vtsConnection::write(const std::string& type, google::protobuf::Message& msg)
{

    std::string s = msg.SerializeAsString();
    vtsMessagePacker packer(type.data(), s.data(), s.size());

    size_t len = packer.len();
    void *data = packer.dump();

    writeAsyncRawData(data, len);

    // writeRawData(packer.data(), packer.len(), e);
}

void vtsConnection::writeRawData(void *data, size_t len, boost::system::error_code& e)
{
    socket().write_some(boost::asio::buffer(data, len), e);
}

const std::string & vtsConnection::channel()
{
    return _channel;
}

void vtsConnection::setChannel(const std::string& name)
{
    _channel = name;
}

void vtsConnection::writeAsyncRawData(void *data, size_t len)
{
    AsyncWriteData asyncData;
    asyncData.data = data;
    asyncData.len = len;

    boost::mutex::scoped_lock lock(_asynWriteMutex);
    _asyncWriteQueue.push_back(asyncData);

    if (!_asyncWriting)
    {
        boost::asio::async_write(socket(), boost::asio::buffer(data, len),
            boost::asio::transfer_at_least(len),
            boost::bind(&vtsConnection::finishWriting, shared_from_this(), 
            boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        _asyncWriting = true;
    }
}