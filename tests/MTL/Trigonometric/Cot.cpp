#include "MTL/Trigonometric/Cot.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Cot()
  {
    KRYS_EXPECT_NEAR("Cot: 1.0 radians", MTL::Cot(1.0), 0.64209261593433, 1e-6f);
    KRYS_EXPECT_NEAR("Cot: pi/2 radians", MTL::Cot(1.57), 0.00079632696322319, 1e-6f);
    KRYS_EXPECT_NEAR("Cot: pi radians", MTL::Cot(3.14), -627.88239758691, 1e-5f);
  }
}