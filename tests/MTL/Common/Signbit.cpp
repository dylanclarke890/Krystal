#include "MTL/Common/Signbit.hpp"
#include "Core/Debug/Expect.hpp"

#include <limits>

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Signbit()
  {
    KRYS_EXPECT_FALSE("Positive value", Signbit(1));
    KRYS_EXPECT_TRUE("Negative value", Signbit(-1));
    KRYS_EXPECT_FALSE("Integer Zero", Signbit(0));
    KRYS_EXPECT_FALSE("Float positive zero", Signbit(0.0f));
    KRYS_EXPECT_TRUE("Float negative zero", Signbit(-0.0f));
    KRYS_EXPECT_FALSE("Float positive", Signbit(1.0f));
    KRYS_EXPECT_TRUE("Float negative", Signbit(-1.0f));
    KRYS_EXPECT_FALSE("Positive Infinity", Signbit(std::numeric_limits<float>::infinity()));
    KRYS_EXPECT_TRUE("Negative Infinity", Signbit(-std::numeric_limits<float>::infinity()));
  }
}
