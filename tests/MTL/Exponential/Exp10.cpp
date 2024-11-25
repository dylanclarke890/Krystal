#include "MTL/Exponential/Exp10.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Exp10()
  {
    KRYS_EXPECT_EQUAL("Exp10 zero", MTL::Exp10(0.0), 1.0);
    KRYS_EXPECT_NEAR("Exp10 positive", MTL::Exp10(2.0), 100.0, 1e-6);
    KRYS_EXPECT_NEAR("Exp10 negative", MTL::Exp10(-2.0), 0.01, 1e-6);
  }
}
