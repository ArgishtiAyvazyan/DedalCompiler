#pragma once

#include "CMemory.h"
#include "ParserDecl.hpp"

TEST(MemoryTest, SimpleTest)
{
    {
        vm::CMemory memory;
        ASSERT_EQ(memory.Size(), 0);
    }
    {
        vm::CMemory memory (1024);
        ASSERT_EQ(memory.Size(), 1024);
    }
}

TEST(MemoryTest, NullTest)
{
    vm::CMemory memory (1024);
    try
    {
        TBYTE value = memory.Read<TBYTE>(vm::CMemory::nulladdress);
    } catch (const gen::CException& a)
    {
        return;
    }
    ASSERT_TRUE(false);
}

TEST(MemoryTest, OutOfMemTest)
{
    vm::CMemory memory (1024);
    try
    {
        vm::CMemory::TAddress address = 2048;
        TBYTE value = memory.Read<TBYTE>(address);
    } catch (const gen::CException& a)
    {
        return;
    }
    ASSERT_TRUE(false);
}

TEST(MemoryTest, ReadWriteTest)
{
    vm::CMemory memory (1024);
    const TBYTE byte = 123;
    const TWORD word = 1234;
    const TDWORD dword = 12345678;
    const TQWORD qwword = 1234567890;

    vm::CMemory::TAddress address = 64;
    memory.Write<TBYTE>(address, byte);
    address += sizeof(TBYTE);
    memory.Write<TWORD>(address, word);
    address += sizeof(TWORD);
    memory.Write<TDWORD>(address, dword);
    address += sizeof(TDWORD);
    memory.Write<TQWORD>(address, qwword);

    ASSERT_EQ(memory.Read<TQWORD>(address), qwword);
    address -= sizeof(TDWORD);
    ASSERT_EQ(memory.Read<TDWORD>(address), dword);
    address -= sizeof(TWORD);
    ASSERT_EQ(memory.Read<TWORD>(address), word);
    address -= sizeof(TBYTE);
    ASSERT_EQ(memory.Read<TBYTE>(address), byte);
}

TEST(BufferTest, ReadWriteTest)
{
    compiler::CBuffer buffer;
    const int target[] = { 1234, 4321, 1234, 4312 };
    const double target2[] = { 12.12, 23.23, 45.45 };
    buffer << target[0] << target[1] << target[2] << target[3] << target2[0] << target2[1] << target2[2];
    int res[] = { -1, -1, -1, -1 };
    double res2[] = { -1, -1, -1 };
    buffer >> res[0] >> res[1] >> res[2] >> res[3] >> res2[0] >> res2[1] >> res2[2];

    ASSERT_EQ(target[0], res[0]);
    ASSERT_EQ(target[1], res[1]);
    ASSERT_EQ(target[2], res[2]);
    ASSERT_EQ(target[3], res[3]);
    ASSERT_EQ(target2[0], res2[0]);
    ASSERT_EQ(target2[1], res2[1]);
    ASSERT_EQ(target2[2], res2[2]);
}