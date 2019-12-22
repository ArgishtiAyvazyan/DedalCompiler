/**
 * @file CMemory.h
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CMemory class.
 * @date 15-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <vector>

#include "CBuffer.h"

namespace vm
{

/**
 * @class CMemory
 * @brief The class CMemory represents memory concept.
 */
class CMemory : public compiler::CBuffer
{
public:
    /**
     * @brief Construct a new CBuffer object
     *
     * @param size The memory size.
     */
    CMemory(int64_t size)
        : CBuffer(size)
    {
    }

    CMemory()
        : CBuffer()
    {
    }

    CMemory(compiler::CBuffer& buf)
    {
        m_vecBuffer = std::move(buf.m_vecBuffer);
    }

        /**
     * @brief Reads the value at the address.
     *
     * @tparam TValue The value type.
     * @param address The address in memory.
     * @return TValue& The value reference.
     */
    template <typename TValue>
    [[nodiscard]] TValue& Read(TAddress address)
    {
        BASE_CHECK (address < this->Size(), "Out of memory range.");
        BASE_CHECK ((int)(address + sizeof(TValue)) < this->Size(), "Out of memory range.");
        BASE_CHECK (address != nulladdress, "null pointer dereference.");
        return reinterpret_cast<TValue&>(m_vecBuffer[address]);
    }

    /**
     * @brief Writess the value at the address.
     *
     * @tparam TValue TValue The value type.
     * @param address The address in memory.
     * @param value The new value.
     */
    template <typename TValue>
    void Write(TAddress address, const TValue& value)
    {
        BASE_CHECK (address < this->Size(), "Out of memory range.");
        BASE_CHECK (address + sizeof(TValue) < this->Size(), "Out of memory range.");
        BASE_CHECK (address != nulladdress, "null pointer dereference.");
        reinterpret_cast<TValue&>(m_vecBuffer[address]) = value;
    }
};

} // namespace vm