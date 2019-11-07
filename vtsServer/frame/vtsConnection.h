#pragma once

#include <QSqlDatabase>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>

#include "vtsMessage.h"
#include "vtsSession.h"
#include "vtsDatabaseHandler.h"

#include "google/protobuf/message.h"

#define USE_HG_SQL_OPERATOR
#ifdef USE_HG_SQL_OPERATOR
#include "hgSqlOperator.h"
#endif

class vtsConnectionManager;
class vtsRequestHandler;
class vtsServer;

class vtsConnection :
    public boost::enable_shared_from_this<vtsConnection>,
    private boost::noncopyable
{
public:
    explicit vtsConnection(vtsServer& s, vtsConnectionManager& manager);
    ~vtsConnection(void);

    boost::asio::ip::tcp::socket& socket();

    vtsSession& session();

    void start();

    void stop();

    boost::asio::io_service& mainService();

    boost::asio::io_service& threadService();

    vtsServer& server();

    vtsConnectionManager& connectionManager();

    const std::string &channel();

    void setChannel(const std::string& name);

    void write(const std::string& type, google::protobuf::Message& msg);

    template <typename CompletionHandler>
    void write(const std::string& type, google::protobuf::Message& msg, BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        std::string s = msg.SerializeAsString();
        vtsMessagePacker packer(type.data(), s.data(), s.size());

        size_t len = packer.len();
        void *data = packer.dump();
        writeAsyncRawData(data, len, handler);
    }

    template <typename CompletionHandler>
    void postToDB(vtsDatabaseHandler* db, BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        auto &s = threadService();
        s.post([&s, this, db, handler]()
        {
            QSqlDatabase database = this->openDBConnection();
#ifdef USE_HG_SQL_OPERATOR
            hgSqlOperator l_sqlOperator(database);
            db->handle(s, l_sqlOperator);
#else
            db->handle(s, database);
#endif
            this->mainService().post(handler);
            // handler();
            this->closeDBConnection(database);
        });
    }

    void dispatchToDB(vtsDatabaseHandler* db);

    QSqlDatabase openDBConnection();

    void closeDBConnection(QSqlDatabase connection);

    void setLimitKbs(int kbs)
    {
        _limitKbs = kbs;
    }

    void setLimitQps(int qps)
    {
        _limitQps = qps;
    }

	clock_t lastTick()
	{
		return _lastTick;
	}

private:

    struct AsyncWriteData 
    {
        void *data;
        size_t len;
        boost::function<void(const boost::system::error_code& e)> f;
    };

    void handleRead(const boost::system::error_code& e, std::size_t bytesTransferred);

    void finishWriting(const boost::system::error_code& e, std::size_t bytesTransferred);

    void unpackMessage();

    void packMessage();

    void doRequestHandler(const std::string& type, boost::asio::const_buffer& data);

    void writeAsyncRawData(void *data, size_t len);

    template <typename CompletionHandler>
    void writeAsyncRawData(void *data, size_t len, BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        AsyncWriteData asyncData;
        asyncData.data = data;
        asyncData.len = len;
        asyncData.f = handler;

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

    void writeRawData(void *data, size_t len, boost::system::error_code& e);

    std::deque<AsyncWriteData> _asyncWriteQueue;

    boost::asio::ip::tcp::socket _socket;

    vtsConnectionManager& _manager;

    // boost::array<char, 8192> _buffer;
    std::vector<char> _buffer;

    std::map<std::string, vtsRequestHandler*> _cachedRequestMap;

    size_t _used;

    vtsSession _session;

    vtsServer& _server;

    bool _asyncWriting;

    double _kbs;

    int _qps;

    // 限制流量
    int _limitKbs;

    // 限制每秒请求数
    int _limitQps;

    clock_t _lastClock;

	time_t _lastTick;

    // 频道名称，用于组播
    std::string _channel;

    boost::mutex _asynWriteMutex;

    friend class vtsConnectionManager;

};

typedef boost::shared_ptr<vtsConnection> ConnectionPtr;