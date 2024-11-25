#include "MTL/Hyperbolic/Sech.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Sech()
  {
    KRYS_EXPECT_NEAR("Sech: 1.0", MTL::Sech(1.0), 0.64805427366389, 1e-6f);
    KRYS_EXPECT_NEAR("Sech: 2.0", MTL::Sech(2.0), 0.26580222883408, 1e-6f);
  }
}