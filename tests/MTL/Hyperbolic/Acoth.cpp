#include "MTL/Hyperbolic/Acoth.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Acoth()
  {
    KRYS_EXPECT_NEAR("Acoth: 2.0", MTL::Acoth(2.0), 0.54930614433405, 1e-6f);
    KRYS_EXPECT_NEAR("Acoth: -2.0", MTL::Acoth(-2.0), -0.54930614433405, 1e-6f);
  }
}