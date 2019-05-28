#pragma once
#include <memory>
#include "BaseInstruction.h"
#include "ExecutableCode.h"
#include "CPU.h"

using TInstructionTable = std::vector<std::unique_ptr<BaseInstruction>>;

class Interpreter
{
public:
	Interpreter(ExecutableCode);

	void run();

private:
	void init(ExecutableCode);

private:
	CPU m_cpu;
	TInstructionTable m_instruction_table;
};

