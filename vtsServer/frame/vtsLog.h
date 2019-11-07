#pragma once

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>

#include <boost/log/attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_file_backend.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/utility/formatting_ostream.hpp>

#include <QString>

template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm, const QString& s)
{
    strm << s.toLatin1().data();
    return strm;
}

template< typename CharT, typename TraitsT, typename AllocatorT>
inline boost::log::basic_formatting_ostream< CharT, TraitsT, AllocatorT >&
    operator<< (boost::log::basic_formatting_ostream< CharT, TraitsT, AllocatorT >& strm, const QString & value)
{
    strm.stream() << value.toLatin1().data();
    return strm;
}

namespace vtsLog
{
    namespace logging = boost::log;
    namespace attrs = boost::log::attributes;
    namespace src = boost::log::sources;
    namespace sinks = boost::log::sinks;
    namespace expr = boost::log::expressions;
    namespace keywords = boost::log::keywords;

    enum SeverityLevel
    {
        Log_Debug,
        Log_Info,
        Log_Warning,
        Log_Error,
        Log_Fatal
    };

    // The formatting logic for the severity level
    template< typename CharT, typename TraitsT >
    inline std::basic_ostream< CharT, TraitsT >& operator<< (
        std::basic_ostream< CharT, TraitsT >& strm, SeverityLevel lvl)
    {
        static const char* const str[] =
        {
            "Debug",
            "Info",
            "Warning",
            "Error",
            "Fatal"
        };
        if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
            strm << str[lvl];
        else
            strm << static_cast< int >(lvl);
        return strm;
    }

    BOOST_LOG_ATTRIBUTE_KEYWORD(log_severity, "Severity", SeverityLevel)
    BOOST_LOG_ATTRIBUTE_KEYWORD(log_timestamp, "TimeStamp", boost::posix_time::ptime)
    BOOST_LOG_ATTRIBUTE_KEYWORD(log_uptime, "Uptime", attrs::timer::value_type)
    BOOST_LOG_ATTRIBUTE_KEYWORD(log_scope, "Scope", attrs::named_scope::value_type)

    //  Global logger declaration
    BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(vts_logger, src::severity_logger<SeverityLevel>)

    void init(SeverityLevel level);

    void deinit();
}

#define vtsDebug \
    BOOST_LOG_NAMED_SCOPE(__FUNCTION__)\
    BOOST_LOG_SEV(vtsLog::vts_logger::get(), vtsLog::Log_Debug)
#define vtsInfo \
    BOOST_LOG_NAMED_SCOPE(__FUNCTION__)\
    BOOST_LOG_SEV(vtsLog::vts_logger::get(), vtsLog::Log_Info)
#define vtsWarning \
    BOOST_LOG_NAMED_SCOPE(__FUNCTION__)\
    BOOST_LOG_SEV(vtsLog::vts_logger::get(), vtsLog::Log_Warning)
#define vtsError \
    BOOST_LOG_NAMED_SCOPE(__FUNCTION__)\
    BOOST_LOG_SEV(vtsLog::vts_logger::get(), vtsLog::Log_Error)
#define vtsFatal \
    BOOST_LOG_NAMED_SCOPE(__FUNCTION__)\
    BOOST_LOG_SEV(vtsLog::vts_logger::get(), vtsLog::Log_Fatal)