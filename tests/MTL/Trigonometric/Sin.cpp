#include "MTL/Trigonometric/Sin.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Sin()
  {
    KRYS_EXPECT_EQUAL("Sin: 0 radians", MTL::Sin(0.0), 0.0);
    KRYS_EXPECT_NEAR("Sin: pi/2 radians", MTL::Sin(1.5707963267948966), 1.0f, 1e-6f);
    KRYS_EXPECT_NEAR("Sin: pi radians", MTL::Sin(3.141592653589793), 0.0f, 1e-6f);
    KRYS_EXPECT_NEAR("Sin: 3*pi/2 radians", MTL::Sin(4.71238898038469), -1.0f, 1e-6f);
  }
}
