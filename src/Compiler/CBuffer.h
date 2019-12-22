/**
 * @file CBuffer.h
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CBuffer class.
 * @date 21-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <vector>
#include <iostream>
#include "CException.h"

namespace compiler
{

class CBuffer
{
    static constexpr int64_t s_default_size = 4096;

public:
    static constexpr int64_t nulladdress = 0;

public:
    using TAddress = int64_t;
    using TCount = int64_t;

    CBuffer(const CBuffer&) = default;
    CBuffer(CBuffer&&) = default;
    CBuffer& operator=(const CBuffer&) = default;
    CBuffer& operator=(CBuffer&&) = default;

    /**
     * @brief Construct a new CBuffer object
     *
     * @param size The memory size.
     */
    CBuffer(int64_t size = 0)
        : m_vecBuffer(size)
    {
    }

    template<typename V>
    CBuffer& operator << (const V& value)
    {
        const auto iCurrentMaxPos = std::size(m_vecBuffer);
        const auto new_size = std::size(m_vecBuffer) + sizeof(V);
        m_vecBuffer.resize(new_size);
        reinterpret_cast<V&>(m_vecBuffer[iCurrentMaxPos]) = value;
        return *this;
    }

    template<typename V>
    CBuffer& operator >> (V& value)
    {
        if (m_iCurrentPos >= std::size(m_vecBuffer)) {
            m_iCurrentPos = 0;
        }
        value = reinterpret_cast<V&>(m_vecBuffer[m_iCurrentPos]);
        m_iCurrentPos += sizeof(V);
        return *this;
    }

    template<typename V>
    V& operator[](TAddress address)
    {
        return reinterpret_cast<V&>(m_vecBuffer[address]);
    }

    size_t TopAddress() const noexcept
    {
        return std::size(m_vecBuffer);
    }

public:

    /**
     * @brief Gets memory size.
     *
     * @return int64_t The memory size.
     */
    int64_t Size() const
    {
        return std::size(m_vecBuffer);
    }

//! TODO change to protected.
public:
// protected:
    size_t m_iCurrentPos{};
    std::vector<uint8_t> m_vecBuffer;
};

} // namespace compiler