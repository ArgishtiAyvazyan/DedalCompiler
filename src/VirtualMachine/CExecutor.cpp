/**
 * @file CExecurot.cpp
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Implementation for CExecurot class.
 * @date 21-12-2019
 * @copyright Copyright (c) 2019
 */

#include "CExecutor.h"
#include "CException.h"

namespace vm
{

void CExecurot::Nop(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Nop not supported.");
}

void CExecurot::Break(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Break not supported.");
}

void CExecurot::Exit(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Exit not supported.");
}


// Execution control
void CExecurot::Jump(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Jump not supported.");
}

void CExecurot::Call(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Call not supported.");
}

void CExecurot::Ret(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Ret not supported.");
}


// Assignment
void CExecurot::Assign(SCPUState& cpustate, CMemory& memory, CInsArg arg1, CInsArg arg2)
{
    BASE_THROW_ERROR("Assign not supported.");
}

void CExecurot::Move(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Move not supported.");
}

void CExecurot::Swap(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Swap not supported.");
}


// Logical
void CExecurot::And(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("And not supported.");
}

void CExecurot::Or(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Or not supported.");
}

void CExecurot::Xor(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Xor not supported.");
}

void CExecurot::Not(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Not not supported.");
}

void CExecurot::Nand(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Nand not supported.");
}

void CExecurot::Nor(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Nor not supported.");
}


// Unsigned integral arithmetic
void CExecurot::Add(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Add not supported.");
}

void CExecurot::Sub(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Sub not supported.");
}

void CExecurot::Mul(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Mul not supported.");
}

void CExecurot::Div(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Div not supported.");
}

void CExecurot::Inc(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Inc not supported.");
}

void CExecurot::Dec(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Dec not supported.");
}


// Signeg integral arithmetic
void CExecurot::AddC(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("AddC not supported.");
}

void CExecurot::SubB(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("SubB not supported.");
}

void CExecurot::IMul(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("IMul not supported.");
}

void CExecurot::IDiv(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("IDiv not supported.");
}

void CExecurot::Neg(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Neg not supported.");
}


// Shift
void CExecurot::ShiftR(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("ShiftR not supported.");
}

void CExecurot::ShiftL(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("ShiftL not supported.");
}

void CExecurot::RotateR(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("RotateR not supported.");
}

void CExecurot::RotateL(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("RotateL not supported.");
}

void CExecurot::ShiftAR(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("ShiftAR not supported.");
}

void CExecurot::ShiftAL(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("ShiftAL not supported.");
}

void CExecurot::RotateCR(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("RotateCR not supported.");
}

void CExecurot::RotateCL(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("RotateCL not supported.");
}


// Comparison
void CExecurot::Test(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Test not supported.");
}

void CExecurot::Cmp(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Cmp not supported.");
}


// Stack
void CExecurot::Push(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Push not supported.");
}

void CExecurot::Pop(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Pop not supported.");
}

void CExecurot::PushF(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("PushF not supported.");
}

void CExecurot::PopF(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("PopF not supported.");
}


// Memory
void CExecurot::Load(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Load not supported.");
}

void CExecurot::Store(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Store not supported.");
}


// Input & Output
void CExecurot::In(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("In not supported.");
}

void CExecurot::Out(SCPUState&, CMemory&, CInsArg, CInsArg)
{
    BASE_THROW_ERROR("Out not supported.");
}

} // namespace vm