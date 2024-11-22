#include "MTL/Floor.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Floor()
  {
    KRYS_EXPECT_EQUAL("Zero", Floor(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Negative Zero", Floor(-0.0f), -0.0f);
    KRYS_EXPECT_EQUAL("Just below 0.5", Floor(0.499999f), 0.0f);
    KRYS_EXPECT_EQUAL("Just above 0.5", Floor(0.500001f), 0.0f);
    KRYS_EXPECT_EQUAL("Just below -0.5", Floor(-0.499999f), -1.0f);
    KRYS_EXPECT_EQUAL("Just above -0.5", Floor(-0.500001f), -1.0f);
    KRYS_EXPECT_EQUAL("Already floored", Floor(1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Large positive", Floor(12345.67f), 12345.0f);
    KRYS_EXPECT_EQUAL("Positive float boundary", Floor(16777216.0f), 16777216.0f);
    KRYS_EXPECT_EQUAL("Negative float boundary", Floor(-16777216.0f), -16777216.0f);
  }
}