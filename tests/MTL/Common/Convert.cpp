#include "MTL/Common/Convert.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Degrees()
  {
    KRYS_EXPECT_EQUAL("Degrees: 0 radians", Degrees(0.0), 0.0);
    KRYS_EXPECT_NEAR("Degrees: pi/2 radians", Degrees(1.5707963267948966), 90.0, 1e-6);
    KRYS_EXPECT_NEAR("Degrees: pi radians", Degrees(3.141592653589793), 180.0, 1e-6);
    KRYS_EXPECT_NEAR("Degrees: 2*pi radians", Degrees(6.283185307179586), 360.0, 1e-6);
    KRYS_EXPECT_NEAR("Degrees: literal operator _deg", 6.283185307179586_deg, 360.0, 1e-6);
    KRYS_EXPECT_NEAR("Degrees: literal operator _degrees", 6.283185307179586_degrees, 360.0, 1e-6);
  }

  static void Test_Radians()
  {
    KRYS_EXPECT_EQUAL("Radians: 0 degrees", Radians(0.0), 0.0);
    KRYS_EXPECT_NEAR("Radians: 90 degrees", Radians(90.0), 1.5707963267948966, 1e-6);
    KRYS_EXPECT_NEAR("Radians: 180 degrees", Radians(180.0), 3.141592653589793, 1e-6);
    KRYS_EXPECT_NEAR("Radians: 360 degrees", Radians(360.0), 6.283185307179586, 1e-6);
    KRYS_EXPECT_NEAR("Radians: literal operator _deg", 360.0_rad, 6.283185307179586, 1e-6);
    KRYS_EXPECT_NEAR("Radians: literal operator _degrees", 360.0_radians, 6.283185307179586, 1e-6);
  }
}
