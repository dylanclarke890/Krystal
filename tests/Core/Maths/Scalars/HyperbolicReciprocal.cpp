#include "Core/Maths/Scalars/HyperbolicReciprocal.hpp"
#include "Core/Debug/Expect.hpp"
#include "Core/Maths/Scalars/Constants.hpp"

namespace Krys::Tests
{
  static void Test_Csch()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csch: 1.0", MTL::Csch(1.0), 0.85091812823932, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csch: -1.0", MTL::Csch(-1.0), -0.85091812823932, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Csch: 2.0", MTL::Csch(2.0), 0.27572056477178, 1e-6f);
  }

  static void Test_Sech()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sech: 1.0", MTL::Sech(1.0), 0.64805427366389, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Sech: 2.0", MTL::Sech(2.0), 0.26580222883408, 1e-6f);
  }

  static void Test_Coth()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Coth: 1.0", MTL::Coth(1.0), 1.3130352854993, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Coth: -1.0", MTL::Coth(-1.0), -1.3130352854993, 1e-6f);
  }

  static void Test_Acsch()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acsch: 1.0", MTL::Acsch(1.0), 0.88137358701954, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acsch: -1.0", MTL::Acsch(-1.0), -0.88137358701954, 1e-6f);
  }

  static void Test_Asech()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asech: 0.5", MTL::Asech(0.5), 1.3169578969248, 1e-4f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Asech: 1.0", MTL::Asech(1.0), 0.0, 1e-6f);
  }

  static void Test_Acoth()
  {
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acoth: 2.0", MTL::Acoth(2.0), 0.54930614433405, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Acoth: -2.0", MTL::Acoth(-2.0), -0.54930614433405, 1e-6f);
  }
}