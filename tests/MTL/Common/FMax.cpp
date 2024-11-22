#include "MTL/Common/FMax.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_FMax()
  {
    KRYS_EXPECT_EQUAL("FMax: Two values", MTL::FMax(3.0f, 5.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMax: Two values, reversed", MTL::FMax(5.0f, 3.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMax: One NaN", MTL::FMax(std::numeric_limits<float>::quiet_NaN(), 5.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMax: Three values", MTL::FMax(3.0f, 5.0f, 7.0f), 7.0f);
    KRYS_EXPECT_EQUAL("FMax: Three values, with NaN",
                      MTL::FMax(std::numeric_limits<float>::quiet_NaN(), 5.0f, 7.0f), 7.0f);
    KRYS_EXPECT_EQUAL("FMax: Four values", MTL::FMax(7.0f, 3.0f, 9.0f, 1.0f), 9.0f);
    KRYS_EXPECT_EQUAL("FMax: Four values, with NaN",
                      MTL::FMax(7.0f, std::numeric_limits<float>::quiet_NaN(), 9.0f, 1.0f), 9.0f);
  }
}
