#include "MTL/Common/Max.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Max()
  {
    KRYS_EXPECT_EQUAL("Max: Two values", Max(3, 5), 5);
    KRYS_EXPECT_EQUAL("Max: Two values, reversed", Max(5, 3), 5);
    KRYS_EXPECT_EQUAL("Max: Three values", Max(3, 5, 7), 7);
    KRYS_EXPECT_EQUAL("Max: Three values, negative", Max(-3, -5, -2), -2);
    KRYS_EXPECT_EQUAL("Max: Four values", Max(7, 3, 9, 1), 9);
    KRYS_EXPECT_EQUAL("Max: Four values, negative", Max(-7, -3, -9, -1), -1);
  }
}
