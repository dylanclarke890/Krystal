#include "MTL/Exponential/Log.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Log()
  {
    KRYS_EXPECT_EQUAL("Log(1)", MTL::Log(1.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Log(10)", MTL::Log(10.0f), 2.302585092994f);
    KRYS_EXPECT_EQUAL("Log(2)", MTL::Log(2.0f), 0.69314718055995f);
    KRYS_EXPECT_EQUAL("Log(2.8)", MTL::Log(2.8f), 1.0296194171812f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Log(e)", MTL::Log(MTL::e<float>()), 1.0f, 1e-6f);
  }
}
