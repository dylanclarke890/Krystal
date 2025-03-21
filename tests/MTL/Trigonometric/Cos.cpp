#include "MTL/Trigonometric/Cos.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Cos()
  {
    KRYS_EXPECT_EQUAL("Cos: 0 radians", MTL::Cos(0.0), 1.0);
    KRYS_EXPECT_NEAR("Cos: pi/2 radians", MTL::Cos(1.5707963267948966), 0.0, 1e-6);
    KRYS_EXPECT_NEAR("Cos: pi radians", MTL::Cos(3.141592653589793), -1.0, 1e-6);
    KRYS_EXPECT_NEAR("Cos: 3*pi/2 radians", MTL::Cos(4.71238898038469), 0.0, 1e-6);
  }
}
