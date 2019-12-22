/**
 * @file CInsArg.cpp
 * @author Argishti Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Implementation for CInsArg class.
 * @date 23-12-2019
 * @copyright Copyright (c) 2019
 */


#include "CInsArg.h"

namespace core
{

CInsArg::CInsArg(EArgType type, t_mem_add add)
    : m_eArgType { type }
    , m_iMemAdd { add }
{}

auto CInsArg::Value() const noexcept -> std::pair<t_mem_add, EArgType>
{
    return std::make_pair(m_iMemAdd, m_eArgType);
}

} // namespace core