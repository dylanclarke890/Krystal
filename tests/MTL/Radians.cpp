#include "MTL/Radians.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Radians()
  {
    KRYS_EXPECT_EQUAL("Radians: 0 degrees", MTL::Radians(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians: 90 degrees", MTL::Radians(90.0), 1.5707963267948966, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians: 180 degrees", MTL::Radians(180.0), 3.141592653589793, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians: 360 degrees", MTL::Radians(360.0), 6.283185307179586, 1e-6);
  }
}
