#include "MTL/Power/Pow.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Pow()
  {
    KRYS_EXPECT_EQUAL("Integer: 2^3", MTL::Pow(2, 3), 8);
    KRYS_EXPECT_EQUAL("Integer: 2^0", MTL::Pow(2, 0), 1);
    KRYS_EXPECT_EQUAL("Integer: 0^5", MTL::Pow(0, 5), 0);
    KRYS_EXPECT_EQUAL("Integer: 1^10", MTL::Pow(1, 10), 1);
    KRYS_EXPECT_EQUAL("Integer: (-1)^5", MTL::Pow(-1, 5), -1);
    KRYS_EXPECT_EQUAL("Integer: (-1)^6", MTL::Pow(-1, 6), 1);
    KRYS_EXPECT_EQUAL("Integer: 2^-2", MTL::Pow(2, 2), 4.0);
    KRYS_EXPECT_EQUAL("Float: 2.0^3", MTL::Pow(2.0f, 3), 8.0f);
    KRYS_EXPECT_EQUAL("Float: 2.0^-2", MTL::Pow(2.0f, -2.0f), 0.25f);
    KRYS_EXPECT_EQUAL("Float: 2.0^0", MTL::Pow(2.0f, 0.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Float: 0.0^5.0", MTL::Pow(0.0f, 5.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Float: 0.0^-1.0", MTL::Pow(0.0f, -1.0f), std::numeric_limits<float>::infinity());
    KRYS_EXPECT_EQUAL("Edge: Tiny exponent", MTL::Pow(2.0f, 1e-10), 1);
    KRYS_EXPECT_EQUAL("Edge: Large negative exponent", MTL::Pow(2.0f, 10), 1'024);
    KRYS_EXPECT_EQUAL("Edge: Small base", MTL::Pow(1e-4f, 3.0), 1e-4f * 1e-4f * 1e-4f);
    KRYS_EXPECT_EQUAL("Edge: Large base", MTL::Pow(1e10f, 2.0f), 1e20f);
  }
}
