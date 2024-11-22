#include "MTL/Sec.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Sec()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sec: 1.0 radians", MTL::Sec(1.0), 1.8508157176809, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sec: pi/2 radians", MTL::Sec(1.57), 1255.7659896642, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sec: pi radians", MTL::Sec(3.14), -1.0000012682741, 1e-6f);
  }
}