#include "FileReader.h"
#include <cassert>

FileReader::FileReader(const std::string& file_name)
	: m_buffer{ file_name, std::fstream::out | std::fstream::in }
{
	if (!m_buffer.is_open())
	{
		throw std::invalid_argument("fatal error: no input files");
	}
}

FileReader::~FileReader()
{
	try
	{
		if (m_buffer.is_open())
		{
			m_buffer.close();
		}
	}
	catch (...)
	{
		assert(false);
	}
}


std::vector<std::string> FileReader::read_in()
{
	std::vector<std::string> result;

	m_buffer.seekg(0);

	if (std::string line; m_buffer.is_open())
	{
		while (getline(m_buffer, line))
		{
			if (line.empty())
			{
				continue;
			}

			result.push_back(line);
		}
	}

	return result;
}

void FileReader::write_out(const std::vector<std::string>& lines)
{
	if (!m_buffer.is_open())
	{
		throw std::invalid_argument("fatal error: no input files");
	}

	m_buffer.seekg(0);
	
    for (const auto& line : lines)
	{
		m_buffer << line << std::endl;
	}
}
