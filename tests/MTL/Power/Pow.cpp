#include "MTL/Power/Pow.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Pow()
  {
    KRYS_EXPECT_EQUAL("Pow - Int: 2^3", MTL::Pow(2, 3), 8);
    KRYS_EXPECT_EQUAL("Pow - Int: 2^0", MTL::Pow(2, 0), 1);
    KRYS_EXPECT_EQUAL("Pow - Int: 0^5", MTL::Pow(0, 5), 0);
    KRYS_EXPECT_EQUAL("Pow - Int: 1^10", MTL::Pow(1, 10), 1);
    KRYS_EXPECT_EQUAL("Pow - Int: (-1)^5", MTL::Pow(-1, 5), -1);
    KRYS_EXPECT_EQUAL("Pow - Int: (-1)^6", MTL::Pow(-1, 6), 1);
    KRYS_EXPECT_EQUAL("Pow - Int: 2^-2", MTL::Pow(2, 2), 4.0);
    KRYS_EXPECT_EQUAL("Pow - Float: 2.0^3", MTL::Pow(2.0f, 3.0f), 8.0f);
    KRYS_EXPECT_EQUAL("Pow - Float: 2.0^-2", MTL::Pow(2.0f, -2.0f), 0.25f);
    KRYS_EXPECT_EQUAL("Pow - Float: 2.0^0", MTL::Pow(2.0f, 0.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Pow - Float: 0.0^5.0", MTL::Pow(0.0f, 5.0f), 0.0f);
    KRYS_EXPECT_NEAR("Edge: Large negative exponent", MTL::Pow(2.0, 10.0), 1'024.0, 1e-6f);
  }
}
