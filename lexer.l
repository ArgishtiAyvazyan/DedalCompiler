%{
    #include "Debug.h"
    #include <iostream>
    #include<stdio.h>
    // #include<stdlib.h>
    
    inline std::size_t lineNumber = 0;

enum Token
{
      STACK = 1
    , DATA
    , CODE
    , MAIN


    , ASSIGN
    , PRINT
    , CMP
    , JUMP
    , JZ
    , JNZ
    , JO
    , JNO
    , JC
    , JNC
    , ADD
    , SUB
    , MUL
    , DIV
    , MOV
    , CALL
    , RET
    , END
    , PUSH
    , POP
    , LABEL

    // assembly types

    , BYTE
    , CHAR
    , WORD
    , DWORD
    , QWORD

    , STRING_LITERAL
    , CHAR_LITERAL

    , ID
    , NUMBER

    , FUNC
    , E_FUNC
};

#define Loger(msg) Debug::Log(std::string(msg) + " : " + yytext);

%}

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

"#".* { /* one line comment */ }

{space}* {}
{tab}* {}

{string}                    { Loger("STRING_LITERAL"); return STRING_LITERAL; }
{char}                      { Loger("CHAR_LITERAL");   return CHAR_LITERAL;   }
{newline}                   { Loger("New Line");     ++lineNumber;        }


".STACK"                    { Loger("STACK"); return STACK; }
".DATA"                     { Loger("DATA"); return DATA; }
".CODE"                     { Loger("CODE"); return CODE; }
".MAIN"                     { Loger("MAIN"); return MAIN; }

"ASSIGN"                    { Loger("ASSIGN"); return ASSIGN; }
"PRINT"                     { Loger("PRINT");  return PRINT; }
"CMP"                       { Loger("CMP");    return CMP; }
"JUMP"                      { Loger("JUMP");   return JUMP; }
"JZ"                        { Loger("JZ");     return JZ; }
"JNZ"                       { Loger("JNZ");    return JNZ; }
"JO"                        { Loger("JO");     return JO; }
"JNO"                       { Loger("JNO");    return JNO; }
"JC"                        { Loger("JC");     return JC; }
"JNC"                       { Loger("JNC");    return JNC; }
"ADD"                       { Loger("ADD");    return ADD; }
"SUB"                       { Loger("SUB");    return SUB; }
"MUL"                       { Loger("MUL");    return MUL; }
"DIV"                       { Loger("DIV");    return DIV; }
"MOV"                       { Loger("MOV");    return MOV; }
"CALL"                      { Loger("CALL");   return CALL; }
"RET"                       { Loger("RET");    return RET; }
"END"                       { Loger("END");    return END; }
"PUSH"                      { Loger("PUSH");   return PUSH; }
"POP"                       { Loger("POP");    return POP; }
"LABEL"                     { Loger("LABEL");  return LABEL; }

"BYTE"                      { Loger("BYTE");   return BYTE; }
"CHAR"                      { Loger("CHAR");   return CHAR; }
"WORD"                      { Loger("WORD");   return WORD; }
"DWORD"                     { Loger("DWORD");  return DWORD; }
"QWORD"                     { Loger("QWORD");  return QWORD; }



"["                         { Loger("[");      return yytext[0]; }
"]"                         { Loger("]");      return yytext[0]; }
";"                         { Loger(";");      return yytext[0]; }
":"                         { Loger(":");      return yytext[0]; }
","                         { Loger(",");      return yytext[0]; }
"="                         { Loger("=");      return yytext[0]; }
"!"                         { Loger("=");      return yytext[0]; }


"Func"                      { Loger("Func");      return FUNC; }
"EndF"                      { Loger("EndF");      return E_FUNC; }


[+-]?{digit}+               { Loger("NUMBER")   return NUMBER; } // Parsing number
"0x"[0-9a-fA-F]+            { Loger("HEX")     return NUMBER; } // parsing hex number
{letter}({letter}|{digit}|{und})* { Loger("IDENTIFIER"); return ID; };


%%



int main(int argc, char** argv)
{
    if (argc < 1)
    {
        Debug::Log("Input file is missing", LogType::Error);
        return -1;
    }

    if(!(yyin = fopen(argv[1], "r"))) {
        Debug::Log("Cannot open file.", LogType::Error);
        return -2;
    }
    while(yylex());

    return 0;
}

int yywrap()
{
    return 1;
}