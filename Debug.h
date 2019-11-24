#pragma once

#include <iostream>
#include <string_view>
#include <cassert>
#include <unordered_map>


class LogType
{
public:
    enum Type
    {
        Info
        , Warning
        , Error
    };

    static inline std::unordered_map <Type, std::string> s_mapLogTypeName
    {
          std::make_pair(Info,    "Info")
        , std::make_pair(Warning, "Warning")
        , std::make_pair(Error,   "Error")
    };
};

class Debug
{
public:
    static constexpr bool DEBUG_MODE = true;

    static void Log(std::string_view log, LogType::Type logType = LogType::Info)
    {
        if constexpr (DEBUG_MODE)
        {
            std::cout << ">>>>> " << LogType::s_mapLogTypeName.at(logType) << " : " << log << std::endl;
        }
    }


    static void ASSERT(const bool expr)
    {
        if constexpr (DEBUG_MODE)
        {
            assert(expr);
        }
    }
};