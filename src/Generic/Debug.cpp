#include "Debug.h"
#include "Configs.hpp"
#include <cassert>
#include <iostream>
#include <boost/stacktrace.hpp>

namespace gen
{

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

void Debug::ASSERT(const bool expression, std::string_view svMessage)
{
    if constexpr (Config::DEBUG)
    {
        if (!expression)
        {
            std::cerr << boost::stacktrace::stacktrace() << std::endl;
            std::cerr << svMessage << std::endl;
            std::abort();
        }
    }
}

} // namespace gen