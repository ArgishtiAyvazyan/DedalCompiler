#include <iostream>

#include "Debug.h"
#include "UIO.h"
#include "CParser.hpp"

static std::string_view module = "Main";

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv)
{
    if (argc < 2)
    {
        UIO::Write("Input file is missing", module, MessageType::Error);
        return -1;
    }

    auto& parser = CParser::get();
    parser.SetFileName(argv[1]);
    parser.StartParsing();

    std::cout << "\nEnd Task." << std::endl;
    return 0;
}