#pragma once
#include <vector>
#include <string>
#include <stdexcept>

namespace util
{
    std::vector<std::string> split(std::string input, const std::string& regex = " ");

    int to_int_t(const std::string& num);

    std::size_t to_size_t(const std::string& num);

    double to_double(const std::string& num);
}
