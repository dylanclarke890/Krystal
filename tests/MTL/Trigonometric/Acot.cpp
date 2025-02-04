#include "MTL/Trigonometric/Acot.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Acot()
  {
    KRYS_EXPECT_NEAR("Acot: 1.0", MTL::Acot(1.0), 0.7853981633974, 1e-6f);    // π/4 radians
    KRYS_EXPECT_NEAR("Acot: -1.0", MTL::Acot(-1.0), -0.7853981633974, 1e-6f); // -π/4 radians
    KRYS_EXPECT_NEAR("Acot: 0.5", MTL::Acot(0.5), 1.1071487177941, 1e-6f);
    KRYS_EXPECT_NEAR("Acot: -0.5", MTL::Acot(-0.5), -1.1071487177941, 1e-6f);
  }
}