#include "MTL/Common/FpClassify.hpp"
#include "tests/__utils__/Expect.hpp"

#include <limits>

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

  static void Test_IsInfinite()
  {
    KRYS_EXPECT_TRUE("Positive infinity", IsInfinite(std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_TRUE("Negative infinity", IsInfinite(-std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_FALSE("Zero", IsInfinite(0.0f));
    KRYS_EXPECT_FALSE("Finite positive", IsInfinite(1.0f));
    KRYS_EXPECT_FALSE("Finite negative", IsInfinite(-1.0f));
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
}
