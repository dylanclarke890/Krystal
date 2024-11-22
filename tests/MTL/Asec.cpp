#include "MTL/Asec.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Asec()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asec: 2.0", MTL::Asec(2.0), 1.0471975511966, 1e-6f);   // π/3 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asec: -2.0", MTL::Asec(-2.0), 2.0943951023932, 1e-6f); // 2π/3 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asec: 1.0", MTL::Asec(1.0), 0.0, 1e-6f);               // 0 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asec: -1.0", MTL::Asec(-1.0), 3.1415926535898, 1e-6f); // π radians
  }
}