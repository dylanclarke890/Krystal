#include "MTL/Exp.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Constants.hpp"

namespace Krys::Tests
{
  static void Test_Exp()
  {
    KRYS_EXPECT_EQUAL("Exp: Zero", MTL::Exp(0.0), 1.0);
    KRYS_EXPECT_EQUAL("Exp: -1.0f", MTL::Exp(-1.0f), 0.367879441171f);
    KRYS_EXPECT_EQUAL("Exp: 1.0f", MTL::Exp(1.0f), MTL::e<float>());
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Exp: Squared", MTL::Exp(3.0),
                                     MTL::e<float>() * MTL::e<float>() * MTL::e<float>(), 1e-6f);
  }
}
