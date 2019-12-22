#include <gtest/gtest.h>

#include "ParserUnitTests.hpp"
#include "FlagsUnitTests.hpp"
#include "MemoryUnitTests.hpp"
#include "CompilerUnitTests.hpp"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
