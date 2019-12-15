#pragma once

#include "CMemory.h"
#include "ParserDecl.hpp"

TEST(MemoryTest, SimpleTest)
{
    {
        vm::CMemory memory;
        ASSERT_EQ(memory.Size(), 4096);
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
