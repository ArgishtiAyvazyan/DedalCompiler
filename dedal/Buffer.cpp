#include "Buffer.h"
#include <stdexcept>
#include <iostream>

Buffer::Buffer() = default;

Buffer& Buffer::operator<<(const int value)
{
    m_data.push_back(value);
	return *this;
}

bool Buffer::operator>>(int& value)
{
    if (m_current_offset >= m_data.size())
    {
        return false;
    }

    value = m_data.at(m_current_offset);
    ++m_current_offset;
    return true;
}

void Buffer::reset_offset(const size_t new_offset)
{
    if (new_offset > m_data.size())
    {
        throw std::out_of_range{"Invalid offset."};
    }

    m_current_offset = new_offset;
}
std::ostream& Buffer::write_out(std::ostream& os) const
{
	for (const auto item : m_data)
	{
		if (item == std::numeric_limits<int>::max())
		{
			os << std::endl;
		}
		else
		{
			os << item;
			os << ' ';
		}
	}

	return os;
}

std::ostream& operator<<(std::ostream& os, Buffer const& m)
{
	return m.write_out(os);
}
