#pragma once
#include <unordered_map>
#include <vector>

using reg_id_t = std::size_t;


// @link http://cpubook.ru/Регистры%20процессора/Регистр%20флагов/
struct StatusRegister
{
    bool CF : 1;
    bool PF : 1;
    bool AF : 1;
    bool ZF : 1;
    bool SF : 1;
    bool TF : 1;
    bool IF : 1;
    bool DF : 1;
    bool OF : 1;
    bool IOPL : 1;
    bool NT : 1;
    bool RF : 1;
    bool VM : 1;
    bool AC : 1;
    bool VIF : 1;
    bool VIP : 1;
    bool ID : 1;
};

class TypeSize
{
public:
    enum class RegSize
    {
        B,
        W,
        DB,
        QW
    };

    static RegSize reg_size_name_to_enum(const std::string& name)
    {
        return s_name_to_reg_size.at(name);
    }

private:
    static inline const std::unordered_map<std::string, RegSize> s_name_to_reg_size{
        {"B", RegSize::B},
        {"W", RegSize::W},
        {"DB", RegSize::DB},
        {"QW", RegSize::QW},
    };
};

class CPU
{
    bool is_add_overflow(reg_id_t left, reg_id_t right) noexcept;

    bool is_add_underflow(reg_id_t left, reg_id_t right) noexcept;

    bool is_sub_overflow(reg_id_t left, reg_id_t right) noexcept;

    bool is_sub_underflow(reg_id_t left, reg_id_t right) noexcept;

    bool is_mul_overflow(reg_id_t left, reg_id_t right) noexcept;

    bool is_mul_underflow(reg_id_t left, reg_id_t right) noexcept;

public:
    void add(reg_id_t left, reg_id_t right);

    void sub(reg_id_t left, reg_id_t right);

    void mul(reg_id_t left, reg_id_t right);

    void div(reg_id_t left, reg_id_t right);

    void mov(reg_id_t left, reg_id_t right);

    void cmp(reg_id_t left, reg_id_t right);

    int get_register_value(reg_id_t id);

    void set_register_value(reg_id_t id, int value);

	int get_register_value(reg_id_t id) const;

    void set_ip(std::size_t new_ip);

    std::size_t get_ip() const;

    void stack_push(TypeSize::RegSize type_size, int64_t value);

    int64_t stack_pop(TypeSize::RegSize type_size);

public:
    CPU(const size_t stack_size);

    ~CPU();

    CPU(const CPU&) = delete;

    CPU& operator=(const CPU&) = delete;

    std::size_t m_ip;

    StatusRegister status_register;

private:
	static constexpr auto registers_count = 100u;
    std::size_t m_stack_size;
    std::vector<int> m_processor_registers;
    char* const m_call_stack;
    char* m_stack_pointer;

};
