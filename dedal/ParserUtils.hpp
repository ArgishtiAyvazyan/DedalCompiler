#pragma once

#include <regex>

/**
 * @brift Code by Karen Nikoghosyan
 */
class RegexCollection
{

public:
    
// supports forward declaration
// CHAR var; 
// BYTE _var2;
// WORD _var2var_;
static inline const std::regex var_forward_decl
{
    "(BYTE|CHAR|WORD|DWORD|QWORD)"
    "([ \t]*[a-zA-Z_][a-zA-Z0-9_]*);"
};

// support variable defin. with init statement
// CHAR var = 'A'; 
// BYTE _var2 = 342; 
// WORD _var2var_=234;
static inline const std::regex var_defin_init
{
    "(BYTE|CHAR|WORD|DWORD|QWORD)"
    "([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
    "([ \t]*=[ \t]*)"
    "('.'|\\d*);"
};

// support array decl.
// CHAR arr1[20]; || BYTE arr2_[];
static inline const std::regex array_decl
{
    "(BYTE|CHAR|WORD|DWORD|QWORD)"
    "([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
    "(\\[\\d*\\]|\\[\\]);"
};

// support string array decl. & init.
//CHAR str1[] = "Hello World!";
static inline const std::regex string_array_decl_init
{
    "(CHAR)"
    "([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
    "(\\[\\])"
    "([ \t]*=[ \t]*)"
    "(\".*\");"
};

// support array decl. & init.
//DWORD adwVal7[5] = {10,20,30,-40,};
static inline const std::regex array_decl_init
{
    "(BYTE|CHAR|WORD|DWORD|QWORD)"
    "([ \t]*[a-zA-Z_][a-zA-Z0-9_]*)"
    "(\\[\\d*\\]|\\[\\])"
    "([ \t]*=[ \t]*)"
    "(\\{(-?\\d*,[ \t]*)*\\};)"
};

};
