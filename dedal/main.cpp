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
	FileReader fr{ R"(C:\Users\argishta\source\repos\dedal\dedal_test\tests\test1.txt)" };
	Parser p{ fr.read_in() };
	return 0;
}
// catch(const std::exception& e)
// {
// 	std::cerr << e.what() << std::endl;
// 	return -1;
// }
