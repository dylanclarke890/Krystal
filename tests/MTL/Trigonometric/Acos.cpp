#include "MTL/Trigonometric/Acos.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Acos()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acos: 1", MTL::Acos(1.0), 0.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acos: 0", MTL::Acos(0.0), 1.5707963267948966, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acos: -1", MTL::Acos(-1.0), 3.141592653589793, 1e-6);
  }
}
