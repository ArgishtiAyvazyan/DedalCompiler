/**
 * @file CParserHelper.cpp
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Implementation for CParserHelper class.
 * @date 03-12-2019
 * @copyright Copyright (c) 2019
 */


#include "CParserHelper.hpp"

#include <boost/numeric/conversion/cast.hpp>
#include <boost/lexical_cast.hpp>

#include "CParser.hpp"


using boost::lexical_cast;
using boost::numeric_cast;



CParserHelper::CParserHelper()
    : m_vecArsQueue(2)
    , m_vecValuesQueue(2)
    , m_eOpSizeFirst()
    , m_eOpSizeSecond()
{
}

void CParserHelper::SetLineNumber(std::size_t iLineNumber)
{
    CParser::get().SetLineNumber(iLineNumber);
}

void CParserHelper::Enqueue(EArgType type, std::string_view svValue)
{
    m_vecArsQueue.push_back(type);
    m_vecValuesQueue.push_back(static_cast<std::string>(svValue));
    gen::Debug::ASSERT(m_vecArsQueue.size() == m_vecValuesQueue.size());
}

void CParserHelper::SetOpSize(EOperationSize opSize) noexcept
{
    m_eOpSizeSecond = m_eOpSizeFirst;
    m_eOpSizeFirst = opSize;
}

void CParserHelper::Clear()
{
    m_vecArsQueue.clear();
    m_vecValuesQueue.clear();
    m_vecLiterals.clear();
    m_stArraySize = 0;
}

CParserHelper& CParserHelper::get()
{
    static CParserHelper ph;
    return ph;
}

void CParserHelper::StartFunctionDeclaration(std::string_view id)
{
    CParser::get().StartFunctionDeclaration(CID(id));
}

void CParserHelper::EndFunctionDeclaration()
{
    CParser::get().EndFunctionDeclaration();
}

void CParserHelper::GenerateOperation(const EOperationCode eOpCode)
{
    const auto iArgCount = std::size(m_vecArsQueue);
    gen::Debug::ASSERT(iArgCount <= 2, "Invalid arguments count.");
    try
    {
        TArgPack tupArgPack;
        switch (iArgCount)
        {
            case 0:
                tupArgPack = std::make_tuple(EArgType::Non, EArgType::Non);
                break;
            case 1:
                tupArgPack = std::make_tuple(m_vecArsQueue[0], EArgType::Non);
                break;
            case 2:
                tupArgPack = std::make_tuple(m_vecArsQueue[0], m_vecArsQueue[1]);
                break;
            default:
                gen::Debug::ASSERT(false, "Invalid arguments count.");
        }

        auto& handler = s_mapArgPackToHender.at(tupArgPack);
        handler(eOpCode, m_eOpSizeFirst, m_vecValuesQueue[0], m_vecValuesQueue[1]);
    }
    catch (...)
    {
        gen::Debug::ASSERT(false, "Unhandled sequence arguments.");
    }


    Clear();
}

void CParserHelper::ReadLabel(CID id)
{
    CParser::get().ReadLabel(id);
}

void CParserHelper::ReadCast()
{
    CParser::get().ReadCast(m_eOpSizeSecond, m_eOpSizeFirst, CReg(m_vecValuesQueue.back()));
}

void CParserHelper::ReadStackSize(std::size_t stackSize)
{
    CParser::get().ReadStackSize(stackSize);
}

void CParserHelper::ReadEntryPoint(CID id)
{
    CParser::get().ReadEntryPoint(id);
}

void CParserHelper::ReadDataSegmentBegin()
{
    CParser::get().ReadDataSegmentBegin();
}

void CParserHelper::ReadCodeSegmentBegin()
{
    CParser::get().ReadCodeSegmentBegin();
}

void CParserHelper::ReadDataType(core::EDataType sDataType)
{
    m_eDataType = sDataType;
}

void CParserHelper::AddToLiteralsList(std::string_view svLiteral)
{
    m_vecLiterals.push_back(static_cast<std::string>(svLiteral));
}

void CParserHelper::ReadArraySize(std::string_view svSize)
{
    m_stArraySize = std::stoi(svSize.data());
}

void CParserHelper::SetVaiableID(std::string_view vaiableID)
{
    m_cidVariableName = vaiableID;
}


void CParserHelper::GenerateVariableDeclaration()
{
    auto lConverter = [this](auto inArg)
    {
        using TValue = decltype(inArg);
        std::vector<TValue> list;
        list.resize(std::size(m_vecLiterals));
        std::transform(std::begin(m_vecLiterals)
                    , std::end(m_vecLiterals)
                    , std::begin(list)
                    , [](const std::string_view val)
                    {
                        TValue res;
                        try
                        {
                            try
                            {
                                res = numeric_cast<TValue>(lexical_cast<core::TQWORD>(val.data()));
                            } catch (...)
                            {
                                res = numeric_cast<TValue>(std::strtol(val.data(), nullptr, 16));
                            }
                        }
                        catch(...)
                        {
                            std::cout << val.data() << std::endl;
                            gen::Debug::ASSERT(false, "Invalid arguments size.");
                        }
                        return res;
                    });
        CParser::get().ReadVariableDeclaration(m_cidVariableName, m_stArraySize, list);
    };
    switch (m_eDataType)
    {
        case core::EDataType::CHAR:
            {
                std::string list;
                if (not m_vecLiterals.empty())
                {
                    list = static_cast<std::string>(m_vecLiterals[0]);
                    gen::Debug::ASSERT(m_vecLiterals.size() == 1, "Unknawn error!");
                }
                CParser::get().ReadVariableDeclaration(m_cidVariableName, m_stArraySize, list);
                break;
            }
        case core::EDataType::BYTE:
            {
                lConverter(core::TBYTE());
            }
         break;
        case core::EDataType::WORD:
            {
                lConverter(core::TWORD());
            }
         break;
        case core::EDataType::DWORD:
            {
                lConverter(core::TDWORD());
            }
         break;
        case core::EDataType::QWORD:
            {
                lConverter(core::TQWORD());
            }
         break;
        default:
            gen::Debug::ASSERT(false, "Unknown data type.");
    }
    Clear();
}

CParserHelper::TArgPackToHander CParserHelper::s_mapArgPackToHender
{
    std::make_pair(std::make_tuple(EArgType::Non, EArgType::Non)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode);
        }),
    std::make_pair(std::make_tuple(EArgType::Id, EArgType::Non)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CID(arg1));
        }),
    std::make_pair(std::make_tuple(EArgType::Reg, EArgType::Non)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CReg(arg1));
        }),
    std::make_pair(std::make_tuple(EArgType::Reg, EArgType::Reg)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CReg(arg1), CReg(arg2));
        }),
    std::make_pair(std::make_tuple(EArgType::Reg, EArgType::Num)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CReg(arg1), CNum(arg2));
        }),
    std::make_pair(std::make_tuple(EArgType::Reg, EArgType::Id)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CReg(arg1), CID(arg2));
        }),
    std::make_pair(std::make_tuple(EArgType::Reg, EArgType::AddReg)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CReg(arg1), CAddReg(arg2));
        }),
    std::make_pair(std::make_tuple(EArgType::AddReg, EArgType::Non)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CAddReg(arg1));
        }),
    std::make_pair(std::make_tuple(EArgType::AddReg, EArgType::Reg)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CAddReg(arg1), CReg(arg2));
        }),
    std::make_pair(std::make_tuple(EArgType::AddReg, EArgType::AddReg)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CAddReg(arg1), CAddReg(arg2));
        }),
    std::make_pair(std::make_tuple(EArgType::AddReg, EArgType::Id)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CAddReg(arg1), CID(arg2));
        }),
    std::make_pair(std::make_tuple(EArgType::AddReg, EArgType::Num)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CAddReg(arg1), CNum(arg2));
        }),
    std::make_pair(std::make_tuple(EArgType::AddReg, EArgType::Null)
        , [](EOperationCode eOpCode, EOperationSize eOpSize, std::string_view arg1, std::string_view arg2)
        {
            CParser::get().ReadOperation(eOpCode, eOpSize, CAddReg(arg1), CNull());
        }),
};