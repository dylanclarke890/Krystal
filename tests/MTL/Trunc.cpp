#include "MTL/Trunc.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Trunc()
  {
    KRYS_EXPECT_EQUAL("Zero", Trunc(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Negative Zero", Trunc(-0.0f), -0.0f);
    KRYS_EXPECT_EQUAL("Just below 0.5", Trunc(0.499999f), 0.0f);
    KRYS_EXPECT_EQUAL("Just above 0.5", Trunc(0.500001f), 0.0f);
    KRYS_EXPECT_EQUAL("Just below -0.5", Trunc(-0.499999f), 0.0f);
    KRYS_EXPECT_EQUAL("Just above -0.5", Trunc(-0.500001f), 0.0f);
    KRYS_EXPECT_EQUAL("Already ceiled", Trunc(1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Large positive", Trunc(12345.67f), 12345.0f);
    KRYS_EXPECT_EQUAL("Positive float boundary", Trunc(16777216.0f), 16777216.0f);
    KRYS_EXPECT_EQUAL("Negative float boundary", Trunc(-16777216.0f), -16777216.0f);
  }
}