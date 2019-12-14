/**
 * @file CException.cpp
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Implementation for CException class.
 * @date 14-12-2019
 * @copyright Copyright (c) 2019
 */

#include "CException.h"

#include <boost/stacktrace.hpp>


namespace gen
{

using namespace std::string_literals;

CException::CException()
    : m_strMessage ("Unknown error"s)
    , m_strStackTrace (CurrentStackTrace())
    , m_svFileName ()
    , m_svLineNumber (0)
{
}

CException::CException(const std::string message)
    : m_strMessage (std::move(message))
    , m_strStackTrace (CurrentStackTrace())
    , m_svFileName ()
    , m_svLineNumber (0)
{
}

CException::CException(const std::string message
        , const std::string_view file
        , const std::size_t line)
    : m_strMessage (std::move(message))
    , m_strStackTrace (CurrentStackTrace())
    , m_svFileName (file)
    , m_svLineNumber (line)
{
}

std::string_view CException::Message() const
{
    return m_strMessage;
}

std::string_view CException::StackTrace() const
{
    return m_strStackTrace;
}

std::string_view CException::FileName() const
{
    return m_svFileName;
}

std::size_t CException::LineNumber() const
{
    return m_svLineNumber;
}

std::string CException::CurrentStackTrace()
{
    std::stringstream ss;
    ss << boost::stacktrace::stacktrace() << std::endl;
    return ss.str();
}


} // namespace gen