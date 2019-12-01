#include <iostream>

#include "UIO.h"

#include "Debug.h"

extern FILE* yyin;

int yyparse();

static std::string_view module = "Main";

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{

    UIO::Write("Messege", "module", MessageType::Info);
    UIO::Write("Messege", "module", MessageType::Warning);
    UIO::Write("Messege", "module", MessageType::Error);
    UIO::Write("Messege", "module", MessageType::Debug);

    if (argc < 2)
    {
        UIO::Write("Input file is missing", module, MessageType::Error);
        return -1;
    }

    yyin = fopen(argv[1], "r");

    if (nullptr == yyin)
    {
        UIO::Write("Cannot open file.", module, MessageType::Error);
        return -2;
    }

    if (0 != yyparse())
    {
        UIO::Write("Unknown result.", module, MessageType::Error);
    }

    std::cout << "\nEnd Task." << std::endl;
    return 0;
}