#include "MTL/Exponential/Exp2.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Exp2()
  {
    KRYS_EXPECT_EQUAL("Exp2 zero", MTL::Exp2(0.0), 1.0);
    KRYS_EXPECT_EQUAL("Exp2 positive", MTL::Exp2(3.0f), 8.0f);
    KRYS_EXPECT_EQUAL("Exp2 negative", MTL::Exp2(-3.0f), 0.125f);
  }
}
