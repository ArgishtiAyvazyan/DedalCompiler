/**
 * @file CExecurot.h
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CExecurot class.
 * @date 20-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include "Commands.h"

#include "CInsArg.h"

namespace vm
{

class CExecurot : public compiler::IInsExecutor
{
public:

    ~CExecurot() = default;

    using CInsArg = core::CInsArg;

    virtual void Nop(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Break(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Exit(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Execution control
    virtual void Jump(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Call(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Ret(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Assignment
    virtual void Assign(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Move(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Swap(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Logical
    virtual void And(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Or(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Xor(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Not(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Nand(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Nor(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Unsigned integral arithmetic
    virtual void Add(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Sub(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Mul(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Div(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Inc(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Dec(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Signeg integral arithmetic
    virtual void AddC(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void SubB(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void IMul(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void IDiv(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Neg(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Shift
    virtual void ShiftR(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void ShiftL(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void RotateR(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void RotateL(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void ShiftAR(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void ShiftAL(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void RotateCR(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void RotateCL(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Comparison
    virtual void Test(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Cmp(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Stack
    virtual void Push(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Pop(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void PushF(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void PopF(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Memory
    virtual void Load(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Store(SCPUState&, CMemory&, CInsArg, CInsArg) override;

    // Input & Output
    virtual void In(SCPUState&, CMemory&, CInsArg, CInsArg) override;
    virtual void Out(SCPUState&, CMemory&, CInsArg, CInsArg) override;
};

} // namespace vm