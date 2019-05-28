#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "ParserDecl.h"
#include "Buffer.h"
#include <regex>

class Parser
 {
 	using code_iterator = std::vector<std::string>::const_iterator;

 public:

     explicit Parser(const std::vector<std::string>& txt_code);

     
 private:

 	code_iterator parse_stack_size(code_iterator begin, code_iterator end);

    void parse_forward_declaration(const std::cmatch& tokens);

    void parse_definition_and_init(const std::cmatch& tokens);

    void parse_array_decl(const std::cmatch& tokens);

    void string_array_decl_init(const std::cmatch& tokens);

    void array_decl_init(const std::cmatch& tokens);

 	code_iterator parse_data_segment(code_iterator begin, code_iterator end);
 	code_iterator parse_code_segment(code_iterator begin, code_iterator end);



	static Type find_type_by_name(const std::string& type_name);

 private:
 	std::size_t m_stack_size;
 	Buffer m_data_segment_buffer;
 	Buffer m_code_segment_buffer;
	std::unordered_map<std::string, std::size_t> m_variable_name_to_id_map;
	std::size_t m_free_id;

 	static const std::unordered_map<std::string, Instructions> s_string_to_instruction_enum_map;
 	static const std::unordered_map<std::string, Type> s_string_to_type_enum_map;
 };
