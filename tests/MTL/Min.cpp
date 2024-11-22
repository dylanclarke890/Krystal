#include "Core/Maths/Scalars/Limits.hpp"
#include "Core/Debug/Expect.hpp"
#include "Core/Maths/Scalars/Constants.hpp"

namespace Krys::Tests
{
  static void Test_Min()
  {
    KRYS_EXPECT_EQUAL("Min: Two values", MTL::Min(3, 5), 3);
    KRYS_EXPECT_EQUAL("Min: Two values, reversed", MTL::Min(5, 3), 3);
    KRYS_EXPECT_EQUAL("Min: Three values", MTL::Min(3, 5, 2), 2);
    KRYS_EXPECT_EQUAL("Min: Three values, negative", MTL::Min(-3, 5, 2), -3);
    KRYS_EXPECT_EQUAL("Min: Four values", MTL::Min(7, 3, 9, 1), 1);
    KRYS_EXPECT_EQUAL("Min: Four values, negative", MTL::Min(-7, -3, -9, -1), -9);
  }

  static void Test_Max()
  {
    KRYS_EXPECT_EQUAL("Max: Two values", MTL::Max(3, 5), 5);
    KRYS_EXPECT_EQUAL("Max: Two values, reversed", MTL::Max(5, 3), 5);
    KRYS_EXPECT_EQUAL("Max: Three values", MTL::Max(3, 5, 7), 7);
    KRYS_EXPECT_EQUAL("Max: Three values, negative", MTL::Max(-3, -5, -2), -2);
    KRYS_EXPECT_EQUAL("Max: Four values", MTL::Max(7, 3, 9, 1), 9);
    KRYS_EXPECT_EQUAL("Max: Four values, negative", MTL::Max(-7, -3, -9, -1), -1);
  }

  static void Test_FMin()
  {
    KRYS_EXPECT_EQUAL("FMin: Two values", MTL::FMin(3.0f, 5.0f), 3.0f);
    KRYS_EXPECT_EQUAL("FMin: Two values, reversed", MTL::FMin(5.0f, 3.0f), 3.0f);
    KRYS_EXPECT_EQUAL("FMin: One NaN", MTL::FMin(std::numeric_limits<float>::quiet_NaN(), 5.0f), 5.0f);
    KRYS_EXPECT_EQUAL(
      "FMin: Both NaN",
      MTL::FMin(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN()),
      std::numeric_limits<float>::quiet_NaN());
    KRYS_EXPECT_EQUAL("FMin: Three values", MTL::FMin(3.0f, 5.0f, 2.0f), 2.0f);
    KRYS_EXPECT_EQUAL("FMin: Three values, with NaN",
                      MTL::FMin(std::numeric_limits<float>::quiet_NaN(), 5.0f, 2.0f), 2.0f);
    KRYS_EXPECT_EQUAL("FMin: Four values", MTL::FMin(7.0f, 3.0f, 9.0f, 1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("FMin: Four values, with NaN",
                      MTL::FMin(7.0f, std::numeric_limits<float>::quiet_NaN(), 9.0f, 1.0f), 1.0f);
  }

  static void Test_FMax()
  {
    KRYS_EXPECT_EQUAL("FMax: Two values", MTL::FMax(3.0f, 5.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMax: Two values, reversed", MTL::FMax(5.0f, 3.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMax: One NaN", MTL::FMax(std::numeric_limits<float>::quiet_NaN(), 5.0f), 5.0f);
    KRYS_EXPECT_EQUAL(
      "FMax: Both NaN",
      MTL::FMax(std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::quiet_NaN()),
      std::numeric_limits<float>::quiet_NaN());
    KRYS_EXPECT_EQUAL("FMax: Three values", MTL::FMax(3.0f, 5.0f, 7.0f), 7.0f);
    KRYS_EXPECT_EQUAL("FMax: Three values, with NaN",
                      MTL::FMax(std::numeric_limits<float>::quiet_NaN(), 5.0f, 7.0f), 7.0f);
    KRYS_EXPECT_EQUAL("FMax: Four values", MTL::FMax(7.0f, 3.0f, 9.0f, 1.0f), 9.0f);
    KRYS_EXPECT_EQUAL("FMax: Four values, with NaN",
                      MTL::FMax(7.0f, std::numeric_limits<float>::quiet_NaN(), 9.0f, 1.0f), 9.0f);
  }

  static void Test_Clamp()
  {
    KRYS_EXPECT_EQUAL("Clamp within range", MTL::Clamp(5, 0, 10), 5);
    KRYS_EXPECT_EQUAL("Clamp below range", MTL::Clamp(-5, 0, 10), 0);
    KRYS_EXPECT_EQUAL("Clamp above range", MTL::Clamp(15, 0, 10), 10);
    KRYS_EXPECT_EQUAL("Clamp floating-point within range", MTL::Clamp(5.5f, 0.0f, 10.0f), 5.5f);
    KRYS_EXPECT_EQUAL("Clamp floating-point below range", MTL::Clamp(-5.5f, 0.0f, 10.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Clamp floating-point above range", MTL::Clamp(15.5f, 0.0f, 10.0f), 10.0f);
  }
}
