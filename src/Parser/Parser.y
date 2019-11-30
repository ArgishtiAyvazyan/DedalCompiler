%{
    #include <iostream>
    #include "Debug.h"
    #include "ParserDecl.h"
    #include "UIO.h"
    #include "Configs.hpp"



    int yylex();
    void yyerror(const char* msg);


    extern std::size_t lineNumber;
    extern int yyint;
    extern char* yytext;
    extern std::string_view yyid;

    static std::string_view module = "Parser";

static void Logger(std::string_view message)
{
    if constexpr (Config::ENABLE_PARSER_LOGING)
    {
        const std::string sFullMessage = "Line : " + std::to_string(lineNumber) + " | " + message.data();
        UIO::Write(sFullMessage, module, MessageType::Debug);
    }
}

%}

%error-verbose

%token STACK DATA CODE MAIN
%token ASSIGN PRINT CMP TEST JUMP JZ JNZ JO JNO JC JNC JNE ADD SUB MUL DIV
%token MOVE CALL PUSH POP PUSHSF POPSF NOP SWAP AND GFLR SFLR
%token SHL SHR ROL ROR SAL SAR RCL RCR ADC SBB IMUL IDIV NEG LOAD STORE
%token INC DEC OUT IN
%token CAST

%token REGISTER ADDRESS_REGISTER OPERATION_SIZE
%token BYTE CHAR WORD DWORD QWORD
%token STRING_LITERAL CHAR_LITERAL ID NUMBER
%token FUNC E_FUNC RET
%token NEW_LINE

%token BREAK

%start translation_unit

%%

translation_unit
    : segment
    | translation_unit segment
    ;


segment
    : STACK stack_size
    | DATA data_segment
    | CODE code_segment
    | MAIN main_entry
    ;

stack_size
    : '=' NUMBER ';'
    {
        Logger(" >>>> Stack size <<<< : " + std::to_string(yyint));
    }
    ;

data_segment
    : variable_declaration
    | data_segment variable_declaration
    ;

variable_declaration
    : variable_type ID ';'
    {
        // parsing variable type and name
        // ...
        Logger("-> variable_type ID");
    }
    | variable_type ID '=' variable_initializer ';'
    {
        Logger("-> variable_type ID '=' variable_initializer");
    }
    | variable_type ID '[' ']' '=' variable_initializer_list ';'
    {
        Logger("-> variable_type ID '[' ']' '=' variable_initializer_list");
    }
    | variable_type ID '[' NUMBER ']' ';'
    {
        Logger("-> variable_type ID '[' NUMBER ']'");
    }
    | variable_type ID '[' NUMBER ']' '=' variable_initializer_list ';'
    {
        Logger("-> variable_type ID '[' NUMBER ']' '=' variable_initializer_list");
    }
    ;

variable_type
    : CHAR
    | BYTE
    | WORD
    | DWORD
    | QWORD
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
    : STRING_LITERAL
    | CHAR_LITERAL
    | NUMBER
    ;

code_segment
    : code_segment function
    | function
    ;

function
    : FUNC ID ':' instruction_list RET ';' E_FUNC
    {
        Logger("Function Definition");
    }
    | FUNC ID ';'
    {
        Logger("Function forward Declaration");
    }
    ;

instruction_list
    : instruction_list instruction
    | instruction
    ;

instruction
    : ASSIGN full_instruction_parametr_list ';'
    | PRINT
    | CMP full_instruction_parametr_list ';'
    | TEST full_instruction_parametr_list ';'
    | JUMP ID ';'
    {
        Logger("Parse jump instruction.");
    }
    | JZ ID ';'
    | JNZ ID ';'
    | JO ID ';'
    | JNO ID ';'
    | JC ID ';'
    | JNC ID ';'
    | JNE ID ';'
    | ADD full_instruction_parametr_list ';'
    | SUB full_instruction_parametr_list ';'
    | MUL full_instruction_parametr_list ';'
    | IMUL full_instruction_parametr_list ';'
    | DIV full_instruction_parametr_list ';'
    | IDIV full_instruction_parametr_list ';'
    | MOVE full_instruction_parametr_list ';'
    | CALL ADDRESS_REGISTER ';'
    | PUSH full_instruction_parametr_list ';'
    | POP full_instruction_parametr_list ';'
    | PUSHSF ';'
    | POPSF ';'
    | ID ':'
    | NOP ';'
    {
        // Empty instruction.
    }
    | SWAP full_instruction_parametr_list ';'
    | AND full_instruction_parametr_list ';'
    | GFLR full_instruction_parametr_list ';'
    | SFLR full_instruction_parametr_list ';'
    | INC full_instruction_parametr_list ';'
    | DEC full_instruction_parametr_list ';'
    | SHL full_instruction_parametr_list ';'
    | SHR full_instruction_parametr_list ';'
    | ROL full_instruction_parametr_list ';'
    | ROR full_instruction_parametr_list ';'
    | SAL full_instruction_parametr_list ';'
    | SAR full_instruction_parametr_list ';'
    | RCL full_instruction_parametr_list ';'
    | RCR full_instruction_parametr_list ';'
    | ADC full_instruction_parametr_list ';'
    | SBB full_instruction_parametr_list ';'
    | NEG full_instruction_parametr_list ';'
    | CAST OPERATION_SIZE OPERATION_SIZE REGISTER ';'
    | LOAD full_instruction_parametr_list ';'
    | STORE full_instruction_parametr_list ';'
    | OUT full_instruction_parametr_list ';'
    | IN full_instruction_parametr_list ';'
    | BREAK ';'
    ;

full_instruction_parametr_list
    : instruction_parametr_list
    | OPERATION_SIZE instruction_parametr_list
    ;

instruction_parametr_list
    : REGISTER instruction_parametr_list
    | ADDRESS_REGISTER instruction_parametr_list
    | REGISTER
    | ADDRESS_REGISTER
    | ID
    | NUMBER
    ;

main_entry
    : '=' ID ';'
    {
        Logger(std::string("MAIN '='") + yyid.data());
    }
    ;

%%


void yyerror(const char* msg)
{
    const std::string message = std::string(msg) + " Line : " + std::to_string(lineNumber)
        + "\n Last token : " + yytext + "\n";
    UIO::Write(message, module, MessageType::Error);
}