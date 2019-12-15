/**
 * @file CMemory.h
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CMemory class.
 * @date 15-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <vector>

#include "CException.h"

namespace vm
{

/**
 * @class CMemory
 * @brief The class CMemory represents memory concept.
 */
class CMemory
{
    static constexpr int64_t s_default_size = 4096;

public:
    static constexpr int64_t nulladdress = 0;

public:
    using TAddress = int64_t;
    using TCount = int64_t;

    CMemory(const CMemory&) = delete;
    CMemory(CMemory&&) = delete;
    void operator=(const CMemory&) = delete;
    void operator=(CMemory&&) = delete;

    /**
     * @brief Construct a new CMemory object
     *
     * @param size The memory size.
     */
    CMemory(int64_t size = s_default_size)
        : m_vecMemory(size)
    {
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
        BASE_CHECK (address + sizeof(TValue) < this->Size(), "Out of memory range.");
        BASE_CHECK (address != nulladdress, "null pointer dereference.");
        return reinterpret_cast<TValue&>(m_vecMemory[address]);
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
        reinterpret_cast<TValue&>(m_vecMemory[address]) = value;
    }

public:

    /**
     * @brief Gets memory size.
     *
     * @return int64_t The memory size.
     */
    int64_t Size() const
    {
        return std::size(m_vecMemory);
    }

private:
    std::vector<uint16_t>	m_vecMemory;
};

} // namespace vm