#include <iostream>
#include "Debug.h"

extern FILE* yyin;

int yyparse();

static std::string_view module = "main";

int main(int argc, char* argv[])
{
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

    return 0;
}