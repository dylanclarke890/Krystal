#include "MTL/Common/Rounding.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Ceil()
  {
    KRYS_EXPECT_EQUAL("Zero", Ceil(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Just below 0.5", Ceil(0.499999f), 1.0f);
    KRYS_EXPECT_EQUAL("Just above 0.5", Ceil(0.500001f), 1.0f);
    KRYS_EXPECT_EQUAL("Just below -0.5", Ceil(-0.499999f), 0.0f);
    KRYS_EXPECT_EQUAL("Just above -0.5", Ceil(-0.500001f), 0.0f);
    KRYS_EXPECT_EQUAL("Already ceiled", Ceil(1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Large positive", Ceil(12345.67f), 12346.0f);
    KRYS_EXPECT_EQUAL("Positive float boundary", Ceil(16777216.0f), 16777216.0f);
    KRYS_EXPECT_EQUAL("Negative float boundary", Ceil(-16777216.0f), -16777216.0f);
  }

  static void Test_Floor()
  {
    KRYS_EXPECT_EQUAL("Zero", Floor(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Just below 0.5", Floor(0.499999f), 0.0f);
    KRYS_EXPECT_EQUAL("Just above 0.5", Floor(0.500001f), 0.0f);
    KRYS_EXPECT_EQUAL("Just below -0.5", Floor(-0.499999f), -1.0f);
    KRYS_EXPECT_EQUAL("Just above -0.5", Floor(-0.500001f), -1.0f);
    KRYS_EXPECT_EQUAL("Already floored", Floor(1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Large positive", Floor(12345.67f), 12345.0f);
    KRYS_EXPECT_EQUAL("Positive float boundary", Floor(16777216.0f), 16777216.0f);
    KRYS_EXPECT_EQUAL("Negative float boundary", Floor(-16777216.0f), -16777216.0f);
  }

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