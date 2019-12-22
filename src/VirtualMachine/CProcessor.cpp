/**
 * @file CProcessor.cpp
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Implementation for CProcessor class.
 * @date 20-12-2019
 * @copyright Copyright (c) 2019
 */

#include "CProcessor.h"
#include "Commands.h"
#include "CExecutor.h"
#include "CCompiler.h"

namespace vm
{

CProcessor::CProcessor()
    : m_eState(EState::NotInitialized)
    , m_pCPUState(std::make_unique<SCPUState>())
    , m_pCurrentCommandContext(std::make_unique<CCommandContext>())
{
    compiler::CCommandMeneger::Get().SetExecutor(std::make_unique<CExecurot>());
}

CProcessor::CProcessor(CMemory mem)
    : CProcessor()
{
    m_pMemory = std::make_unique<CMemory>(mem);
    BASE_CHECK(nullptr != m_pMemory, "Memory is not initialized.");
    this->init();
    this->Run();
}


void CProcessor::Run(bool bDebug)
{
    BASE_CHECK(m_eState != EState::NotInitialized, "Memory is empty.");

    m_eState = EState::Running;

    do
    {
        // Fetch current command
        EOperationCode pCmd = Fetch();

        // Decode current command
        Decode(*m_pCurrentCommandContext);

        // Increment program counter
        m_pCPUState->IP += m_pCurrentCommandContext->MetaInfo().Length();

        // Execute current command
        Execute(pCmd, *m_pCurrentCommandContext);

    } while (EState::Running == m_eState);
}

auto CProcessor::Fetch() -> EOperationCode
{
    return Memory().Read<EOperationCode>(m_pCPUState->IP);
}

void CProcessor::Decode(CCommandContext& context)
{
    context = m_pMemory->Read<CCommandContext>(m_pCPUState->IP);
}

void CProcessor::Execute(EOperationCode eOpCode, CCommandContext& context)
{
    compiler::FExecutor excutor = context.MetaInfo().Executor();
    excutor(*m_pCPUState, *m_pMemory, context.cInsArgFirst, context.cInsArgLast);
}

CMemory& CProcessor::Memory() const
{
    return *m_pMemory;
}

void CProcessor::init()
{
    using namespace compiler;
    m_eState = EState::Running;
    m_iStackSize = m_pMemory->Read<size_t>(CCompiler::s_iStackSizeAddress);
    m_aEntryPoint = m_pMemory->Read<TAddress>(CCompiler::s_iEntryPointAddress);
    m_aDataSegmentStart = m_pMemory->Read<TAddress>(CCompiler::s_iDataSegmentBeginAddress);
    m_aCodeSegmentStart = m_pMemory->Read<TAddress>(CCompiler::s_iCodeSegmentBeginAddress);

    m_pCPUState->IP = m_aCodeSegmentStart;
}

} // namespace vm