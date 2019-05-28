#include "BaseInstruction.h"

BaseInstruction::~BaseInstruction() = default;

ArithmeticInstructions::ArithmeticInstructions(const reg_id_t left, const reg_id_t right)
    : m_left{left}
    , m_right{right}
{
}

JumpInstructions::JumpInstructions(const std::size_t new_ip)
    : m_new_ip{new_ip}
{
}
