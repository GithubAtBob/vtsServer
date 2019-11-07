
#include "stdafx.h"

#include "vtsLog.h"

namespace vtsLog
{

    void vtsLog::init(SeverityLevel level)
    {
        logging::formatter formatter=
            expr::stream
            <<"["<<expr::format_date_time(log_timestamp,"%H:%M:%S")
            <<"]"<<expr::if_(expr::has_attr(log_uptime))
            [
                expr::stream<<" ["<<format_date_time(log_uptime,"%O:%M:%S")<<"]"
            ]

        <<expr::if_(expr::has_attr(log_scope))
            [
                expr::stream<<" ["<<expr::format_named_scope(log_scope,keywords::format = "%n (%f:%l)")<<"]"
            ]
        <<" <"<<log_severity<<"> "<<expr::message;

        logging::add_common_attributes();

        auto console_sink=logging::add_console_log(std::clog,
            keywords::format = "%TimeStamp%: %Message%");
        auto file_sink=logging::add_file_log
            (
            keywords::file_name="logs/%Y-%m-%d_%N.log",      //�ļ���
            keywords::rotation_size=10*1024*1024,       //�����ļ����ƴ�С
            keywords::time_based_rotation=sinks::file::rotation_at_time_point(0,0,0)    //ÿ���ؽ�
            );

        file_sink->locked_backend()->set_file_collector(sinks::file::make_collector(
            keywords::target="logs",        //�ļ�����
            keywords::max_size=50*1024*1024,    //�ļ�����ռ���ռ�
            keywords::min_free_space=100*1024*1024  //������СԤ���ռ�
            ));

        file_sink->set_filter(log_severity>=level);   //��־�������

        file_sink->locked_backend()->scan_for_files();

        console_sink->set_formatter(formatter);
        file_sink->set_formatter(formatter);
        file_sink->locked_backend()->auto_flush(true);

        logging::core::get()->add_global_attribute("Scope",attrs::named_scope());
        // logging::core::get()->add_sink(console_sink);
        //logging::core::get()->add_sink(file_sink);
    }

    void deinit()
    {
        logging::core::get()->remove_all_sinks();
    }

}
