#include "MTL/Matrices/Ext/Floor.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL;

  static void Test_Floor()
  {
    // mat2x2
    constexpr mat2x2_t<float> v1 {1.1f, -2.7f, 3.4f, -4.9f};
    KRYS_EXPECT_EQUAL("Floor Mat2x2", Floor(v1), (mat2x2_t<float> {1.0f, -3.0f, 3.0f, -5.0f}));

    // mat3x3
    constexpr mat3x3_t<float> v2 {-10.5f, -5.2f, 0.0f, 5.1f, 10.8f, 15.3f, -3.7f, 4.2f, 6.6f};
    KRYS_EXPECT_EQUAL("Floor Mat3x3", Floor(v2),
                      (mat3x3_t<float> {-11.0f, -6.0f, 0.0f, 5.0f, 10.0f, 15.0f, -4.0f, 4.0f, 6.0f}));

    // mat4x4
    constexpr mat4x4_t<float> v3 {-20.1f, -10.6f, 0.0f,  10.3f, 20.5f, 30.9f, -15.2f, 15.7f,
                                  25.4f,  5.8f,   -5.3f, 0.0f,  -1.1f, 1.4f,  50.6f,  -50.9f};
    KRYS_EXPECT_EQUAL("Floor Mat4x4", Floor(v3),
                      (mat4x4_t<float> {-21.0f, -11.0f, 0.0f, 10.0f, 20.0f, 30.0f, -16.0f, 15.0f, 25.0f, 5.0f,
                                        -6.0f, 0.0f, -2.0f, 1.0f, 50.0f, -51.0f}));
  }
}
