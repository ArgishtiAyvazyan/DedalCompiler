#include <iostream>
#include "FileReader.h"
#include <cassert>
#include <regex>
#include <string>
#include "Parser.h"
#include "ParserDecl.h"
using namespace std::string_literals;



int main(int argc, char* argv[])
// try
{
	FileReader fr{ R"(C:\Users\argishta\source\repos\dedal\dedal_test\tests\test1.txt)" };
	Parser p{ fr.read_in() };


	/*std::string var = ".SHATCK = [2245346]";
	std::cout << var << std::endl;
	std::smatch matches;

	std::regex re("([[:digit:]]+)");
	regex_search(var, matches, re);
	const int number = stoi(matches[1]);
	std::cout << number << std::endl;*/

	return 0;
}
// catch(const std::exception& e)
// {
// 	std::cerr << e.what() << std::endl;
// 	return -1;
// }
