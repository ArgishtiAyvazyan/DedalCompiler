#pragma once

/**
 * @copyright (C) 2019 by Argishti Ayvazyan
 * @file UIO.h
 * @author Argishti
 * @date 28 nov 2019
 * @brief A file containing an interface for input and output.
 */

#include <string_view>

/**
 * @brief The types of messages. \n
 *          Depending on the type of message, it is processed differently.
 */
enum class MessageType : char
{
      Info
    , Warning
    , Error
    , Debug
};

/**
 * @class UIO
 * @brief A class that is a wrapper for console output methods.
 *          It also saves all the conclusions to the log file.
 */
class UIO
{

    static constexpr int s_iIndentLevel = 25;

public:

    /**
     * @brief Writes message in console and log file.
     * 
     * @param message Message for writing.
     * @param module The name of the module from which the writing occurs.
     * @param eMessageType The message type. \n
     */
    static void Write(std::string_view message, std::string_view module, MessageType eMessageType = MessageType::Info);

private:
};