.CODE

Func F1;
Func F2;

Func Main:
    PUSHSF;
    JUMP start;
    NOP;
    NOP;
    NOP;
start:
    ASSIGN A7, null;
    ASSIGN A4, F1;
    CALL A4;
    ASSIGN A4, F2;
    CALL A4;
    POPSF;

    ASSIGN B R1, 4;
    SHL W R6, 5;
    SHR W R6, R1;
    ROL W R6, 7;
    ROR W R6, R1;
    SAL W R6, 3;
    SAR W R6, R1;
    RCL W R6, 1;
    RCR W R6, R1;

    ADC R8, R12;
    SBB R8, R12;
    MUL R8, R12;
    IMUL R8, R12;
    DIV R8, R12;
    IDIV R8, R12;
    NEG QW R8;

    CAST W DW R4;
    CAST DW W R16;
    CAST QW DW R1;
    CAST B QW R7;

    ASSIGN A4, bVal1;
    ASSIGN A5, wVal1;
    ASSIGN A6, dwVal1;
    ASSIGN A7, qwVal1;

    LOAD B R0,A4;
    LOAD W R0,A5;
    LOAD DW R0,A6;
    LOAD QW R0,A7;
    RET;
EndF