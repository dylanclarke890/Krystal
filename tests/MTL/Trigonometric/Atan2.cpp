#include "MTL/Trigonometric/Atan2.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Atan2()
  {
    KRYS_EXPECT_NEAR("Atan2: (1, 1)", MTL::Atan2(1.0, 1.0), 0.7853981633974483, 1e-6);
    KRYS_EXPECT_NEAR("Atan2: (-1, -1)", MTL::Atan2(-1.0, -1.0), -2.356194490192345, 1e-6);
    KRYS_EXPECT_NEAR("Atan2: (1, -1)", MTL::Atan2(1.0, -1.0), 2.356194490192345, 1e-6);
    KRYS_EXPECT_NEAR("Atan2: (-1, 1)", MTL::Atan2(-1.0, 1.0), -0.7853981633974483, 1e-6);
  }
}
