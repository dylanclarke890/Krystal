#include "MTL/Common/FMin.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_FMin()
  {
    KRYS_EXPECT_EQUAL("FMin: Two values", MTL::FMin(3.0f, 5.0f), 3.0f);
    KRYS_EXPECT_EQUAL("FMin: Two values, reversed", MTL::FMin(5.0f, 3.0f), 3.0f);
    KRYS_EXPECT_EQUAL("FMin: One NaN", MTL::FMin(std::numeric_limits<float>::quiet_NaN(), 5.0f), 5.0f);
    KRYS_EXPECT_EQUAL("FMin: Three values", MTL::FMin(3.0f, 5.0f, 2.0f), 2.0f);
    KRYS_EXPECT_EQUAL("FMin: Three values, with NaN",
                      MTL::FMin(std::numeric_limits<float>::quiet_NaN(), 5.0f, 2.0f), 2.0f);
    KRYS_EXPECT_EQUAL("FMin: Four values", MTL::FMin(7.0f, 3.0f, 9.0f, 1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("FMin: Four values, with NaN",
                      MTL::FMin(7.0f, std::numeric_limits<float>::quiet_NaN(), 9.0f, 1.0f), 1.0f);
  }
}