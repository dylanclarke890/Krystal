#include "MTL/Common/IsNaN.hpp"
#include "Core/Debug/Expect.hpp"

#include <limits>

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_IsNaN()
  {
    KRYS_EXPECT_TRUE("Quiet NaN", IsNaN(std::numeric_limits<float>::quiet_NaN()));
    KRYS_EXPECT_TRUE("Signaling NaN", IsNaN(std::numeric_limits<float>::signaling_NaN()));
    KRYS_EXPECT_FALSE("Zero", IsNaN(0.0f));
    KRYS_EXPECT_FALSE("Positive finite", IsNaN(1.0f));
    KRYS_EXPECT_FALSE("Negative finite", IsNaN(-1.0f));
  }
}
