#include "Instructions.h"
#include <iostream>


InstructionAssign::InstructionAssign(const reg_id_t reg_id, const int value)
    : m_reg_id{reg_id}
    , m_value{value}
{
}

InstructionAssign::~InstructionAssign() = default;

void InstructionAssign::execute(CPU& cpu) const
{
    cpu.set_register_value(m_reg_id, m_value);
}

InstructionPrint::InstructionPrint(const reg_id_t reg_id)
    : m_reg_id{reg_id}
{
}

InstructionPrint::~InstructionPrint() = default;

void InstructionPrint::execute(CPU& cpu) const
{
    std::cout << cpu.get_register_value(m_reg_id) << std::endl;
}

InstructionCmp::InstructionCmp(const reg_id_t left, const reg_id_t right)
    : ArithmeticInstructions{left, right}
{
}

InstructionCmp::~InstructionCmp() = default;

void InstructionCmp::execute(CPU& cpu) const
{
    cpu.cmp(m_left, m_right);
}


InstructionJump::InstructionJump(const std::size_t new_ip)
    : JumpInstructions{new_ip - 1}
{
}

InstructionJump::~InstructionJump() = default;

void InstructionJump::execute(CPU& cpu) const
{
    cpu.set_ip(m_new_ip);
}

InstructionJz::InstructionJz(const std::size_t new_ip)
    : JumpInstructions{new_ip - 1}
{
}

InstructionJz::~InstructionJz() = default;

void InstructionJz::execute(CPU& cpu) const
{
    if (cpu.status_register.ZF)
    {
        cpu.set_ip(m_new_ip);
    }
}

InstructionJnz::InstructionJnz(const std::size_t new_ip)
    : JumpInstructions{new_ip - 1}
{
}

InstructionJnz::~InstructionJnz() = default;

void InstructionJnz::execute(CPU& cpu) const
{
    if (!cpu.status_register.ZF)
    {
        cpu.set_ip(m_new_ip);
    }
}

InstructionJo::InstructionJo(const std::size_t new_ip)
    : JumpInstructions{new_ip - 1}
{
}

InstructionJo::~InstructionJo() = default;

void InstructionJo::execute(CPU& cpu) const
{
    if (cpu.status_register.OF)
    {
        cpu.set_ip(m_new_ip);
    }
}

InstructionJno::InstructionJno(const std::size_t new_ip)
    : JumpInstructions{new_ip - 1}
{
}

InstructionJno::~InstructionJno() = default;

void InstructionJno::execute(CPU& cpu) const
{
    if (!cpu.status_register.OF)
    {
        cpu.set_ip(m_new_ip);
    }
}

InstructionJc::InstructionJc(const std::size_t new_ip)
    : JumpInstructions{new_ip - 1}
{
}

InstructionJc::~InstructionJc() = default;

void InstructionJc::execute(CPU& cpu) const
{
    if (cpu.status_register.CF)
    {
        cpu.set_ip(m_new_ip);
    }
}

InstructionJnc::InstructionJnc(const std::size_t new_ip)
    : JumpInstructions{new_ip - 1}
{
}

InstructionJnc::~InstructionJnc() = default;

void InstructionJnc::execute(CPU& cpu) const
{
    if (!cpu.status_register.CF)
    {
        cpu.set_ip(m_new_ip);
    }
}

InstructionAdd::InstructionAdd(const reg_id_t left, const reg_id_t right)
    : ArithmeticInstructions{left, right}
{
}

InstructionAdd::~InstructionAdd() = default;

void InstructionAdd::execute(CPU& cpu) const
{
    cpu.add(m_left, m_right);
}

InstructionSub::InstructionSub(const reg_id_t left, const reg_id_t right)
    : ArithmeticInstructions{left, right}
{
}

InstructionSub::~InstructionSub() = default;

void InstructionSub::execute(CPU& cpu) const
{
    cpu.sub(m_left, m_right);
}

InstructionMul::InstructionMul(const reg_id_t left, const reg_id_t right)
    : ArithmeticInstructions{left, right}
{
}

InstructionMul::~InstructionMul() = default;

void InstructionMul::execute(CPU& cpu) const
{
    cpu.mul(m_left, m_right);
}

InstructionDiv::InstructionDiv(const reg_id_t left, const reg_id_t right)
    : ArithmeticInstructions{left, right}
{
}

InstructionDiv::~InstructionDiv() = default;

void InstructionDiv::execute(CPU& cpu) const
{
    cpu.div(m_left, m_right);
}

InstructionMov::InstructionMov(const reg_id_t left, const reg_id_t right)
    : m_left{left}
    , m_right{right}
{
}

InstructionMov::~InstructionMov() = default;

void InstructionMov::execute(CPU& cpu) const
{
    cpu.mov(m_left, m_right);
}

InstructionLabel::InstructionLabel() = default;

InstructionLabel::~InstructionLabel() = default;

void InstructionLabel::execute(CPU& cpu) const
{
    std::ignore = cpu;
}

InstructionCall::InstructionCall(const size_t new_ip)
    : JumpInstructions{new_ip}
{
}

InstructionCall::~InstructionCall() = default;

void InstructionCall::execute(CPU& cpu) const
{
    cpu.stack_push(TypeSize::RegSize::W, cpu.get_ip());
    cpu.set_ip(m_new_ip);
}

InstructionRet::InstructionRet(const size_t new_ip)
    : JumpInstructions{new_ip}
{
}

InstructionRet::~InstructionRet() = default;

void InstructionRet::execute(CPU& cpu) const
{
    cpu.set_ip(cpu.stack_pop(TypeSize::RegSize::W));
}

InstructionEnd::InstructionEnd() = default;

InstructionEnd::~InstructionEnd() = default;

void InstructionEnd::execute(CPU& cpu) const
{
    cpu.set_ip(std::numeric_limits<decltype(cpu.m_ip)>::max());
}

InstructionPush::InstructionPush(const TypeSize::RegSize reg_size, const reg_id_t reg_id)
    : m_reg_size(reg_size)
    , m_reg_id(reg_id)
{
}

InstructionPush::~InstructionPush() = default;

void InstructionPush::execute(CPU& cpu) const
{
    cpu.stack_push(m_reg_size, cpu.get_register_value(m_reg_id));
}

InstructionPop::InstructionPop(const TypeSize::RegSize reg_size, const reg_id_t reg_id)
    : m_reg_size(reg_size)
    , m_reg_id(reg_id)
{
}

InstructionPop::~InstructionPop() = default;

void InstructionPop::execute(CPU& cpu) const
{
    //TODO invalid conversion
    cpu.set_register_value(m_reg_id, static_cast<int>(cpu.stack_pop(m_reg_size)));
}
