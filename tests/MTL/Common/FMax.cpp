#include "MTL/Common/FMax.hpp"
#include "Core/Debug/Expect.hpp"

#include <limits>

namespace Krys::Tests
{
  using namespace Krys::MTL;

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
