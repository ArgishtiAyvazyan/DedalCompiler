#include "Interpreter.h"
#include "InstructionFramework.h"

Interpreter::Interpreter(ExecutableCode ec)
	: m_cpu { ec.stack_size() }
{
	this->init(ec);
}

void Interpreter::run()
{
	while (m_cpu.m_ip < m_instruction_table.size())
	{
		const auto current_ip = m_cpu.m_ip;
		++m_cpu.m_ip;
		m_instruction_table[current_ip]->execute(m_cpu);
	}
}

void Interpreter::init(ExecutableCode ex)
{
	InstructionFramework instruction_framework;
	m_instruction_table = instruction_framework.generate_program(ex);
}
