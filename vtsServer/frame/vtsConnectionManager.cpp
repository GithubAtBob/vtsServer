
#include "stdafx.h"

#include "vtsConnectionManager.h"

#include <algorithm>
#include <boost/bind.hpp>

#include "vtsLog.h"


void vtsConnectionManager::start(ConnectionPtr c)
{
    QMutexLocker locker(&_mutex);

    _connections.insert(c);
    c->setLimitKbs(_limitKbs);
    c->setLimitQps(_limitQps);
    c->start();
}

void vtsConnectionManager::stop(ConnectionPtr c)
{
	vtsDebug << "vtsConnectionManager::stop " << c->channel().c_str();
    QMutexLocker locker(&_mutex);

    _connections.erase(c);
    c->stop();
}

void vtsConnectionManager::stop_all()
{
    QMutexLocker locker(&_mutex);

    std::for_each(_connections.begin(), _connections.end(), boost::bind(&vtsConnection::stop, _1));
    _connections.clear();
}

void vtsConnectionManager::multicast(const std::string& channel, const std::string& type, google::protobuf::Message& msg)
{
    QMutexLocker locker(&_mutex);

    std::string s = msg.SerializeAsString();
    vtsMessagePacker packer(type.data(), s.data(), s.size());

    multicastRawData(channel, packer.data(), packer.len());
}

void vtsConnectionManager::multicastRawData(const std::string& channel, void *data, size_t len)
{
    for (auto iter=_connections.begin(); iter!=_connections.end(); ++iter)
    {
        if ((*iter)->channel() == channel)
        {
            void *d = new char[len];
            memcpy(d, data, len);
            (*iter)->writeAsyncRawData(d, len, 
                [channel](const boost::system::error_code& e)
                {
                    if (e)
                    {
                        vtsWarning << "multicast error, channel: " << channel << " " << e.message();
                    }
                });
            /*
            boost::system::error_code e;
            (*iter)->writeRawData(data, len, e);
            if (e)
            {
                vtsWarning << "multicast error, channel: " << channel << " " << e.message();
            }
            */
        }
    }
}

void vtsConnectionManager::broadcast(const std::string& type, google::protobuf::Message& msg)
{
    QMutexLocker locker(&_mutex);

    std::string s = msg.SerializeAsString();
    vtsMessagePacker packer(type.data(), s.data(), s.size());

    broadcastRawData(packer.data(), packer.len());
}

void vtsConnectionManager::broadcastRawData(void *data, size_t len)
{
    for (auto iter=_connections.begin(); iter!=_connections.end(); ++iter)
    {

        void *d = new char[len];
        memcpy(d, data, len);
        (*iter)->writeAsyncRawData(d, len, 
            [](const boost::system::error_code& e)
            {
                if (e)
                {
                    vtsWarning << "broadcast error, " << e.message();
                }
            });
    /*
        boost::system::error_code e;
        (*iter)->writeRawData(data, len, e);
        if (e)
        {
            vtsWarning << "broadcast error, " << e.message();
        }
        */
    }

}

vtsConnectionManager::vtsConnectionManager()
    :_mutex(QMutex::Recursive)
{
    _limitKbs = 0;
    _limitQps = 0;
}
