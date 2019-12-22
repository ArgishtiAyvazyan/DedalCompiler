/**
 * @file ParserDecl.hpp
 * @author Argishti Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration of the element classes for a parser.
 * @date 01-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <string>

#include "Decl.h"

/**
 * @class CReg
 * @brief The c++ representation of assembly register.
 */
class CReg
{
public:
    CReg(int value)
        : m_iValue(value)
    {
    }

    CReg(std::string_view value)
        : m_iValue(std::stoi(value.data()))
    {
    }


    [[nodiscard]] bool operator==(const CReg& other) const noexcept
    {
        return other.m_iValue == m_iValue;
    }

    [[nodiscard]] int Data() const
    {
        return m_iValue;
    }

private:
    int m_iValue;
};

/**
 * @class
 * @brief The c++ representation of assembly address register.
 */
class CAddReg
{
public:
    CAddReg(int value)
        : m_iValue(value)
    {
    }

    CAddReg(std::string_view value)
        : m_iValue(std::stoi(value.data()))
    {
    }

    [[nodiscard]] bool operator==(const CAddReg& other) const noexcept
    {
        return other.m_iValue == m_iValue;
    }

    [[nodiscard]] int Data() const
    {
        return m_iValue;
    }

private:
    int m_iValue;
};

/**
 * @class
 * @brief The c++ representation of assembly identifiers.
 */
class CID
{
public:
    CID(std::string value = "")
        : m_strValue(std::move(value))
    {
    }

    CID(std::string_view value)
        : m_strValue(static_cast<std::string>(value))
    {
    }

    CID& operator=(const std::string& value)
    {
        m_strValue = value;
        return *this;
    }

    CID& operator=(std::string_view value)
    {
        m_strValue = static_cast<std::string>(value);
        return *this;
    }

    [[nodiscard]] bool operator==(const CID& other) const noexcept
    {
        return other.m_strValue == m_strValue;
    }

    [[nodiscard]] const std::string& Data() const
    {
        return m_strValue;
    }

private:
    std::string m_strValue;
};

/**
 * @class
 * @brief The c++ representation of assembly numbers.
 */
class CNum
{
public:
    CNum(int value)
        : m_iValue(value)
    {
    }

    CNum(std::string_view value)
        : m_iValue(std::stoi(value.data()))
    {
    }

    [[nodiscard]] bool operator==(const CNum& other) const noexcept
    {
        return other.m_iValue == m_iValue;
    }

    [[nodiscard]] int Data() const
    {
        return m_iValue;
    }


private:
    int m_iValue;
};

/**
 * @brief The c++ representation of assembly null.
 */
class CNull
{
public:

    [[nodiscard]] std::nullptr_t Data() const
    {
        return nullptr;
    }

};

