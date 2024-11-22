#include "MTL/Common/Min.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Min()
  {
    KRYS_EXPECT_EQUAL("Min: Two values", MTL::Min(3, 5), 3);
    KRYS_EXPECT_EQUAL("Min: Two values, reversed", MTL::Min(5, 3), 3);
    KRYS_EXPECT_EQUAL("Min: Three values", MTL::Min(3, 5, 2), 2);
    KRYS_EXPECT_EQUAL("Min: Three values, negative", MTL::Min(-3, 5, 2), -3);
    KRYS_EXPECT_EQUAL("Min: Four values", MTL::Min(7, 3, 9, 1), 1);
    KRYS_EXPECT_EQUAL("Min: Four values, negative", MTL::Min(-7, -3, -9, -1), -9);
  }
}
