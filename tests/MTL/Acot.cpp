#include "MTL/Acot.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Acot()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acot: 1.0", MTL::Acot(1.0), 0.7853981633974, 1e-6f);    // π/4 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acot: -1.0", MTL::Acot(-1.0), -0.7853981633974, 1e-6f); // -π/4 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acot: 0.5", MTL::Acot(0.5), 1.1071487177941, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acot: -0.5", MTL::Acot(-0.5), -1.1071487177941, 1e-6f);
  }
}