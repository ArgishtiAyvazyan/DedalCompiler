%{
    #include "Debug.h"
    #include "ParserDecl.h"
    #include <iostream>
    #include <stdio.h>
    #include "Parser.hpp"
    #include "Configs.hpp"
    #include "UIO.h"

    std::size_t lineNumber = 1;
    long long yyint = 0;
    std::string_view yyid;
    OperationSize enumOpSize = OperationSize::B;

    static std::string_view module = "Lexer";

static void Logger(std::string_view message)
{
    if constexpr (Config::ENABLE_LEXER_LOGING)
    {
        const std::string sFullMessage = "Line : " + std::to_string(lineNumber) + " | " + message.data();
        UIO::Write(sFullMessage, module, MessageType::Debug);
    }
}

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

{string}                    { Logger("STRING_LITERAL"); return STRING_LITERAL; }
{char}                      { Logger("CHAR_LITERAL");   return CHAR_LITERAL;   }
{newline}                   { Logger("New Line");       ++lineNumber;          }


".STACK"                    { Logger("STACK");  return STACK;                  }
".DATA"                     { Logger("DATA");   return DATA;                   }
".CODE"                     { Logger("CODE");   return CODE;                   }
".MAIN"                     { Logger("MAIN");   return MAIN;                   }

"ASSIGN"                    { BEGIN(INSTRUCTION); Logger("ASSIGN"); return ASSIGN;                 }
"PRINT"                     { BEGIN(INSTRUCTION); Logger("PRINT");  return PRINT;                  }
"CMP"                       { BEGIN(INSTRUCTION); Logger("CMP");    return CMP;                    }
"TEST"                      { BEGIN(INSTRUCTION); Logger("TEST");   return TEST;                   }
"JUMP"                      { BEGIN(INSTRUCTION); Logger("JUMP");   return JUMP;                   }
"JZ"                        { BEGIN(INSTRUCTION); Logger("JZ");     return JZ;                     }
"JNZ"                       { BEGIN(INSTRUCTION); Logger("JNZ");    return JNZ;                    }
"JO"                        { BEGIN(INSTRUCTION); Logger("JO");     return JO;                     }
"JNO"                       { BEGIN(INSTRUCTION); Logger("JNO");    return JNO;                    }
"JC"                        { BEGIN(INSTRUCTION); Logger("JC");     return JC;                     }
"JNC"                       { BEGIN(INSTRUCTION); Logger("JNC");    return JNC;                    }
"JNE"                       { BEGIN(INSTRUCTION); Logger("JNE");    return JNE;                    }
"ADD"                       { BEGIN(INSTRUCTION); Logger("ADD");    return ADD;                    }
"SUB"                       { BEGIN(INSTRUCTION); Logger("SUB");    return SUB;                    }
"MUL"                       { BEGIN(INSTRUCTION); Logger("MUL");    return MUL;                    }
"IMUL"                      { BEGIN(INSTRUCTION); Logger("IMUL");   return IMUL;                   }
"DIV"                       { BEGIN(INSTRUCTION); Logger("DIV");    return DIV;                    }
"IDIV"                      { BEGIN(INSTRUCTION); Logger("IDIV");   return IDIV;                   }
"MOVE"                      { BEGIN(INSTRUCTION); Logger("MOVE");   return MOVE;                   }
"CALL"                      { BEGIN(INSTRUCTION); Logger("CALL");   return CALL;                   }
"PUSH"                      { BEGIN(INSTRUCTION); Logger("PUSH");   return PUSH;                   }
"POP"                       { BEGIN(INSTRUCTION); Logger("POP");    return POP;                    }
"PUSHSF"                    { BEGIN(INSTRUCTION); Logger("PUSHSF"); return PUSHSF;                 }
"POPSF"                     { BEGIN(INSTRUCTION); Logger("POPSF");  return POPSF;                  }
"NOP"                       { BEGIN(INSTRUCTION); Logger("NOP");    return NOP;                    }
"SWAP"                      { BEGIN(INSTRUCTION); Logger("SWAP");   return SWAP;                   }
"AND"                       { BEGIN(INSTRUCTION); Logger("AND");    return AND;                    }
"GFLR"                      { BEGIN(INSTRUCTION); Logger("GFLR");   return GFLR;                   }
"SFLR"                      { BEGIN(INSTRUCTION); Logger("SFLR");   return SFLR;                   }
"INC"                       { BEGIN(INSTRUCTION); Logger("INC");    return INC;                    }
"DEC"                       { BEGIN(INSTRUCTION); Logger("DEC");    return DEC;                    }

"SHL"                       { BEGIN(INSTRUCTION); Logger("SHL");    return SHL;                    }
"SHR"                       { BEGIN(INSTRUCTION); Logger("SHR");    return SHR;                    }
"ROL"                       { BEGIN(INSTRUCTION); Logger("ROL");    return ROL;                    }
"ROR"                       { BEGIN(INSTRUCTION); Logger("ROR");    return ROR;                    }
"SAL"                       { BEGIN(INSTRUCTION); Logger("SAL");    return SAL;                    }
"SAR"                       { BEGIN(INSTRUCTION); Logger("SAR");    return SAR;                    }
"RCL"                       { BEGIN(INSTRUCTION); Logger("RCL");    return RCL;                    }
"RCR"                       { BEGIN(INSTRUCTION); Logger("RCR");    return RCR;                    }

"ADC"                       { BEGIN(INSTRUCTION); Logger("ADC");    return ADC;                    }
"SBB"                       { BEGIN(INSTRUCTION); Logger("SBB");    return SBB;                    }
"NEG"                       { BEGIN(INSTRUCTION); Logger("NEG");    return NEG;                    }
"CAST"                      { BEGIN(INSTRUCTION); Logger("CAST");   return CAST;                   }

"OUT"                       { BEGIN(INSTRUCTION); Logger("OUT");    return OUT;                    }
"IN"                        { BEGIN(INSTRUCTION); Logger("IN");     return IN;                     }

"LOAD"                      { BEGIN(INSTRUCTION); Logger("LOAD");   return LOAD;                   }
"STORE"                     { BEGIN(INSTRUCTION); Logger("STORE");  return STORE;                  }

"BREAK"                     { BEGIN(INSTRUCTION); Logger("BREAK");   return BREAK;                 }

<INSTRUCTION>
{
"R"{digit}+                 { Logger("Register"); yyint = std::stoi(yytext + 1); return REGISTER;                       }
"A"{digit}+                 { Logger("Address register"); yyint = std::stoi(yytext + 1); return ADDRESS_REGISTER;       }

"B"                         { Logger("B");   enumOpSize = OperationSize::B;  return OPERATION_SIZE;                     }
"W"                         { Logger("W");   enumOpSize = OperationSize::W;  return OPERATION_SIZE;                     }
"DW"                        { Logger("DW");  enumOpSize = OperationSize::DW;  return OPERATION_SIZE;                    }
"QW"                        { Logger("QW");  enumOpSize = OperationSize::QW;  return OPERATION_SIZE;                    }

"\n"                        { enumOpSize = OperationSize::B; BEGIN(INITIAL); Logger("End instruction state"); ++lineNumber; }
}

"BYTE"                      { Logger("BYTE");   return BYTE;                   }
"CHAR"                      { Logger("CHAR");   return CHAR;                   }
"WORD"                      { Logger("WORD");   return WORD;                   }
"DWORD"                     { Logger("DWORD");  return DWORD;                  }
"QWORD"                     { Logger("QWORD");  return QWORD;                  }



"["                         { Logger("[");      return yytext[0];              }
"]"                         { Logger("]");      return yytext[0];              }
<*>";"                      { Logger(";");      return yytext[0];              }
":"                         { Logger(":");      return yytext[0];              }
","                         { Logger(",");      return yytext[0];              }
"="                         { Logger("=");      return yytext[0];              }
"!"                         { Logger("=");      return yytext[0];              }


"Func"                      { Logger("Func");      return FUNC;                }
"RET"                       { Logger("RET");    return RET;                    }
"EndF"                      { Logger("EndF");      return E_FUNC;              }


<*>[+-]?{digit}+            {
                                // Parsing number
                                Logger("NUMBER");
                                yyint = std::stol(yytext);
                                return NUMBER; 
                            }
<*>"0x"[0-9a-fA-F]+         { Logger("HEX");     return NUMBER;                } // parsing hex number
<*>{letter}({letter}|{digit}|{und})* {
                                Logger("IDENTIFIER");
                                yyid = yytext;
                                return ID;
                            }


%%

int yywrap()
{
    return 1;
}