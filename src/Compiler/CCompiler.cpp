/**
 * @file CCompiler.cpp
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Implementation for CCompiler class.
 * @date 22-12-2019
 * @copyright Copyright (c) 2019
 */

#include "CCompiler.h"

namespace compiler
{

CCompiler::CCompiler(std::vector<std::string> files)
    : m_vecFiles { std::move(files) }
    , m_pBuffer { std::make_unique<CBuffer>() }
{
    init();
    for (auto& file : m_vecFiles)
    {
        auto& parser = CParser::get();
        parser.SetFileName(file);
        parser.StartParsing();
    }
    link();
    initDefinitions();
}

CCompiler::~CCompiler()
{
    CParser::get().Clear();
}

const CBuffer& CCompiler::GetCompiledCode()
{
    return *m_pBuffer;
}

void CCompiler::init()
{
    this->initCodeDefinition();
    this->initInstructionsCallbacks();
    this->initDataCallbacks();
}

void CCompiler::initCodeDefinition()
{
    decltype(m_sDefinition.StackSize)::value_type iStackSize;
    (*m_pBuffer) << iStackSize;
    TAddress aEntryPoint;
    (*m_pBuffer) << aEntryPoint;
    TAddress aDataSegmentStart;
    (*m_pBuffer) << aDataSegmentStart;
    TAddress aCodeSegmentStart;
    (*m_pBuffer) << aCodeSegmentStart;
}

void CCompiler::initInstructionsCallbacks()
{
    using namespace std::string_literals;

    auto& parser = CParser::get();

    // Read stack size.
    parser.EventReadStackSize.Add([this](const size_t size)
    {
        BASE_CHECK (not m_sDefinition.StackSize.has_value()
            , ("Compile error: stack size double definition. Line: "s
            + std::to_string(CParser::get().GetLineNumber())).data());
        m_sDefinition.StackSize = size;
    });

    // Read entry point.
    parser.EventReadEntryPoint.Add([this](const CID& EntryPoint)
    {
        BASE_CHECK (m_sDefinition.EntryPoint.empty()
            , ("Compile error: Entry point double definition. Line: "s
            + std::to_string(CParser::get().GetLineNumber())).data());
        m_sDefinition.EntryPoint = EntryPoint.Data();
    });

    // .DATA segment begin
    parser.EventReadDataSegmentBegin.Add([this]()
    {
        BASE_CHECK (not m_sDefinition.DataSegmentBegin.has_value()
            , ("Compile error: DATA segment double definition. Line: "s
            + std::to_string(CParser::get().GetLineNumber())).data());
        m_sDefinition.DataSegmentBegin = m_pBuffer->TopAddress();
    });
    
    // Code segment begin
    parser.EventReadCodeSegmentBegin.Add([this]()
    {
        BASE_CHECK (not m_sDefinition.CodeSegmentBegin.has_value()
            , ("Compile error: Code segment double definition. Line: "s
            + std::to_string(CParser::get().GetLineNumber())).data());
        m_sDefinition.CodeSegmentBegin = m_pBuffer->TopAddress();
    });

    parser.EventReadLabel.Add([this](const CID& label)
    {
        auto [it, complite] = m_mapLabelToAddress.insert({ label.Data(), m_pBuffer->TopAddress() });
        BASE_CHECK(complite
            , ("Compile error: Label double definition. Line: "s
            + std::to_string(CParser::get().GetLineNumber())).data());
    });

    parser.EventReadOperation.Add([this](EOperationCode eOpCode)
    {
        (*m_pBuffer) << eOpCode;
    });

    parser.EventReadOperationID.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CID arg1)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg (CInsArg::EArgType::NotInit, nulladdress);
        m_mapNotInitializedArgs[arg1.Data()].push_back(m_pBuffer->TopAddress());
        (*m_pBuffer) << arg;
    });

    parser.EventReadOperationReg.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CReg reg)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg (CInsArg::EArgType::GenReg, reg.Data());
        (*m_pBuffer) << arg;
    });

    parser.EventReadOperationAddReg.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CAddReg reg)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg (CInsArg::EArgType::AddReg, reg.Data());
        (*m_pBuffer) << arg;
    });

    parser.EventReadOperationRegReg.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CReg reg1, CReg reg2)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg1 (CInsArg::EArgType::AddReg, reg1.Data());
        (*m_pBuffer) << arg1;
        CInsArg arg2 (CInsArg::EArgType::AddReg, reg2.Data());
        (*m_pBuffer) << arg2;
    });

    parser.EventReadOperationRegNum.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CReg reg, CNum num)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg1 (CInsArg::EArgType::GenReg, reg.Data());
        (*m_pBuffer) << arg1;
        CInsArg arg2 (CInsArg::EArgType::Number, num.Data());
        (*m_pBuffer) << arg2;
    });

    parser.EventReadOperationAddRegAddReg.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CAddReg reg1, CAddReg reg2)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg1 (CInsArg::EArgType::AddReg, reg1.Data());
        (*m_pBuffer) << arg1;
        CInsArg arg2 (CInsArg::EArgType::AddReg, reg2.Data());
        (*m_pBuffer) << arg2;
    });

    parser.EventReadOperationRegID.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CReg reg1, CID reg2)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg1 (CInsArg::EArgType::GenReg, reg1.Data());
        (*m_pBuffer) << arg1;
        CInsArg arg2 (CInsArg::EArgType::NotInit, nulladdress);
        m_mapNotInitializedArgs[reg2.Data()].push_back(m_pBuffer->TopAddress());
        (*m_pBuffer) << arg2;
    });

    parser.EventReadOperationRegAddReg.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CReg reg1, CAddReg reg2)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg1 (CInsArg::EArgType::GenReg, reg1.Data());
        (*m_pBuffer) << arg1;
        CInsArg arg2 (CInsArg::EArgType::AddReg, nulladdress);
        (*m_pBuffer) << arg2;
    });

    parser.EventReadOperationAddRegReg.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CAddReg reg1, CReg reg2)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg1 (CInsArg::EArgType::AddReg, reg1.Data());
        (*m_pBuffer) << arg1;
        CInsArg arg2 (CInsArg::EArgType::GenReg, reg2.Data());
        (*m_pBuffer) << arg2;
    });

    parser.EventReadOperationAddRegID.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CAddReg reg1, CID id)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg1 (CInsArg::EArgType::AddReg, reg1.Data());
        (*m_pBuffer) << arg1;
        CInsArg arg2 (CInsArg::EArgType::NotInit, nulladdress);
        m_mapNotInitializedArgs[id.Data()].push_back(m_pBuffer->TopAddress());
        (*m_pBuffer) << arg2;
    });

    parser.EventReadOperationAddRegNum.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CAddReg reg1, CNum num)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg1 (CInsArg::EArgType::AddReg, reg1.Data());
        (*m_pBuffer) << arg1;
        CInsArg arg2 (CInsArg::EArgType::Number, num.Data());
        (*m_pBuffer) << arg2;
    });

    parser.EventReadOperationAddRegNull.Add([this](EOperationCode eOpCode, EOperationSize eOpSize, CAddReg reg1, CNull null)
    {
        (*m_pBuffer) << eOpCode;
        (*m_pBuffer) << eOpSize;
        CInsArg arg1 (CInsArg::EArgType::AddReg, reg1.Data());
        (*m_pBuffer) << arg1;
        CInsArg arg2 (CInsArg::EArgType::Number, nulladdress);
        (*m_pBuffer) << arg2;
    });

    parser.EventStartFunctionDecl.Add([this](const CID& id)
    {
        [[maybe_unused]] auto [it, complete] = m_mapFunctionsAddresses.insert({ id.Data(), m_pBuffer->TopAddress()});
        // BASE_CHECK(complete
        //     , "Compile error: Function double defitions. Line"s
        //     + std::to_string(CParser::get().GetLineNumber()));
    });
}

void CCompiler::initDataCallbacks()
{
    using namespace std::string_literals;
    auto& parser = CParser::get();

    parser.EventReadCHARDeclaration.Add([this](CID id , int size, std::string values)
    {
        auto [it, complete] = m_mapDATAsAddresses.insert({ id.Data(), m_pBuffer->TopAddress() });
        BASE_CHECK(complete
            , "Compile Error: Data double definition. Line:"s
            + std::to_string(CParser::get().GetLineNumber()));
        if (size == 0)
        {
            for (char c : values)
            {
                (*m_pBuffer) << static_cast<TCHAR>(c);
            }
        }
        else
        {
            BASE_CHECK (size >= static_cast<int>(std::size(values))
                , "Compile Error: Too many initialize variables Line:"s
                + std::to_string(CParser::get().GetLineNumber()));

            auto flag = size;
            for (char c : values)
            {
                --flag;
                (*m_pBuffer) << static_cast<TCHAR>(c);
            }

            for (;flag >= 0; --flag)
            {
                (*m_pBuffer) << static_cast<TCHAR>(0);
            }
        }

    });

    auto l = [this](CID id, int size, const auto& values)
    {
        using type = typename std::remove_reference_t<decltype(values)>::value_type;

        auto [it, complete] = m_mapDATAsAddresses.insert({ id.Data(), m_pBuffer->TopAddress() });
        BASE_CHECK(complete
            , "Compile Error: Data double definition. Line:"s
            + std::to_string(CParser::get().GetLineNumber()));
        if (size == 0)
        {
            for (char c : values)
            {
                (*m_pBuffer) << static_cast<type>(c);
            }
        }
        else
        {
            BASE_CHECK (size >= static_cast<int>(std::size(values))
                , "Compile Error: Too many initialize variables Line:"s
                + std::to_string(CParser::get().GetLineNumber()));

            auto flag = size;
            for (char c : values)
            {
                --flag;
                (*m_pBuffer) << static_cast<type>(c);
            }

            for (;flag >= 0; --flag)
            {
                (*m_pBuffer) << static_cast<type>(0);
            }
        }

    };

    parser.EventReadBYTEDeclaration.Add(l);
    parser.EventReadWORDDeclaration.Add(l);
    parser.EventReadDWORDDeclaration.Add(l);
    parser.EventReadQWORDDeclaration.Add(l);
}


void CCompiler::link()
{
    for (auto [id, add] : m_mapDATAsAddresses)
    {
        try
        {
            auto it = m_mapNotInitializedArgs.find(id);
            if (it != std::end(m_mapNotInitializedArgs))
            {
                for (auto arg_add : it->second)
                {
                    m_pBuffer->template operator[]<TAddress>(arg_add) = add;
                }
            }
        }
        catch (...)
        {
            BASE_THROW_ERROR ("Link Error: Undefined reference.")
        }
    }
}

void CCompiler::initDefinitions()
{
    // Stack size
    (m_pBuffer->template operator[]<TStackSize>(s_iStackSizeAddress)) = m_sDefinition.StackSize.value_or(1024);

    // Entry point
    try
    {
        const auto& strEntryPoint = m_sDefinition.EntryPoint;
        TAddress aEntryPoint = m_mapFunctionsAddresses.at(strEntryPoint);
        (m_pBuffer->template operator[]<TAddress>(s_iEntryPointAddress)) = aEntryPoint;
    }
    catch (...)
    {
        BASE_THROW_ERROR("Link Error: Undefined reference to the entry point.");
    }

    // DATA segment begin
    try
    {
        (m_pBuffer->template operator[]<TStackSize>(s_iDataSegmentBeginAddress)) = m_sDefinition.DataSegmentBegin.value();
    }
    catch(...)
    {
        BASE_THROW_ERROR("Link Error: Undefined reference to the DATA segment.");
    }

    // CODE segment begin
    try
    {
        (m_pBuffer->template operator[]<TStackSize>(s_iCodeSegmentBeginAddress)) = m_sDefinition.CodeSegmentBegin.value();
    }
    catch(...)
    {
        BASE_THROW_ERROR("Link Error: Undefined reference to the CODE segment.");
    }
}

} // namespace compiler