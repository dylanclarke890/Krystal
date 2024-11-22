#include "MTL/Hyperbolic/Asech.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Asech()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asech: 0.5", MTL::Asech(0.5), 1.3169578969248, 1e-4f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asech: 1.0", MTL::Asech(1.0), 0.0, 1e-6f);
  }
}