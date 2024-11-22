#include "MTL/Common/IsInfinite.hpp"
#include "Core/Debug/Expect.hpp"

#include <limits>

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_IsInfinite()
  {
    KRYS_EXPECT_TRUE("Positive infinity", IsInfinite(std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_TRUE("Negative infinity", IsInfinite(-std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_FALSE("Zero", IsInfinite(0.0f));
    KRYS_EXPECT_FALSE("Finite positive", IsInfinite(1.0f));
    KRYS_EXPECT_FALSE("Finite negative", IsInfinite(-1.0f));
  }
}
