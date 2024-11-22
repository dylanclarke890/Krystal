#include "MTL/Common/Round.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Round()
  {
    KRYS_EXPECT_EQUAL("Zero", Round(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Negative Zero", Round(-0.0f), -0.0f);
    KRYS_EXPECT_EQUAL("Just below 0.5", Round(0.499999f), 0.0f);
    KRYS_EXPECT_EQUAL("Just above 0.5", Round(0.500001f), 1.0f);
    KRYS_EXPECT_EQUAL("Just below -0.5", Round(-0.499999f), 0.0f);
    KRYS_EXPECT_EQUAL("Just above -0.5", Round(-0.500001f), -1.0f);
    KRYS_EXPECT_EQUAL("Already rounded", Round(1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Large positive", Round(12345.67f), 12346.0f);
    KRYS_EXPECT_EQUAL("Positive float boundary", Round(16777216.0f), 16777216.0f);
    KRYS_EXPECT_EQUAL("Negative float boundary", Round(-16777216.0f), -16777216.0f);
  }
}