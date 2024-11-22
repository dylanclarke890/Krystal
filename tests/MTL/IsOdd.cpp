#include "MTL/IsOdd.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_IsOdd()
  {
    KRYS_EXPECT_TRUE("Odd positive", IsOdd(1));
    KRYS_EXPECT_TRUE("Odd negative", IsOdd(-1));
    KRYS_EXPECT_FALSE("Even positive", IsOdd(2));
    KRYS_EXPECT_FALSE("Even negative", IsOdd(-2));
    KRYS_EXPECT_FALSE("Zero", IsOdd(0));
  }
}
