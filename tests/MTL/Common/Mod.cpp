#include "MTL/Common/Mod.hpp"
#include "tests/__utils__/Expect.hpp"

#include <limits>

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void TestMod()
  {
    KRYS_EXPECT_EQUAL("Positive dividend and divisor", Mod(10, 3), 1);
    KRYS_EXPECT_EQUAL("Negative dividend", Mod(-10, 3), -1);
    KRYS_EXPECT_EQUAL("Negative divisor", Mod(10, -3), 1);
    KRYS_EXPECT_EQUAL("Negative dividend and divisor", Mod(-10, -3), -1);
    KRYS_EXPECT_EQUAL("Dividend is zero", Mod(0, 3), 0);
    KRYS_EXPECT_EQUAL("Positive float mod", Mod(10.5f, 3.0f), 1.5f);
    KRYS_EXPECT_EQUAL("Negative float mod", Mod(-10.5f, 3.0f), -1.5f);
    KRYS_EXPECT_EQUAL("Negative divisor float mod", Mod(10.5f, -3.0f), 1.5f);
    KRYS_EXPECT_EQUAL("Negative dividend and divisor float mod", Mod(-10.5f, -3.0f), -1.5f);
    KRYS_EXPECT_EQUAL("Large dividend", Mod(std::numeric_limits<int>::max(), 2), 1);
    KRYS_EXPECT_EQUAL("Smallest negative dividend", Mod(std::numeric_limits<int>::min(), 2), 0);
  }
}