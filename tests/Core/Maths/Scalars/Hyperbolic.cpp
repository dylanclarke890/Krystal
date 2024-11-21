#include "Core/Maths/Scalars/Hyperbolic.hpp"
#include "Core/Debug/Expect.hpp"
#include "Core/Maths/Scalars/Constants.hpp"

namespace Krys::Tests
{
  static void Test_Sinh()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sinh: 0", MTL::Sinh(0.0), 0.0, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sinh: 1.0", MTL::Sinh(1.0), 1.1752011936438, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sinh: -1.0", MTL::Sinh(-1.0), -1.1752011936438, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sinh: 2.0", MTL::Sinh(2.0), 3.626860407847, 1e-6f);
  }

  static void Test_Cosh()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cosh: 0", MTL::Cosh(0.0), 1.0, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cosh: 1.0", MTL::Cosh(1.0), 1.5430806348152, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cosh: -1.0", MTL::Cosh(-1.0), 1.5430806348152, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Cosh: 2.0", MTL::Cosh(2.0), 3.7621956910836, 1e-6f);
  }

  static void Test_Tanh()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tanh: 0", MTL::Tanh(0.0), 0.0, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tanh: 1.0", MTL::Tanh(1.0), 0.76159415595576, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tanh: -1.0", MTL::Tanh(-1.0), -0.76159415595576, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Tanh: 2.0", MTL::Tanh(2.0), 0.96402758007582, 1e-6f);
  }

  static void Test_Asinh()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asinh: 0", MTL::Asinh(0.0), 0.0, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asinh: 1.0", MTL::Asinh(1.0), 0.88137358701954, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asinh: -1.0", MTL::Asinh(-1.0), -0.88137358701954, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asinh: 2.0", MTL::Asinh(2.0), 1.4436354751788, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asinh: 0.5", MTL::Asinh(0.5), 0.4812118250596, 1e-6f);
  }

  static void Test_Acosh()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acosh: 1.0", MTL::Acosh(1.0), 0.0, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acosh: 2.0", MTL::Acosh(2.0), 1.3169578969248, 1e-4f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acosh: 3.0", MTL::Acosh(3.0), 1.7627471740391, 1e-6f);
  }

  static void Test_Atanh()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atanh: 0", MTL::Atanh(0.0), 0.0, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atanh: 0.5", MTL::Atanh(0.5), 0.54930614433405, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Atanh: -0.5", MTL::Atanh(-0.5), -0.54930614433405, 1e-6f);
  }
}
