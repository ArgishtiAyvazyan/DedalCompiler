/**
 * @file CException.h
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CException class.
 * @date 14-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <string>
#include <string_view>


namespace gen
{

/**
 * @class CException
 * @brief The base class for all exceptional conditions.
 */
class CException
{
public:

    CException();

    /**
     * @brief Construct a new CException.
     *
     * @param message The error description.
     */
    CException(const std::string message);

    /**
     * @brief Construct a new CException object
     *
     * @param message The error description.
     * @param file The filename that contains the code that is throwing an exception.
     * @param line The line number in the file that contains the code that is throwing an exception.
     */
    CException(const std::string message
             , const std::string_view file
             , const size_t line);

    /**
     * @brief Gets a message that describes the current exception.
     *
     * @return std::string_view The error message that explains the \n
     *          reason for the exception, or an empty string_view ("")
     */
    std::string_view Message() const;


    /**
     * @brief Gets a string representation of the immediate frames on the call stack.
     *
     * @return std::string_view A string that describes the immediate frames of the call stack.
     */
    std::string_view StackTrace() const;

    /**
     * @brief Gets the filename that contains the code that is throwing an exception.
     *
     * @return std::string_view The file name, or Empty string if the file name \n
     *          cannot be determined.
     */
    std::string_view FileName() const;

    /**
     * @brief Gets the line number in the file that contains the code that is throwing an exception.
     *
     * @return std::string_view The file line number, or 0 (zero) if the file line \n
     *          number cannot be determined.
     */
    std::size_t LineNumber() const;

private:

    /**
     * @internal
     * @brief Returns all stack frames in the current stack trace.
     *
     * @return std::string Represents a stack trace, which is an ordered collection \n
     *          of one or more stack frames.
     */
    std::string CurrentStackTrace();

private:
    std::string m_strMessage;
    std::string m_strStackTrace;
    std::string_view m_svFileName;
    std::size_t m_svLineNumber;
};

} // namespace gen


/**
 * @brief Helpers for error handling.
 */

#define BASE_SRC_LINE					std::string_view(__FILE__), int(__LINE__)
#define BASE_THROW_ERROR( _message_ )	throw ::gen::CException( _message_, BASE_SRC_LINE );

#define BASE_CHECK(_cndtn_, _message_)	if( !bool(_cndtn_) ) { BASE_THROW_ERROR( _message_ ) }

