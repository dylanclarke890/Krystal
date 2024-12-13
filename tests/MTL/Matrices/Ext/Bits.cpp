#include "MTL/Matrices/Ext/Bits.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Matrices/Mat2x2.hpp"
#include "MTL/Matrices/Mat2x3.hpp"
#include "MTL/Matrices/Mat2x4.hpp"
#include "MTL/Matrices/Mat3x2.hpp"
#include "MTL/Matrices/Mat3x3.hpp"
#include "MTL/Matrices/Mat3x4.hpp"
#include "MTL/Matrices/Mat4x2.hpp"
#include "MTL/Matrices/Mat4x3.hpp"
#include "MTL/Matrices/Mat4x4.hpp"

namespace Krys::Tests
{
#pragma region Mask

  static void Test_Bits_Mat2x2_Mask()
  {
    using mat_t = mat2x2_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(0)), mat_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(8)), mat_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(3)), mat_t(0b00'000'111));
  }

  static void Test_Bits_Mat2x3_Mask()
  {
    using mat_t = mat2x3_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(0)), mat_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(8)), mat_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(3)), mat_t(0b00'000'111));
  }

  static void Test_Bits_Mat2x4_Mask()
  {
    using mat_t = mat2x4_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(0)), mat_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(8)), mat_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(3)), mat_t(0b00'000'111));
  }

  static void Test_Bits_Mat3x2_Mask()
  {
    using mat_t = mat3x2_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(0)), mat_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(8)), mat_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(3)), mat_t(0b00'000'111));
  }

  static void Test_Bits_Mat3x3_Mask()
  {
    using mat_t = mat3x3_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(0)), mat_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(8)), mat_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(3)), mat_t(0b00'000'111));
  }

  static void Test_Bits_Mat3x4_Mask()
  {
    using mat_t = mat3x4_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(0)), mat_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(8)), mat_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(3)), mat_t(0b00'000'111));
  }

  static void Test_Bits_Mat4x2_Mask()
  {
    using mat_t = mat4x2_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(0)), mat_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(8)), mat_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(3)), mat_t(0b00'000'111));
  }

  static void Test_Bits_Mat4x3_Mask()
  {
    using mat_t = mat4x3_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(0)), mat_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(8)), mat_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(3)), mat_t(0b00'000'111));
  }

  static void Test_Bits_Mat4x4_Mask()
  {
    using mat_t = mat4x4_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(0)), mat_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(8)), mat_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(mat_t(3)), mat_t(0b00'000'111));
  }

#pragma endregion Mask

#pragma region Set

  static void Test_Bits_Mat2x2_Set()
  {
    using vec_t = mat2x2_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(), 3, 2), vec_t(24, 24, 24, 24));
  }

  static void Test_Bits_Mat2x3_Set()
  {
    using vec_t = mat2x3_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(), 3, 2), vec_t(24));
  }

  static void Test_Bits_Mat2x4_Set()
  {
    using vec_t = mat2x4_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(), 3, 2), vec_t(24));
  }

  static void Test_Bits_Mat3x2_Set()
  {
    using vec_t = mat3x2_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(), 3, 2), vec_t(24));
  }

  static void Test_Bits_Mat3x3_Set()
  {
    using vec_t = mat3x3_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(), 3, 2), vec_t(24, 24, 24, 24, 24, 24, 24, 24, 24));
  }

  static void Test_Bits_Mat3x4_Set()
  {
    using vec_t = mat3x4_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(), 3, 2), vec_t(24));
  }

  static void Test_Bits_Mat4x2_Set()
  {
    using vec_t = mat4x2_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(), 3, 2), vec_t(24));
  }

  static void Test_Bits_Mat4x3_Set()
  {
    using vec_t = mat4x3_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(), 3, 2), vec_t(24));
  }

  static void Test_Bits_Mat4x4_Set()
  {
    using vec_t = mat4x4_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(), 3, 2),
                      vec_t(24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24));
  }

#pragma endregion Set

#pragma region Unset

  static void Test_Bits_Mat2x2_Unset()
  {
    using mat_t = mat2x2_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(mat_t(0b00'011'000), 3, 2), mat_t(0b00'000'000));
  }

  static void Test_Bits_Mat2x3_Unset()
  {
    using mat_t = mat2x3_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(mat_t(0b00'011'000), 3, 2), mat_t(0b00'000'000));
  }

  static void Test_Bits_Mat2x4_Unset()
  {
    using mat_t = mat2x4_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(mat_t(0b00'011'000), 3, 2), mat_t(0b00'000'000));
  }

  static void Test_Bits_Mat3x2_Unset()
  {
    using mat_t = mat3x2_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(mat_t(0b00'011'000), 3, 2), mat_t(0b00'000'000));
  }

  static void Test_Bits_Mat3x3_Unset()
  {
    using mat_t = mat3x3_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(mat_t(0b00'011'000), 3, 2), mat_t(0b00'000'000));
  }

  static void Test_Bits_Mat3x4_Unset()
  {
    using mat_t = mat3x4_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(mat_t(0b00'011'000), 3, 2), mat_t(0b00'000'000));
  }

  static void Test_Bits_Mat4x2_Unset()
  {
    using mat_t = mat4x2_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(mat_t(0b00'011'000), 3, 2), mat_t(0b00'000'000));
  }

  static void Test_Bits_Mat4x3_Unset()
  {
    using mat_t = mat4x3_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(mat_t(0b00'011'000), 3, 2), mat_t(0b00'000'000));
  }

  static void Test_Bits_Mat4x4_Unset()
  {
    using mat_t = mat4x4_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(mat_t(0b00'011'000), 3, 2), mat_t(0b00'000'000));
  }

#pragma endregion Unset

#pragma region RotateLeft

  static void Test_Bits_Mat2x2_RotateLeft()
  {
    using mat_t = mat2x2_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(mat_t(0b10'000'000U), 1), mat_t(0b00'000'001U));
  }

  static void Test_Bits_Mat2x3_RotateLeft()
  {
    using mat_t = mat2x3_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(mat_t(0b10'000'000U), 1), mat_t(0b00'000'001U));
  }

  static void Test_Bits_Mat2x4_RotateLeft()
  {
    using mat_t = mat2x4_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(mat_t(0b10'000'000U), 1), mat_t(0b00'000'001U));
  }

  static void Test_Bits_Mat3x2_RotateLeft()
  {
    using mat_t = mat3x2_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(mat_t(0b10'000'000U), 1), mat_t(0b00'000'001U));
  }

  static void Test_Bits_Mat3x3_RotateLeft()
  {
    using mat_t = mat3x3_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(mat_t(0b10'000'000U), 1), mat_t(0b00'000'001U));
  }

  static void Test_Bits_Mat3x4_RotateLeft()
  {
    using mat_t = mat3x4_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(mat_t(0b10'000'000U), 1), mat_t(0b00'000'001U));
  }

  static void Test_Bits_Mat4x2_RotateLeft()
  {
    using mat_t = mat4x2_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(mat_t(0b10'000'000U), 1), mat_t(0b00'000'001U));
  }

  static void Test_Bits_Mat4x3_RotateLeft()
  {
    using mat_t = mat4x3_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(mat_t(0b10'000'000U), 1), mat_t(0b00'000'001U));
  }

  static void Test_Bits_Mat4x4_RotateLeft()
  {
    using mat_t = mat4x4_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(mat_t(0b10'000'000U), 1), mat_t(0b00'000'001U));
  }

#pragma endregion RotateLeft

#pragma region RotateRight

  static void Test_Bits_Mat2x2_RotateRight()
  {
    using mat_t = mat2x2_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(mat_t(0b10'000'000U), 1), mat_t(0b01'000'000U));
  }

  static void Test_Bits_Mat2x3_RotateRight()
  {
    using mat_t = mat2x3_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(mat_t(0b10'000'000U), 1), mat_t(0b01'000'000U));
  }

  static void Test_Bits_Mat2x4_RotateRight()
  {
    using mat_t = mat2x4_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(mat_t(0b10'000'000U), 1), mat_t(0b01'000'000U));
  }

  static void Test_Bits_Mat3x2_RotateRight()
  {
    using mat_t = mat3x2_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(mat_t(0b10'000'000U), 1), mat_t(0b01'000'000U));
  }

  static void Test_Bits_Mat3x3_RotateRight()
  {
    using mat_t = mat3x3_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(mat_t(0b10'000'000U), 1), mat_t(0b01'000'000U));
  }

  static void Test_Bits_Mat3x4_RotateRight()
  {
    using mat_t = mat3x4_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(mat_t(0b10'000'000U), 1), mat_t(0b01'000'000U));
  }

  static void Test_Bits_Mat4x2_RotateRight()
  {
    using mat_t = mat4x2_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(mat_t(0b10'000'000U), 1), mat_t(0b01'000'000U));
  }

  static void Test_Bits_Mat4x3_RotateRight()
  {
    using mat_t = mat4x3_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(mat_t(0b10'000'000U), 1), mat_t(0b01'000'000U));
  }

  static void Test_Bits_Mat4x4_RotateRight()
  {
    using mat_t = mat2x2_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(mat_t(0b10'000'000U), 1), mat_t(0b01'000'000U));
  }

#pragma endregion RotateRight
}