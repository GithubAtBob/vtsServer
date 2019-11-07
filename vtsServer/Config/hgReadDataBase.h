#pragma once

#include <list>
#include <boost/noncopyable.hpp>

#include "frame/vtsPreprocessHandler.h"

class hgReadDataBase :
    public vtsPreprocessHandler
{
public:
    hgReadDataBase();
    ~hgReadDataBase();

    virtual void beforeServerRun(vtsServer *s) ;

};
