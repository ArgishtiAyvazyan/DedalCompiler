/**
 * @file SCPUState.h
 * @author Argishti Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for SCPUState struct.
 * @date 15-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <memory>

#include "CFlags.h"
#include "CMemory.h"

namespace vm
{

struct SCPUState
{
    using TFlags = std::shared_ptr<CFlags>;
    using TAddress = CMemory::TAddress;

    static constexpr int16_t s_iAddressRegisterCount = 16;
    static constexpr int16_t s_iGenPurposeRegisterCount = 16;

public:

    SCPUState()
        : IP(0)
    {}

    // Next command address.
    TAddress IP;

    // Address Registers
    TAddress AddressRegisters[s_iAddressRegisterCount];

    // General purpose registers.
    int64_t GenPurposeRegisters[s_iGenPurposeRegisterCount];

    // CPU flags.
    TFlags Flags;
};

} // namespace vm