/**
 * @file Decl.h
 * @author Argishti Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for core essence.
 * @date 23-12-2019
 * @copyright Copyright (c) 2019
 */


#pragma once


namespace core
{

/**
 * @brief The c++ representation of assembly types.
 */

using TCHAR  = char;
using TBYTE  = std::int8_t;
using TWORD  = std::int16_t;
using TDWORD = std::int32_t;
using TQWORD = std::int64_t;



/**
 * @enum EDataType
 * @brief Declaration assembly types.
 */
enum class EDataType
{
      CHAR  // Character
    , BYTE  // Integer 8-bit
    , WORD  // Integer 16-bit
    , DWORD // Integer 32-bit
    , QWORD // Integer 64-bit
};


/**
 * @brief Declared operations.
 */
enum class EOperationCode : uint8_t
{
      ASSIGN
    , PRINT
    , CMP
    , TEST
    , JUMP
    , JZ
    , JNZ
    , JO
    , JNO
    , JC
    , JNC
    , JNE
    , ADD
    , SUB
    , MUL
    , IMUL
    , DIV
    , IDIV
    , MOVE
    , CALL
    , PUSH
    , POP
    , PUSHSF
    , POPSF
    , NOP
    , SWAP
    , AND
    , GFLR
    , SFLR
    , INC
    , DEC
    , SHL
    , SHR
    , ROL
    , ROR
    , SAL
    , SAR
    , RCL
    , RCR
    , ADC
    , SBB
    , NEG
    , CAST
    , OUT
    , IN
    , LOAD
    , STORE
    , BREAK
    , RET
    , NON
};

/**
 * @brief Size of operand.
 */
enum class EOperationSize
{
      B  // 1 bytes
    , W  // 2 bytes
    , DW // 4 bytes
    , QW // 8 bytes
};

} // core