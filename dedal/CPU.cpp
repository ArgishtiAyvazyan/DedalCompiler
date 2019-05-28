#include "CPU.h"
#include <cassert>
#include <cstring>

auto CPU::is_add_overflow(const reg_id_t left, const reg_id_t right) noexcept -> bool
{
    return (m_processor_registers[right] > 0) && (m_processor_registers[left] > std::numeric_limits<int>::max() -
        m_processor_registers[right]);
}

auto CPU::is_add_underflow(const reg_id_t left, const reg_id_t right) noexcept -> bool
{
    return (m_processor_registers[right] < 0) && (m_processor_registers[left] < std::numeric_limits<int>::min() -
        m_processor_registers[right]);
}

auto CPU::is_sub_overflow(const reg_id_t left, const reg_id_t right) noexcept -> bool
{
    return (m_processor_registers[right] < 0) && (m_processor_registers[left] > std::numeric_limits<int>::max() +
        m_processor_registers[right]);
}

auto CPU::is_sub_underflow(const reg_id_t left, const reg_id_t right) noexcept -> bool
{
    return (m_processor_registers[right] > 0) && (m_processor_registers[left] < std::numeric_limits<int>::min() +
        m_processor_registers[right]);
}

auto CPU::is_mul_overflow(const reg_id_t left, const reg_id_t right) noexcept -> bool
{
    return (m_processor_registers[left] > std::numeric_limits<int>::max() / m_processor_registers[right]) || ((
        m_processor_registers[left] == -1) && (m_processor_registers[right] == std::numeric_limits<int>::min()));
}

auto CPU::is_mul_underflow(const reg_id_t left, const reg_id_t right) noexcept -> bool
{
    return (m_processor_registers[left] < std::numeric_limits<int>::min() / m_processor_registers[right]) || ((
        m_processor_registers[left] == -1) && (m_processor_registers[right] == std::numeric_limits<int>::min()));
}

void CPU::add(const reg_id_t left, const reg_id_t right)
{
    status_register.OF = is_add_overflow(left, right) || is_add_underflow(left, right);
    m_processor_registers[left] += m_processor_registers[right];
    status_register.ZF = (m_processor_registers[left] == 0);
    status_register.CF = ((m_processor_registers[left] >> 31) & 1u);
}

void CPU::sub(const reg_id_t left, const reg_id_t right)
{
    status_register.OF = is_sub_overflow(left, right) || is_sub_underflow(left, right);
    m_processor_registers[left] -= m_processor_registers[right];
    status_register.ZF = (m_processor_registers[left] == 0);
    status_register.CF = ((m_processor_registers[left] >> 31) & 1u);
}

void CPU::mul(const reg_id_t left, const reg_id_t right)
{
    status_register.OF = is_mul_overflow(left, right) || is_mul_underflow(left, right);
    m_processor_registers[left] *= m_processor_registers[right];
    status_register.ZF = (m_processor_registers[left] == 0);
    status_register.CF = ((m_processor_registers[left] >> 31) & 1u);
}

void CPU::div(const reg_id_t left, const reg_id_t right)
{
    status_register.OF = false;
    m_processor_registers[left] /= m_processor_registers[right];
    status_register.ZF = (m_processor_registers[left] == 0);
    status_register.CF = ((m_processor_registers[left] >> 31) & 1u);
}

void CPU::cmp(const reg_id_t left, const reg_id_t right)
{
    status_register.OF = is_sub_overflow(left, right) || is_sub_underflow(left, right);
    const auto res = m_processor_registers[left] - m_processor_registers[right];
    status_register.ZF = (res == 0);
    status_register.CF = ((res >> 31) & 1u);
}

void CPU::mov(const reg_id_t left, const reg_id_t right)
{
    m_processor_registers[left] = m_processor_registers[right];
}

auto CPU::get_register_value(const reg_id_t id) -> int
{
    return m_processor_registers.at(id);
}

void CPU::set_register_value(const reg_id_t id, const int value)
{
    m_processor_registers[id] = value;
}

int CPU::get_register_value(const reg_id_t id) const
{
	return m_processor_registers.at(id);
}

void CPU::set_ip(const std::size_t new_ip)
{
    m_ip = new_ip;
}

std::size_t CPU::get_ip() const
{
    return m_ip;
}

void CPU::stack_push(const TypeSize::RegSize type_size, const int64_t value)
{
    const auto load_in_stack = [this](const auto val)
    {
        using type = decltype(val);
        type tmp = static_cast<type>(val);
        m_stack_pointer -= sizeof(type);
        std::memcpy(m_stack_pointer, &tmp, sizeof(type));
    };

    switch (type_size)
    {
    case TypeSize::RegSize::B:
        load_in_stack(static_cast<int8_t>(value));
        break;
    case TypeSize::RegSize::W:
        load_in_stack(static_cast<int16_t>(value));
        break;
    case TypeSize::RegSize::DB:
        load_in_stack(static_cast<int32_t>(value));
        break;
    case TypeSize::RegSize::QW:
        load_in_stack(static_cast<int64_t>(value));
        break;
    default:
        assert(false);
    }
}

int64_t CPU::stack_pop(const TypeSize::RegSize type_size)
{
    switch (type_size)
    {
    case TypeSize::RegSize::B:
        {
            int8_t tmp{0};
            std::memcpy(&tmp, m_stack_pointer, sizeof(int8_t));
            m_stack_pointer += sizeof(int8_t);
            return tmp;
        }
    case TypeSize::RegSize::W:
        {
            int16_t tmp{0};
            std::memcpy(&tmp, m_stack_pointer, sizeof(int16_t));
            m_stack_pointer += sizeof(int16_t);
            return tmp;
        }
    case TypeSize::RegSize::DB:
        {
            int32_t tmp{0};
            std::memcpy(&tmp, m_stack_pointer, sizeof(int32_t));
            m_stack_pointer += sizeof(int32_t);
            return tmp;
        }
    case TypeSize::RegSize::QW:
        {
            int64_t tmp{0};
            std::memcpy(&tmp, m_stack_pointer, sizeof(int64_t));
            m_stack_pointer += sizeof(int64_t);
            return tmp;
        }
    default:
        assert(false);
    }

    return {};
}

CPU::CPU()
    : m_ip{0}
    , status_register{}
    , m_processor_registers (registers_count)
    , m_call_stack{new char[max_stack_size]}
    , m_stack_pointer{m_call_stack + max_stack_size}
{
}

CPU::~CPU()
{
    delete[] m_call_stack;
}
