#include "MTL/Degrees.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Degrees()
  {
    KRYS_EXPECT_EQUAL("Degrees: 0 radians", MTL::Degrees(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: pi/2 radians", MTL::Degrees(1.5707963267948966), 90.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: pi radians", MTL::Degrees(3.141592653589793), 180.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: 2*pi radians", MTL::Degrees(6.283185307179586), 360.0, 1e-6);
  }
}
