#include "MTL/Hyperbolic/Asech.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Asech()
  {
    KRYS_EXPECT_NEAR("Asech: 0.5", MTL::Asech(0.5), 1.3169578969248, 1e-4f);
    KRYS_EXPECT_NEAR("Asech: 1.0", MTL::Asech(1.0), 0.0, 1e-6f);
  }
}