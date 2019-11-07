#pragma once

#include <boost/noncopyable.hpp>
#include <boost/asio/io_service.hpp>

class vtsServicePool :
    private boost::noncopyable
{
public:
    explicit vtsServicePool(size_t poolSize);

    ~vtsServicePool(void);

    void run();

    void stop();

    boost::asio::io_service& getService();

private:
    typedef boost::shared_ptr<boost::asio::io_service> io_service_ptr;
    typedef boost::shared_ptr<boost::asio::io_service::work> work_ptr;

    /// The pool of io_services.
    std::vector<io_service_ptr> _services;

    /// The work that keeps the io_services running.
    std::vector<work_ptr> _works;

    /// The next io_service to use for a connection.
    std::size_t _nextService;
};

