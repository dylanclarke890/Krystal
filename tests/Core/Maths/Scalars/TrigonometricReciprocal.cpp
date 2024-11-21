#include "Core/Maths/Scalars/TrigonometricReciprocal.hpp"
#include "Core/Debug/Expect.hpp"
#include "Core/Maths/Scalars/Constants.hpp"

namespace Krys::Tests
{
  static void Test_Csc()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csc: 0.5 radians", MTL::Csc(0.5), 2.0858296429335, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csc: pi/2 radians", MTL::Csc(1.57), 1.0f, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csc: pi radians", MTL::Csc(3.14), 627.88319391388, 1e-5f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csc: 3*pi/2 radians", MTL::Csc(4.71238898038469), -1.0f, 1e-6f);
  }

  static void Test_Sec()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sec: 1.0 radians", MTL::Sec(1.0), 1.8508157176809, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sec: pi/2 radians", MTL::Sec(1.57), 1255.7659896642, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sec: pi radians", MTL::Sec(3.14), -1.0000012682741, 1e-6f);
  }

  static void Test_Cot()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cot: 1.0 radians", MTL::Cot(1.0), 0.64209261593433, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cot: pi/2 radians", MTL::Cot(1.57), 0.00079632696322319, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cot: pi radians", MTL::Cot(3.14), -627.88239758691, 1e-5f);
  }

  static void Test_Acsc()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acsc: 2.0", MTL::Acsc(2.0), 0.5235987755983, 1e-6f);    // π/6 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acsc: -2.0", MTL::Acsc(-2.0), -0.5235987755983, 1e-6f); // -π/6 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acsc: 1.0", MTL::Acsc(1.0), 1.5707963267949, 1e-6f);    // π/2 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acsc: -1.0", MTL::Acsc(-1.0), -1.5707963267949, 1e-6f); // -π/2 radians
  }

  static void Test_Asec()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asec: 2.0", MTL::Asec(2.0), 1.0471975511966, 1e-6f);   // π/3 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asec: -2.0", MTL::Asec(-2.0), 2.0943951023932, 1e-6f); // 2π/3 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asec: 1.0", MTL::Asec(1.0), 0.0, 1e-6f);               // 0 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asec: -1.0", MTL::Asec(-1.0), 3.1415926535898, 1e-6f); // π radians
  }

  static void Test_Acot()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acot: 1.0", MTL::Acot(1.0), 0.7853981633974, 1e-6f);    // π/4 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acot: -1.0", MTL::Acot(-1.0), -0.7853981633974, 1e-6f); // -π/4 radians
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acot: 0.5", MTL::Acot(0.5), 1.1071487177941, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acot: -0.5", MTL::Acot(-0.5), -1.1071487177941, 1e-6f);
  }
}