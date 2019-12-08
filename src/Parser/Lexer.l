%{
    #include "CParserHelper.hpp"
    #include "Debug.h"
    #include "ParserDecl.hpp"
    #include <string>
    #include <stdio.h>
    #include "Parser.hpp"
    #include "Configs.hpp"
    #include "UIO.h"

    std::size_t lineNumber = 1;
    long long yyint = 0;
    std::string_view yyid;
    EOperationCode eOperationCode = EOperationCode::NON;
    static std::string_view module = "Lexer";

static void Logger(std::string_view message)
{
    if constexpr (gen::Config::ENABLE_LEXER_LOGING)
    {
        const std::string sFullMessage = "Line : " + std::to_string(lineNumber) + " | " + message.data();
        UIO::Write(sFullMessage, module, MessageType::Debug);
    }
}

%}

%option nounput
%x INSTRUCTION
%x INITIALIZER_LIST
%x INITIALIZER_LIST_COUNT

letter [A-Za-z]
digit [0-9]
und [_]
space [ ]
tab [	]
newline [\n]
char \'.\'
at [@]
string \".*\"

%%

<*>"#".* { /* one line comment */ }

<*>{space}* {}
<*>{tab}* {}

{string}                    { Logger("STRING_LITERAL"); return TK_STRING_LITERAL; }
{char}                      { Logger("CHAR_LITERAL");   return TK_CHAR_LITERAL;   }
{newline}                   { Logger("New Line");       ++lineNumber;          }


".STACK"                    { Logger("STACK");  return TK_STACK;                  }
".DATA"                     { Logger("DATA");   return TK_DATA;                   }
".CODE"                     { Logger("CODE");   return TK_CODE;                   }
".MAIN"                     { Logger("MAIN");   return TK_MAIN;                   }

"ASSIGN"                    { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::ASSIGN; Logger("ASSIGN"); return TK_OPERATION; }
"PRINT"                     { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::PRINT;  Logger("PRINT");  return TK_OPERATION; }
"CMP"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::CMP;    Logger("CMP");    return TK_OPERATION; }
"TEST"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::TEST;   Logger("TEST");   return TK_OPERATION; }
"JUMP"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::JUMP;   Logger("JUMP");   return TK_OPERATION; }
"JZ"                        { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::JZ;     Logger("JZ");     return TK_OPERATION; }
"JNZ"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::JNZ;    Logger("JNZ");    return TK_OPERATION; }
"JO"                        { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::JO;     Logger("JO");     return TK_OPERATION; }
"JNO"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::JNO;    Logger("JNO");    return TK_OPERATION; }
"JC"                        { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::JC;     Logger("JC");     return TK_OPERATION; }
"JNC"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::JNC;    Logger("JNC");    return TK_OPERATION; }
"JNE"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::JNE;    Logger("JNE");    return TK_OPERATION; }
"ADD"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::ADD;    Logger("ADD");    return TK_OPERATION; }
"SUB"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::SUB;    Logger("SUB");    return TK_OPERATION; }
"MUL"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::MUL;    Logger("MUL");    return TK_OPERATION; }
"IMUL"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::IMUL;   Logger("IMUL");   return TK_OPERATION; }
"DIV"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::DIV;    Logger("DIV");    return TK_OPERATION; }
"IDIV"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::IDIV;   Logger("IDIV");   return TK_OPERATION; }
"MOVE"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::MOVE;   Logger("MOVE");   return TK_OPERATION; }
"CALL"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::CALL;   Logger("CALL");   return TK_OPERATION; }
"PUSH"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::PUSH;   Logger("PUSH");   return TK_OPERATION; }
"POP"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::POP;    Logger("POP");    return TK_OPERATION; }
"PUSHSF"                    { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::PUSHSF; Logger("PUSHSF"); return TK_OPERATION; }
"POPSF"                     { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::POPSF;  Logger("POPSF");  return TK_OPERATION; }
"NOP"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::NOP;    Logger("NOP");    return TK_OPERATION; }
"SWAP"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::SWAP;   Logger("SWAP");   return TK_OPERATION; }
"AND"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::AND;    Logger("AND");    return TK_OPERATION; }
"GFLR"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::GFLR;   Logger("GFLR");   return TK_OPERATION; }
"SFLR"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::SFLR;   Logger("SFLR");   return TK_OPERATION; }
"INC"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::INC;    Logger("INC");    return TK_OPERATION; }
"DEC"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::DEC;    Logger("DEC");    return TK_OPERATION; }

"SHL"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::SHL;    Logger("SHL");    return TK_OPERATION; }
"SHR"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::SHR;    Logger("SHR");    return TK_OPERATION; }
"ROL"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::ROL;    Logger("ROL");    return TK_OPERATION; }
"ROR"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::ROR;    Logger("ROR");    return TK_OPERATION; }
"SAL"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::SAL;    Logger("SAL");    return TK_OPERATION; }
"SAR"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::SAR;    Logger("SAR");    return TK_OPERATION; }
"RCL"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::RCL;    Logger("RCL");    return TK_OPERATION; }
"RCR"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::RCR;    Logger("RCR");    return TK_OPERATION; }

"ADC"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::ADC;    Logger("ADC");    return TK_OPERATION; }
"SBB"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::SBB;    Logger("SBB");    return TK_OPERATION; }
"NEG"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::NEG;    Logger("NEG");    return TK_OPERATION; }

"OUT"                       { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::OUT;    Logger("OUT");    return TK_OPERATION; }
"IN"                        { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::IN;     Logger("IN");     return TK_OPERATION; }

"LOAD"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::LOAD;   Logger("LOAD");   return TK_OPERATION; }
"STORE"                     { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::STORE;  Logger("STORE");  return TK_OPERATION; }

"BREAK"                     { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::BREAK;  Logger("BREAK");  return TK_OPERATION; }

"CAST"                      { BEGIN(INSTRUCTION); eOperationCode = EOperationCode::CAST;   Logger("CAST");   return TK_CAST;      }

<INSTRUCTION>
{

"R"{digit}+                 {
                                Logger("Register");
                                CParserHelper::get().Enqueue(CParserHelper::EArgType::Reg, yytext + 1);
                                return TK_REGISTER;
                            }
"A"{digit}+                 {
                                Logger("Address register");
                                CParserHelper::get().Enqueue(CParserHelper::EArgType::AddReg, yytext + 1);
                                return TK_ADDRESS_REGISTER;
                            }

[+-]?{digit}+               {
                                // Parsing number
                                Logger("NUMBER");
                                yyint = std::stol(yytext);
                                CParserHelper::get().Enqueue(CParserHelper::EArgType::Num, yytext);
                                return TK_NUMBER;
                            }

"B"                         {
                                Logger("B");
                                CParserHelper::get().SetOpSize(EOperationSize::B);
                                return TK_OPERATION_SIZE;
                            }
"W"                         {
                                Logger("W");
                                CParserHelper::get().SetOpSize(EOperationSize::W);
                                return TK_OPERATION_SIZE;
                            }
"DW"                        {
                                Logger("DW");
                                CParserHelper::get().SetOpSize(EOperationSize::DW);
                                return TK_OPERATION_SIZE;
                            }
"QW"                        {
                                Logger("QW");
                                CParserHelper::get().SetOpSize(EOperationSize::QW);
                                return TK_OPERATION_SIZE;
                            }

"null"                      {
                                Logger("null");
                                CParserHelper::get().Enqueue(CParserHelper::EArgType::Null, "");
                                return TK_NULL;
                            }

{letter}({letter}|{digit}|{und})* {
                                Logger("IDENTIFIER");
                                yyid = yytext;
                                CParserHelper::get().Enqueue(CParserHelper::EArgType::Id, yytext);
                                return TK_ID;
                            }


"\n"                        {
                                CParserHelper::get().Clear();
                                CParserHelper::get().SetOpSize(EOperationSize::B);
                                BEGIN(INITIAL);
                                Logger("End instruction state");
                                ++lineNumber;
                            }
}

"BYTE"                      {
                                BEGIN(INITIALIZER_LIST);
                                CParserHelper::get().ReadDataType(EDataType::BYTE);
                                Logger("BYTE");
                                return TK_BYTE;
                            }
"CHAR"                      {
                                BEGIN(INITIALIZER_LIST);
                                CParserHelper::get().ReadDataType(EDataType::CHAR);
                                Logger("CHAR");
                                return TK_CHAR;
                            }
"WORD"                      {
                                BEGIN(INITIALIZER_LIST);
                                CParserHelper::get().ReadDataType(EDataType::WORD);
                                Logger("WORD");
                                return TK_WORD;
                            }
"DWORD"                     {
                                BEGIN(INITIALIZER_LIST);
                                CParserHelper::get().ReadDataType(EDataType::DWORD);
                                Logger("DWORD");
                                return TK_DWORD;
                           }
"QWORD"                     {
                                BEGIN(INITIALIZER_LIST);
                                CParserHelper::get().ReadDataType(EDataType::QWORD);
                                Logger("QWORD");
                                return TK_QWORD;
                           }


<INITIALIZER_LIST>
{
{string}                    {
                                Logger("INITIALIZER_LIST STRING_LITERAL");
                                std::string_view arg = yytext;
                                std::string_view result = arg.substr(1, arg.length() - 2);
                                CParserHelper::get().AddToLiteralsList(result);
                                Logger(std::string(yytext) + " <<<<<<");
                                return TK_STRING_LITERAL;
                            }
{char}                      {
                                Logger("INITIALIZER_LIST CHAR_LITERAL");
                                std::string_view arg = yytext;
                                std::string_view result = arg.substr(1, arg.length() - 2);
                                CParserHelper::get().AddToLiteralsList(result);
                                Logger(std::string(yytext) + " <<<<<<");
                                return TK_CHAR_LITERAL;
                            }
{newline}                   {
                                Logger("INITIALIZER_LIST New Line");
                                CParserHelper::get().Clear();
                                BEGIN(INITIAL);
                                ++lineNumber;
                            }

{letter}({letter}|{digit}|{und})* {
                                Logger("INITIALIZER_LIST IDENTIFIER");
                                CParserHelper::get().SetVaiableID(yytext);
                                return TK_ID;
                            }

[+-]?{digit}+               {
                                Logger("INITIALIZER_LIST NUMBER");
                                CParserHelper::get().AddToLiteralsList(yytext);
                                return TK_NUMBER;
                            }
"0x"[0-9a-fA-F]+            {
                                Logger("INITIALIZER_LIST HEX");
                                CParserHelper::get().AddToLiteralsList(yytext);
                                return TK_NUMBER;
                            }

"["                         {
                                Logger("[");
                                BEGIN(INITIALIZER_LIST_COUNT);
                                return yytext[0];
                            }

<INITIALIZER_LIST_COUNT>
{
[+-]?{digit}+               {
                                Logger("INITIALIZER_LIST_COUNT NUMBER");
                                CParserHelper::get().ReadArraySize(yytext);
                                return TK_NUMBER;
                            }
"]"                         {
                                Logger("]");
                                BEGIN(INITIALIZER_LIST);
                                return yytext[0];
                            }
}
f
}


"["                         { Logger("[");  return yytext[0]; }
"]"                         { Logger("]");  return yytext[0]; }
<*>";"                      { Logger(";");  return yytext[0]; }
":"                         { Logger(":");  return yytext[0]; }
<*>","                      { Logger(",");  return yytext[0]; }
<*>"="                      { Logger("=");  return yytext[0]; }
"!"                         { Logger("=");  return yytext[0]; }


"Func"                      { Logger("Func"); return TK_FUNC;   }
"RET"                       {
                                Logger("RET");
                                eOperationCode = EOperationCode::RET;
                                return TK_RET;
                            }
"EndF"                      { Logger("EndF"); return TK_E_FUNC; }


[+-]?{digit}+               {
                                // Parsing number
                                Logger("NUMBER");
                                yyint = std::stol(yytext);
                                return TK_NUMBER;
                            }
<*>"0x"[0-9a-fA-F]+         {  // TODO parsing hex number
                                Logger("HEX");
                                return TK_NUMBER;
                            }
{letter}({letter}|{digit}|{und})* {
                                Logger("IDENTIFIER");
                                yyid = yytext;
                                return TK_ID;
                            }


%%

int yywrap()
{
    return 1;
}
