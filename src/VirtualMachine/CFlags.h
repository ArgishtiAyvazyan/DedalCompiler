/**
 * @file CFlags.h
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Declaration for CFlags class.
 * @date 15-12-2019
 * @copyright Copyright (c) 2019
 */

#pragma once

#include <cstdint>

namespace vm
{

/**
 * @class CFlags
 * @brief The CPU flags container class.
 */
class CFlags
{
public:

    /**
     * @brief The flags.
     */
    enum : uint16_t
    {
          eMask_CF = 0b0001
        , eMask_ZF = 0b0010
        , eMask_SF = 0b0100
        , eMask_OF = 0b1000

        , eMask_ALL = 0b0000
    };

    CFlags();

    [[nodiscard]] bool getCarry() const;
    [[nodiscard]] bool getZero() const;
    [[nodiscard]] bool getSign() const;
    [[nodiscard]] bool getOverflow() const;
    [[nodiscard]] uint16_t getFlags() const;

    void setCarry(bool);
    void setZero(bool);
    void setSign(bool);
    void setOverflow(bool);
    void setFlags(uint16_t);

    void clearCarry();
    void clearZero();
    void clearSign();
    void clearOverflow();
    void clearFlags();

    [[nodiscard]] bool isEqual() const;
    [[nodiscard]] bool isNotEqual() const;
    [[nodiscard]] bool isAbove() const;
    [[nodiscard]] bool isAboveOrEqual() const;
    [[nodiscard]] bool isBelow() const;
    [[nodiscard]] bool isBelowOrEqual() const;
    [[nodiscard]] bool isGreat() const;
    [[nodiscard]] bool isGreatOrEqual() const;
    [[nodiscard]] bool isLow() const;
    [[nodiscard]] bool isLowOrEqual() const;
    [[nodiscard]] bool isOverflow() const;
    [[nodiscard]] bool isNotOverflow() const;
    [[nodiscard]] bool isSigned() const;
    [[nodiscard]] bool isNotSigned() const;

private:
    uint16_t	m_ui16Value;
};


} // namespace vm