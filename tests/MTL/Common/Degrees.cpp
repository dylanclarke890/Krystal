#include "MTL/Common/Degrees.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Degrees()
  {
    KRYS_EXPECT_EQUAL("Degrees: 0 radians", Degrees(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: pi/2 radians", Degrees(1.5707963267948966), 90.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: pi radians", Degrees(3.141592653589793), 180.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: 2*pi radians", Degrees(6.283185307179586), 360.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: literal operator _deg", 6.283185307179586_deg, 360.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: literal operator _degrees", 6.283185307179586_degrees, 360.0,
                                     1e-6);
  }
}
