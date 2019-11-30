#include <iostream>

#include "UIO.h"

#include "Debug.h"

extern FILE* yyin;

int yyparse();

static std::string_view module = "main";

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{

    UIO::Write("Messege", "module", MessageType::Info);
    UIO::Write("Messege", "module", MessageType::Warning);
    UIO::Write("Messege", "module", MessageType::Error);
    UIO::Write("Messege", "module", MessageType::Debug);

    if (argc < 2)
    {
        Debug::Log(module, "Input file is missing", LogType::Error);
        return -1;
    }

    yyin = fopen(argv[1], "r");

    if (nullptr == yyin)
    {
        Debug::Log(module, "Cannot open file.", LogType::Error);
        return -2;
    }

    if (0 != yyparse())
    {
        Debug::Log(module, "Unknown result.", LogType::Error);
    }

    std::cout << "End"<< std::endl;
    return 0;
}