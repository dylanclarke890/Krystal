#include "Core/Maths/Scalars/Trigonometric.hpp"
#include "Core/Debug/Expect.hpp"
#include "Core/Maths/Scalars/Constants.hpp"

namespace Krys::Tests
{
  static void Test_Radians()
  {
    KRYS_EXPECT_EQUAL("Radians: 0 degrees", MTL::Radians(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians: 90 degrees", MTL::Radians(90.0), 1.5707963267948966, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians: 180 degrees", MTL::Radians(180.0), 3.141592653589793, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Radians: 360 degrees", MTL::Radians(360.0), 6.283185307179586, 1e-6);
  }

  static void Test_Degrees()
  {
    KRYS_EXPECT_EQUAL("Degrees: 0 radians", MTL::Degrees(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: pi/2 radians", MTL::Degrees(1.5707963267948966), 90.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: pi radians", MTL::Degrees(3.141592653589793), 180.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Degrees: 2*pi radians", MTL::Degrees(6.283185307179586), 360.0, 1e-6);
  }

  static void Test_Sin()
  {
    KRYS_EXPECT_EQUAL("Sin: 0 radians", MTL::Sin(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sin: pi/2 radians", MTL::Sin(1.5707963267948966), 1.0f, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sin: pi radians", MTL::Sin(3.141592653589793), 0.0f, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sin: 3*pi/2 radians", MTL::Sin(4.71238898038469), -1.0f, 1e-6f);
  }

  static void Test_Cos()
  {
    KRYS_EXPECT_EQUAL("Cos: 0 radians", MTL::Cos(0.0), 1.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cos: pi/2 radians", MTL::Cos(1.5707963267948966), 0.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cos: pi radians", MTL::Cos(3.141592653589793), -1.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cos: 3*pi/2 radians", MTL::Cos(4.71238898038469), 0.0, 1e-6);
  }

  static void Test_Tan()
  {
    KRYS_EXPECT_EQUAL("Tan: 0 radians", MTL::Tan(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tan: pi/4 radians", MTL::Tan(0.7853981633974483), 1.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tan: -pi/4 radians", MTL::Tan(-0.7853981633974483), -1.0, 1e-6);
  }

  static void Test_Asin()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asin: 0", MTL::Asin(0.0), 0.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asin: 1", MTL::Asin(1.0), 1.5707963267948966, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asin: -1", MTL::Asin(-1.0), -1.5707963267948966, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asin: -0.5", MTL::Asin(-0.5), -0.5235987755983, 1e-6);
  }

  static void Test_Acos()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acos: 1", MTL::Acos(1.0), 0.0, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acos: 0", MTL::Acos(0.0), 1.5707963267948966, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acos: -1", MTL::Acos(-1.0), 3.141592653589793, 1e-6);
  }

  static void Test_Atan()
  {
    KRYS_EXPECT_EQUAL("Atan: 0", MTL::Atan(0.0), 0.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atan: 0.5", MTL::Atan(0.5), 0.46364760900081, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atan: 1", MTL::Atan(1.0), 0.7853981633974483, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atan: -0.5", MTL::Atan(-0.5), -0.46364760900081, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atan: -1", MTL::Atan(-1.0), -0.78539816339745, 1e-6);
  }

  static void Test_Atan2()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atan2: (1, 1)", MTL::Atan2(1.0, 1.0), 0.7853981633974483, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atan2: (-1, -1)", MTL::Atan2(-1.0, -1.0), -2.356194490192345, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atan2: (1, -1)", MTL::Atan2(1.0, -1.0), 2.356194490192345, 1e-6);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atan2: (-1, 1)", MTL::Atan2(-1.0, 1.0), -0.7853981633974483, 1e-6);
  }
}
