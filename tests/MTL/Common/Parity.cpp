#include "MTL/Common/Parity.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_IsEven()
  {
    KRYS_EXPECT_TRUE("Even positive", IsEven(2));
    KRYS_EXPECT_TRUE("Even negative", IsEven(-2));
    KRYS_EXPECT_FALSE("Odd positive", IsEven(1));
    KRYS_EXPECT_FALSE("Odd negative", IsEven(-1));
    KRYS_EXPECT_TRUE("Zero", IsEven(0));
  }

  static void Test_IsOdd()
  {
    KRYS_EXPECT_TRUE("Odd positive", IsOdd(1));
    KRYS_EXPECT_TRUE("Odd negative", IsOdd(-1));
    KRYS_EXPECT_FALSE("Even positive", IsOdd(2));
    KRYS_EXPECT_FALSE("Even negative", IsOdd(-2));
    KRYS_EXPECT_FALSE("Zero", IsOdd(0));
  }
}
