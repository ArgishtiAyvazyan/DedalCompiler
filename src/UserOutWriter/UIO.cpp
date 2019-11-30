#include "UIO.h"
#include "Configs.hpp"

#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>



static inline const std::unordered_map <MessageType, std::string_view> s_mapMessageTypeName
{
      std::make_pair(MessageType::Info,    "Info")
    , std::make_pair(MessageType::Warning, "Warning")
    , std::make_pair(MessageType::Error,   "Error")
    , std::make_pair(MessageType::Debug,   "Debug")
};

enum class Color
{
      FG_RED      = 31
    , FG_GREEN    = 32
    , FG_YELLOW   = 33
    , FG_BLUE     = 34
    , FG_DEFAULT  = 39
    , BG_RED      = 41
    , BG_GREEN    = 42
    , BG_BLUE     = 44
    , BG_DEFAULT  = 49
};

static inline const std::unordered_map <MessageType, Color> s_mapMessageColors
{ 
      std::make_pair(MessageType::Info,    Color::FG_GREEN)
    , std::make_pair(MessageType::Warning, Color::FG_BLUE)
    , std::make_pair(MessageType::Error,   Color::FG_RED)
    , std::make_pair(MessageType::Debug,   Color::FG_YELLOW)
};

static int Color(MessageType type)
{
    return static_cast<int>(s_mapMessageColors.at(type));
}

void UIO::Write(std::string_view svMessage, std::string_view svModule, MessageType eMessageType)
{
    const auto color = Color(eMessageType);
    std::cout << "\033[4;" << color << "m";
    if constexpr (Config::DEBUG)
    {
        const auto& strLogType = s_mapMessageTypeName.at(eMessageType);
        std::cout << strLogType << "\t";
        std::cout << "\033[0;" << color << "m";
        std::cout << " > "
            << svModule << "\t"
            << " : " << svMessage << std::endl;
    }
    else
    {
        if (eMessageType == MessageType::Debug)
        {
            return;
        }
        const auto& strLogType = s_mapMessageTypeName.at(eMessageType);
        std::cout << strLogType << "\t";
        std::cout << "\033[0;" << color << "m";
        std::cout << " > "
            << " : " << svMessage << std::endl;
    }
    std::cout << "\033[0m";
}