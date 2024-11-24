#include "MTL/Exponential/Exp.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Constants.hpp"

namespace Krys::Tests
{
  static void Test_Exp()
  {
    constexpr float e = MTL::e<float>();

    KRYS_EXPECT_EQUAL("Exp: Zero", MTL::Exp(0.0), 1.0);
    KRYS_EXPECT_EQUAL("Exp: -1.0f", MTL::Exp(-1.0f), 0.367879441171f);
    KRYS_EXPECT_EQUAL("Exp: 1.0f", MTL::Exp(1.0f), e);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Exp: Cubed", MTL::Exp(3.0), e * e * e, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Exp: 7.5", MTL::Exp(7.5), 1808.04241445606, 1e-6f);
  }
}
