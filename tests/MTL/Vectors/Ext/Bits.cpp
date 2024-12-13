#include "MTL/Vectors/Ext/Bits.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Vectors/Vec1.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  static void Test_Bits_Vec1_Mask()
  {
    using vec_t = vec1_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(0)), vec_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(8)), vec_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(3)), vec_t(0b00'000'111));
  }

  static void Test_Bits_Vec2_Mask()
  {
    using vec_t = vec2_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(0)), vec_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(8)), vec_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(3)), vec_t(0b00'000'111));
  }

  static void Test_Bits_Vec3_Mask()
  {
    using vec_t = vec3_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(0)), vec_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(8)), vec_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(3)), vec_t(0b00'000'111));
  }

  static void Test_Bits_Vec4_Mask()
  {
    using vec_t = vec4_t<uint8>;

    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(0)), vec_t(0));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(8)), vec_t(0b11'111'111));
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask(vec_t(3)), vec_t(0b00'000'111));
  }

  static void Test_Bits_Vec1_Set()
  {
    using vec_t = vec1_t<uint8>;
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set(vec_t(0b00'000'000), 3, 2), vec_t(0b00'011'000));
  }

  static void Test_Bits_Vec1_Unset()
  {
    using vec_t = vec1_t<uint8>;
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset(vec_t(0b00'011'000), 3, 2), vec_t(0b00'000'000));
  }

  static void Test_Bits_Vec1_RotateLeft()
  {
    using vec_t = vec1_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft(vec_t(0b10'000'000U), 1), vec_t(0b00'000'001U));
  }

  static void Test_Bits_Vec1_RotateRight()
  {
    using vec_t = vec1_t<uint8>;
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight(vec_t(0b10'000'000U), 1), vec_t(0b01'000'000U));
  }
}