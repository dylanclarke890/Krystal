#include "MTL/Hyperbolic/Cosh.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Cosh()
  {
    KRYS_EXPECT_NEAR("Cosh: 0", MTL::Cosh(0.0), 1.0, 1e-6f);
    KRYS_EXPECT_NEAR("Cosh: 1.0", MTL::Cosh(1.0), 1.5430806348152, 1e-6f);
    KRYS_EXPECT_NEAR("Cosh: -1.0", MTL::Cosh(-1.0), 1.5430806348152, 1e-6f);
    KRYS_EXPECT_NEAR("Cosh: 2.0", MTL::Cosh(2.0), 3.7621956910836, 1e-6f);
  }
}
