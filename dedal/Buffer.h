#pragma once
#include <vector>
#include <stdexcept>

class Buffer
{
public:

	Buffer();

	Buffer& operator << (const int value);

	bool operator >> (int& value);

	void reset_offset(const size_t new_offset = 0);

	std::ostream& write_out(std::ostream& os) const;

private:
	std::vector<size_t> m_data;
	std::size_t m_current_offset{ 0u };
};

std::ostream& operator<<(std::ostream& os, Buffer const& m);
