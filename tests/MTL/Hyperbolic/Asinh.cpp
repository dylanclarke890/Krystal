#include "MTL/Hyperbolic/Asinh.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Asinh()
  {
    KRYS_EXPECT_NEAR("Asinh: 0", MTL::Asinh(0.0), 0.0, 1e-6f);
    KRYS_EXPECT_NEAR("Asinh: 1.0", MTL::Asinh(1.0), 0.88137358701954, 1e-6f);
    KRYS_EXPECT_NEAR("Asinh: -1.0", MTL::Asinh(-1.0), -0.88137358701954, 1e-6f);
    KRYS_EXPECT_NEAR("Asinh: 2.0", MTL::Asinh(2.0), 1.4436354751788, 1e-6f);
    KRYS_EXPECT_NEAR("Asinh: 0.5", MTL::Asinh(0.5), 0.4812118250596, 1e-6f);
  }
}
