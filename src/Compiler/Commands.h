/**
 * @file Commands.h
 * @author Argishty Ayvayzan (argishty.ayvazyan@gmail.com)
 * @brief The file contains the instructions definitions.
 * @date 16-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <functional>
#include <unordered_map>
#include <memory>

#include "ParserDecl.hpp"
#include "CInsArg.h"

namespace vm
{
struct SCPUState;
class CMemory;
} // namespace vm

namespace compiler
{

enum class EArgsType : uint8_t
{
    Non
    , Reg
    , RegReg
    , AddReg
    , AddRegAddReg
    , ID
    , RegNum
    , RegID
    , RegAddReg
    , AddRegReg
    , AddRegID
    , AddRegNum
    , AddRegNull
};

/**
 * @class IInsExecutor
 * @brief Instruction executor
 */
class IInsExecutor
{
protected:
    using SCPUState = vm::SCPUState;
    using CMemory = vm::CMemory;
    using CInsArg = core::CInsArg;
public:

    virtual ~IInsExecutor() = default;

    virtual void Nop(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Break(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Exit(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Execution control
    virtual void Jump(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Call(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Ret(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Assignment
    virtual void Assign(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Move(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Swap(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Logical
    virtual void And(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Or(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Xor(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Not(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Nand(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Nor(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Unsigned integral arithmetic
    virtual void Add(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Sub(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Mul(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Div(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Inc(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Dec(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Signeg integral arithmetic
    virtual void AddC(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void SubB(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void IMul(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void IDiv(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Neg(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Shift
    virtual void ShiftR(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void ShiftL(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void RotateR(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void RotateL(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void ShiftAR(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void ShiftAL(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void RotateCR(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void RotateCL(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Comparison
    virtual void Test(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Cmp(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Stack
    virtual void Push(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Pop(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void PushF(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void PopF(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Memory
    virtual void Load(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Store(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;

    // Input & Output
    virtual void In(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
    virtual void Out(SCPUState&, CMemory&, CInsArg, CInsArg) = 0;
};

class FExecutor
{
    using SCPUState = vm::SCPUState;
    using CMemory = vm::CMemory;
    using CInsArg = core::CInsArg;
    using TFuncPtr = std::function<void(SCPUState&, CMemory&, CInsArg&, CInsArg&)>;
public:

    FExecutor() = delete;
    ~FExecutor() = default;
    FExecutor(FExecutor&&) = default;
    FExecutor(const FExecutor&) = default;
    FExecutor& operator=(FExecutor&&) = default;
    FExecutor& operator=(const FExecutor&) = default;

    template<typename Fn>
    FExecutor(Fn&& fn)
        : m_pFunc (std::move(fn))
    {}

    void operator()(SCPUState& state, CMemory& mem, CInsArg arg1, CInsArg arg2) const
    {
        (m_pFunc)(state, mem, arg1, arg2);
    }

private:
    TFuncPtr m_pFunc;
};

/**
 * @class CInsMetaInfo
 * @brief The class CInsMetaInfo contains meta info for assembly instruction.
 */
class CInsMetaInfo
{
    using SCPUState = vm::SCPUState;
    using CMemory = vm::CMemory;
    using EOperationCode = core::EOperationCode;

    public:

    CInsMetaInfo(
        EOperationCode eOperationCode
        , int iLength
        , FExecutor pExecutor
        , std::string sName
    )
        : m_eOpType (eOperationCode)
        , m_iLength (iLength)
        , m_pExecutor (pExecutor)
        , m_sName (sName)
    {
    }

    EOperationCode Type() const
    {
        return m_eOpType;
    }

    int Length() const
    {
        return m_iLength;
    }

    FExecutor Executor() const
    {
        return m_pExecutor;
    }

    std::string Name() const
    {
        return m_sName;
    }

private:
    EOperationCode m_eOpType;
    int m_iLength;
    FExecutor m_pExecutor;
    std::string m_sName;
};


class CCommandMeneger
{
    using CInsArg = core::CInsArg;
    using EOperationCode = core::EOperationCode;
public:

    CCommandMeneger();

    static CCommandMeneger& Get()
    {
        static CCommandMeneger cm;
        return cm;
    }

    CInsMetaInfo& MetaInfo(EOperationCode);

    void SetExecutor(std::unique_ptr<IInsExecutor>&& ex)
    {
        m_pExecutor = std::move(ex);
    }

private:

    void init();

private:
    std::unique_ptr<IInsExecutor> m_pExecutor;

    std::unordered_map<EOperationCode, CInsMetaInfo> m_mapOpCodeToMetaInfo;
};

} // namespace compiler
