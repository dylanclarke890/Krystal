#include "MTL/Common/IsDenormal.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_IsDenormal()
  {
    KRYS_EXPECT_TRUE("Subnormal", IsDenormal(std::numeric_limits<float>::denorm_min()));
    KRYS_EXPECT_FALSE("Zero", IsDenormal(0.0f));
    KRYS_EXPECT_FALSE("Normal positive", IsDenormal(1.0f));
    KRYS_EXPECT_FALSE("Normal negative", IsDenormal(-1.0f));
    KRYS_EXPECT_FALSE("NaN", IsDenormal(std::numeric_limits<float>::quiet_NaN()));
  }
}
