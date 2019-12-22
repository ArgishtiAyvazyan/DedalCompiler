/**
 * @file CProcessor.h
 * @author Argishti Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CException class.
 * @date 15-12-2019
 * @copyright Copyright (c) 2019
 */


#pragma once

#include <memory>

#include "ParserDecl.hpp"

#include "CMemory.h"
#include "CFlags.h"
#include "SCPUState.h"

#include "CCommandContext.h"

namespace vm
{

class CProcessor
{
    using TAddress = CMemory::TAddress;
    using TMemory = std::unique_ptr<CMemory>;
    using TSCPUState = std::unique_ptr<SCPUState>;
    using CCommandContext = compiler::CCommandContext;
    using TCommandContext = std::unique_ptr<CCommandContext>;
    using EOperationCode = core::EOperationCode;

    enum class EState
    {
        Running
        , Stopped
        , NotInitialized
    };

public:

    CProcessor();

    CProcessor(CMemory mem);

    void Run(bool bDebug = false);

    EOperationCode Fetch();

    void Decode(CCommandContext& context);

    void Execute(EOperationCode, CCommandContext&);

private:

    CMemory& Memory() const;

    void init();

private:
    TMemory m_pMemory;
    EState m_eState;
    TSCPUState m_pCPUState;

    TCommandContext m_pCurrentCommandContext;

    size_t m_iStackSize;
    TAddress m_aEntryPoint;
    TAddress m_aDataSegmentStart;
    TAddress m_aCodeSegmentStart;
};


} // namespace vm
