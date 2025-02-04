#include "MTL/Common/Factorial.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Factorial()
  {
    KRYS_EXPECT_EQUAL("Factorial zero", Factorial(0U), 1);
    KRYS_EXPECT_EQUAL("Factorial one", Factorial(1U), 1);
    KRYS_EXPECT_EQUAL("Factorial five", Factorial(5U), 120);
    KRYS_EXPECT_EQUAL("Factorial ten", Factorial(10U), 3'628'800);
  }
}
