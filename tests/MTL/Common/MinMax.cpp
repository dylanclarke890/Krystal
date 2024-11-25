#include "MTL/Common/MinMax.hpp"
#include "Core/Debug/Expect.hpp"

#include <limits>

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Min()
  {
    KRYS_EXPECT_EQUAL("Min: Two values", Min(3, 5), 3);
    KRYS_EXPECT_EQUAL("Min: Two values, reversed", Min(5, 3), 3);
    KRYS_EXPECT_EQUAL("Min: Three values", Min(3, 5, 2), 2);
    KRYS_EXPECT_EQUAL("Min: Three values, negative", Min(-3, 5, 2), -3);
    KRYS_EXPECT_EQUAL("Min: Four values", Min(7, 3, 9, 1), 1);
    KRYS_EXPECT_EQUAL("Min: Four values, negative", Min(-7, -3, -9, -1), -9);
  }

  static void Test_FMin()
  {
    KRYS_EXPECT_EQUAL("FMin: Two values", FMin(3.0f, 5.0f), 3.0f);
    KRYS_EXPECT_EQUAL("FMin: Two values, reversed", FMin(5.0f, 3.0f), 3.0f);
    KRYS_EXPECT_EQUAL("FMin: One NaN", FMin(std::numeric_limits<float>::quiet_NaN(), 5.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMin: Three values", FMin(3.0f, 5.0f, 2.0f), 2.0f);
    KRYS_EXPECT_EQUAL("FMin: Three values, with NaN",
                      FMin(std::numeric_limits<float>::quiet_NaN(), 5.0f, 2.0f), 2.0f);
    KRYS_EXPECT_EQUAL("FMin: Four values", FMin(7.0f, 3.0f, 9.0f, 1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("FMin: Four values, with NaN",
                      FMin(7.0f, std::numeric_limits<float>::quiet_NaN(), 9.0f, 1.0f), 1.0f);
  }

  static void Test_Max()
  {
    KRYS_EXPECT_EQUAL("Max: Two values", Max(3, 5), 5);
    KRYS_EXPECT_EQUAL("Max: Two values, reversed", Max(5, 3), 5);
    KRYS_EXPECT_EQUAL("Max: Three values", Max(3, 5, 7), 7);
    KRYS_EXPECT_EQUAL("Max: Three values, negative", Max(-3, -5, -2), -2);
    KRYS_EXPECT_EQUAL("Max: Four values", Max(7, 3, 9, 1), 9);
    KRYS_EXPECT_EQUAL("Max: Four values, negative", Max(-7, -3, -9, -1), -1);
  }

  static void Test_FMax()
  {
    KRYS_EXPECT_EQUAL("FMax: Two values", FMax(3.0f, 5.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMax: Two values, reversed", FMax(5.0f, 3.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMax: One NaN", FMax(std::numeric_limits<float>::quiet_NaN(), 5.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMax: Three values", FMax(3.0f, 5.0f, 7.0f), 7.0f);
    KRYS_EXPECT_EQUAL("FMax: Three values, with NaN",
                      FMax(std::numeric_limits<float>::quiet_NaN(), 5.0f, 7.0f), 7.0f);
    KRYS_EXPECT_EQUAL("FMax: Four values", FMax(7.0f, 3.0f, 9.0f, 1.0f), 9.0f);
    KRYS_EXPECT_EQUAL("FMax: Four values, with NaN",
                      FMax(7.0f, std::numeric_limits<float>::quiet_NaN(), 9.0f, 1.0f), 9.0f);
  }
}
