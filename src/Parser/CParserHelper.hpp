/**
 * @file CParserHelper.hpp
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CParserHelper class.
 * @date 03-12-2019
 * @copyright Copyright (c) 2019
 */


#pragma once

#include <vector>
#include <string_view>
#include <map>
#include <functional>
#include <iostream>

#include "Debug.h"
#include "ParserDecl.hpp"

class CParserHelper
{
    using EOperationSize = core::EOperationSize;
    using EOperationCode = core::EOperationCode;

public:

    enum class EArgType
    {
          Non
        , Reg
        , AddReg
        , Id
        , Num
        , Null
    };

private:
    using TArgTypeVec = std::vector<EArgType>;
    using TValueVec = std::vector<std::string>;
    using TLiteralsVec = std::vector<std::string>;
    using TArgPack = std::tuple<EArgType, EArgType>;
    using THandler = std::function<void(EOperationCode, EOperationSize, std::string_view, std::string_view)>;
    using TArgPackToHander = std::map<TArgPack, THandler>;

public:


    CParserHelper();

    void SetLineNumber(std::size_t iLineNumber);

    void Enqueue(EArgType type, std::string_view svValue);

    void SetOpSize(EOperationSize opSize) noexcept;

    void Clear();

    static CParserHelper& get();

    void StartFunctionDeclaration(std::string_view id);

    void EndFunctionDeclaration();

    void GenerateOperation(const EOperationCode eOpCode);

    void ReadLabel(CID id);

    void ReadCast();

    void ReadStackSize(std::size_t stackSize);

    void ReadEntryPoint(CID id);

    void ReadDataSegmentBegin();

    void ReadCodeSegmentBegin();

    void ReadDataType(core::EDataType sDataType);

    void AddToLiteralsList(std::string_view svLiteral);

    void ReadArraySize(std::string_view svSize);

    void SetVaiableID(std::string_view vaiableID);

    void GenerateVariableDeclaration();
private:

    TArgTypeVec m_vecArsQueue;
    TValueVec m_vecValuesQueue;
    TLiteralsVec m_vecLiterals;
    core::EDataType m_eDataType;
    CID m_cidVariableName;
    std::size_t m_stArraySize;
    EOperationSize m_eOpSizeFirst;
    EOperationSize m_eOpSizeSecond;
    static TArgPackToHander s_mapArgPackToHender;
};