#include "MTL/Hyperbolic/Csch.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Csch()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csch: 1.0", MTL::Csch(1.0), 0.85091812823932, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csch: -1.0", MTL::Csch(-1.0), -0.85091812823932, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csch: 2.0", MTL::Csch(2.0), 0.27572056477178, 1e-6f);
  }
}