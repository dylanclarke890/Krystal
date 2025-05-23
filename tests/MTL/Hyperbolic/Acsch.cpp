#include "MTL/Hyperbolic/Acsch.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Acsch()
  {
    KRYS_EXPECT_NEAR("Acsch: 1.0", MTL::Acsch(1.0), 0.88137358701954, 1e-6f);
    KRYS_EXPECT_NEAR("Acsch: -1.0", MTL::Acsch(-1.0), -0.88137358701954, 1e-6f);
  }
}