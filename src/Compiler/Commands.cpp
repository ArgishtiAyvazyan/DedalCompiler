/**
 * @file Commands.cpp
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Implementation for CCommandMeneger class.
 * @date 20-12-2019
 * @copyright Copyright (c) 2019
 */

#include "Commands.h"
#include "CException.h"

namespace compiler
{

CCommandMeneger::CCommandMeneger()
{
    this->init();
}

void CCommandMeneger::init()
{
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Assign(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::ASSIGN, 4, l, "ASSIGN");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Print(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::PRINT, 4, l, "PRINT");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Cmp(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::CMP, 4, l, "CMP");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Test(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::TEST, 4, l, "TEST");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Jump(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::JUMP, 4, l, "JUMP");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Jz(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::JZ, 4, l, "JZ");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Jnz(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::JNZ, 4, l, "JNZ");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Jo(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::JO, 4, l, "JO");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Jno(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::JNO, 4, l, "JNO");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Jc(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::JC, 4, l, "JC");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Jnc(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::JNC, 4, l, "JNC");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Jne(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::JNE, 4, l, "JNE");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Add(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::ADD, 4, l, "ADD");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Sub(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::SUB, 4, l, "SUB");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Mul(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::MUL, 4, l, "MUL");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->IMul(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::IMUL, 4, l, "IMUL");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Div(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::DIV, 4, l, "DIV");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Idiv(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::IDIV, 4, l, "IDIV");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Move(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::MOVE, 4, l, "MOVE");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Call(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::CALL, 4, l, "CALL");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Push(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::PUSH, 4, l, "PUSH");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Pop(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::POP, 4, l, "POP");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Pushsf(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::PUSHSF, 4, l, "PUSHSF");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Popsf(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::POPSF, 4, l, "POPSF");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Nop(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::NOP, 4, l, "NOP");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Swap(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::SWAP, 4, l, "SWAP");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->And(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::AND, 4, l, "AND");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Gflr(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::GFLR, 4, l, "GFLR");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Sflr(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::SFLR, 4, l, "SFLR");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Inc(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::INC, 4, l, "INC");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Dec(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::DEC, 4, l, "DEC");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Shl(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::SHL, 4, l, "SHL");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Shr(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::SHR, 4, l, "SHR");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Rol(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::ROL, 4, l, "ROL");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Ror(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::ROR, 4, l, "ROR");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Sal(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::SAL, 4, l, "SAL");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Sar(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::SAR, 4, l, "SAR");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Rcl(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::RCL, 4, l, "RCL");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Rcr(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::RCR, 4, l, "RCR");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Adc(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::ADC, 4, l, "ADC");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Sbb(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::SBB, 4, l, "SBB");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Neg(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::NEG, 4, l, "NEG");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Cast(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::CAST, 4, l, "CAST");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Out(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::OUT, 4, l, "OUT");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->In(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::IN, 4, l, "IN");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Load(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::LOAD, 4, l, "LOAD");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Store(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::STORE, 4, l, "STORE");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Break(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::BREAK, 4, l, "BREAK");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    {
        auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
        { m_pExecutor->Ret(s, m, a1, a2); };
        CInsMetaInfo ins(EOperationCode::RET, 4, l, "RET");
        m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    }
    // {
    //     auto l = [this](vm::SCPUState& s, vm::CMemory& m, CInsArg a1, CInsArg a2)
    //     { m_pExecutor->Non(s, m, a1, a2); };
    //     CInsMetaInfo ins(EOperationCode::NON, 4, l, "NON");
    //     m_mapOpCodeToMetaInfo.insert(std::make_pair(ins.Type(), ins));
    // }
}

CInsMetaInfo& CCommandMeneger::MetaInfo(const EOperationCode eOpCode)
{
    BASE_CHECK (nullptr != m_pExecutor, "Executor is not initialized!");
    try
    {
        return m_mapOpCodeToMetaInfo.at(eOpCode);
    }
    catch (const std::out_of_range& e)
    {
        BASE_THROW_ERROR(e.what());
    }
    catch (...)
    {
        BASE_THROW_ERROR ("Unknown error!");
    }
}


} // namespace compiler