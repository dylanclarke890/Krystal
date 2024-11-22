#include "MTL/Csc.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Csc()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csc: 0.5 radians", MTL::Csc(0.5), 2.0858296429335, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csc: pi/2 radians", MTL::Csc(1.57), 1.0f, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csc: pi radians", MTL::Csc(3.14), 627.88319391388, 1e-5f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csc: 3*pi/2 radians", MTL::Csc(4.71238898038469), -1.0f, 1e-6f);
  }
}