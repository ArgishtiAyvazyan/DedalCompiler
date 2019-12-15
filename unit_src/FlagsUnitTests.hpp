#pragma once

#include "CFlags.h"

TEST(FlagTest, SimpleTest)
{
    vm::CFlags flags;
    ASSERT_EQ(flags.getCarry(), false);
    ASSERT_EQ(flags.getZero(), false);
    ASSERT_EQ(flags.getSign(), false);
    ASSERT_EQ(flags.getOverflow(), false);
}


TEST(FlagTest, SetTest)
{
    vm::CFlags flags;
    flags.setCarry(true);
    flags.setZero(true);
    flags.setSign(true);
    flags.setOverflow(true);
    ASSERT_EQ(flags.getCarry(), true);
    ASSERT_EQ(flags.getZero(), true);
    ASSERT_EQ(flags.getSign(), true);
    ASSERT_EQ(flags.getOverflow(), true);

    flags.setCarry(false);
    flags.setZero(false);
    flags.setSign(false);
    flags.setOverflow(false);
    ASSERT_EQ(flags.getCarry(), false);
    ASSERT_EQ(flags.getZero(), false);
    ASSERT_EQ(flags.getSign(), false);
    ASSERT_EQ(flags.getOverflow(), false);
}
