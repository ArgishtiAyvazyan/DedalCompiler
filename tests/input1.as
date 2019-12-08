# Assembly file sample
.STACK = 1024;

# Variables section
.DATA
CHAR var;                        # Variable definition
CHAR ch1 = 'A';                  # Variable definition with initialization statement
CHAR str1[] = "Hello World!";    # Variable array
BYTE bVal1;                      # Forward declaration
BYTE bVal2 = 127;
BYTE abVal3[] = 0x4F,0x0F;       # Array size should be determined by its initializer list
BYTE abVal4[10];                 # Array size explicitly specified
WORD wVal5 = -10;
DWORD dwVal6 = 0xA0B0C0D;
DWORD adwVal7[5] = 10,20,30,-40,0x0F00;
QWORD qwVal9 = 0xFFFFFFFFFFFFFFFF;

.MAIN = Start;                   # Entry point definition

# Functions
.CODE
Func PrintString;               # Function forward declaration
Func Start:                     # Function definition
    ASSIGN A4, str1;
    ASSIGN A5, PrintString;
    CALL A5;
    RET;
EndF                            # End of function body
Func PrintString:
    PUSHSF;

    JUMP Label1;

Label1 :
    POPSF;
    RET;
EndF
