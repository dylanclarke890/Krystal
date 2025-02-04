#include "MTL/Hyperbolic/Atanh.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Atanh()
  {
    KRYS_EXPECT_NEAR("Atanh: 0", MTL::Atanh(0.0), 0.0, 1e-6f);
    KRYS_EXPECT_NEAR("Atanh: 0.5", MTL::Atanh(0.5), 0.54930614433405, 1e-6f);
    KRYS_EXPECT_NEAR("Atanh: -0.5", MTL::Atanh(-0.5), -0.54930614433405, 1e-6f);
  }
}
