#include "MTL/Acosh.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Acosh()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acosh: 1.0", MTL::Acosh(1.0), 0.0, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acosh: 2.0", MTL::Acosh(2.0), 1.3169578969248, 1e-4f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acosh: 3.0", MTL::Acosh(3.0), 1.7627471740391, 1e-6f);
  }
}
