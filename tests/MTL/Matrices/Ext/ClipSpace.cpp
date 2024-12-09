#include "MTL/Matrices/Ext/ClipSpace.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Common/Radians.hpp"
#include "MTL/Trigonometric/Cos.hpp"
#include "MTL/Trigonometric/Sin.hpp"
#include "MTL/Trigonometric/Tan.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  constexpr float left = -1.0f;
  constexpr float right = 1.0f;
  constexpr float bottom = -1.0f;
  constexpr float top = 1.0f;
  constexpr float zNear = 0.1f;
  constexpr float zFar = 100.0f;

  constexpr float fovy = Radians(45.0f);
  constexpr float aspect = 16.0f / 9.0f;

  constexpr float fov = Radians(45.0f);
  constexpr float width = 1920.0f;
  constexpr float height = 1080.0f;

#pragma region Ortho

  void Test_Ortho_LH_ZO()
  {
    constexpr Mat4 expected {
      1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1.0f / (zFar - zNear), 0, 0, 0, -zNear / (zFar - zNear), 1};
    KRYS_EXPECT_EQUAL("Orthographic LH ZO", Ortho_LH_ZO(left, right, bottom, top, zNear, zFar), expected);
  }

  void Test_Ortho_LH_NO()
  {
    constexpr Mat4 expected {
      1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2.0f / (zFar - zNear), 0, 0, 0, -(zFar + zNear) / (zFar - zNear), 1};
    KRYS_EXPECT_EQUAL("Orthographic LH NO", Ortho_LH_NO(left, right, bottom, top, zNear, zFar), expected);
  }

  void Test_Ortho_RH_ZO()
  {
    constexpr Mat4 expected {
      1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1.0f / (zFar - zNear), 0, 0, 0, -zNear / (zFar - zNear), 1};
    KRYS_EXPECT_EQUAL("Orthographic RH ZO", Ortho_RH_ZO(left, right, bottom, top, zNear, zFar), expected);
  }

  void Test_Ortho_RH_NO()
  {
    constexpr Mat4 expected {
      1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -2.0f / (zFar - zNear), 0, 0, 0, -(zFar + zNear) / (zFar - zNear), 1};
    KRYS_EXPECT_EQUAL("Orthographic RH NO", Ortho_RH_NO(left, right, bottom, top, zNear, zFar), expected);
  }

  void Test_Ortho()
  {
    constexpr Mat4 expected {1.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

    KRYS_EXPECT_EQUAL("Orthographic Projection", Ortho(left, right, bottom, top), expected);
  }

#pragma endregion Ortho

#pragma region Frustum

  void Test_Frustum_LH_ZO()
  {
    constexpr Mat4 expected {0.1f, 0.0f, 0.0f,      0.0f, 0.0f, 0.1f, 0.0f,        0.0f,
                             0.0f, 0.0f, 1.001001f, 1.0f, 0.0f, 0.0f, -0.1001001f, 0.0f};

    KRYS_EXPECT_EQUAL("Frustum LH ZO", Frustum_LH_ZO(left, right, bottom, top, zNear, zFar), expected);
  }

  void Test_Frustum_LH_NO()
  {
    constexpr Mat4 expected {0.1f, 0.0f, 0.0f,      0.0f, 0.0f, 0.1f, 0.0f,        0.0f,
                             0.0f, 0.0f, 1.002002f, 1.0f, 0.0f, 0.0f, -0.2002002f, 0.0f};

    KRYS_EXPECT_EQUAL("Frustum LH NO", Frustum_LH_NO(left, right, bottom, top, zNear, zFar), expected);
  }

  void Test_Frustum_RH_ZO()
  {
    constexpr Mat4 expected {0.1f, 0.0f, 0.0f,       0.0f,  0.0f, 0.1f, 0.0f,        0.0f,
                             0.0f, 0.0f, -1.001001f, -1.0f, 0.0f, 0.0f, -0.1001001f, 0.0f};

    KRYS_EXPECT_EQUAL("Frustum RH ZO", Frustum_RH_ZO(left, right, bottom, top, zNear, zFar), expected);
  }

  void Test_Frustum_RH_NO()
  {
    constexpr Mat4 expected {0.1f, 0.0f, 0.0f,       0.0f,  0.0f, 0.1f, 0.0f,        0.0f,
                             0.0f, 0.0f, -1.002002f, -1.0f, 0.0f, 0.0f, -0.2002002f, 0.0f};
    KRYS_EXPECT_EQUAL("Frustum RH NO", Frustum_RH_NO(left, right, bottom, top, zNear, zFar), expected);
  }

#pragma endregion Frustum

#pragma region Perspective

  void Test_Perspective_RH_ZO()
  {
    constexpr float tanHalfFovy = Tan(fovy / 2.0f);
    constexpr Mat4 expected {1 / (aspect * tanHalfFovy),
                             0,
                             0,
                             0,
                             0,
                             1 / tanHalfFovy,
                             0,
                             0,
                             0,
                             0,
                             zFar / (zNear - zFar),
                             -1,
                             0,
                             0,
                             -(zFar * zNear) / (zFar - zNear),
                             0};

    KRYS_EXPECT_EQUAL("Perspective RH ZO", Perspective_RH_ZO(fovy, aspect, zNear, zFar), expected);
  }

  void Test_Perspective_RH_NO()
  {
    constexpr float tanHalfFovy = Tan(fovy / 2.0f);
    constexpr Mat4 expected {1.0f / (aspect * tanHalfFovy),
                             0,
                             0,
                             0,
                             0,
                             1.0f / tanHalfFovy,
                             0,
                             0,
                             0,
                             0,
                             -(zFar + zNear) / (zFar - zNear),
                             -1,
                             0,
                             0,
                             -(2.0f * zFar * zNear) / (zFar - zNear),
                             0};

    KRYS_EXPECT_EQUAL("Perspective RH NO", Perspective_RH_NO(fovy, aspect, zNear, zFar), expected);
  }

  void Test_Perspective_LH_ZO()
  {
    constexpr float tanHalfFovy = Tan(fovy / 2.0f);
    constexpr Mat4 expected {1.0f / (aspect * tanHalfFovy),
                             0.0f,
                             0.0f,
                             0.0f,
                             0.0f,
                             1.0f / tanHalfFovy,
                             0.0f,
                             0.0f,
                             0.0f,
                             0.0f,
                             zFar / (zFar - zNear),
                             1.0f,
                             0.0f,
                             0.0f,
                             -(zFar * zNear) / (zFar - zNear),
                             0.0f};

    KRYS_EXPECT_EQUAL("Perspective LH ZO", Perspective_LH_ZO(fovy, aspect, zNear, zFar), expected);
  }

  void Test_Perspective_LH_NO()
  {
    constexpr float tanHalfFovy = Tan(fovy / 2.0f);
    constexpr Mat4 expected {1.0f / (aspect * tanHalfFovy),
                             0.0f,
                             0.0f,
                             0.0f,
                             0.0f,
                             1.0f / tanHalfFovy,
                             0.0f,
                             0.0f,
                             0.0f,
                             0.0f,
                             (zFar + zNear) / (zFar - zNear),
                             1.0f,
                             0.0f,
                             0.0f,
                             -(2.0f * zFar * zNear) / (zFar - zNear),
                             0.0f};

    KRYS_EXPECT_EQUAL("Perspective LH NO", Perspective_LH_NO(fovy, aspect, zNear, zFar), expected);
  }

#pragma endregion Perspective

#pragma region PerspectiveFov

  void Test_PerspectiveFov_RH_ZO()
  {
    constexpr float tanHalfFov = Tan(fov / 2.0f);
    constexpr float h = Cos(fov / 2.0f) / Sin(fov / 2.0f);
    constexpr float w = h * height / width;

    constexpr Mat4 expected {
      w, 0, 0, 0, 0, h, 0, 0, 0, 0, zFar / (zNear - zFar), -1, 0, 0, -(zFar * zNear) / (zFar - zNear), 0};

    KRYS_EXPECT_EQUAL("PerspectiveFov RH ZO", PerspectiveFov_RH_ZO(fov, width, height, zNear, zFar),
                      expected);
  }

  void Test_PerspectiveFov_RH_NO()
  {
    constexpr float tanHalfFov = Tan(fov / 2.0f);
    constexpr float h = Cos(fov / 2.0f) / Sin(fov / 2.0f);
    constexpr float w = h * height / width;
    constexpr float zDiff = zFar - zNear;

    constexpr Mat4 expected {
      w, 0, 0, 0, 0, h, 0, 0, 0, 0, -(zFar + zNear) / zDiff, -1, 0, 0, -(2 * zFar * zNear) / zDiff, 0};

    KRYS_EXPECT_EQUAL("PerspectiveFov RH NO", PerspectiveFov_RH_NO(fov, width, height, zNear, zFar),
                      expected);
  }

  void Test_PerspectiveFov_LH_ZO()
  {
    constexpr float tanHalfFov = Tan(fov / 2.0f);
    constexpr float h = Cos(fov / 2.0f) / Sin(fov / 2.0f);
    constexpr float w = h * height / width;

    constexpr Mat4 expected {
      w, 0, 0, 0, 0, h, 0, 0, 0, 0, zFar / (zFar - zNear), 1, 0, 0, -(zFar * zNear) / (zFar - zNear), 0};

    KRYS_EXPECT_EQUAL("PerspectiveFov LH ZO", PerspectiveFov_LH_ZO(fov, width, height, zNear, zFar),
                      expected);
  }

  void Test_PerspectiveFov_LH_NO()
  {
    constexpr float tanHalfFov = Tan(fov / 2.0f);
    constexpr float h = Cos(fov / 2.0f) / Sin(fov / 2.0f);
    constexpr float w = h * height / width;
    constexpr float zDiff = zFar - zNear;

    constexpr Mat4 expected {
      w, 0, 0, 0, 0, h, 0, 0, 0, 0, (zFar + zNear) / zDiff, 1, 0, 0, -(2 * zFar * zNear) / zDiff, 0};

    KRYS_EXPECT_EQUAL("PerspectiveFov LH NO", PerspectiveFov_LH_NO(fov, width, height, zNear, zFar),
                      expected);
  }

#pragma endregion PerspectiveFov

#pragma region InfinitePerspective

  void Test_InfinitePerspective_RH_ZO()
  {
    constexpr float range = Tan(fovy / 2.0f) * zNear;
    constexpr float left = -range * aspect;
    constexpr float right = range * aspect;
    constexpr float bottom = -range;
    constexpr float top = range;
    constexpr float zNear2 = 2 * zNear;

    constexpr Mat4 expected {
      zNear2 / (right - left), 0, 0, 0, 0, zNear2 / (top - bottom), 0, 0, 0, 0, -1, -1, 0, 0, -zNear, 0};

    KRYS_EXPECT_EQUAL("Infinite Perspective RH ZO", InfinitePerspective_RH_ZO(fovy, aspect, zNear), expected);
  }

  void Test_InfinitePerspective_RH_NO()
  {
    constexpr float range = Tan(fovy / 2.0f) * zNear;
    constexpr float left = -range * aspect;
    constexpr float right = range * aspect;
    constexpr float bottom = -range;
    constexpr float top = range;
    constexpr float zNear2 = 2 * zNear;

    constexpr Mat4 expected {
      zNear2 / (right - left), 0, 0, 0, 0, zNear2 / (top - bottom), 0, 0, 0, 0, -1, -1, 0, 0, -2 * zNear, 0};

    KRYS_EXPECT_EQUAL("Infinite Perspective RH NO", InfinitePerspective_RH_NO(fovy, aspect, zNear), expected);
  }

  void Test_InfinitePerspective_LH_ZO()
  {
    constexpr float range = Tan(fovy / 2.0f) * zNear;
    constexpr float left = -range * aspect;
    constexpr float right = range * aspect;
    constexpr float bottom = -range;
    constexpr float top = range;
    constexpr float zNear2 = 2 * zNear;

    constexpr Mat4 expected {
      zNear2 / (right - left), 0, 0, 0, 0, zNear2 / (top - bottom), 0, 0, 0, 0, 1, 1, 0, 0, -zNear, 0};

    KRYS_EXPECT_EQUAL("Infinite Perspective LH ZO", InfinitePerspective_LH_ZO(fovy, aspect, zNear), expected);
  }

  void Test_InfinitePerspective_LH_NO()
  {
    constexpr float range = Tan(fovy / 2.0f) * zNear;
    constexpr float left = -range * aspect;
    constexpr float right = range * aspect;
    constexpr float bottom = -range;
    constexpr float top = range;
    constexpr float zNear2 = 2 * zNear;

    constexpr Mat4 expected {
      zNear2 / (right - left), 0, 0, 0, 0, zNear2 / (top - bottom), 0, 0, 0, 0, 1, 1, 0, 0, -zNear2, 0};

    KRYS_EXPECT_EQUAL("Infinite Perspective LH NO", InfinitePerspective_LH_NO(fovy, aspect, zNear), expected);
  }

#pragma endregion InfinitePerspective
}
