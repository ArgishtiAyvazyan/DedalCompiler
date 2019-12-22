/**
 * @copyright (C) 2019 by Argishti Ayvazyan
 * @file Configs.h
 * @author Argishti
 * @date 28 nov 2019
 * @brief The file contains interfaces for controlling compilation modes.
 */

#pragma once

namespace gen
{

/**
 * @class Config
 * @brief A class that contains the global constant parameters of the program.
 */
class Config
{
public:

    /**
     * @brief if true, various mechanisms for checking the validity of the \n
     *      code are turned on, which can cause a slowdown in execution time \n
     *      and also includes a detailed infarmation for data output.
     */
    static constexpr bool DEBUG = true;

    /**
     * @brief If true, the Parser logging system is enabled.
     */
    static constexpr bool ENABLE_PARSER_LOGING = false;

    /**
     * @brief If true, the Lexer logging system is enabled.
     */
    static constexpr bool ENABLE_LEXER_LOGING = false;
};

} // namespace gen