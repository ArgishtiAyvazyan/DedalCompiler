/**
 * @file CInsArg.h
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CInsArg class.
 * @date 19-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <cstdint>
#include <utility>

namespace core
{

#pragma pack (push, 1)

/**
 * @brief The class is a c++ representation of instruction arguments.
 */
class CInsArg
{
public:

    enum class EArgType
    {
        NotInit
        , AddReg
        , GenReg
        , MemAdd
        , Number
    };

public:

    using t_mem_add = int32_t;

    CInsArg(EArgType type, t_mem_add add);

    CInsArg() = default;
    ~CInsArg() = default;
    CInsArg(const CInsArg&) = default;
    CInsArg& operator=(const CInsArg&) = default;
    CInsArg(CInsArg&&) = default;
    CInsArg& operator=(CInsArg&&) = default;

    std::pair<t_mem_add, EArgType> Value() const noexcept;

private:

    // TODO use 4 bits
    EArgType m_eArgType;
    t_mem_add m_iMemAdd;

};

#pragma pack (pop)

} // namespace core