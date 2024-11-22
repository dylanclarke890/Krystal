#include "MTL/Common/Ceil.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Ceil()
  {
    KRYS_EXPECT_EQUAL("Zero", Ceil(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Negative Zero", Ceil(-0.0f), -0.0f);
    KRYS_EXPECT_EQUAL("Just below 0.5", Ceil(0.499999f), 1.0f);
    KRYS_EXPECT_EQUAL("Just above 0.5", Ceil(0.500001f), 1.0f);
    KRYS_EXPECT_EQUAL("Just below -0.5", Ceil(-0.499999f), 0.0f);
    KRYS_EXPECT_EQUAL("Just above -0.5", Ceil(-0.500001f), 0.0f);
    KRYS_EXPECT_EQUAL("Already ceiled", Ceil(1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Large positive", Ceil(12345.67f), 12346.0f);
    KRYS_EXPECT_EQUAL("Positive float boundary", Ceil(16777216.0f), 16777216.0f);
    KRYS_EXPECT_EQUAL("Negative float boundary", Ceil(-16777216.0f), -16777216.0f);
  }
}