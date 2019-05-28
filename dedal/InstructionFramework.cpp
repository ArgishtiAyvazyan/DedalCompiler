#include "InstructionFramework.h"
#include "Utility.h"
#include <cassert>

InstructionFramework::InstructionFramework()
    : m_label_id_to_label_map()
    , m_label_to_id_map()
{
}

TInstructionTable InstructionFramework::generate_program(const ExecutableCode& code)
{
    TInstructionTable program;
    auto code_segment = code.code_segment();
    int value = 0;
	while (code_segment >> value)
	{
		std::unique_ptr<BaseInstruction> res = nullptr;

		switch (static_cast<Instructions>(value))
		{
		case Instructions::assign:
		{
			int id;
			code_segment >> id;
			int value;
			code_segment >> value;
			res = create_instruction_assign(id, value);
			break;
		}
		case Instructions::print:
		{
			int id;
			code_segment >> id;
			res = create_instruction_print(id);
			break;
		}
		case Instructions::cmp:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<InstructionCmp>(id, id1);
			break;
		}
		case Instructions::jump:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<InstructionJump>(id);
			break;
		}
		case Instructions::jz:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<InstructionJz>(id);
			break;
		}
		case Instructions::jnz:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<InstructionJnz>(id);
			break;
		}
		case Instructions::jo:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<InstructionJo>(id);
			break;
		}
		case Instructions::jno:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<InstructionJno>(id);
			break;
		}
		case Instructions::jc:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<InstructionJc>(id);
			break;
		}
		case Instructions::jnc:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<InstructionJnc>(id);
			break;
		}
		case Instructions::call:
		{
			int id;
			code_segment >> id;
			res = create_instruction_jump<InstructionCall>(id);
			break;
		}
		case Instructions::add:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<InstructionAdd>(id, id1);
			break;
		}
		case Instructions::sub:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<InstructionSub>(id, id1);
			break;
		}
		case Instructions::mul:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<InstructionMul>(id, id1);
			break;
		}
		case Instructions::div:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<InstructionDiv>(id, id1);
			break;
		}
		case Instructions::mov:
		{
			int id;
			code_segment >> id;
			int id1;
			code_segment >> id1;
			res = std::make_unique<InstructionMov>(id, id1);
			break;
		}
		case Instructions::ret:
			res = std::make_unique<InstructionRet>();
			break;
		case Instructions::end:
			res = std::make_unique<InstructionEnd>();
			break;
		case Instructions::push:
		{
			int reg_size;
			code_segment >> reg_size;
			int reg_id;
			code_segment >> reg_id;
			res = create_instruction_ls<InstructionPush>(reg_size, reg_id);
			break;
		}
		case Instructions::pop:
		{
			int reg_size;
			code_segment >> reg_size;
			int reg_id;
			code_segment >> reg_id;
			res = create_instruction_ls<InstructionPop>(reg_size, reg_id);
			break;
		}
		case Instructions::label:
		{
			// TODO add validate check
			auto inst = std::make_unique<InstructionLabel>();

			assert(inst);

			int id;
			code_segment >> id;
			m_label_to_id_map[inst.get()] = id;

			res = std::move(inst);
			break;
		}
		default:
			assert(false);
		}

		int chack_point;
		code_segment >> chack_point;
		assert(std::numeric_limits<int>::max() == chack_point);

		program.push_back(std::move(res));

	}

    make_jamps(program);

    return program;
}

void InstructionFramework::make_jamps(TInstructionTable& program)
{
    for (auto i = 0u; i < program.size(); ++i)
    {
        auto label_to_name_pair = m_label_to_id_map.find(static_cast<InstructionLabel*>(program[i].get()));

        if (label_to_name_pair == m_label_to_id_map.end())
        {
            continue;
        }

        auto [label, name] = *label_to_name_pair;

        m_label_to_id_map.erase(static_cast<InstructionLabel*>(program[i].get()));

        auto name_to_jumps_pair = m_label_id_to_label_map.find(name);

        if (name_to_jumps_pair == m_label_id_to_label_map.end())
        {
            continue;
        }

        auto [n, jumps] = *name_to_jumps_pair;

        for (auto ji : jumps)
        {
            ji->set_ip(i);
        }

        m_label_id_to_label_map.erase(name);
    }

    if (!m_label_id_to_label_map.empty() || !m_label_to_id_map.empty())
    {
        throw std::invalid_argument{"Invalid Jump or label"};
    }

    m_label_id_to_label_map.clear();
    m_label_to_id_map.clear();
}

//template <class ... TArgs>
//std::unique_ptr<BaseInstruction> InstructionFramework::get_instruction(const std::string& command, TArgs&&... args)
//{
//    const auto instruction_type_it = s_string_enum_map.find(command);
//
//    if (instruction_type_it == s_string_enum_map.end())
//    {
//        // TODO add validate check
//        auto inst = std::make_unique<InstructionLabel>();
//
//        assert(inst);
//
//        m_label_to_id_map[inst.get()] = command;
//
//        return inst;
//    }
//
//    switch ((*instruction_type_it).second)
//    {
//    case instructions::assign:
//        return create_instruction_assign(args...);
//    case instructions::print:
//        return create_instruction_print(util::to_size_t(args)...);
//    case instructions::cmp:
//        return std::make_unique<InstructionCmp>(util::to_size_t(args)...);
//    case instructions::jump:
//        return create_instruction_jump<InstructionJump>(args...);
//    case instructions::jz:
//        return create_instruction_jump<InstructionJz>(args...);
//    case instructions::jnz:
//        return create_instruction_jump<InstructionJnz>(args...);
//    case instructions::jo:
//        return create_instruction_jump<InstructionJo>(args...);
//    case instructions::jno:
//        return create_instruction_jump<InstructionJno>(args...);
//    case instructions::jc:
//        return create_instruction_jump<InstructionJc>(args...);
//    case instructions::jnc:
//        return create_instruction_jump<InstructionJnc>(args...);
//    case instructions::call:
//        return create_instruction_jump<InstructionCall>(args...);
//    case instructions::add:
//        return std::make_unique<InstructionAdd>(util::to_size_t(args)...);
//    case instructions::sub:
//        return std::make_unique<InstructionSub>(util::to_size_t(args)...);
//    case instructions::mul:
//        return std::make_unique<InstructionMul>(util::to_size_t(args)...);
//    case instructions::div:
//        return std::make_unique<InstructionDiv>(util::to_size_t(args)...);
//    case instructions::mov:
//        return std::make_unique<InstructionMov>(util::to_size_t(args)...);
//    case instructions::ret:
//        return std::make_unique<InstructionRet>();
//    case instructions::end:
//        return std::make_unique<InstructionEnd>();
//    case instructions::push:
//        return create_instruction_ls<InstructionPush>(args...);
//    case instructions::pop:
//        return create_instruction_ls<InstructionPop>(args...);
//    default:
//        assert(false);
//    }
//
//    return {};
//}

std::unique_ptr<BaseInstruction> InstructionFramework::create_instruction_print(const std::size_t id)
{
    return std::unique_ptr<BaseInstruction>(std::make_unique<InstructionPrint>(id));
}

std::unique_ptr<BaseInstruction> InstructionFramework::create_instruction_assign(const reg_id_t id, const int value)
{
    return std::unique_ptr<BaseInstruction>(
        std::make_unique<InstructionAssign>(id, value));
}

template <class T>
std::unique_ptr<BaseInstruction> InstructionFramework::create_instruction_ls(const size_t reg_size, const size_t reg_id)
{
    //return std::make_unique<T>(TypeSize::reg_size_name_to_enum(reg_size), util::to_int_t(reg_id));
    return std::make_unique<T>(static_cast<TypeSize::RegSize>(reg_size), reg_id);
}

template <class T, class ... TArgs>
std::unique_ptr<BaseInstruction> InstructionFramework::create_instruction_jump(const int label_id)
{
    auto inst = std::make_unique<T>();
    m_label_id_to_label_map[label_id].push_front(inst.get());
    return inst;
}

