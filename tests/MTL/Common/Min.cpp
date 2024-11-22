#include "MTL/Common/Min.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Min()
  {
    KRYS_EXPECT_EQUAL("Min: Two values", Min(3, 5), 3);
    KRYS_EXPECT_EQUAL("Min: Two values, reversed", Min(5, 3), 3);
    KRYS_EXPECT_EQUAL("Min: Three values", Min(3, 5, 2), 2);
    KRYS_EXPECT_EQUAL("Min: Three values, negative", Min(-3, 5, 2), -3);
    KRYS_EXPECT_EQUAL("Min: Four values", Min(7, 3, 9, 1), 1);
    KRYS_EXPECT_EQUAL("Min: Four values, negative", Min(-7, -3, -9, -1), -9);
  }
}
