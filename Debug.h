#pragma once

#include <iostream>
#include <string_view>
#include <cassert>
#include <unordered_map>
#include <iomanip>


using namespace std::string_literals;

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
    static constexpr int s_iIndentLevel = 25;
public:
    static constexpr bool DEBUG_MODE = true;


    static void Log(std::string_view module, std::string_view log, LogType::Type logType = LogType::Info)
    {
        if constexpr (DEBUG_MODE)
        {
            const auto& strLogType = LogType::s_mapLogTypeName.at(logType);
            const auto iIndentLevel = s_iIndentLevel - module.length() - strLogType.length();
            std::cout << strLogType << " >>>>> "
                << module << std::setw(20 - iIndentLevel)
                << " : " << log << std::endl;
        }
    }

    static void Log(std::string_view module, const int line, std::string_view log, LogType::Type logType = LogType::Info)
    {
        if constexpr (DEBUG_MODE)
        {
            std::string lineNumber = " Line : " + std::to_string(line);
            const auto& strLogType = LogType::s_mapLogTypeName.at(logType);
            const auto iIndentLevel = s_iIndentLevel - lineNumber.length() - module.length() - strLogType.length();

            std::cout << strLogType << lineNumber
                << " >>>>> " << module << std::setw(iIndentLevel)
                << " : " << log << std::endl;
        }
    }


    static void Log(std::string_view module, std::string_view log, std::string_view log2, LogType::Type logType = LogType::Info)
    {
        if constexpr (DEBUG_MODE)
        {
            const auto& strLogType = LogType::s_mapLogTypeName.at(logType);
            const auto iIndentLevel = s_iIndentLevel - module.length() - strLogType.length();
            std::cout << LogType::s_mapLogTypeName.at(logType)
                << " >>>>> " << module << std::setw(iIndentLevel)
                << " : " << log << " " << log2 << std::endl;
        }
    }

    static void Log(std::string_view module, const int line, std::string_view log, std::string_view log2, LogType::Type logType = LogType::Info)
    {
        if constexpr (DEBUG_MODE)
        {
            std::string lineNumber = " Line : " + std::to_string(line);
            const auto& strLogType = LogType::s_mapLogTypeName.at(logType);
            const auto iIndentLevel = s_iIndentLevel - lineNumber.length() - module.length() - strLogType.length();
            std::cout << strLogType << lineNumber
                << " >>>>> " << module << std::setw(iIndentLevel)
                << " : " << log << " " << log2 << std::endl;
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