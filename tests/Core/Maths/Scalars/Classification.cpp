#include "Core/Maths/Scalars/Classification.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_IsNaN()
  {
    KRYS_EXPECT_TRUE("Quiet NaN", IsNaN(std::numeric_limits<float>::quiet_NaN()));
    KRYS_EXPECT_TRUE("Signaling NaN", IsNaN(std::numeric_limits<float>::signaling_NaN()));
    KRYS_EXPECT_FALSE("Zero", IsNaN(0.0f));
    KRYS_EXPECT_FALSE("Positive finite", IsNaN(1.0f));
    KRYS_EXPECT_FALSE("Negative finite", IsNaN(-1.0f));
  }

  static void Test_IsInf()
  {
    KRYS_EXPECT_TRUE("Positive infinity", IsInf(std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_TRUE("Negative infinity", IsInf(-std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_FALSE("Zero", IsInf(0.0f));
    KRYS_EXPECT_FALSE("Finite positive", IsInf(1.0f));
    KRYS_EXPECT_FALSE("Finite negative", IsInf(-1.0f));
  }

  static void Test_IsFinite()
  {
    KRYS_EXPECT_TRUE("Zero", IsFinite(0.0f));
    KRYS_EXPECT_TRUE("Positive finite", IsFinite(1.0f));
    KRYS_EXPECT_TRUE("Negative finite", IsFinite(-1.0f));
    KRYS_EXPECT_FALSE("Positive infinity", IsFinite(std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_FALSE("Negative infinity", IsFinite(-std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_FALSE("NaN", IsFinite(std::numeric_limits<float>::quiet_NaN()));
  }

  static void Test_IsDenormal()
  {
    KRYS_EXPECT_TRUE("Subnormal", IsDenormal(std::numeric_limits<float>::denorm_min()));
    KRYS_EXPECT_FALSE("Zero", IsDenormal(0.0f));
    KRYS_EXPECT_FALSE("Normal positive", IsDenormal(1.0f));
    KRYS_EXPECT_FALSE("Normal negative", IsDenormal(-1.0f));
    KRYS_EXPECT_FALSE("NaN", IsDenormal(std::numeric_limits<float>::quiet_NaN()));
  }

  static void Test_IsNormal()
  {
    KRYS_EXPECT_TRUE("Normal positive", IsNormal(1.0f));
    KRYS_EXPECT_TRUE("Normal negative", IsNormal(-1.0f));
    KRYS_EXPECT_FALSE("Zero", IsNormal(0.0f));
    KRYS_EXPECT_FALSE("Subnormal", IsNormal(std::numeric_limits<float>::denorm_min()));
    KRYS_EXPECT_FALSE("NaN", IsNormal(std::numeric_limits<float>::quiet_NaN()));
  }

  static void Test_Sign()
  {
    KRYS_EXPECT_FALSE("Positive value", Signbit(1));
    KRYS_EXPECT_TRUE("Negative value", Signbit(-1));
    KRYS_EXPECT_FALSE("Integer Zero", Signbit(0), 0);
    KRYS_EXPECT_FALSE("Float positive zero", Signbit(0.0f));
    KRYS_EXPECT_TRUE("Float negative zero", Signbit(-0.0f));
    KRYS_EXPECT_FALSE("Float positive", Signbit(1.0f));
    KRYS_EXPECT_TRUE("Float negative", Signbit(-1.0f));
    KRYS_EXPECT_FALSE("Positive Infinity", Signbit(std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_TRUE("Negative Infinity", Signbit(-std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_FALSE("Positive NaN", Signbit(std::numeric_limits<float>::quiet_NaN()));
    KRYS_EXPECT_TRUE("Negative NaN", Signbit(-std::numeric_limits<float>::quiet_NaN()));
  }

  static void Test_IsOdd()
  {
    KRYS_EXPECT_TRUE("Odd positive", IsOdd(1));
    KRYS_EXPECT_TRUE("Odd negative", IsOdd(-1));
    KRYS_EXPECT_FALSE("Even positive", IsOdd(2));
    KRYS_EXPECT_FALSE("Even negative", IsOdd(-2));
    KRYS_EXPECT_FALSE("Zero", IsOdd(0));
  }

  static void Test_IsEven()
  {
    KRYS_EXPECT_TRUE("Even positive", IsEven(2));
    KRYS_EXPECT_TRUE("Even negative", IsEven(-2));
    KRYS_EXPECT_FALSE("Odd positive", IsEven(1));
    KRYS_EXPECT_FALSE("Odd negative", IsEven(-1));
    KRYS_EXPECT_TRUE("Zero", IsEven(0));
  }
}
