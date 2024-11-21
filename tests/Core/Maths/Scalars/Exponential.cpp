#include "Core/Maths/Scalars/Exponential.hpp"
#include "Core/Debug/Expect.hpp"
#include "Core/Maths/Scalars/Constants.hpp"

namespace Krys::Tests
{
  static void Test_Pow()
  {
    KRYS_EXPECT_EQUAL("Integer: 2^3", MTL::Pow(2, 3), 8);
    KRYS_EXPECT_EQUAL("Integer: 2^0", MTL::Pow(2, 0), 1);
    KRYS_EXPECT_EQUAL("Integer: 0^5", MTL::Pow(0, 5), 0);
    KRYS_EXPECT_EQUAL("Integer: 1^10", MTL::Pow(1, 10), 1);
    KRYS_EXPECT_EQUAL("Integer: (-1)^5", MTL::Pow(-1, 5), -1);
    KRYS_EXPECT_EQUAL("Integer: (-1)^6", MTL::Pow(-1, 6), 1);
    KRYS_EXPECT_EQUAL("Integer: 2^-2", MTL::Pow(2, 2), 4.0);
    KRYS_EXPECT_EQUAL("Float: 2.0^3", MTL::Pow(2.0f, 3), 8.0f);
    KRYS_EXPECT_EQUAL("Float: 2.0^-2", MTL::Pow(2.0f, -2.0f), 0.25f);
    KRYS_EXPECT_EQUAL("Float: 2.0^0", MTL::Pow(2.0f, 0.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Float: 0.0^5.0", MTL::Pow(0.0f, 5.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Float: 0.0^-1.0", MTL::Pow(0.0f, -1.0f), std::numeric_limits<float>::infinity());
    KRYS_EXPECT_EQUAL("Edge: Tiny exponent", MTL::Pow(2.0f, 1e-10), 1);
    KRYS_EXPECT_EQUAL("Edge: Large negative exponent", MTL::Pow(2.0f, 10), 1'024);
    KRYS_EXPECT_EQUAL("Edge: Small base", MTL::Pow(1e-4f, 3.0), 1e-4f * 1e-4f * 1e-4f);
    KRYS_EXPECT_EQUAL("Edge: Large base", MTL::Pow(1e10f, 2.0f), 1e20f);
  }

  static void Test_Factorial()
  {
    KRYS_EXPECT_EQUAL("Factorial zero", MTL::Factorial(0U), 1);
    KRYS_EXPECT_EQUAL("Factorial one", MTL::Factorial(1U), 1);
    KRYS_EXPECT_EQUAL("Factorial five", MTL::Factorial(5U), 120);
    KRYS_EXPECT_EQUAL("Factorial ten", MTL::Factorial(10U), 3'628'800);
  }

  static void Test_Exp()
  {
    KRYS_EXPECT_EQUAL("Exp: Zero", MTL::Exp(0.0), 1.0);
    KRYS_EXPECT_EQUAL("Exp: -1.0f", MTL::Exp(-1.0f), 0.367879441171f);
    KRYS_EXPECT_EQUAL("Exp: 1.0f", MTL::Exp(1.0f), MTL::e<float>());
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Exp: Squared", MTL::Exp(3.0),
                                     MTL::e<float>() * MTL::e<float>() * MTL::e<float>(), 1e-6f);
  }

  static void Test_Exp2()
  {
    KRYS_EXPECT_EQUAL("Exp2 zero", MTL::Exp2(0.0), 1.0);
    KRYS_EXPECT_EQUAL("Exp2 positive", MTL::Exp2(3.0f), 8.0f);
    KRYS_EXPECT_EQUAL("Exp2 negative", MTL::Exp2(-3.0f), 0.125f);
  }

  static void Test_Exp10()
  {
    KRYS_EXPECT_EQUAL("Exp10 zero", MTL::Exp10(0.0), 1.0);
    KRYS_EXPECT_EQUAL("Exp10 positive", MTL::Exp10(2.0), 100.0);
    KRYS_EXPECT_EQUAL("Exp10 negative", MTL::Exp10(-2.0), 0.01);
  }

  static void Test_Log()
  {
    KRYS_EXPECT_EQUAL("Log(1)", MTL::Log(1.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Log(10)", MTL::Log(10.0f), 2.302585092994f);
    KRYS_EXPECT_EQUAL("Log(2)", MTL::Log(2.0f), 0.69314718055995f);
    KRYS_EXPECT_EQUAL("Log(2.8)", MTL::Log(2.8f), 1.0296194171812f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Log(e)", MTL::Log(MTL::e<float>()), 1.0f, 1e-6f);
  }

  static void Test_Log2()
  {
    KRYS_EXPECT_EQUAL("Log2(1)", MTL::Log2(1.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Log2(2)", MTL::Log2(2.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Log2(4)", MTL::Log2(4.0f), 2.0f);
    KRYS_EXPECT_EQUAL("Log2(8)", MTL::Log2(8.0f), 3.0f);
    KRYS_EXPECT_EQUAL("Log2(0.5)", MTL::Log2(0.5f), -1.0f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("Log2(10)", MTL::Log2(10.0f), 3.3219281f, 1e-6f);
  }

  static void Test_Sqrt()
  {
    KRYS_EXPECT_EQUAL("Sqrt zero", MTL::Sqrt(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Sqrt one", MTL::Sqrt(1.0f), 1.0f);
    KRYS_EXPECT_EQUAL("Sqrt four", MTL::Sqrt(4.0f), 2.0f);
    KRYS_EXPECT_EQUAL("Sqrt fractional", MTL::Sqrt(0.25f), 0.5f);
  }

  static void Test_InverseSqrt()
  {
    KRYS_EXPECT_EQUAL("InverseSqrt one", MTL::InverseSqrt(1.0), 1.0);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("InverseSqrt four", MTL::InverseSqrt(4.0f), 0.5f, 1e-6f);
    KRYS_EXPECT_EQUAL_WITH_TOLERANCE("InverseSqrt fractional", MTL::InverseSqrt(0.25f), 2.0f, 1e-6f);
  }
}
