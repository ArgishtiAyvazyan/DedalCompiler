#include "Parser.h"
#include "Utility.h"
#include <ostream>
#include <iostream>
#include <regex>
#include "ParserUtils.hpp"
#include <cassert>
#include <string>

using namespace std::string_literals;
using namespace std::string_view_literals;

Parser::Parser(const std::vector<std::string>& txt_code)
	: m_stack_size(0)
	, m_free_id(0)
{
    auto end_phase = this->parse_stack_size(std::cbegin(txt_code), std::cend(txt_code));
    end_phase = this->parse_data_segment(end_phase, std::cend(txt_code));
    end_phase = this->parse_code_segment(end_phase, std::cend(txt_code));
}

Parser::code_iterator Parser::parse_stack_size(const code_iterator begin, const code_iterator end)
{
    auto it = begin;
    for (; it != end; ++it)
    {
        const auto res = (*it).find(".STACK");
        if (std::string::npos != res)
        {
            break;
        }
    }

    if (it == end)
    {
        throw std::invalid_argument{"stack size not found."};
    }

    try
    {
        std::smatch matches;
        const std::regex re("([[:digit:]]+)");
        std::regex_search(*it, matches, re);

        m_stack_size = util::to_size_t(matches[1]);
    }
    catch (...)
    {
        throw std::invalid_argument{"stack size not found."};
    }

    return ++it;
}


void Parser::parse_forward_declaration(const std::cmatch& tokens)
{
    // std::cout << "########  parse_forward_declaration  ########" << std::endl;
    // for (auto it = ++std::begin(tokens); it != std::end(tokens); ++it)
    // {
    //     std::cout << *it << ' ';
    // }
    // std::cout << std::endl;

	auto it = ++std::begin(tokens);
	m_data_segment_buffer << static_cast<int>(find_type_by_name(*it)); // insert type
	const auto variable_name = (*(++it)).str();
	const auto search = m_variable_name_to_id_map.find(variable_name);
    if (search != std::end(m_variable_name_to_id_map))
    {
		throw std::invalid_argument{ " Double declaration : \n"s + variable_name };
    }
	m_variable_name_to_id_map[std::string{ variable_name }] = m_free_id;
	m_data_segment_buffer << m_free_id;
	++m_free_id;
	m_data_segment_buffer << 1; // inset count
	m_data_segment_buffer << 0; // inset default value
	assert(++it == std::end(tokens));
}

void Parser::parse_definition_and_init(const std::cmatch& tokens)
{
    // std::cout << "########  parse_definition_and_init  ########" << std::endl;
    // for (auto it = ++std::begin(tokens); it != std::end(tokens); ++it)
    // {
    //     std::cout << *it << ' ';
    // }
    // std::cout << std::endl;

	auto it = ++std::begin(tokens);
	const auto type = find_type_by_name(*it);
	m_data_segment_buffer << static_cast<int>(type); // insert type
	const auto variable_name = (*(++it)).str();
	const auto search = m_variable_name_to_id_map.find(variable_name);
	if (search != std::end(m_variable_name_to_id_map))
	{
		throw std::invalid_argument{ " Double declaration : \n"s + variable_name };
	}
	m_variable_name_to_id_map[std::string{ variable_name }] = m_free_id;
	m_data_segment_buffer << m_free_id;
	++m_free_id;
	m_data_segment_buffer << 1; // inset count
	++it;
	const auto value = std::string{ (*(++it)).str() };
	if (Type::char_type == type)
	{
		if (value.length() != 3) // char literal length
		{
			throw std::invalid_argument{ " Invalid value : \n"s + value };
		}
	    m_data_segment_buffer << static_cast<int>(value[1]); // inset value
	}
	else
	{
		try
		{
			m_data_segment_buffer << util::to_int_t(value);
		}
        catch(...)
        {
			throw std::invalid_argument{ " Invalid value : \n"s + value };
        }
	}

	assert(++it == std::end(tokens));
}

void Parser::parse_array_decl(const std::cmatch& tokens)
{
    // std::cout << "########  parse_array_decl  ########" << std::endl;
    // for (auto it = ++std::begin(tokens); it != std::end(tokens); ++it)
    // {
    //     std::cout << *it << ' ';
    // }
    // std::cout << std::endl;

	auto it = ++std::begin(tokens);
	const auto type = find_type_by_name(*it);
	m_data_segment_buffer << static_cast<int>(type); // insert type
	const auto variable_name = (*(++it)).str();
	const auto search = m_variable_name_to_id_map.find(variable_name);
	if (search != std::end(m_variable_name_to_id_map))
	{
		throw std::invalid_argument{ " Double declaration : \n"s + variable_name };
	}
	m_variable_name_to_id_map[std::string{ variable_name }] = m_free_id;
	m_data_segment_buffer << m_free_id;
	++m_free_id;

	auto count_string = std::string{ (*(++it)).str() };
	count_string.erase(std::begin(count_string));
	count_string.erase(std::end(count_string) - 1);
	const auto count = util::to_int_t(count_string);
	m_data_segment_buffer << count; // inset count
	for (auto i = 0; i < count; ++i)
    {
		m_data_segment_buffer << 0;
    }
	assert(++it == std::end(tokens));
}

void Parser::string_array_decl_init(const std::cmatch& tokens)
{
    // std::cout << "########  string_array_decl_init  ########" << std::endl;
    // for (auto it = ++std::begin(tokens); it != std::end(tokens); ++it)
    // {
    //     std::cout << *it << ' ';
    // }
    // std::cout << std::endl;

	auto it = ++std::begin(tokens);
	const auto type = find_type_by_name(*it);
	m_data_segment_buffer << static_cast<int>(type); // insert type
	const auto variable_name = (*(++it)).str();
	const auto search = m_variable_name_to_id_map.find(variable_name);
	if (search != std::end(m_variable_name_to_id_map))
	{
		throw std::invalid_argument{ " Double declaration : \n"s + variable_name };
	}
	m_variable_name_to_id_map[std::string{ variable_name }] = m_free_id;
	m_data_segment_buffer << m_free_id;
	++m_free_id;
	++it;
	++it; // []
	++it; // =
	auto values_string = std::string{ (*(it)).str() };
	values_string.erase(std::begin(values_string));
	values_string.erase(std::end(values_string) - 1);
	const auto count = std::size(values_string);
	m_data_segment_buffer << count; // inset count
	for (const auto ch : values_string)
	{
		m_data_segment_buffer << static_cast<int>(ch);
	}
	assert(++it == std::end(tokens));
}

void Parser::array_decl_init(const std::cmatch& tokens)
{
    // std::cout << "########  array_decl_init  ########" << std::endl;
    // for (auto it = ++std::begin(tokens); it != std::end(tokens); ++it)
    // {
    //     std::cout << *it << ' ';
    // }
    // std::cout << std::endl;

	auto it = ++std::begin(tokens);
	const auto type = find_type_by_name(*it);
	m_data_segment_buffer << static_cast<int>(type); // insert type
	const auto variable_name = (*(++it)).str();
	const auto search = m_variable_name_to_id_map.find(variable_name);
	if (search != std::end(m_variable_name_to_id_map))
	{
		throw std::invalid_argument{ " Double declaration : \n"s + variable_name };
	}
	m_variable_name_to_id_map[std::string{ variable_name }] = m_free_id;
	m_data_segment_buffer << m_free_id;
	++m_free_id;
	++it;
	++it; // []
	++it; // =
	auto values_string = std::string{ (*(it)).str() };
	values_string = values_string.substr(1, std::size(values_string) - 4);
	const auto values = util::split(values_string, ", ");
	const auto count = std::size(values);
	m_data_segment_buffer << count; // inset count
	for (const auto& value : values)
	{
		m_data_segment_buffer << util::to_int_t(value);
	}
	assert(++++it == std::end(tokens));
}

Parser::code_iterator Parser::parse_data_segment(const code_iterator begin, const code_iterator end)
{
    auto it = begin;
    for (; it != end; ++it)
    {
        const auto res = (*it).find(".DATA");
        if (std::string::npos != res)
        {
            break;
        }
    }

    if (it == end)
    {
        throw std::invalid_argument{ "DATA segment not found." };
    }
    ++it;
    for (; it != end; ++it)
    {
        const auto& line = *it;
        std::cmatch result;
        if (std::regex_match(line.c_str(), result, RegexCollection::var_forward_decl))
        {
            this->parse_forward_declaration(result);
        }
        else if (std::regex_match(line.c_str(), result, RegexCollection::var_defin_init))
        {
            this->parse_definition_and_init(result);
        }
        else if (std::regex_match(line.c_str(), result, RegexCollection::array_decl))
        {
            this->parse_array_decl(result);
        }
        else if (std::regex_match(line.c_str(), result, RegexCollection::string_array_decl_init))
        {
            this->string_array_decl_init(result);
        }
        else if (std::regex_match(line.c_str(), result, RegexCollection::array_decl_init))
        {
            this->array_decl_init(result);
        }
        else
        {
            assert(false);
        }
    }

    return it;
}

Parser::code_iterator Parser::parse_code_segment(code_iterator begin, code_iterator end)
{
    return {};
}

Type Parser::find_type_by_name(const std::string& type_name)
{
	return s_string_to_type_enum_map.at(type_name);
}


const std::unordered_map<std::string, Instructions> Parser::s_string_to_instruction_enum_map
{
    {"ASSIGN", Instructions::assign},
    {"PRINT", Instructions::print},
    {"CMP", Instructions::cmp},
    {"JUMP", Instructions::jump},
    {"JZ", Instructions::jz},
    {"JNZ", Instructions::jnz},
    {"JO", Instructions::jo},
    {"JNO", Instructions::jno},
    {"JC", Instructions::jc},
    {"JNC", Instructions::jnc},
    {"ADD", Instructions::add},
    {"SUB", Instructions::sub},
    {"MUL", Instructions::mul},
    {"DIV", Instructions::div},
    {"MOV", Instructions::mov},
    {"CALL", Instructions::call},
    {"RET", Instructions::ret},
    {"END", Instructions::end},
    {"PUSH", Instructions::push},
    {"POP", Instructions::pop},
};

const std::unordered_map<std::string, Type> Parser::s_string_to_type_enum_map
{
    {"BYTE", Type::byte_type},
    {"CHAR", Type::char_type},
    {"WORD", Type::word_type},
    {"DWORD", Type::dword_type},
    {"QWORD", Type::qword_type},
};
