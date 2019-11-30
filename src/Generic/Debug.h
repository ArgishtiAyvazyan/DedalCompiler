#pragma once

/**
 * @copyright (C) 2019 by Argishti Ayvazyan
 * @file Debug.h
 * @author Argishti
 * @date 30 nov 2019
 * @brief The file contains interfaces for debugging tools.
 */

/**
 * @class Debug
 * @brief The class is a wrapper for debugging tools.
 */
class Debug
{
public:

    /**
     * @brief If the argument expression of this macro with functional form compares \n
     *          equal to zero (i.e., the expression is false), a message is written to \n
     *          the standard error device, print stack trace and abort is called, \n
     *          terminating the program execution.
     *
     * @param expression
     */
    static void ASSERT(const bool expression);
};