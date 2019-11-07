#include "StdAfx.h"
#include "vtsSession.h"

QVariant vtsSession::get(const std::string& key)
{
    if (has(key))
        return _dataMap[key];
    else
        return QVariant();
}

QVariant vtsSession::get(const std::string& key, const QVariant& defaultValue)
{
    if (has(key))
        return _dataMap[key];
    else
        return defaultValue;
}

void vtsSession::set(const std::string& key, const QVariant& value)
{
    _dataMap[key] = value;
}

bool vtsSession::has(const std::string& key)
{
    return _dataMap.contains(key);
}
