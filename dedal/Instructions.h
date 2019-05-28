#pragma once

#include "BaseInstruction.h"

class InstructionAssign final : public BaseInstruction
{
public:
    InstructionAssign(reg_id_t reg_id, int value);

    ~InstructionAssign();

    void execute(CPU& cpu) const override;

private:
    const reg_id_t m_reg_id;
    const int m_value;
};

class InstructionPrint final : public BaseInstruction
{
public:
    InstructionPrint(reg_id_t reg_id);

    ~InstructionPrint();

    void execute(CPU& cpu) const override;

private:
    const reg_id_t m_reg_id;
};

class InstructionCmp final : public ArithmeticInstructions
{
public:
    InstructionCmp(reg_id_t left, reg_id_t right);

    ~InstructionCmp();

    void execute(CPU& cpu) const override;
};

class InstructionJump final : public JumpInstructions
{
public:
    explicit InstructionJump(std::size_t new_ip = 0);

    ~InstructionJump();

    void execute(CPU& cpu) const override;
};

class InstructionJz final : public JumpInstructions
{
public:
    explicit InstructionJz(std::size_t new_ip = 0);

    ~InstructionJz();

    void execute(CPU& cpu) const override;
};

class InstructionJnz final : public JumpInstructions
{
public:
    explicit InstructionJnz(std::size_t new_ip = 0);

    ~InstructionJnz();

    void execute(CPU& cpu) const override;
};

class InstructionJo final : public JumpInstructions
{
public:
    explicit InstructionJo(std::size_t new_ip = 0);

    ~InstructionJo();

    void execute(CPU& cpu) const override;
};

class InstructionJno final : public JumpInstructions
{
public:
    explicit InstructionJno(std::size_t new_ip = 0);

    ~InstructionJno();

    void execute(CPU& cpu) const override;
};

class InstructionJc final : public JumpInstructions
{
public:
    explicit InstructionJc(std::size_t new_ip = 0);

    ~InstructionJc();

    void execute(CPU& cpu) const override;
};

class InstructionJnc final : public JumpInstructions
{
public:
    explicit InstructionJnc(std::size_t new_ip = 0);

    ~InstructionJnc();

    void execute(CPU& cpu) const override;
};

class InstructionAdd final : public ArithmeticInstructions
{
public:
    InstructionAdd(reg_id_t left, reg_id_t right);

    ~InstructionAdd();

    void execute(CPU& cpu) const override;
};

class InstructionSub final : public ArithmeticInstructions
{
public:
    InstructionSub(reg_id_t left, reg_id_t right);

    ~InstructionSub();

    void execute(CPU& cpu) const override;
};

class InstructionMul final : public ArithmeticInstructions
{
public:
    InstructionMul(reg_id_t left, reg_id_t right);

    ~InstructionMul();

    void execute(CPU& cpu) const override;
};

class InstructionDiv final : public ArithmeticInstructions
{
public:
    InstructionDiv(reg_id_t left, reg_id_t right);

    ~InstructionDiv();

    void execute(CPU& cpu) const override;
};

class InstructionMov final : public BaseInstruction
{
public:
    InstructionMov(reg_id_t left, reg_id_t right);

    ~InstructionMov();

    void execute(CPU& cpu) const override;

private:
    const reg_id_t m_left;
    const reg_id_t m_right;
};


class InstructionLabel final : public BaseInstruction
{
public:
    InstructionLabel();

    ~InstructionLabel();

    void execute(CPU& cpu) const override;
};


class InstructionCall final : public JumpInstructions
{
public:
    InstructionCall(size_t new_ip = 0);

    ~InstructionCall();

    void execute(CPU& cpu) const override;
};


class InstructionRet final : public JumpInstructions
{
public:
    InstructionRet(size_t new_ip = 0);

    ~InstructionRet();

    void execute(CPU& cpu) const override;
};

class InstructionEnd final : public BaseInstruction
{
public:
    InstructionEnd();

    ~InstructionEnd();

    void execute(CPU& cpu) const override;
};


class InstructionPush final : public BaseInstruction
{
public:
    InstructionPush(TypeSize::RegSize reg_size, reg_id_t reg_id);

    ~InstructionPush();

    void execute(CPU& cpu) const override;

private:

    const TypeSize::RegSize m_reg_size;
    const reg_id_t m_reg_id;
};


class InstructionPop final : public BaseInstruction
{
public:
    InstructionPop(TypeSize::RegSize reg_size, reg_id_t reg_id);

    ~InstructionPop();

    void execute(CPU& cpu) const override;


private:
    const TypeSize::RegSize m_reg_size;
    const reg_id_t m_reg_id;
};
