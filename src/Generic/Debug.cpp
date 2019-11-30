#include "Debug.h"
#include "Configs.hpp"
#include <cassert>
#include <iostream>
#include <boost/stacktrace.hpp>


void Debug::ASSERT(const bool expression)
{
    if constexpr (Config::DEBUG)
    {
        if (!expression)
        {
            std::cerr << boost::stacktrace::stacktrace() << std::endl;
            std::abort();
        }
    }
}