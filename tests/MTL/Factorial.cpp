#include "MTL/Factorial.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Factorial()
  {
    KRYS_EXPECT_EQUAL("Factorial zero", MTL::Factorial(0U), 1);
    KRYS_EXPECT_EQUAL("Factorial one", MTL::Factorial(1U), 1);
    KRYS_EXPECT_EQUAL("Factorial five", MTL::Factorial(5U), 120);
    KRYS_EXPECT_EQUAL("Factorial ten", MTL::Factorial(10U), 3'628'800);
  }
}
