#include "Core/Maths/Scalars/Arithmetic.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  static void TestAbs()
  {
    KRYS_EXPECT_EQUAL("Negative integer", MTL::Abs(-10), 10);
    KRYS_EXPECT_EQUAL("Positive integer", MTL::Abs(10), 10);
    KRYS_EXPECT_EQUAL("Zero integer", MTL::Abs(0), 0);
    KRYS_EXPECT_EQUAL("Negative float", MTL::Abs(-10.5f), 10.5f);
    KRYS_EXPECT_EQUAL("Positive float", MTL::Abs(10.5f), 10.5f);
    KRYS_EXPECT_EQUAL("Zero float", MTL::Abs(0.0f), 0.0f);
    KRYS_EXPECT_EQUAL("Largest positive int", MTL::Abs(std::numeric_limits<int>::max()),
                      std::numeric_limits<int>::max());
    KRYS_EXPECT_EQUAL("Negative infinity", MTL::Abs(-std::numeric_limits<float>::infinity()),
                      std::numeric_limits<float>::infinity());
    KRYS_EXPECT_EQUAL("Positive infinity", MTL::Abs(std::numeric_limits<float>::infinity()),
                      std::numeric_limits<float>::infinity());
  }

  static void TestMod()
  {
    KRYS_EXPECT_EQUAL("Positive dividend and divisor", MTL::Mod(10, 3), 1);
    KRYS_EXPECT_EQUAL("Negative dividend", MTL::Mod(-10, 3), -1);
    KRYS_EXPECT_EQUAL("Negative divisor", MTL::Mod(10, -3), 1);
    KRYS_EXPECT_EQUAL("Negative dividend and divisor", MTL::Mod(-10, -3), -1);
    KRYS_EXPECT_EQUAL("Dividend is zero", MTL::Mod(0, 3), 0);
    KRYS_EXPECT_EQUAL("Positive float mod", MTL::Mod(10.5f, 3.0f), 1.5f);
    KRYS_EXPECT_EQUAL("Negative float mod", MTL::Mod(-10.5f, 3.0f), -1.5f);
    KRYS_EXPECT_EQUAL("Negative divisor float mod", MTL::Mod(10.5f, -3.0f), 1.5f);
    KRYS_EXPECT_EQUAL("Negative dividend and divisor float mod", MTL::Mod(-10.5f, -3.0f), -1.5f);
    KRYS_EXPECT_EQUAL("Large dividend", MTL::Mod(std::numeric_limits<int>::max(), 2), 1);
    KRYS_EXPECT_EQUAL("Smallest negative dividend", MTL::Mod(std::numeric_limits<int>::min(), 2), 0);
  }
}