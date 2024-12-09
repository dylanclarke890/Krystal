#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Radians.hpp"
#include "MTL/Matrices/Ext/Transform.hpp"
#include "MTL/Matrices/Mat4x4.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Translate()
  {
    using mat_t = Mat4x4;

    constexpr mat_t mat {1};
    KRYS_EXPECT_EQUAL("Transform", Translate(mat, {1, 3, 4}),
                      mat_t({1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {1, 3, 4, 1}));
  }

  static void Test_Rotate()
  {
    using mat_t = Mat4x4;

    constexpr mat_t mat {1};
    KRYS_EXPECT_EQUAL(
      "Rotate", Rotate(mat, Radians(50.0f), {0.0f, 0.0f, 1.0f}),
      mat_t({0.6427877f, 0.76604444f, 0, 0}, {-0.76604444f, 0.6427877f, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}));
  }

  static void Test_Scale()
  {
    using mat_t = Mat4x4;

    constexpr mat_t mat {1};
    KRYS_EXPECT_EQUAL("Scale", Scale(mat, {2, 3, 4}),
                      mat_t({2, 0, 0, 0}, {0, 3, 0, 0}, {0, 0, 4, 0}, {0, 0, 0, 1}));
  }

  static void Test_LookAt_LH()
  {
    using mat_t = Mat4x4;
    using vec_t = Vec3;

    KRYS_EXPECT_EQUAL("LookAtLH", LookAt_LH(vec_t(0, 3, 5), vec_t(0), vec_t(0, 0, 1)),
                      mat_t({1, 0, 0, 0}, {0, -0.857493f, -0.5144958f, 0}, {0, 0.5144958f, -0.857493f, 0},
                            {0, 0, 5.8309526f, 1}));
  }

  static void Test_LookAtRH()
  {
    using mat_t = Mat4x4;
    using vec_t = Vec3;

    KRYS_EXPECT_EQUAL("LookAtRH", LookAt_RH(vec_t(0, 3, 5), vec_t(0), vec_t(0, 0, 1)),
                      mat_t({-1, 0, 0, 0}, {0, -0.857493f, 0.5144958f, 0}, {0, 0.5144958f, 0.857493f, 0},
                            {0, 0, -5.8309526f, 1}));
  }
}