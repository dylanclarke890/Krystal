#include "MTL/IsEven.hpp"
#include "Core/Debug/Expect.hpp"

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
}
