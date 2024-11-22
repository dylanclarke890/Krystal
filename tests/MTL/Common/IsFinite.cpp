#include "MTL/Common/IsFinite.hpp"
#include "Core/Debug/Expect.hpp"

#include <limits>

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_IsFinite()
  {
    KRYS_EXPECT_TRUE("Zero", IsFinite(0.0f));
    KRYS_EXPECT_TRUE("Positive finite", IsFinite(1.0f));
    KRYS_EXPECT_TRUE("Negative finite", IsFinite(-1.0f));
    KRYS_EXPECT_FALSE("Positive infinity", IsFinite(std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_FALSE("Negative infinity", IsFinite(-std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_FALSE("NaN", IsFinite(std::numeric_limits<float>::quiet_NaN()));
  }
}
