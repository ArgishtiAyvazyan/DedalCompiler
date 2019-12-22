/**
 * @file CCompiler.h
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CCompiler class.
 * @date 22-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <vector>
#include <string>
#include <optional>
#include <memory>

#include "CBuffer.h"
#include "CParser.hpp"
#include "CException.h"
#include "CInsArg.h"
#include "Decl.h"

namespace compiler
{

class CCompiler
{
    using EOperationSize = core::EOperationSize;
    using TBuffer = std::unique_ptr<CBuffer>;
    using TAddress = CBuffer::TAddress;
    using TStackSize = size_t;
    using CInsArg = core::CInsArg;
    using EOperationCode = core::EOperationCode;
    using TCHAR = core::TCHAR;
    using TBYTE = core::TBYTE;
    using TWORD = core::TWORD;
    using TDWORD = core::TDWORD;
    using TQWORD = core::TQWORD;


public:

    static constexpr auto s_iStackSizeAddress = 64;
    static constexpr auto s_iEntryPointAddress = s_iStackSizeAddress + sizeof(TStackSize);
    static constexpr auto s_iDataSegmentBeginAddress = s_iEntryPointAddress + sizeof(TAddress);
    static constexpr auto s_iCodeSegmentBeginAddress = s_iDataSegmentBeginAddress + sizeof(TAddress);

    static constexpr auto nulladdress = CBuffer::nulladdress;

    struct SDefinition
    {
        std::optional<TStackSize> StackSize;
        std::string EntryPoint;
        std::optional<TAddress> DataSegmentBegin;
        std::optional<TAddress> CodeSegmentBegin;
    };

public:

    CCompiler(std::vector<std::string> files);

    ~CCompiler();

    const CBuffer& GetCompiledCode();

private:

    void init();

    void initCodeDefinition();

    void initInstructionsCallbacks();

    void initDataCallbacks();

    void link();

    void initDefinitions();

private:
    std::vector<std::string> m_vecFiles;
    TBuffer m_pBuffer;
    SDefinition m_sDefinition;
    std::unordered_map<std::string, TAddress> m_mapLabelToAddress;
    std::unordered_map<std::string, std::vector<TAddress>> m_mapNotInitializedArgs;
    std::unordered_map<std::string, TAddress> m_mapDATAsAddresses;
    std::unordered_map<std::string, TAddress> m_mapFunctionsAddresses;
};

} // namespace compiler