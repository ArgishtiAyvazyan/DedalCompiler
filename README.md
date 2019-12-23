# Assembly compiler.

An implementation of Assembly compiler.

## Building DedalCompiler

```bash
mkdir ./build
cd ./build
cmake ..
make -j <job count>
```

### How to run?

```bash
./bin/gmain_exec <source_code>
```

### How to run unit tests?

```bash
./bin/runTests
```

## External dependencies

* [cmake 3.6 or higher](https://cmake.org/)
* [make](https://www.gnu.org/software/make/)
* [GCC 7.1 or higher](https://gcc.gnu.org/)
* [Bison](https://github.com/gitGNU/gnu_bison)
* [Flex](https://github.com/westes/flex)
* [Boost](https://github.com/boostorg/boost)
* [Gtest](https://github.com/google/googletest)

## Platform dependencies

* Linux
* WSL (Windows Subsystem for Linux)

## Project structure

```
├── Application
│   ├── CMakeLists.txt
│   └── main.cpp
├── CMakeLists.txt
├── Compiler
│   ├── CBuffer.h
│   ├── CCommandContext.h
│   ├── CCompiler.cpp
│   ├── CCompiler.h
│   ├── CMakeLists.txt
│   ├── Commands.cpp
│   └── Commands.h
├── Core
│   ├── CInsArg.cpp
│   ├── CInsArg.h
│   ├── CMakeLists.txt
│   └── Decl.h
├── Generic
│   ├── CEvent.hpp
│   ├── CException.cpp
│   ├── CException.h
│   ├── CMakeLists.txt
│   ├── Configs.hpp
│   ├── Debug.cpp
│   └── Debug.h
├── Parser
│   ├── CMakeLists.txt
│   ├── CParser.cpp
│   ├── CParserHelper.cpp
│   ├── CParserHelper.hpp
│   ├── CParser.hpp
│   ├── Lexer.l
│   ├── ParserDecl.hpp
│   └── Parser.y
├── tree.txt
├── UserOutWriter
│   ├── CMakeLists.txt
│   ├── UIO.cpp
│   └── UIO.h
└── VirtualMachine
    ├── CExecutor.cpp
    ├── CExecutor.h
    ├── CFlags.cpp
    ├── CFlags.h
    ├── CMakeLists.txt
    ├── CMemory.h
    ├── CProcessor.cpp
    ├── CProcessor.h
    └── SCPUState.h
```

## Simple example

```assembly
# Assembly file sample
.STACK = 1024;

# Variables section
.DATA
CHAR var;                        # Variable definition
BYTE abVal3[] = 0x4F,0x0F;       # Array size should be determined by its initializer list
WORD wVal5 = -10;
QWORD qwVal9 = 0xFFFFFFFFFFFFFFFF;


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

.MAIN = Start;                   # Entry point definition
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
