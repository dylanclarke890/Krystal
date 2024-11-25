#include "MTL/Hyperbolic/Sinh.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Sinh()
  {
    KRYS_EXPECT_NEAR("Sinh: 0", MTL::Sinh(0.0), 0.0, 1e-6f);
    KRYS_EXPECT_NEAR("Sinh: 1.0", MTL::Sinh(1.0), 1.1752011936438, 1e-6f);
    KRYS_EXPECT_NEAR("Sinh: -1.0", MTL::Sinh(-1.0), -1.1752011936438, 1e-6f);
    KRYS_EXPECT_NEAR("Sinh: 2.0", MTL::Sinh(2.0), 3.626860407847, 1e-6f);
  }
}
