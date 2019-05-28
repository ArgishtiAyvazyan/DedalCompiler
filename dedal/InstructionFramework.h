#pragma once

#include "Instructions.h"
#include <string>
#include <regex>
#include <forward_list>
#include "ParserDecl.h"
#include "ExecutableCode.h"

using TInstructionTable = std::vector<std::unique_ptr<BaseInstruction>>;

class InstructionFramework
{
public:

    InstructionFramework();

    TInstructionTable generate_program(const ExecutableCode& code);


private:
    void make_jamps(TInstructionTable& program);

    static std::unique_ptr<BaseInstruction> create_instruction_print(const std::size_t id);

    static std::unique_ptr<BaseInstruction> create_instruction_assign(const reg_id_t id, const int value);

    template <class T>
    static std::unique_ptr<BaseInstruction> create_instruction_ls(const size_t reg_size, const size_t reg_id);

    template <class T, class... TArgs>
    std::unique_ptr<BaseInstruction> create_instruction_jump(const int label_id);


    std::unordered_map<int, std::forward_list<JumpInstructions*>> m_label_id_to_label_map;

    std::unordered_map<InstructionLabel*, int> m_label_to_id_map;

};
