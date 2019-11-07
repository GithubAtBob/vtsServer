#pragma once

#include <set>
#include <boost/noncopyable.hpp>
#include <QMutexLocker>

#include "vtsConnection.h"

class vtsConnectionManager :
    private boost::noncopyable
{
public:

    vtsConnectionManager();

    void start(ConnectionPtr c);

    void stop(ConnectionPtr c);

    void stop_all();

    template <typename CompletionHandler>
    inline void for_each(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        QMutexLocker locker(&_mutex);

        for (auto it=_connections.begin(); it!=_connections.end(); ++it)
        {
            handler(*it);
        }
    }

    template <typename CompletionHandler>
    inline ConnectionPtr find(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler)
    {
        QMutexLocker locker(&_mutex);

        for (auto it=_connections.begin(); it!=_connections.end(); ++it)
        {
            if (handler(*it))
                return *it;
        }
        return ConnectionPtr();
    }

    void broadcast(const std::string& type, google::protobuf::Message& msg);

    void multicast(const std::string& channel, const std::string& type, google::protobuf::Message& msg);

    void setLimitKbs(int kbs)
    {
        _limitKbs = kbs;
    }

    void setLimitQps(int qps)
    {
        _limitQps = qps;
    }

protected:

    void broadcastRawData(void *data, size_t len);

    void multicastRawData(const std::string& channel, void *data, size_t len);

    // 限制流量
    int _limitKbs;

    // 限制每秒请求数
    int _limitQps;

    QMutex _mutex;

private:

    std::set<ConnectionPtr> _connections;

};

