%{
    #include "CParserHelper.hpp"
    #include <string>
    #include <vector>
    #include "Debug.h"
    #include "ParserDecl.hpp"
    #include "UIO.h"
    #include "Configs.hpp"
    #include "CParser.hpp"
    #include <iostream>
    #include <map>


    int yylex();
    void yyerror(const char* msg);


    extern std::size_t lineNumber;
    extern int yyint;
    extern char* yytext;
    extern std::string_view yyid;
    extern core::EOperationCode eOperationCode;
    static std::string_view module = "Parser";

static void Logger(std::string_view message)
{
    if constexpr (gen::Config::ENABLE_PARSER_LOGING)
    {
        const std::string sFullMessage = "Line : " + std::to_string(lineNumber) + " | " + message.data();
        UIO::Write(sFullMessage, module, MessageType::Debug);
    }
}

%}

%error-verbose

%token TK_STACK TK_DATA TK_CODE TK_MAIN
%token TK_OPERATION
%token TK_ASSIGN TK_PRINT TK_CMP TK_TEST TK_JUMP TK_JZ TK_JNZ TK_JO TK_JNO TK_JC TK_JNC TK_JNE TK_ADD TK_SUB TK_MUL TK_DIV
%token TK_MOVE TK_CALL TK_PUSH TK_POP TK_PUSHSF TK_POPSF TK_NOP TK_SWAP TK_AND TK_GFLR TK_SFLR TK_NULL
%token TK_SHL TK_SHR TK_ROL TK_ROR TK_SAL TK_SAR TK_RCL TK_RCR TK_ADC TK_SBB TK_IMUL TK_IDIV TK_NEG TK_LOAD TK_STORE
%token TK_INC TK_DEC TK_OUT TK_IN
%token TK_CAST

%token TK_REGISTER TK_ADDRESS_REGISTER TK_OPERATION_SIZE
%token TK_BYTE TK_CHAR TK_WORD TK_DWORD TK_QWORD
%token TK_STRING_LITERAL TK_CHAR_LITERAL TK_ID TK_NUMBER
%token TK_FUNC TK_E_FUNC TK_RET
%token TK_NEW_LINE

%token TK_BREAK

%start translation_unit

%%

translation_unit
    : segment
    | translation_unit segment
    ;


segment
    : TK_STACK stack_size
    | TK_DATA
    {
        CParserHelper::get().ReadDataSegmentBegin();
    }
    data_segment
    | TK_CODE
    {
        CParserHelper::get().ReadCodeSegmentBegin();
    }
    code_segment
    | TK_MAIN main_entry
    ;

stack_size
    : '=' TK_NUMBER ';'
    {
        Logger(" >>>> Stack size <<<< : " + std::to_string(yyint));
        CParserHelper::get().ReadStackSize(yyint);
    }
    ;

data_segment
    : variable_declaration
    | data_segment variable_declaration
    ;

variable_declaration
    : variable_type TK_ID ';'
    {
        // parsing variable type and name
        // ...
        Logger("-> variable_type ID");
        CParserHelper::get().GenerateVariableDeclaration();
    }
    | variable_type TK_ID '=' variable_initializer ';'
    {
        Logger("-> variable_type ID '=' variable_initializer");
        CParserHelper::get().GenerateVariableDeclaration();
    }
    | variable_type TK_ID '[' ']' '=' variable_initializer_list ';'
    {
        Logger("-> variable_type ID '[' ']' '=' variable_initializer_list");
        CParserHelper::get().GenerateVariableDeclaration();
    }
    | variable_type TK_ID '[' TK_NUMBER ']' ';'
    {
        Logger("-> variable_type ID '[' TK_NUMBER ']'");
        CParserHelper::get().GenerateVariableDeclaration();
    }
    | variable_type TK_ID '[' TK_NUMBER ']' '=' variable_initializer_list ';'
    {
        Logger("-> variable_type ID '[' TK_NUMBER ']' '=' variable_initializer_list");
        CParserHelper::get().GenerateVariableDeclaration();
    }
    ;

variable_type
    : TK_CHAR
    | TK_BYTE
    | TK_WORD
    | TK_DWORD
    | TK_QWORD
    ;

/* TODO : qnnarkerl = momendy. */
variable_initializer_list /* Parsing variable variable initializer list */
    : variable_initializer
    | variable_initializer_list ',' variable_initializer
    ;

variable_initializer
    : literal
    | { /* Empty initialization. */ }
    ;

literal
    : TK_STRING_LITERAL
    | TK_CHAR_LITERAL
    | TK_NUMBER
    ;

code_segment
    : code_segment function
    | function
    ;

function
    : TK_FUNC TK_ID
    {
        CParserHelper::get().StartFunctionDeclaration(yyid);
        Logger("-> function");
    } ':' instruction_list TK_RET ';' TK_E_FUNC
    {
        CParserHelper::get().EndFunctionDeclaration();
        Logger("-> end function");
    }
    {
        Logger("Function Definition");
    }
    | TK_FUNC TK_ID ';'
    {
        Logger("Function forward Declaration");
    }
    ;

instruction_list
    : instruction_list instruction
    | instruction
    ;

instruction
    : TK_OPERATION full_instruction_parametr_list ';'
    {
        CParserHelper::get().GenerateOperation(eOperationCode);
    }
    | TK_OPERATION ';'
    {
        CParserHelper::get().GenerateOperation(eOperationCode);
    }
    | TK_ID ':'
    {
        // CParserHelper::get().ReadLabel();
    }
    | TK_CAST TK_OPERATION_SIZE TK_OPERATION_SIZE TK_REGISTER ';'
    {
        CParserHelper::get().ReadCast();
    }
    ;


full_instruction_parametr_list
    : instruction_parametr_list
    | TK_OPERATION_SIZE instruction_parametr_list
    ;

instruction_parametr_list
    : TK_ID
    | TK_REGISTER
    | TK_REGISTER ',' TK_REGISTER
    | TK_REGISTER ',' TK_NUMBER
    | TK_REGISTER ',' TK_ID
    | TK_REGISTER ',' TK_ADDRESS_REGISTER
    | TK_ADDRESS_REGISTER
    | TK_ADDRESS_REGISTER ',' TK_REGISTER
    | TK_ADDRESS_REGISTER ',' TK_ADDRESS_REGISTER
    | TK_ADDRESS_REGISTER ',' TK_ID
    | TK_ADDRESS_REGISTER ',' TK_NUMBER
    | TK_ADDRESS_REGISTER ',' TK_NULL
    ;

main_entry
    : '=' TK_ID ';'
    {
        Logger(std::string("MAIN '='") + yyid.data());
        CParserHelper::get().ReadEntryPoint(yyid);
    }
    ;

%%


void yyerror(const char* msg)
{
    const std::string message = std::string(msg) + " Line : " + std::to_string(lineNumber)
        + "\n Last token : " + yytext + "\n";
    UIO::Write(message, module, MessageType::Error);
}
