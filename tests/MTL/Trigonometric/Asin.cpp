#include "MTL/Trigonometric/Asin.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Asin()
  {
    KRYS_EXPECT_EQUAL("Asin: 0", MTL::Asin(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asin: 1", MTL::Asin(1.0), 1.5707963267948966, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asin: -1", MTL::Asin(-1.0), -1.5707963267948966, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asin: -0.5", MTL::Asin(-0.5), -0.5235987755983, 1e-6);
  }
}
