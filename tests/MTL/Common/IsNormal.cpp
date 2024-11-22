#include "MTL/Common/IsNormal.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_IsNormal()
  {
    KRYS_EXPECT_TRUE("Normal positive", IsNormal(1.0f));
    KRYS_EXPECT_TRUE("Normal negative", IsNormal(-1.0f));
    KRYS_EXPECT_FALSE("Zero", IsNormal(0.0f));
    KRYS_EXPECT_FALSE("Subnormal", IsNormal(std::numeric_limits<float>::denorm_min()));
    KRYS_EXPECT_FALSE("NaN", IsNormal(std::numeric_limits<float>::quiet_NaN()));
  }
}
