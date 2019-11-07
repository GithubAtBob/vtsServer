#pragma once

#include "frame/vtsTimerHandler.h"
#include <boost/asio.hpp>  
#include <boost/bind.hpp>  
#include <boost/lexical_cast.hpp>  
#include <iostream>
using boost::asio::io_service;     
using boost::asio::ip::tcp; 


class hgRadarAisTimerHandler : public vtsTimerHandler
{
public:
    hgRadarAisTimerHandler(const std::string& name);
    ~hgRadarAisTimerHandler(void);

    WorkMode workMode();

    void handle(const boost::system::error_code& e);

    void Connection();
protected:
    bool m_bConnect;
    int m_iCount;
    io_service * io_service_;     
    tcp::socket * socket_; 
    QString m_str;
    int a;

};
