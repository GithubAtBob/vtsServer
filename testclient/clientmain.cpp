
#include <stdio.h>
#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <windows.h>

#include "frame/vtsMessage.h"
#include "login.pb.h"
#include "register.pb.h"
#include "aidsail.pb.h"


int main()
{
    std::string host = "127.0.0.1";

    std::cout << host << std::endl;
    // 所有asio类都需要io_service对象
    boost::asio::io_service iosev;
    // socket对象
    boost::asio::ip::tcp::socket socket(iosev);
    // 连接端点，这里使用了本机连接，可以修改IP地址测试远程连接
    boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address_v4::from_string(host), 8002);
    // 连接服务器
    boost::system::error_code ec;
    socket.connect(ep,ec);
    // 如果出错，打印出错信息
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return -1;
    }

    //LoginRequest msg;
    //msg.set_username("hwllo r");
    //msg.set_password("123456");

//     RegisterRequest msg_Reguister;
//     std::string account;
//     std::cin >> account;
//     msg_Reguister.set_account(account);
//     msg_Reguister.set_name("name");
//     msg_Reguister.set_password("123456");
//     msg_Reguister.set_phone("138");
//     msg_Reguister.set_groupid(5);
//     msg_Reguister.set_avatar("ok");

    AidSailRequest msg;
//     int account;
//     std::cin >> account;
    msg.set_id("a");

    std::string type = "aidsail";
    std::string s = msg.SerializeAsString();
    int write_len = MESSAGE_HEAD_LEN + MESSAGE_TYPE_LEN + s.size();
    char *write_data = new char[write_len];
    memset(write_data, 0, write_len);

    vtsMessageHead head;
    head.head1 = MESSAGE_HEAD1;
    head.head2 = MESSAGE_HEAD2;
    head.majorVer = MESSAGE_MAJOR;
    head.minorVer = MESSAGE_MINOR;
    head.contentSize = MESSAGE_TYPE_LEN + s.size();
    head.dump = 0;
    memcpy(write_data, &head, MESSAGE_HEAD_LEN);
    memcpy(write_data+MESSAGE_HEAD_LEN, type.data(), std::min((int)type.size(), MESSAGE_TYPE_LEN));
    memcpy(write_data+MESSAGE_HEAD_LEN+MESSAGE_TYPE_LEN, s.data(), s.size());
    socket.write_some(boost::asio::buffer(write_data, write_len), ec);

    std::cout << ec.message() << std::endl;

    std::clock_t t0 = clock();
    char buf[256];
    int count = 0;
    int sent_count = 0;
    int recv_count = 0;
    for (int i=100;i>0;i--)
    {
        // socket.write_some(boost::asio::buffer(write_data, write_len), ec);
    }
    while (1)
    {
        socket.write_some(boost::asio::buffer(write_data, write_len), ec);
        if (ec)
        {
            std::cout << ec.message() << std::endl;
            break;
        }
        else
        {
            sent_count++;
        }
        size_t len=socket.read_some(boost::asio::buffer(buf), ec);
        if (ec)
        {
            std::cout << ec.message() << std::endl;
            break;
        }
        else
        {
            recv_count++;
        }

        count++;
        std::clock_t t1 = clock();
        if (t1 - t0 >= 1000)
        {
            std::cout << ">>>qps: " << count
                << "  sent count: " << sent_count 
                << "  recv count: " << recv_count 
                << std::endl;
            t0 = t1;
            count = 0;
            // getchar();
        }
        // Sleep(1);
    }
    /*
    // 接收数据
    char buf[256];
    size_t len=socket.read_some(boost::asio::buffer(buf), ec);
    socket.io_control(boost::asio::ip::tcp::socket::non_blocking_io(false));
    std::cout.write(buf, len);
    int count = 0;
    boost::posix_time::ptime t1 = boost::posix_time::second_clock::local_time();
    */

    /*
    boost::posix_time::ptime::time_duration_type d(0, 0, 3, 0);
    while (1)
    {
        strncpy(buf, "ok", 3);
        socket.write_some(boost::asio::buffer(buf), ec);
        size_t len=socket.read_some(boost::asio::buffer(buf), ec);
        count ++;
        if (len != 128)
        {
            std::cout << count << "and   " << len << std::endl;;
        }

        boost::thread::sleep(boost::get_system_time() + boost::posix_time::microseconds(delay_msec));
        boost::posix_time::ptime t2 = boost::posix_time::second_clock::local_time();
        if (t2 - t1 >= d)
        {
            std::cout << count << std::endl;
            t1 = boost::posix_time::second_clock::local_time();
        }
    }
    */
    return 0;
}