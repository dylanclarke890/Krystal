#include "MTL/Hyperbolic/Coth.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Coth()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Coth: 1.0", MTL::Coth(1.0), 1.3130352854993, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Coth: -1.0", MTL::Coth(-1.0), -1.3130352854993, 1e-6f);
  }
}