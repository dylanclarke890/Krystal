#include "MTL/Tan.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Tan()
  {
    KRYS_EXPECT_EQUAL("Tan: 0 radians", MTL::Tan(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tan: pi/4 radians", MTL::Tan(0.7853981633974483), 1.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tan: -pi/4 radians", MTL::Tan(-0.7853981633974483), -1.0, 1e-6);
  }
}
