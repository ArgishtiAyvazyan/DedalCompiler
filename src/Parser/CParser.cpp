#include "CParser.hpp"

#include <iostream>

#include "UIO.h"
#include "Debug.h"

static constexpr std::string_view svModule = "Paresr";

extern FILE* yyin;

int yyparse();

CParser::CParser()
    : m_svFileName()
{
}

CParser::~CParser()
{
    fclose(yyin);
    yyin = nullptr;
}


void CParser::SetFileName(std::string_view svFileName)
{
    m_svFileName = svFileName;
}

void CParser::StartParsing()
{
    gen::Debug::ASSERT(not m_svFileName.empty(), "File name is empty");

    yyin = fopen(m_svFileName.data(), "r");

    if (nullptr == yyin)
    {
        UIO::Write("Cannot open file.", svModule, MessageType::Error);
        exit(-2);
    }

    if (0 != yyparse())
    {
        UIO::Write("Unknown result.", svModule, MessageType::Error);
        exit(-3);
    }
    fclose(yyin);
    yyin = nullptr;
}

void CParser::Clear()
{
    EventReadOperation.Clear();
    EventReadOperationID.Clear();
    EventReadOperationReg.Clear();
    EventReadOperationAddReg.Clear();
    EventReadOperationRegReg.Clear();
    EventReadOperationRegNum.Clear();
    EventReadOperationAddRegAddReg.Clear();
    EventReadOperationRegID.Clear();
    EventReadOperationRegAddReg.Clear();
    EventReadOperationAddRegReg.Clear();
    EventReadOperationAddRegID.Clear();
    EventReadOperationAddRegNum.Clear();
    EventReadOperationAddRegNull.Clear();
    EventReadLabel.Clear();
    EventReadCast.Clear();
    EventReadStackSize.Clear();
    EventReadEntryPoint.Clear();
    EventReadDataSegmentBegin.Clear();
    EventReadCodeSegmentBegin.Clear();
    EventReadCHARDeclaration.Clear();
    EventReadBYTEDeclaration.Clear();
    EventReadWORDDeclaration.Clear();
    EventReadDWORDDeclaration.Clear();
    EventReadQWORDDeclaration.Clear();
}

void CParser::StartFunctionDeclaration(CID id)
{
    EventStartFunctionDecl.Invoke(id);
}

void CParser::EndFunctionDeclaration()
{
    EventEndFunctionDecl.Invoke();
}

void CParser::ReadOperation(EOperationCode eOpCode)
{
    EventReadOperation.Invoke(eOpCode);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CID arg)
{
    EventReadOperationID.Invoke(eOpCode, eOpSize, arg);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg)
{
    EventReadOperationReg.Invoke(eOpCode, eOpSize, arg);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg)
{
    EventReadOperationAddReg.Invoke(eOpCode, eOpSize, arg);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg1, CReg arg2)
{
    EventReadOperationRegReg.Invoke(eOpCode, eOpSize, arg1, arg2);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg1, CNum arg2)
{
    EventReadOperationRegNum.Invoke(eOpCode, eOpSize, arg1, arg2);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CAddReg arg2)
{
    EventReadOperationAddRegAddReg.Invoke(eOpCode, eOpSize, arg1, arg2);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg1, CID arg2)
{
    EventReadOperationRegID.Invoke(eOpCode, eOpSize, arg1, arg2);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg1, CAddReg arg2)
{
    EventReadOperationRegAddReg.Invoke(eOpCode, eOpSize, arg1, arg2);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CReg arg2)
{
    EventReadOperationAddRegReg.Invoke(eOpCode, eOpSize, arg1, arg2);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CID arg2)
{
    EventReadOperationAddRegID.Invoke(eOpCode, eOpSize, arg1, arg2);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CNum arg2)
{
    EventReadOperationAddRegNum.Invoke(eOpCode, eOpSize, arg1, arg2);
}

void CParser::ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CNull arg2)
{
    EventReadOperationAddRegNull.Invoke(eOpCode, eOpSize, arg1, arg2);
}

void CParser::ReadLabel(CID id)
{
    EventReadLabel.Invoke(id);
}

void CParser::ReadCast(EOperationSize eOpSize1, EOperationSize eOpSize2, CReg arg)
{
    EventReadCast.Invoke(eOpSize1, eOpSize2, arg);
}

void CParser::ReadStackSize(std::size_t stackSize)
{
    EventReadStackSize.Invoke(stackSize);
}

void CParser::ReadEntryPoint(CID id)
{
    EventReadEntryPoint.Invoke(id);
}

void CParser::ReadDataSegmentBegin()
{
    EventReadDataSegmentBegin.Invoke();
}

void CParser::ReadCodeSegmentBegin()
{
    EventReadCodeSegmentBegin.Invoke();
}

void CParser::ReadVariableDeclaration(CID id, std::size_t stSize, std::string vecInitializerList)
{
    EventReadCHARDeclaration.Invoke(id, stSize, vecInitializerList);
}

void CParser::ReadVariableDeclaration(CID id, std::size_t stSize, std::vector<std::int8_t> vecInitializerList)
{
    EventReadBYTEDeclaration.Invoke(id, stSize, vecInitializerList);
}

void CParser::ReadVariableDeclaration(CID id, std::size_t stSize, std::vector<std::int16_t> vecInitializerList)
{
    EventReadWORDDeclaration.Invoke(id, stSize, vecInitializerList);
}

void CParser::ReadVariableDeclaration(CID id, std::size_t stSize, std::vector<std::int32_t> vecInitializerList)
{
    EventReadDWORDDeclaration.Invoke(id, stSize, vecInitializerList);
}

void CParser::ReadVariableDeclaration(CID id, std::size_t stSize, std::vector<std::int64_t> vecInitializerList)
{
    EventReadQWORDDeclaration.Invoke(id, stSize, vecInitializerList);
}