#include "MTL/Trigonometric/Acsc.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Acsc()
  {
    KRYS_EXPECT_NEAR("Acsc: 2.0", MTL::Acsc(2.0), 0.5235987755983, 1e-6f);    // π/6 radians
    KRYS_EXPECT_NEAR("Acsc: -2.0", MTL::Acsc(-2.0), -0.5235987755983, 1e-6f); // -π/6 radians
    KRYS_EXPECT_NEAR("Acsc: 1.0", MTL::Acsc(1.0), 1.5707963267949, 1e-6f);    // π/2 radians
    KRYS_EXPECT_NEAR("Acsc: -1.0", MTL::Acsc(-1.0), -1.5707963267949, 1e-6f); // -π/2 radians
  }
}