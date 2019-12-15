/**
 * @file CFlags.cpp
 * @author Argishty Ayvazyan (argishty.ayvazyan@gmail.com)
 * @brief Implementation for CFlags class.
 * @date 15-12-2019
 * @copyright Copyright (c) 2019
 */


#include "CFlags.h"

namespace vm
{

CFlags::CFlags()
    : m_ui16Value(0)
{
}

bool CFlags::getCarry() const
{
    return (m_ui16Value & eMask_CF) != 0;
}

bool CFlags::getZero() const
{
    return (m_ui16Value & eMask_ZF) != 0;
}

bool CFlags::getSign() const
{
    return (m_ui16Value & eMask_SF) != 0;
}

bool CFlags::getOverflow() const
{
    return (m_ui16Value & eMask_OF) != 0;
}

uint16_t CFlags::getFlags() const
{
    return (m_ui16Value & eMask_ALL);
}

void CFlags::setCarry(bool b)
{
    m_ui16Value = b ? (m_ui16Value | uint16_t(eMask_CF)) : (m_ui16Value & ~uint16_t(eMask_CF));
}

void CFlags::setZero(bool b)
{
    m_ui16Value = b ? (m_ui16Value | uint16_t(eMask_ZF)) : (m_ui16Value & ~uint16_t(eMask_ZF));
}

void CFlags::setSign(bool b)
{
    m_ui16Value = b ? (m_ui16Value | uint16_t(eMask_SF)) : (m_ui16Value & ~uint16_t(eMask_SF));
}

void CFlags::setOverflow(bool b)
{
    m_ui16Value = b ? (m_ui16Value | uint16_t(eMask_OF)) : (m_ui16Value & ~uint16_t(eMask_OF));
}

void CFlags::setFlags(uint16_t ui16Value)
{
    m_ui16Value = (ui16Value & eMask_ALL);
}

void CFlags::clearCarry()
{
    m_ui16Value &= ~uint16_t(eMask_CF);
}

void CFlags::clearZero()
{
    m_ui16Value &= ~uint16_t(eMask_ZF);
}

void CFlags::clearSign()
{
    m_ui16Value &= ~uint16_t(eMask_SF);
}

void CFlags::clearOverflow()
{
    m_ui16Value &= ~uint16_t(eMask_OF);
}

void CFlags::clearFlags()
{
    m_ui16Value = 0;
}

bool CFlags::isEqual() const
{
    return (getZero() == true);
}

bool CFlags::isNotEqual() const
{
    return (getZero() == false);
}

bool CFlags::isAbove() const
{
    return (getCarry() == false && getZero() == false);
}

bool CFlags::isAboveOrEqual() const
{
    return (getCarry() == false);
}

bool CFlags::isBelow() const
{
    return (getCarry() == true);
}

bool CFlags::isBelowOrEqual() const
{
    return (getCarry() == true || getZero() == true);
}

bool CFlags::isGreat() const
{
    return (getZero() == false && getSign() == getOverflow());
}

bool CFlags::isGreatOrEqual() const
{
    return (getSign() == getOverflow());
}

bool CFlags::isLow() const
{
    return (getSign() != getOverflow());
}

bool CFlags::isLowOrEqual() const
{
    return (getZero() == true && getSign() != getOverflow());
}

bool CFlags::isOverflow() const
{
    return (getOverflow() == true);
}

bool CFlags::isNotOverflow() const
{
    return (getOverflow() == false);
}

bool CFlags::isSigned() const
{
    return (getSign() == true);
}

bool CFlags::isNotSigned() const
{
    return (getSign() == false);
}

} // namespace gen
