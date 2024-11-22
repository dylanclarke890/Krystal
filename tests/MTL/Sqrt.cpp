#include "MTL/Sqrt.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Sqrt()
  {
    KRYS_EXPECT_EQUAL("Sqrt zero", MTL::Sqrt(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Sqrt one", MTL::Sqrt(1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Sqrt four", MTL::Sqrt(4.0f), 2.0f);
    KRYS_EXPECT_EQUAL("Sqrt fractional", MTL::Sqrt(0.25f), 0.5f);
  }
}
