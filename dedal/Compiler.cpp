#include "Compiler.h"
#include "FileReader.h"
#include "Parser.h"

Compiler::Compiler(std::string_view file_name)
	: m_file_name { file_name }
{
}

ExecutableCode Compiler::compile_code() const
{
	FileReader fr{ std::string {m_file_name} };
	const auto txt_code = fr.read_in();
	Parser parser{txt_code};
	return parser.executavle_code();
}
