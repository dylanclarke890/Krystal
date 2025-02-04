#include "MTL/Vectors/Ext/Norm.hpp"
#include "MTL/Common/Constants.hpp"
#include "MTL/Power/Sqrt.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_L1Norm()
  {
    using MTL::Norm::L1;

    KRYS_EXPECT_EQUAL("L1Norm Single Vec3", L1(Vec3(-1, 2, -3)), 6);
    KRYS_EXPECT_EQUAL("L1Norm Single Vec3", L1(Vec3(0, 0, 0)), 0);

    KRYS_EXPECT_EQUAL("L1Norm Pair Vec3", L1(Vec3(-1, 2, -3), Vec3(1, -2, 3)), 12);
    KRYS_EXPECT_EQUAL("L1Norm Pair Vec3", L1(Vec3(0, 0, 0), Vec3(0, 0, 0)), 0);
  }

  static void Test_L2Norm()
  {
    using MTL::Norm::L2;

    KRYS_EXPECT_EQUAL("L2Norm Single Vec3", L2(Vec3(3, 4, 0)), 5); // Pythagoras: sqrt(3^2 + 4^2)
    KRYS_EXPECT_EQUAL("L2Norm Single Vec3", L2(Vec3(0, 0, 0)), 0);

    KRYS_EXPECT_EQUAL("L2Norm Pair Vec3", L2(Vec3(1, 2, 3), Vec3(4, 5, 6)),
                      MTL::Sqrt(27.f)); // sqrt((4-1)^2 + (5-2)^2 + (6-3)^2)
    KRYS_EXPECT_EQUAL("L2Norm Pair Vec3", L2(Vec3(0, 0, 0), Vec3(0, 0, 0)), 0);
  }

  static void Test_LxNorm()
  {
    using MTL::Norm::Lx;

    constexpr uint depth = 3;

    KRYS_EXPECT_NEAR("LxNorm Single Vec3", Lx(Vec3(-1, 2, -3), depth),
                     MTL::Pow(MTL::Pow(1.0f, 3) + MTL::Pow(2.0f, 3) + MTL::Pow(3.0f, 3), 1.0f / 3.0f), 1e-5f);

    KRYS_EXPECT_NEAR("LxNorm Pair Vec3", Lx(Vec3(-1, 2, -3), Vec3(1, -2, 3), depth),
                     MTL::Pow(MTL::Pow(2.0f, 3) + MTL::Pow(4.0f, 3) + MTL::Pow(6.0f, 3), 1.0f / 3.0f), 1e-5f);
  }

  static void Test_LMaxNorm()
  {
    using MTL::Norm::LMax;

    KRYS_EXPECT_EQUAL("LMaxNorm Single Vec3", LMax(Vec3(-1, -2, -3)), 3);
    KRYS_EXPECT_EQUAL("LMaxNorm Single Vec3", LMax(Vec3(1, 2, 3)), 3);
    KRYS_EXPECT_EQUAL("LMaxNorm Pair Vec3", LMax(Vec3(-1, -2, -3), Vec3(1, 2, 3)), 6);
    KRYS_EXPECT_EQUAL("LMaxNorm Pair Vec3", LMax(Vec3(0, 0, 0), Vec3(0, 0, 0)), 0);
  }
}
