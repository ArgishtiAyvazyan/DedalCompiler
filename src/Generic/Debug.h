/**
 * @copyright (C) 2019 by Argishti Ayvazyan
 * @file Debug.h
 * @author Argishti
 * @date 30 nov 2019
 * @brief The file contains interfaces for debugging tools.
 */

#pragma once

#include <string_view>

namespace gen
{

/**
 * @class Debug
 * @brief The class is a wrapper for debugging tools.
 */
class Debug
{
public:

    /**
     * @brief If the argument expression of this macro with functional form \n
     *          compares equal to zero (i.e., the expression is false), \n
     *          a message is written to the standard error device, print \n
     *          stack trace and abort is called, terminating the program \n
     *          execution.
     *
     * @param expression Expression to be evaluated. If this expression \n
     *          evaluates to 0, this causes an assertion failure that \n
     *          terminates the program.
     */
    static void ASSERT(const bool expression);


    /**
     * @brief If the argument expression of this macro with functional form \n
     *          compares equal to zero (i.e., the expression is false), \n
     *          a message is written to the standard error device, print \n
     *          stack trace and abort is called, terminating the program \n
     *          execution.
     *
     * @param expression Expression to be evaluated. If this expression \n
     *          evaluates to 0, this causes an assertion failure that \n
     *          terminates the program.
     * @param message Message to be printed in case of the assertion.
     */
    static void ASSERT(const bool expression, std::string_view message);
};

} // namespace gen