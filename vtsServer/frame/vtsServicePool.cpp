#include "StdAfx.h"
#include "vtsServicePool.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>


vtsServicePool::vtsServicePool(size_t poolSize)
    :_nextService(0)
{
    if (poolSize == 0)
        throw std::runtime_error("io_service_pool size is 0");

    // Give all the io_services work to do so that their run() functions will not
    // exit until they are explicitly stopped.
    for (std::size_t i = 0; i < poolSize; ++i)
    {
        io_service_ptr io_service(new boost::asio::io_service);
        work_ptr work(new boost::asio::io_service::work(*io_service));
        _services.push_back(io_service);
        _works.push_back(work);
    }

}

vtsServicePool::~vtsServicePool(void)
{

}

void vtsServicePool::run()
{
    // Create a pool of threads to run all of the io_services.
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for (std::size_t i = 0; i < _services.size(); ++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
            boost::bind(&boost::asio::io_service::run, _services[i])));
        threads.push_back(thread);
    }

    // Wait for all threads in the pool to exit.
    // for (std::size_t i = 0; i < threads.size(); ++i)
    //    threads[i]->join();
}

void vtsServicePool::stop()
{
    for (std::size_t i = 0; i < _services.size(); ++i)
        _services[i]->stop();
}

boost::asio::io_service& vtsServicePool::getService()
{
    // Use a round-robin scheme to choose the next io_service to use.
    boost::asio::io_service& io_service = *_services[_nextService];
    ++_nextService;
    if (_nextService == _services.size())
        _nextService = 0;
    return io_service;
}
