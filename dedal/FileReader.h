#pragma once

#include <vector>
#include <string>
#include <fstream>


class FileReader
{
public:

    explicit FileReader(const std::string& file_name);

	~FileReader();

	std::vector<std::string> read_in();

	void write_out(const std::vector<std::string>& lines);

private:
	std::fstream m_buffer;
};
