#include "MTL/Trigonometric/Atan.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Atan()
  {
    KRYS_EXPECT_EQUAL("Atan: 0", MTL::Atan(0.0), 0.0);
    KRYS_EXPECT_NEAR("Atan: 0.5", MTL::Atan(0.5), 0.46364760900081, 1e-6);
    KRYS_EXPECT_NEAR("Atan: 1", MTL::Atan(1.0), 0.7853981633974483, 1e-6);
    KRYS_EXPECT_NEAR("Atan: -0.5", MTL::Atan(-0.5), -0.46364760900081, 1e-6);
    KRYS_EXPECT_NEAR("Atan: -1", MTL::Atan(-1.0), -0.78539816339745, 1e-6);
  }
}
