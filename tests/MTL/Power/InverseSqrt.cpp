#include "MTL/Power/InverseSqrt.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_InverseSqrt()
  {
    KRYS_EXPECT_EQUAL("InverseSqrt one", MTL::InverseSqrt(1.0), 1.0);
    KRYS_EXPECT_NEAR("InverseSqrt four", MTL::InverseSqrt(4.0f), 0.5f, 1e-6f);
    KRYS_EXPECT_NEAR("InverseSqrt fractional", MTL::InverseSqrt(0.25f), 2.0f, 1e-6f);
  }
}
