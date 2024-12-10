#include "MTL/Common/Interpolate.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Lerp()
  {
    KRYS_EXPECT_EQUAL("Lerp(t=0)", Lerp(10.0f, 20.0f, 0.0f), 10.0f);
    KRYS_EXPECT_EQUAL("Lerp(t=0)", Lerp(10, 20, 0.5f), 15.0f);
    KRYS_EXPECT_EQUAL("Lerp(t=1)", Lerp(10.0f, 20.0f, 1.0f), 20.0f);
    KRYS_EXPECT_EQUAL("Lerp(t=0.5)", Lerp(10.0f, 20.0f, 0.5f), 15.0f);
  }

  static void Test_Smoothstep()
  {
    constexpr float edge0 = 0.0f;
    constexpr float edge1 = 1.0f;

    KRYS_EXPECT_EQUAL("Smoothstep(v<edge0)", Smoothstep(edge0, edge1, -0.5f), 0.0f);
    KRYS_EXPECT_EQUAL("Smoothstep(v=edge0)", Smoothstep(edge0, edge1, edge0), 0.0f);
    KRYS_EXPECT_EQUAL("Smoothstep(v=mid)  ", Smoothstep(edge0, edge1, 0.5f), 0.5f);
    KRYS_EXPECT_EQUAL("Smoothstep(v=edge1)", Smoothstep(edge0, edge1, edge1), 1.0f);
    KRYS_EXPECT_EQUAL("Smoothstep(v>edge1)", Smoothstep(edge0, edge1, 1.5f), 1.0f);
  }

  static void Test_Step()
  {
    KRYS_EXPECT_EQUAL("Step(v>=0.5)", Step(-2, 5, 0.5f), 5);
    KRYS_EXPECT_EQUAL("Step(v<0.5 )", Step(2, 9, 0.45), 2);
    KRYS_EXPECT_EQUAL("Step - Single Arg", Step(10, 2), 0);
  }
}