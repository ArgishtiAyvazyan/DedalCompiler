#include "Utility.h"
#include <algorithm>
#include <regex>
#include <charconv>
#include <system_error>


std::vector<std::string> util::split(std::string input, const std::string& regex)
{
    input.erase(std::unique_copy(std::begin(input), std::end(input), std::begin(input)
      , [](const char c1, const char c2)
        {
            return c1 == ' ' && c2 == ' ';
        }), std::end(input));
    const std::regex re(regex);
    const std::sregex_token_iterator first{std::begin(input), std::end(input), re, -1};
    const std::sregex_token_iterator last;
    return {first, last};
}

int util::to_int_t(const std::string& num)
{
    auto result = 0;
    if (auto [p, ec] = std::from_chars(num.data(), num.data() + num.length(), result); ec != std::error_code())
    {
        return result;
    }

    throw std::logic_error{"is not a int"};
}

std::size_t util::to_size_t(const std::string& num)
{
    auto result = 0u;
    if (auto [p, ec] = std::from_chars(num.data(), num.data() + num.length(), result); ec != std::error_code())
    {
        return result;
    }

    throw std::logic_error{"is not a size_t"};
}

double util::to_double(const std::string& num)
{
    return std::stod(num);
}
