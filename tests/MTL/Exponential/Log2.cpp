#include "MTL/Exponential/Log2.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Log2()
  {
    KRYS_EXPECT_EQUAL("Log2(1)", MTL::Log2(1.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Log2(2)", MTL::Log2(2.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Log2(4)", MTL::Log2(4.0f), 2.0f);
    KRYS_EXPECT_EQUAL("Log2(8)", MTL::Log2(8.0f), 3.0f);
    KRYS_EXPECT_EQUAL("Log2(0.5)", MTL::Log2(0.5f), -1.0f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Log2(10)", MTL::Log2(10.0f), 3.3219281f, 1e-6f);
  }
}
