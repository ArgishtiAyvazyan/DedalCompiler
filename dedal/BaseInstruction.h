#pragma once


#include "CPU.h"

using reg_id_t = std::size_t;

class BaseInstruction
{
public:

    virtual void execute(CPU& cpu) const = 0;

    virtual ~BaseInstruction();
};

class ArithmeticInstructions : public BaseInstruction
{
public:
    ArithmeticInstructions(reg_id_t left, reg_id_t right);

protected:
    const reg_id_t m_left;
    const reg_id_t m_right;
};

class JumpInstructions : public BaseInstruction
{
public:
    explicit JumpInstructions(std::size_t new_ip);

    void set_ip(const size_t ip) noexcept
    {
        m_new_ip = ip;
    }

protected:
    std::size_t m_new_ip;
};
