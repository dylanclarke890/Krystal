#include "MTL/Common/Clamp.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Clamp()
  {
    KRYS_EXPECT_EQUAL("Clamp within range", Clamp(5, 0, 10), 5);
    KRYS_EXPECT_EQUAL("Clamp below range", Clamp(-5, 0, 10), 0);
    KRYS_EXPECT_EQUAL("Clamp above range", Clamp(15, 0, 10), 10);
    KRYS_EXPECT_EQUAL("Clamp floating-point within range", Clamp(5.5f, 0.0f, 10.0f), 5.5f);
    KRYS_EXPECT_EQUAL("Clamp floating-point below range", Clamp(-5.5f, 0.0f, 10.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Clamp floating-point above range", Clamp(15.5f, 0.0f, 10.0f), 10.0f);
  }
}
