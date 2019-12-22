/**
 * @file CParser.hpp
 * @author Argishti Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration of the element classes for a parser.
 * @date 01-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <string_view>

#include "CEvent.hpp"
#include "ParserDecl.hpp"

/**
 * @class CParser
 * @brief CParser is a singleton class that provides APIs for parsing assembler code.
 *
 * @details Class CParser Provides an interface for parsing assembler code; this is implemented in \n
 *           the style of an observer.
 */
class CParser
{
    using EOperationSize = core::EOperationSize;
    using EOperationCode = core::EOperationCode;

    friend class CParserHelper;

    template <typename ... TArgs>
    using CEvent = typename gen::CEvent<CParser, void(TArgs...)>;

    using TStartFunctionDeclEvent           = CEvent<CID>;
    using TEndFunctionDeclEvent             = CEvent<>;

    using TReadOperationEvent               = CEvent<EOperationCode>;
    using TReadOperationIDEvent             = CEvent<EOperationCode, EOperationSize, CID>;
    using TReadOperationRegEvent            = CEvent<EOperationCode, EOperationSize, CReg>;
    using TReadOperationAddRegEvent         = CEvent<EOperationCode, EOperationSize, CAddReg>;
    using TReadOperationRegRegEvent         = CEvent<EOperationCode, EOperationSize, CReg, CReg>;
    using TReadOperationRegNumEvent         = CEvent<EOperationCode, EOperationSize, CReg, CNum>;
    using TReadOperationAddRegAddRegEvent   = CEvent<EOperationCode, EOperationSize, CAddReg, CAddReg>;
    using TReadOperationRegIDEvent          = CEvent<EOperationCode, EOperationSize, CReg, CID>;
    using TReadOperationRegAddRegEvent      = CEvent<EOperationCode, EOperationSize, CReg, CAddReg>;
    using TReadOperationAddRegRegEvent      = CEvent<EOperationCode, EOperationSize, CAddReg, CReg>;
    using TReadOperationAddRegIDEvent       = CEvent<EOperationCode, EOperationSize, CAddReg, CID>;
    using TReadOperationAddRegNumEvent      = CEvent<EOperationCode, EOperationSize, CAddReg, CNum>;
    using TReadOperationAddRegNullEvent     = CEvent<EOperationCode, EOperationSize, CAddReg, CNull>;

    using TReadLabelEvent                   = CEvent<CID>;
    using TReadCastEvent                    = CEvent<EOperationSize, EOperationSize, CReg>;

    using TReadStackSizeEvent               = CEvent<std::size_t>;
    using TReadEntryPointEvent              = CEvent<CID>;
    using TReadDataSegmentBeginEvent        = CEvent<>;
    using TReadCodeSegmentBeginEvent        = CEvent<>;

    using TReadCHARDeclarationEvent         = CEvent<CID, std::size_t, std::string>;
    using TReadBYTEDeclarationEvent         = CEvent<CID, std::size_t, std::vector<core::TBYTE>>;
    using TReadWORDDeclarationEvent         = CEvent<CID, std::size_t, std::vector<core::TWORD>>;
    using TReadDWORDDeclarationEvent        = CEvent<CID, std::size_t, std::vector<core::TDWORD>>;
    using TReadQWORDDeclarationEvent        = CEvent<CID, std::size_t, std::vector<core::TQWORD>>;

public:

    TStartFunctionDeclEvent                 EventStartFunctionDecl;
    TEndFunctionDeclEvent                   EventEndFunctionDecl;

    TReadOperationEvent                     EventReadOperation;
    TReadOperationIDEvent                   EventReadOperationID;
    TReadOperationRegEvent                  EventReadOperationReg;
    TReadOperationAddRegEvent               EventReadOperationAddReg;
    TReadOperationRegRegEvent               EventReadOperationRegReg;
    TReadOperationRegNumEvent               EventReadOperationRegNum;
    TReadOperationAddRegAddRegEvent         EventReadOperationAddRegAddReg;
    TReadOperationRegIDEvent                EventReadOperationRegID;
    TReadOperationRegAddRegEvent            EventReadOperationRegAddReg;
    TReadOperationAddRegRegEvent            EventReadOperationAddRegReg;
    TReadOperationAddRegIDEvent             EventReadOperationAddRegID;
    TReadOperationAddRegNumEvent            EventReadOperationAddRegNum;
    TReadOperationAddRegNullEvent           EventReadOperationAddRegNull;

    TReadLabelEvent                         EventReadLabel;
    TReadCastEvent                          EventReadCast;

    TReadStackSizeEvent                     EventReadStackSize;
    TReadEntryPointEvent                    EventReadEntryPoint;
    TReadDataSegmentBeginEvent              EventReadDataSegmentBegin;
    TReadCodeSegmentBeginEvent              EventReadCodeSegmentBegin;

    TReadCHARDeclarationEvent               EventReadCHARDeclaration;
    TReadBYTEDeclarationEvent               EventReadBYTEDeclaration;
    TReadWORDDeclarationEvent               EventReadWORDDeclaration;
    TReadDWORDDeclarationEvent              EventReadDWORDDeclaration;
    TReadQWORDDeclarationEvent              EventReadQWORDDeclaration;

public:

    CParser();

    ~CParser();

    /**
     * @brief Set the assembly filename object. \n
     *         After call Starts Parsing, starts parsing assembly code.
     *
     * @param svFileName The file name.
     */
    void SetFileName(std::string_view svFileName);

    /**
     * @brief Starts parsing assembly.
     */
    void StartParsing();

    /**
     * @brief Clears all registered listeners.
     */
    void Clear();

    /**
     * @brief Gets CParser singleton instance.
     *
     * @return CParser The reference to CParser.
     */
    static CParser& get()
    {
        static CParser p;
        return p;
    }

    std::size_t GetLineNumber() const;

private:

    void SetLineNumber(const std::size_t iLineNumber);


    void StartFunctionDeclaration(CID id);

    void EndFunctionDeclaration();

    void ReadOperation(EOperationCode eOpCode);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CID arg);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg1, CReg arg2);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg1, CNum arg2);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CAddReg arg2);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg1, CID arg2);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CReg arg1, CAddReg arg2);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CReg arg2);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CID arg2);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CNum arg2);

    void ReadOperation(EOperationCode eOpCode, EOperationSize eOpSize, CAddReg arg1, CNull arg2);


    void ReadLabel(CID id);

    void ReadCast(EOperationSize sOpSize1, EOperationSize sOpSize2, CReg arg);

    void ReadStackSize(std::size_t stackSize);

    void ReadEntryPoint(CID id);

    void ReadDataSegmentBegin();

    void ReadCodeSegmentBegin();


////////////////////////////////////////////////////////////////////////////////////////////////////
////    .Data
////////////////////////////////////////////////////////////////////////////////////////////////////


    void ReadVariableDeclaration(CID id, std::size_t stSize, std::string vecInitializerList);

    void ReadVariableDeclaration(CID id, std::size_t stSize, std::vector<std::int8_t> vecInitializerList);

    void ReadVariableDeclaration(CID id, std::size_t stSize, std::vector<std::int16_t> vecInitializerList);

    void ReadVariableDeclaration(CID id, std::size_t stSize, std::vector<std::int32_t> vecInitializerList);

    void ReadVariableDeclaration(CID id, std::size_t stSize, std::vector<std::int64_t> vecInitializerList);


private:
    std::string_view m_svFileName;

    std::size_t m_iLineNumber;
};