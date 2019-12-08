#pragma once

#include <vector>
#include <string>

#include "CParser.hpp"

using namespace std::string_literals;
using namespace std::string_view_literals;

TEST(ParserTest, StabilityParsing)
{
    auto& parser = CParser::get();
    parser.SetFileName("..//tests//input1.as");
    parser.StartParsing();
    parser.SetFileName("..//tests//input2.as");
    parser.StartParsing();
}

TEST(ParserTest, StackSizeParsing)
{
    std::vector<std::size_t> targets
    { 1024, 1, 3000, 1234, 0, 4444, 9797, 9999, 1111 };
    std::vector<std::size_t> results;
    auto lHandler = [&results](std::size_t size)
    {
        results.push_back(size);
    };
    auto& parser = CParser::get();
    parser.EventReadStackSize.Add(lHandler);
    parser.SetFileName("..//tests//UnitStackSize.as");
    parser.StartParsing();
    ASSERT_EQ(targets, results);
}

TEST(ParserTest, EntryPointParsing)
{
    std::vector<std::string> targets
    { "Main1", "Main2", "Main3", "Main4", "Main5", "Main6", "Main7", "Main8" };
    std::vector<std::string> results;
    auto lHandler = [&results](CID id)
    {
        results.push_back(id.Data());
    };
    auto& parser = CParser::get();
    parser.EventReadEntryPoint.Add(lHandler);
    parser.SetFileName("..//tests//UnitEntryPoint.as");
    parser.StartParsing();
    ASSERT_EQ(targets, results);
}

TEST(ParserTest, CharVariableDeclParsing)
{
    /**
     * @brief CHAR parsing test.
     */
    std::vector<std::tuple<std::string, std::size_t, std::string>> vecCharTargets
    {
          std::make_tuple("var"s, 0, ""s)
        , std::make_tuple("var"s, 0, ""s)
        , std::make_tuple("var"s, 0, ""s)
        , std::make_tuple("str1"s, 0, "Hello World!"s)
        , std::make_tuple("ch1"s, 0, "A"s)
    };
    std::vector<std::tuple<std::string, std::size_t, std::string>> charResults;
    auto lCharHandler = [&charResults](CID id, std::size_t size, std::string args)
    {
        charResults.push_back(std::make_tuple(id.Data(), size, std::move(args)));
    };

    auto& parser = CParser::get();
    parser.EventReadCHARDeclaration.Add(lCharHandler);
    parser.SetFileName("..//tests//UnitTypeDecl.as");
    parser.StartParsing();
    ASSERT_EQ(vecCharTargets, charResults);
    parser.Clear();
}

TEST(ParserTest, ByteVariableDeclParsing)
{
    /**
     * @brief BYTE parsing test.
     */

    using TVecArgsByte = std::vector<TBYTE>;

    std::vector<std::tuple<std::string, std::size_t, TVecArgsByte>> vecByteTargets
    {
          std::make_tuple("bVal1"s, 0, TVecArgsByte{})
        , std::make_tuple("bVal0"s, 0, TVecArgsByte{})
        , std::make_tuple("bVal1"s, 0, TVecArgsByte{ 1 })
        , std::make_tuple("bVal2"s, 0, TVecArgsByte{ 127 })
        , std::make_tuple("bVal3"s, 0, TVecArgsByte { 0x4F, 0x0F })
        , std::make_tuple("bVal4"s, 10, TVecArgsByte { 10, 20, 30, 40, 50, 60, 70, 80, 90, 0x10 })
    };
    std::vector<std::tuple<std::string, std::size_t, TVecArgsByte>> byteResults;
    auto lByteHandler = [&byteResults](CID id, std::size_t size, TVecArgsByte args)
    {
        byteResults.push_back(std::make_tuple(id.Data(), size, std::move(args)));
    };

    auto& parser = CParser::get();
    parser.EventReadBYTEDeclaration.Add(lByteHandler);
    parser.SetFileName("..//tests//UnitTypeDecl.as");
    parser.StartParsing();
    ASSERT_EQ(vecByteTargets, byteResults);
    parser.Clear();
}

TEST(ParserTest, WordVariableDeclParsing)
{
    /**
     * @brief WORD parsing test.
     */

    using TVecArgWord = std::vector<TWORD>;

    std::vector<std::tuple<std::string, std::size_t, TVecArgWord>> vecWordTargets
    {
          std::make_tuple("wVal1"s, 0, TVecArgWord{})
        , std::make_tuple("wVal1"s, 0, TVecArgWord{})
        , std::make_tuple("wVal2"s, 0, TVecArgWord{ 10000 })
        , std::make_tuple("wVal3"s, 0, TVecArgWord { 0x0100 })
        , std::make_tuple("wVal4"s, 5, TVecArgWord { 100, 200, 300, 400 })
    };
    std::vector<std::tuple<std::string, std::size_t, TVecArgWord>> wordResults;
    auto lWordHandler = [&wordResults](CID id, std::size_t size, TVecArgWord args)
    {
        wordResults.push_back(std::make_tuple(id.Data(), size, std::move(args)));
    };

    auto& parser = CParser::get();
    parser.EventReadWORDDeclaration.Add(lWordHandler);
    parser.SetFileName("..//tests//UnitTypeDecl.as");
    parser.StartParsing();
    ASSERT_EQ(vecWordTargets, wordResults);
    parser.Clear();
}

TEST(ParserTest, DWordVariableDeclParsing)
{
    /**
     * @brief DWORD parsing test.
     */

    using TVecArgDWord = std::vector<TDWORD>;

    std::vector<std::tuple<std::string, std::size_t, TVecArgDWord>> vecDWordTargets
    {
          std::make_tuple("dwVal1"s, 0, TVecArgDWord{ -1 })
        , std::make_tuple("dwVal2"s, 0, TVecArgDWord{ 10000000 })
        , std::make_tuple("dwVal3"s, 0, TVecArgDWord{ 0xA0B0C0D })
        , std::make_tuple("dwVal4"s, 5, TVecArgDWord { })
        , std::make_tuple("dwVal5"s, 4, TVecArgDWord { 0, 100, 0, 0xAAAAAAA })
    };
    std::vector<std::tuple<std::string, std::size_t, TVecArgDWord>> dWordResults;
    auto lDWordHandler = [&dWordResults](CID id, std::size_t size, TVecArgDWord args)
    {
        dWordResults.push_back(std::make_tuple(id.Data(), size, std::move(args)));
    };

    auto& parser = CParser::get();
    parser.EventReadDWORDDeclaration.Add(lDWordHandler);
    parser.SetFileName("..//tests//UnitTypeDecl.as");
    parser.StartParsing();
    ASSERT_EQ(vecDWordTargets, dWordResults);
    parser.Clear();
}

TEST(ParserTest, QWordVariableDeclParsing)
{
    /**
     * @brief QWORD parsing test.
     */

    using TVecArgQWord = std::vector<TQWORD>;

    std::vector<std::tuple<std::string, std::size_t, TVecArgQWord>> vecQWordTargets
    {
          std::make_tuple("qwVal1"s, 0, TVecArgQWord{ -10 })
        , std::make_tuple("qwVal2"s, 0, TVecArgQWord{ 10000000 })
        , std::make_tuple("qwVal3"s, 0, TVecArgQWord{ 0xA0B0C0D })
        , std::make_tuple("qwVal4"s, 5, TVecArgQWord { })
        , std::make_tuple("qwVal5"s, 0, TVecArgQWord { 0xFFFFFFFFFFFFFF })
        , std::make_tuple("qwVal6"s, 0, TVecArgQWord { 0x80000000000000 })
        , std::make_tuple("qwVal7"s, 4, TVecArgQWord { 0, 0xFFFF, 0, 188900967592960 })
    };
    std::vector<std::tuple<std::string, std::size_t, TVecArgQWord>> qWordResults;
    auto lQWordHandler = [&qWordResults](CID id, std::size_t size, TVecArgQWord args)
    {
        qWordResults.push_back(std::make_tuple(id.Data(), size, std::move(args)));
    };

    auto& parser = CParser::get();
    parser.EventReadQWORDDeclaration.Add(lQWordHandler);
    parser.SetFileName("..//tests//UnitTypeDecl.as");
    parser.StartParsing();
    ASSERT_EQ(vecQWordTargets, qWordResults);
    parser.Clear();
}

TEST(ParserTest, FunctionParsingTest)
{
    /**
     * @brief Function parsing test.
     */

    const std::vector<std::tuple<EOperationCode, EOperationSize, CID, CReg, CReg, CAddReg, CAddReg, CNum, bool>> vecTargets
    {
          std::make_tuple (EOperationCode::PUSHSF , EOperationSize::B, CID{ ""sv },      CReg{ 0 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::JUMP   , EOperationSize::B, CID{ "start"sv }, CReg{ 0 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::NOP    , EOperationSize::B, CID{ ""sv },      CReg{ 0 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::NOP    , EOperationSize::B, CID{ ""sv },      CReg{ 0 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::NOP    , EOperationSize::B, CID{ ""sv },      CReg{ 0 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::ASSIGN , EOperationSize::B, CID{ ""sv },      CReg{ 0 }, CReg{ 0 }, CAddReg{ 7 }, CAddReg{ 0 }, CNum{ 0 }, true)
        , std::make_tuple (EOperationCode::ASSIGN , EOperationSize::B, CID{ "F1"sv },    CReg{ 0 }, CReg{ 0 }, CAddReg{ 4 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::CALL   , EOperationSize::B, CID{ ""sv },      CReg{ 0 }, CReg{ 0 }, CAddReg{ 4 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::ASSIGN , EOperationSize::B, CID{ "F2"sv },    CReg{ 0 }, CReg{ 0 }, CAddReg{ 4 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::CALL   , EOperationSize::B, CID{ ""sv },      CReg{ 0 }, CReg{ 0 }, CAddReg{ 4 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::POPSF  , EOperationSize::B, CID{ ""sv },      CReg{ 0 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)

        , std::make_tuple (EOperationCode::ASSIGN , EOperationSize::B, CID{ ""sv },      CReg{ 1 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 4 }, false)
        , std::make_tuple (EOperationCode::SHL    , EOperationSize::W, CID{ ""sv },      CReg{ 6 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 5 }, false)
        , std::make_tuple (EOperationCode::SHR    , EOperationSize::W, CID{ ""sv },      CReg{ 6 }, CReg{ 1 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::ROL    , EOperationSize::W, CID{ ""sv },      CReg{ 6 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 7 }, false)
        , std::make_tuple (EOperationCode::ROR    , EOperationSize::W, CID{ ""sv },      CReg{ 6 }, CReg{ 1 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::SAL    , EOperationSize::W, CID{ ""sv },      CReg{ 6 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 3 }, false)
        , std::make_tuple (EOperationCode::SAR    , EOperationSize::W, CID{ ""sv },      CReg{ 6 }, CReg{ 1 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::RCL    , EOperationSize::W, CID{ ""sv },      CReg{ 6 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 1 }, false)
        , std::make_tuple (EOperationCode::RCR    , EOperationSize::W, CID{ ""sv },      CReg{ 6 }, CReg{ 1 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)

        , std::make_tuple (EOperationCode::ADC    , EOperationSize::B,  CID{ ""sv },     CReg{ 8 }, CReg{ 12 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::SBB    , EOperationSize::B,  CID{ ""sv },     CReg{ 8 }, CReg{ 12 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::MUL    , EOperationSize::B,  CID{ ""sv },     CReg{ 8 }, CReg{ 12 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::IMUL   , EOperationSize::B,  CID{ ""sv },     CReg{ 8 }, CReg{ 12 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::DIV    , EOperationSize::B,  CID{ ""sv },     CReg{ 8 }, CReg{ 12 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::IDIV   , EOperationSize::B,  CID{ ""sv },     CReg{ 8 }, CReg{ 12 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::NEG    , EOperationSize::QW, CID{ ""sv },     CReg{ 8 }, CReg{ 0 } , CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false)

        , std::make_tuple (EOperationCode::ASSIGN , EOperationSize::B,  CID{ "bVal1"sv } , CReg{ 0 }, CReg{ 0 } , CAddReg{ 4 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::ASSIGN , EOperationSize::B,  CID{ "wVal1"sv } , CReg{ 0 }, CReg{ 0 } , CAddReg{ 5 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::ASSIGN , EOperationSize::B,  CID{ "dwVal1"sv }, CReg{ 0 }, CReg{ 0 } , CAddReg{ 6 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::ASSIGN , EOperationSize::B,  CID{ "qwVal1"sv }, CReg{ 0 }, CReg{ 0 } , CAddReg{ 7 }, CAddReg{ 0 }, CNum{ 0 }, false)

        , std::make_tuple (EOperationCode::LOAD   , EOperationSize::B,   CID{ ""sv },     CReg{ 0 }, CReg{ 0 } , CAddReg{ 4 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::LOAD   , EOperationSize::W,   CID{ ""sv },     CReg{ 0 }, CReg{ 0 } , CAddReg{ 5 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::LOAD   , EOperationSize::DW,  CID{ ""sv },     CReg{ 0 }, CReg{ 0 } , CAddReg{ 6 }, CAddReg{ 0 }, CNum{ 0 }, false)
        , std::make_tuple (EOperationCode::LOAD   , EOperationSize::QW,  CID{ ""sv },     CReg{ 0 }, CReg{ 0 } , CAddReg{ 7 }, CAddReg{ 0 }, CNum{ 0 }, false)

        // , std::make_tuple (EOperationCode::RET    , EOperationSize::B)
    };


    std::vector<std::tuple<EOperationCode, EOperationSize, CID, CReg, CReg, CAddReg, CAddReg, CNum, bool>> vecOperations;

    bool bStart = false;
    bool bEnd = false;
    int iOpCount = 0;
    auto lFuncStartHandler = [&bStart](CID id)
    {
        bStart = true;
    };

    auto lFuncEndHandler = [&bEnd, &iOpCount, &vecOperations]()
    {
        iOpCount = std::size(vecOperations);
        bEnd = true;
    };


    auto lReadOp1 = [&vecOperations] (EOperationCode eOpCode)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, EOperationSize::B
                    , CID { ""sv }, CReg{ 0 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false));
    };
    auto lReadOp2 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CID id)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , id, CReg{ 0 }, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false));
    };
    auto lReadOp3 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CReg reg)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , CID { ""sv }, reg, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false));
    };
    auto lReadOp4 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CAddReg addReg)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , CID { ""sv }, CReg{ 0 }, CReg{ 0 }, addReg, CAddReg{ 0 }, CNum{ 0 }, false));
    };
    auto lReadOp5 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CReg reg1, CReg reg2)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , CID { ""sv }, reg1, reg2, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false));
    };
    auto lReadOp6 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CReg reg, CNum num)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , CID { ""sv }, reg, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, num, false));
    };
    auto lReadOp7 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CAddReg addReg1, CAddReg addReg2)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , CID { ""sv }, CReg{ 0 }, CReg{ 0 }, addReg1, addReg2, CNum{ 0 }, false));
    };
    auto lReadOp8 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CReg reg, CID id)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , id, reg, CReg{ 0 }, CAddReg{ 0 }, CAddReg{ 0 }, CNum{ 0 }, false));
    };
    auto lReadOp9 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CReg reg, CAddReg addReg)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , CID { ""sv }, reg, CReg{ 0 }, addReg, CAddReg{ 0 }, CNum{ 0 }, false));
    };
    auto lReadOp10 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CAddReg addReg, CReg reg)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , CID { ""sv }, reg, CReg{ 0 }, addReg, CAddReg{ 0 }, CNum{ 0 }, false));
    };
    auto lReadOp11 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CAddReg addReg, CID id)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , id, CReg{ 0 }, CReg{ 0 }, addReg, CAddReg{ 0 }, CNum{ 0 }, false));
    };
    auto lReadOp12 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CAddReg addReg, CNum num)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , CID { ""sv }, CReg{ 0 }, CReg{ 0 }, addReg, CAddReg{ 0 }, num, false));
    };
    auto lReadOp13 = [&vecOperations] (EOperationCode eOpCode, EOperationSize eOpSize, CAddReg addReg, CNull)
    {
        vecOperations.push_back(std::make_tuple(eOpCode, eOpSize
                    , CID { ""sv }, CReg{ 0 }, CReg{ 0 }, addReg, CAddReg{ 0 }, CNum{ 0 }, true));
    };

    auto& parser = CParser::get();
    parser.EventStartFunctionDecl.Add(lFuncStartHandler);
    parser.EventEndFunctionDecl.Add(lFuncEndHandler);

    parser.EventReadOperation.Add(lReadOp1);
    parser.EventReadOperationID.Add(lReadOp2);
    parser.EventReadOperationReg.Add(lReadOp3);
    parser.EventReadOperationAddReg.Add(lReadOp4);
    parser.EventReadOperationRegReg.Add(lReadOp5);
    parser.EventReadOperationRegNum.Add(lReadOp6);
    parser.EventReadOperationAddRegAddReg.Add(lReadOp7);
    parser.EventReadOperationRegID.Add(lReadOp8);
    parser.EventReadOperationRegAddReg.Add(lReadOp9);
    parser.EventReadOperationAddRegReg.Add(lReadOp10);
    parser.EventReadOperationAddRegID.Add(lReadOp11);
    parser.EventReadOperationAddRegNum.Add(lReadOp12);
    parser.EventReadOperationAddRegNull.Add(lReadOp13);

    parser.SetFileName("..//tests//UnitFunc.as");
    parser.StartParsing();
    parser.Clear();
    ASSERT_EQ(bStart, true);
    ASSERT_EQ(bEnd, true);
    ASSERT_EQ(vecOperations, vecTargets);
    ASSERT_EQ(iOpCount, std::size(vecOperations));
}

TEST(ParserTest, CASTParsing)
{
    /**
     * @brief CAST parsing test.
     */

    using TVecArgQWord = std::vector<TQWORD>;

    std::vector<std::tuple<EOperationSize, EOperationSize, CReg>> vecTarget
    {
          std::make_tuple(EOperationSize::W, EOperationSize::DW, CReg{ 4 })
        , std::make_tuple(EOperationSize::DW, EOperationSize::W, CReg{ 16 })
        , std::make_tuple(EOperationSize::QW, EOperationSize::DW, CReg{ 1 })
        , std::make_tuple(EOperationSize::B, EOperationSize::QW, CReg{ 7 })

    };
    std::vector<std::tuple<EOperationSize, EOperationSize, CReg>> vecResults;
    auto lHandler = [&vecResults](EOperationSize eOpSize1, EOperationSize eOpSize2, CReg reg)
    {
        vecResults.push_back(std::make_tuple(eOpSize1, eOpSize2, std::move(reg)));
    };

    auto& parser = CParser::get();
    parser.EventReadCast.Add(lHandler);
    parser.SetFileName("..//tests//UnitFunc.as");
    parser.StartParsing();
    ASSERT_EQ(vecTarget, vecResults);
    parser.Clear();
}
