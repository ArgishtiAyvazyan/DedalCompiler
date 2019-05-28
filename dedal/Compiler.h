#pragma once
#include <string_view>
#include "ExecutableCode.h"

class Compiler
{
public:
	Compiler(std::string_view);

	~Compiler() = default;
	
	ExecutableCode compile_code() const;

private:
	std::string_view m_file_name;
};

