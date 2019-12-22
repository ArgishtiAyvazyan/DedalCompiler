#include <iostream>

#include "Debug.h"
#include "UIO.h"
#include "CParser.hpp"
#include "CException.h"
#include "CCompiler.h"
#include "CProcessor.h"
#include "CMemory.h"

using namespace std::string_literals;

static std::string_view module = "Main";

int main([[maybe_unused]]int argc, [[maybe_unused]]char** argv)
try
{
    BASE_CHECK (argc >= 2, "Input file is missing.");
    // auto& parser = CParser::get();
    // parser.SetFileName(argv[1]);
    // parser.StartParsing();

    using namespace compiler;

    CCompiler compiler({ argv[1] });

    CBuffer buffer = compiler.GetCompiledCode();

    vm::CMemory memory { buffer };
    vm::CProcessor procesor { memory };

    std::cout << "\nEnd Task." << std::endl;
    return 0;
}
catch (const gen::CException& e)
{
    std::cerr << e.StackTrace() << std::endl;

    UIO::Write(e.Message(), module, MessageType::Error);
    UIO::Write("File : "s + e.FileName().data(), module, MessageType::Error);
    UIO::Write("Line : "s + std::to_string(e.LineNumber()), module, MessageType::Error);

}
catch (const std::exception& e)
{
    gen::Debug::ASSERT(false, e.what());
}
catch (...)
{
    gen::Debug::ASSERT(false, "Unknown error!");
}