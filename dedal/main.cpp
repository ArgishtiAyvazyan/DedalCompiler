#include <iostream>
#include "FileReader.h"
#include <cassert>
#include <regex>
#include <string>
#include "Parser.h"

using namespace std::string_literals;

int main(int argc, char* argv[])
// try
{
	// FileReader fr{ R"(C:\Users\argishta\source\repos\assembly_interpreter\assembly_interpreter\tests\test.txt)" };
 //
 //    for (const auto& line : fr.read_in())
 //    {
	// 	std::cout << line << std::endl;
 //    }

	std::string var = "Zara =2245346";
	// 	var.erase(var.begin());
	// var.erase(var.end() - 1);
	// std::cout << var << std::endl;
	std::smatch matches;

    // if (var[var.length() - 1] == ']')
	// {
	// 	const std::regex re("([[:digit:]]+)");
	// 	regex_search(var, matches, re);
	// 	std::cout << matches[0] << std::endl;
	// 	std::cout << matches[1] << std::endl;
 //
 //        const auto number = std::stoi(matches[1]);
	// 	std::cout << number << std::endl;
	// }


	FileReader fr{ R"(C:\Users\argishta\source\repos\dedal\dedal_test\tests\test1.txt)" };
	Parser p{ fr.read_in() };
	return 0;
}
// catch(const std::exception& e)
// {
// 	std::cerr << e.what() << std::endl;
// 	return -1;
// }
