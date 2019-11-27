%{
    #include "Debug.h"
    #include "ParserDecl.h"
    #include <iostream>
    #include <stdio.h>
    #include "y.tab.h"

    static std::string_view module = "lexer";

    std::size_t lineNumber = 1;
    long long yyint = 0;
    std::string_view yyid;
    OperationSize enumOpSize = OperationSize::B;

#define Loger(msg)  Debug::Log(module, lineNumber, msg, yytext); 

%}

%option nounput
%x INSTRUCTION

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
{newline}                   { Loger("New Line");       ++lineNumber; /* return NEW_LINE;*/ }


".STACK"                    { Loger("STACK");  return STACK;                  }
".DATA"                     { Loger("DATA");   return DATA;                   }
".CODE"                     { Loger("CODE");   return CODE;                   }
".MAIN"                     { Loger("MAIN");   return MAIN;                   }

"ASSIGN"                    { BEGIN(INSTRUCTION); Loger("ASSIGN"); return ASSIGN;                 }
"PRINT"                     { BEGIN(INSTRUCTION); Loger("PRINT");  return PRINT;                  }
"CMP"                       { BEGIN(INSTRUCTION); Loger("CMP");    return CMP;                    }
"TEST"                      { BEGIN(INSTRUCTION); Loger("TEST");   return TEST;                    }
"JUMP"                      { BEGIN(INSTRUCTION); Loger("JUMP");   return JUMP;                   }
"JZ"                        { BEGIN(INSTRUCTION); Loger("JZ");     return JZ;                     }
"JNZ"                       { BEGIN(INSTRUCTION); Loger("JNZ");    return JNZ;                    }
"JO"                        { BEGIN(INSTRUCTION); Loger("JO");     return JO;                     }
"JNO"                       { BEGIN(INSTRUCTION); Loger("JNO");    return JNO;                    }
"JC"                        { BEGIN(INSTRUCTION); Loger("JC");     return JC;                     }
"JNC"                       { BEGIN(INSTRUCTION); Loger("JNC");    return JNC;                    }
"JNE"                       { BEGIN(INSTRUCTION); Loger("JNE");    return JNE;                    }
"ADD"                       { BEGIN(INSTRUCTION); Loger("ADD");    return ADD;                    }
"SUB"                       { BEGIN(INSTRUCTION); Loger("SUB");    return SUB;                    }
"MUL"                       { BEGIN(INSTRUCTION); Loger("MUL");    return MUL;                    }
"IMUL"                      { BEGIN(INSTRUCTION); Loger("IMUL");   return IMUL;                    }
"DIV"                       { BEGIN(INSTRUCTION); Loger("DIV");    return DIV;                    }
"IDIV"                      { BEGIN(INSTRUCTION); Loger("IDIV");   return IDIV;                    }
"MOVE"                      { BEGIN(INSTRUCTION); Loger("MOVE");   return MOVE;                  }
"CALL"                      { BEGIN(INSTRUCTION); Loger("CALL");   return CALL;                   }
"PUSH"                      { BEGIN(INSTRUCTION); Loger("PUSH");   return PUSH;                   }
"POP"                       { BEGIN(INSTRUCTION); Loger("POP");    return POP;                    }
"PUSHSF"                    { BEGIN(INSTRUCTION); Loger("PUSHSF"); return PUSHSF;               }
"POPSF"                     { BEGIN(INSTRUCTION); Loger("POPSF");  return POPSF;                 }
"NOP"                       { BEGIN(INSTRUCTION); Loger("NOP");    return NOP;                     }
"SWAP"                      { BEGIN(INSTRUCTION); Loger("SWAP");   return SWAP;                   }
"AND"                       { BEGIN(INSTRUCTION); Loger("AND");    return AND;                   }
"GFLR"                      { BEGIN(INSTRUCTION); Loger("GFLR");   return GFLR;                   }
"SFLR"                      { BEGIN(INSTRUCTION); Loger("SFLR");   return SFLR;                   }
"INC"                       { BEGIN(INSTRUCTION); Loger("INC");    return INC;                   }
"DEC"                       { BEGIN(INSTRUCTION); Loger("DEC");    return DEC;                   }

"SHL"                       { BEGIN(INSTRUCTION); Loger("SHL");    return SHL;                   }
"SHR"                       { BEGIN(INSTRUCTION); Loger("SHR");    return SHR;                   }
"ROL"                       { BEGIN(INSTRUCTION); Loger("ROL");    return ROL;                   }
"ROR"                       { BEGIN(INSTRUCTION); Loger("ROR");    return ROR;                   }
"SAL"                       { BEGIN(INSTRUCTION); Loger("SAL");    return SAL;                   }
"SAR"                       { BEGIN(INSTRUCTION); Loger("SAR");    return SAR;                   }
"RCL"                       { BEGIN(INSTRUCTION); Loger("RCL");    return RCL;                   }
"RCR"                       { BEGIN(INSTRUCTION); Loger("RCR");    return RCR;                   }

"ADC"                       { BEGIN(INSTRUCTION); Loger("ADC");    return ADC;                   }
"SBB"                       { BEGIN(INSTRUCTION); Loger("SBB");    return SBB;                   }
"NEG"                       { BEGIN(INSTRUCTION); Loger("NEG");    return NEG;                   }
"CAST"                      { BEGIN(INSTRUCTION); Loger("CAST");   return CAST;                   }

"OUT"                       { BEGIN(INSTRUCTION); Loger("OUT");    return OUT;                   }
"IN"                        { BEGIN(INSTRUCTION); Loger("IN");     return IN;                   }

"LOAD"                      { BEGIN(INSTRUCTION); Loger("LOAD");   return LOAD;                   }
"STORE"                     { BEGIN(INSTRUCTION); Loger("STORE");  return STORE;                   }

"BREAK"                       { BEGIN(INSTRUCTION); Loger("BREAK");   return BREAK;                   }

<INSTRUCTION>
{
"R"{digit}+                 { Loger("Register"); yyint = std::stoi(yytext + 1); return REGISTER; }
"A"{digit}+                 { Loger("Address register"); yyint = std::stoi(yytext + 1); return ADDRESS_REGISTER; }

"B"                         { Loger("B");   enumOpSize = OperationSize::B;  return OPERATION_SIZE;                     }
"W"                         { Loger("W");   enumOpSize = OperationSize::W;  return OPERATION_SIZE;                     }
"DW"                        { Loger("DW");  enumOpSize = OperationSize::DW;  return OPERATION_SIZE;                    }
"QW"                        { Loger("QW");  enumOpSize = OperationSize::QW;  return OPERATION_SIZE;                    }

"\n"                        { enumOpSize = OperationSize::B; BEGIN(INITIAL); Loger("End instruction state"); ++lineNumber; }
}

"BYTE"                      { Loger("BYTE");   return BYTE;                   }
"CHAR"                      { Loger("CHAR");   return CHAR;                   }
"WORD"                      { Loger("WORD");   return WORD;                   }
"DWORD"                     { Loger("DWORD");  return DWORD;                  }
"QWORD"                     { Loger("QWORD");  return QWORD;                  }



"["                         { Loger("[");      return yytext[0];              }
"]"                         { Loger("]");      return yytext[0];              }
<*>";"                      { Loger(";");      return yytext[0];              }
":"                         { Loger(":");      return yytext[0];              }
","                         { Loger(",");      return yytext[0];              }
"="                         { Loger("=");      return yytext[0];              }
"!"                         { Loger("=");      return yytext[0];              }


"Func"                      { Loger("Func");      return FUNC;                }
"RET"                       { Loger("RET");    return RET;                    }
"EndF"                      { Loger("EndF");      return E_FUNC;              }


<*>[+-]?{digit}+               { 
                                // Parsing number
                                Loger("NUMBER");
                                yyint = std::stol(yytext);
                                return NUMBER; 
                            }
<*>"0x"[0-9a-fA-F]+            { Loger("HEX");     return NUMBER;                } // parsing hex number
<*>{letter}({letter}|{digit}|{und})* {
                                Loger("IDENTIFIER");
                                yyid = yytext;
                                return ID;
                            }


%%

int yywrap()
{
    return 1;
}