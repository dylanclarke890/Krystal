#include "MTL/Common/Mod.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void TestMod()
  {
    KRYS_EXPECT_EQUAL("Positive dividend and divisor", MTL::Mod(10, 3), 1);
    KRYS_EXPECT_EQUAL("Negative dividend", MTL::Mod(-10, 3), -1);
    KRYS_EXPECT_EQUAL("Negative divisor", MTL::Mod(10, -3), 1);
    KRYS_EXPECT_EQUAL("Negative dividend and divisor", MTL::Mod(-10, -3), -1);
    KRYS_EXPECT_EQUAL("Dividend is zero", MTL::Mod(0, 3), 0);
    KRYS_EXPECT_EQUAL("Positive float mod", MTL::Mod(10.5f, 3.0f), 1.5f);
    KRYS_EXPECT_EQUAL("Negative float mod", MTL::Mod(-10.5f, 3.0f), -1.5f);
    KRYS_EXPECT_EQUAL("Negative divisor float mod", MTL::Mod(10.5f, -3.0f), 1.5f);
    KRYS_EXPECT_EQUAL("Negative dividend and divisor float mod", MTL::Mod(-10.5f, -3.0f), -1.5f);
    KRYS_EXPECT_EQUAL("Large dividend", MTL::Mod(std::numeric_limits<int>::max(), 2), 1);
    KRYS_EXPECT_EQUAL("Smallest negative dividend", MTL::Mod(std::numeric_limits<int>::min(), 2), 0);
  }
}