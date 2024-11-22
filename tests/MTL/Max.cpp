#include "MTL/Max.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Max()
  {
    KRYS_EXPECT_EQUAL("Max: Two values", MTL::Max(3, 5), 5);
    KRYS_EXPECT_EQUAL("Max: Two values, reversed", MTL::Max(5, 3), 5);
    KRYS_EXPECT_EQUAL("Max: Three values", MTL::Max(3, 5, 7), 7);
    KRYS_EXPECT_EQUAL("Max: Three values, negative", MTL::Max(-3, -5, -2), -2);
    KRYS_EXPECT_EQUAL("Max: Four values", MTL::Max(7, 3, 9, 1), 9);
    KRYS_EXPECT_EQUAL("Max: Four values, negative", MTL::Max(-7, -3, -9, -1), -1);
  }
}
