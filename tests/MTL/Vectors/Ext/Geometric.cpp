#include "MTL/Vectors/Ext/Geometric.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"
#include "MTL/Vectors/Ext/Abs.hpp"
#include "MTL/Vectors/Ext/Comparison.hpp"
#include "MTL/Vectors/Ext/Predicate.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  static void Test_Length()
  {
    KRYS_EXPECT_NEAR("Vec1 Length", MTL::Length(Vec1 {1.0f}) - 1.0f, 0.0f, 1e-6f);
    KRYS_EXPECT_NEAR("Vec2 Length", MTL::Length(Vec2 {1.0f, 0.0f}) - 1.0f, 0.0f, 1e-6f);
    KRYS_EXPECT_NEAR("Vec3 Length", MTL::Length(Vec3 {1.0f, 0.0f, 0.0f}) - 1.0f, 0.0f, 1e-6f);
    KRYS_EXPECT_NEAR("Vec4 Length", MTL::Length(Vec4 {1.0f, 0.0f, 0.0f, 0.0f}) - 1.0f, 0.0f, 1e-6f);
  }

  static void Test_LengthSquared()
  {
    KRYS_EXPECT_EQUAL("Vec1 LengthSquared", MTL::LengthSquared(Vec1 {2.0f}), 4.0f);
    KRYS_EXPECT_EQUAL("Vec2 LengthSquared", MTL::LengthSquared(Vec2 {2.0f}), 4.0f);
    KRYS_EXPECT_EQUAL("Vec3 LengthSquared", MTL::LengthSquared(Vec3 {2.0f}), 4.0f);
    KRYS_EXPECT_EQUAL("Vec4 LengthSquared", MTL::LengthSquared(Vec4 {2.0f}), 4.0f);
  }

  static void Test_Distance()
  {
    KRYS_EXPECT_NEAR("Vec1 Distance", MTL::Distance(Vec1 {1.0f}, Vec1 {1.0f}), 0.0f, 1e-6f);
    KRYS_EXPECT_NEAR("Vec2 Distance", MTL::Distance(Vec2 {1.0f, 0.0f}, Vec2 {1.0f, 0.0f}), 0.0f, 1e-6f);
    KRYS_EXPECT_NEAR("Vec3 Distance", MTL::Distance(Vec3 {1.0f, 0.0f, 0.0f}, Vec3 {1.0f, 0.0f, 0.0f}), 0.0f,
                     1e-6f);
    KRYS_EXPECT_NEAR("Vec4 Distance",
                     MTL::Distance(Vec4 {1.0f, 0.0f, 0.0f, 0.0f}, Vec4 {1.0f, 0.0f, 0.0f, 0.0f}), 0.0f,
                     1e-6f);
  }

  static void Test_DistanceSquared()
  {
    KRYS_EXPECT_EQUAL("Vec1 DistanceSquared", MTL::DistanceSquared(Vec1 {2.0f}, Vec1 {4.0f}), 4.0f);
    KRYS_EXPECT_EQUAL("Vec2 DistanceSquared", MTL::DistanceSquared(Vec2 {2.0f}, Vec2 {4.0f}), 4.0f);
    KRYS_EXPECT_EQUAL("Vec3 DistanceSquared", MTL::DistanceSquared(Vec3 {2.0f}, Vec3 {4.0f}), 4.0f);
    KRYS_EXPECT_EQUAL("Vec4 DistanceSquared", MTL::DistanceSquared(Vec4 {2.0f}, Vec4 {4.0f}), 4.0f);
  }

  static void Test_Dot()
  {
    constexpr float d1 = MTL::Dot(Vec1(1), Vec1(1));
    KRYS_EXPECT_NEAR("Vec1 Dot", d1 - 1.0f, 0.0f, 1e-6f);

    constexpr float d2 = MTL::Dot(Vec2(1), Vec2(1));
    KRYS_EXPECT_NEAR("Vec2 Dot", d2 - 2.0f, 0.0f, 1e-6f);

    constexpr float d3 = MTL::Dot(Vec3(1), Vec3(1));
    KRYS_EXPECT_NEAR("Vec3 Dot", d3 - 3.0f, 0.0f, 1e-6f);

    constexpr float d4 = MTL::Dot(Vec4(1), Vec4(1));
    KRYS_EXPECT_NEAR("Vec4 Dot", d4 - 4.0f, 0.0f, 1e-6f);
  }

  static void Test_Cross()
  {
    constexpr auto IsTrue = [](float v)
    {
      return v < std::numeric_limits<float>::epsilon();
    };

    constexpr Vec3 c1 = MTL::Cross(Vec3(1, 0, 0), Vec3(0, 1, 0));
    constexpr Vec3 c2 = MTL::Cross(Vec3(0, 1, 0), Vec3(1, 0, 0));

    KRYS_EXPECT_TRUE("Cross1", MTL::AllOf(MTL::Abs(c1 - Vec3(0, 0, 1)), IsTrue));
    KRYS_EXPECT_TRUE("Cross2", MTL::AllOf(MTL::Abs(c2 - Vec3(0, 0, -1)), IsTrue));
  }

  static void Test_Normalize()
  {
    constexpr auto IsTrue = [](float v)
    {
      return v < std::numeric_limits<float>::epsilon();
    };

    constexpr Vec3 n1 = MTL::Normalize(Vec3(1, 0, 0));
    constexpr Vec3 n2 = MTL::Normalize(Vec3(2, 0, 0));

    KRYS_EXPECT_TRUE("Normalize1", MTL::AllOf(MTL::Abs(n1 - Vec3(1, 0, 0)), IsTrue));
    KRYS_EXPECT_TRUE("Normalize2", MTL::AllOf(MTL::Abs(n2 - Vec3(1, 0, 0)), IsTrue));

    constexpr Vec3 ro = Vec3(MTL::Cos(5.0f) * 3.0f, 2.0f, MTL::Sin(5.0f) * 3.0f);
    constexpr Vec3 w = MTL::Normalize(Vec3(0, -0.2f, 0) - ro);
    constexpr Vec3 u = MTL::Normalize(MTL::Cross(w, Vec3(0, 1, 0)));
    constexpr Vec3 v = MTL::Cross(u, w);
    constexpr Vec3 x = MTL::Cross(w, u);

    KRYS_EXPECT_TRUE("Normalize3", MTL::AllOf(MTL::Abs(x + v), IsTrue));
  }

  static void Test_Reflect()
  {
    constexpr Vec2 A(1.0f, -1.0f);
    constexpr Vec2 B(0.0f, 1.0f);
    constexpr Vec2 C = MTL::Reflect(A, B);

    KRYS_EXPECT_EQUAL("Reflect", C, Vec2(1.0, 1.0));
  }

  static void Test_Refract()
  {
    constexpr Vec2 A(0.0f, -1.0f);
    constexpr Vec2 B(0.0f, 1.0f);
    constexpr Vec2 C = MTL::Refract(A, B, 0.5f);
    KRYS_EXPECT_EQUAL("Refract", C, Vec2(0.0, -1.0));
  }

  static void Test_FaceForward()
  {
    constexpr Vec3 n(0.0f, 0.0f, 1.0f);
    constexpr Vec3 i(1.0f, 0.0f, 1.0f);
    constexpr Vec3 nRef(0.0f, 0.0f, 1.0f);
    constexpr Vec3 F = MTL::FaceForward(n, i, nRef);
    KRYS_EXPECT_EQUAL("FaceForward", F, Vec3(0, 0, -1));
  }

  static void Test_TriangleNormal()
  {
    using vec3 = vec3_t<float>;

    constexpr float epsilon = 1e-5f;

    // Triangle in the XY plane
    constexpr vec3 p1(0, 0, 0);
    constexpr vec3 p2(1, 0, 0);
    constexpr vec3 p3(0, 1, 0);
    constexpr vec3 expectedNormal(0, 0, 1); // Normal points along +Z axis

    constexpr vec3 result = MTL::TriangleNormal(p1, p2, p3);
    KRYS_EXPECT_EQUAL("TriangleNormal XY Plane", result, expectedNormal);
  }
}