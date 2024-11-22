#include "MTL/Common/Abs.hpp"
#include "Core/Debug/Expect.hpp"

#include <limits>

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void TestAbs()
  {
    KRYS_EXPECT_EQUAL("signed integer", Abs(1), 1);
    KRYS_EXPECT_EQUAL("Negative integer", Abs(-10), 10);
    KRYS_EXPECT_EQUAL("Positive integer", Abs(10), 10);
    KRYS_EXPECT_EQUAL("Zero integer", Abs(0), 0);
    KRYS_EXPECT_EQUAL("Negative float", Abs(-10.5f), 10.5f);
    KRYS_EXPECT_EQUAL("Positive float", Abs(10.5f), 10.5f);
    KRYS_EXPECT_EQUAL("Zero float", Abs(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Largest positive int", Abs(std::numeric_limits<int>::max()),
                      std::numeric_limits<int>::max());
    KRYS_EXPECT_EQUAL("Negative infinity", Abs(-std::numeric_limits<float>::infinity()),
                      std::numeric_limits<float>::infinity());
    KRYS_EXPECT_EQUAL("Positive infinity", Abs(std::numeric_limits<float>::infinity()),
                      std::numeric_limits<float>::infinity());
  }
}