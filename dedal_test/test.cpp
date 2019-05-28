#include "pch.h"
#include "../dedal/FileReader.h"
#include "../dedal/FileReader.cpp"
// #include "../dedal/Parser.h"
// #include "../dedal/Parser.cpp"

TEST(FileRederTest, ReadWriteTest)
{
	FileReader fr{ R"(C:\Users\argishta\source\repos\dedal\dedal_test\tests\test.txt)" };

	auto string_random_generator = [](const int len = 50)
	{
		static constexpr char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		std::string rand_string;
		rand_string.reserve(len);
		for (auto i = 0; i < len; ++i)
		{
			rand_string += alphanum[rand() % (sizeof(alphanum) - 1)];
		}

		return rand_string;
	};

	constexpr auto file_lines_count = 1000u;

	std::vector<std::string> lines;
	lines.resize(file_lines_count);

	for (auto i = 0u; i < file_lines_count; ++i)
	{
		lines[i] = string_random_generator();
	}


	fr.write_out(lines);

	const auto file_lines = fr.read_in();

	for (auto i = 0u; i < file_lines_count; ++i)
	{
		ASSERT_EQ(lines[i], file_lines[i]);
	}
}

// TEST(ParserTest, ReadTest)
// {
// 	FileReader fr{ R"(C:\Users\argishta\source\repos\dedal\dedal_test\tests\test1.txt)" };
// 	Parser p { fr.read_in() };
// }