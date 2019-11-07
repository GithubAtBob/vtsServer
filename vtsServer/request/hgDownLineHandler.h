#pragma once

#include <list>
#include <boost/noncopyable.hpp>

#include "frame/vtsPreprocessHandler.h"

class hgDownLineHandler :
    public vtsPreprocessHandler
{
public:
    //virtual void whenConnectionConnected(ConnectionPtr c) { }

    virtual void whenConnectionDisconnected(ConnectionPtr c);
};

vtsSETUP_PREPROCESS_HANDLER( hgDownLineHandler );