#include <iostream>
#include "Compiler.h"
#include "Interpreter.h"


using namespace std::string_literals;
using namespace std::string_view_literals;


int main(int argc, char* argv[])
// try
{
	const auto file_path = R"(C:\Users\argishta\source\repos\dedal\dedal_test\tests\test1.txt)"sv;
	
	Compiler compiler{ file_path };



	const auto ec = compiler.compile_code();

	std::cout << "Stack Size : " << ec.stack_size() << std::endl;

	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

	std::cout << "Data segment :\n" << ec.data_segment() << std::endl;

	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;

	std::cout << "Code segment :\n" << ec.code_segment() << std::endl;

	Interpreter interpreter{ compiler.compile_code() };

	interpreter.run();

	return 0;
}
// catch(const std::exception& e)
// {
// 	std::cerr << e.what() << std::endl;
// 	return -1;
// }
