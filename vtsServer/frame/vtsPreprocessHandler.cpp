#include "StdAfx.h"
#include "vtsPreprocessHandler.h"

std::list<vtsPreprocessHandler*> & vtsPreprocessHandler::handlerList()
{
    static std::list<vtsPreprocessHandler*> s_inst;
    return s_inst;
}
