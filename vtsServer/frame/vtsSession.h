#pragma once

#include <string>
#include <boost/noncopyable.hpp>
#include <QVariant>
#include <QMap>


// sessionÊý¾Ý
class vtsSession :
    private boost::noncopyable
{
public:
    QVariant get(const std::string& key);
    QVariant get(const std::string& key, const QVariant& defaultValue);
    void set(const std::string& key, const QVariant& value);
    bool has(const std::string& key);
private:
    QMap<std::string, QVariant> _dataMap;
};

