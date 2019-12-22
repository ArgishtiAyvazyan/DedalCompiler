/**
 * @file CCommandContext.h
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CCommandContext class.
 * @date 19-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include "Commands.h"
#include "CInsArg.h"
#include "Decl.h"

namespace compiler
{

#pragma pack (push, 1)

class CCommandContext
{
    using CInsArg = core::CInsArg;
    using EOperationSize = core::EOperationSize;
    using EOperationCode = core::EOperationCode;
public:

    CCommandContext() = default;
    CCommandContext(CCommandContext&&) = default;
    CCommandContext& operator=(CCommandContext&&) = default;
    CCommandContext(const CCommandContext&) = default;
    CCommandContext& operator=(const CCommandContext&) = default;

    CCommandContext(EOperationCode eCode, EOperationSize eSize, CInsArg cArg1, CInsArg cArg2)
        : eOpCode(eCode)
        , eOpSize(eSize)
        , cInsArgFirst(cArg1)
        , cInsArgLast(cArg2)
    {
    }

    CInsMetaInfo& MetaInfo() const
    {
        return CCommandMeneger::Get().MetaInfo(eOpCode);
    }

    EOperationCode eOpCode;
    EOperationSize eOpSize;
    CInsArg cInsArgFirst;
    CInsArg cInsArgLast;
};

#pragma pack (pop)

} // namespace compiler