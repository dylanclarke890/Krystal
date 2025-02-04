#include "MTL/Hyperbolic/Coth.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Coth()
  {
    KRYS_EXPECT_NEAR("Coth: 1.0", MTL::Coth(1.0), 1.3130352854993, 1e-6f);
    KRYS_EXPECT_NEAR("Coth: -1.0", MTL::Coth(-1.0), -1.3130352854993, 1e-6f);
  }
}