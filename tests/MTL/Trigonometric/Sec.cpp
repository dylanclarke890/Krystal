#include "MTL/Trigonometric/Sec.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Sec()
  {
    KRYS_EXPECT_NEAR("Sec: 1.0 radians", MTL::Sec(1.0), 1.8508157176809, 1e-6f);
    KRYS_EXPECT_NEAR("Sec: pi/2 radians", MTL::Sec(1.57), 1255.7659896642, 1e-6f);
    KRYS_EXPECT_NEAR("Sec: pi radians", MTL::Sec(3.14), -1.0000012682741, 1e-6f);
  }
}