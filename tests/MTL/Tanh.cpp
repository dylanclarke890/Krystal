#include "MTL/Tanh.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Tanh()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tanh: 0", MTL::Tanh(0.0), 0.0, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tanh: 1.0", MTL::Tanh(1.0), 0.76159415595576, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tanh: -1.0", MTL::Tanh(-1.0), -0.76159415595576, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tanh: 2.0", MTL::Tanh(2.0), 0.96402758007582, 1e-6f);
  }
}
