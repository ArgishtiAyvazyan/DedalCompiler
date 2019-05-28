#include "Buffer.h"
#include <stdexcept>

Buffer::Buffer() = default;

void Buffer::operator<<(const int value)
{
    m_data.push_back(value);
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
