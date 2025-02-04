#include "MTL/MortonCodes.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL::Morton;

#pragma region uint8

  static void Test_MortonCodes_Encode_2_uint8()
  {
    constexpr uint8 x = 0b11'111'111;
    constexpr uint8 y = 0b00'000'000;

    constexpr uint16 expected = 0b0'101'010'101'010'101;
    constexpr uint16 result = Encode(x, y);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint8, uint8)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec2_uint8()
  {
    constexpr uint8 x = 0b11'111'111;
    constexpr uint8 y = 0b00'000'000;
    constexpr vec2_t<uint8> v(x, y);

    constexpr uint16 expected = 0b0'101'010'101'010'101;
    constexpr uint16 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec2(uint8, uint8)", result, expected);
  }

  static void Test_MortonCodes_Encode_3_uint8()
  {
    constexpr uint8 x = 5;
    constexpr uint8 y = 9;
    constexpr uint8 z = 1;

    constexpr uint16 expected = 0b010'001'000'111;
    constexpr uint16 result = Encode(x, y, z);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint8, uint8, uint8)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec3_uint8()
  {
    constexpr uint8 x = 5;
    constexpr uint8 y = 9;
    constexpr uint8 z = 1;
    constexpr vec3_t<uint8> v(x, y, z);

    constexpr uint16 expected = 0b010'001'000'111;
    constexpr uint16 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec3(uint8, uint8, uint8)", result, expected);
  }

  static void Test_MortonCodes_Encode_4_uint8()
  {
    constexpr uint8 x = 0b11'111'111;
    constexpr uint8 y = 0b11'111'111;
    constexpr uint8 z = 0b00'000'000;
    constexpr uint8 w = 0b00'000'000;

    constexpr uint32 expected = 0b00'110'011'001'100'110'011'001'100'110'011;
    constexpr uint32 result = Encode(x, y, z, w);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint8, uint8, uint8, uint8)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec4_uint8()
  {
    constexpr uint8 x = 0b11'111'111;
    constexpr uint8 y = 0b11'111'111;
    constexpr uint8 z = 0b00'000'000;
    constexpr uint8 w = 0b00'000'000;
    constexpr vec4_t<uint8> v(x, y, z, w);

    constexpr uint32 expected = 0b00'110'011'001'100'110'011'001'100'110'011;
    constexpr uint32 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec4(uint8, uint8, uint8, uint8)", result, expected);
  }

  static void Test_MortonCodes_Decode_uint16()
  {
    constexpr uint16 v = 0b0'101'010'101'010'101;
    constexpr vec2_t<uint8> expected(0b11'111'111, 0b00'000'000);

    constexpr auto result = Decode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Decode uint16", result, expected);
  }

#pragma endregion uint8

#pragma region int8

  static void Test_MortonCodes_Encode_2_int8()
  {
    constexpr int8 x = 0b11'111'111;
    constexpr int8 y = 0b00'000'000;

    constexpr int16 expected = 0b0'101'010'101'010'101;
    constexpr int16 result = Encode(x, y);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (int8, int8)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec2_int8()
  {
    constexpr int8 x = 0b11'111'111;
    constexpr int8 y = 0b00'000'000;
    constexpr vec2_t<int8> v(x, y);

    constexpr int16 expected = 0b0'101'010'101'010'101;
    constexpr int16 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec2(int8, int8)", result, expected);
  }

  static void Test_MortonCodes_Encode_3_int8()
  {
    constexpr int8 x = 5;
    constexpr int8 y = 9;
    constexpr int8 z = 1;

    constexpr int32 expected = 0b010'001'000'111;
    constexpr int32 result = Encode(x, y, z);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (int8, int8, int8)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec3_int8()
  {
    constexpr int8 x = 5;
    constexpr int8 y = 9;
    constexpr int8 z = 1;
    constexpr vec3_t<int8> v(x, y, z);

    constexpr int16 expected = 0b010'001'000'111;
    constexpr int16 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec3(int8, int8, int8)", result, expected);
  }

  static void Test_MortonCodes_Encode_4_int8()
  {
    constexpr int8 x = 0b11'111'111;
    constexpr int8 y = 0b11'111'111;
    constexpr int8 z = 0b00'000'000;
    constexpr int8 w = 0b00'000'000;

    constexpr int32 expected = 0b00'110'011'001'100'110'011'001'100'110'011;
    constexpr int32 result = Encode(x, y, z, w);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (int8, int8, int8, int8)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec4_int8()
  {
    constexpr int8 x = 0b11'111'111;
    constexpr int8 y = 0b11'111'111;
    constexpr int8 z = 0b00'000'000;
    constexpr int8 w = 0b00'000'000;
    constexpr vec4_t<int8> v(x, y, z, w);

    constexpr int32 expected = 0b00'110'011'001'100'110'011'001'100'110'011;
    constexpr int32 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec4(int8, int8, int8, int8)", result, expected);
  }

#pragma endregion int8

#pragma region uint16

  static void Test_MortonCodes_Encode_2_uint16()
  {
    constexpr uint16 x = 0b1'111'111'111'111'111;
    constexpr uint16 y = 0b0'000'000'000'000'000;

    constexpr uint32 expected = 0b01'010'101'010'101'010'101'010'101'010'101;
    constexpr uint32 result = Encode(x, y);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint16, uint16)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec2_uint16()
  {
    constexpr uint16 x = 0b1'111'111'111'111'111;
    constexpr uint16 y = 0b0'000'000'000'000'000;

    constexpr vec2_t<uint16> v(x, y);

    constexpr uint32 expected = 0b01'010'101'010'101'010'101'010'101'010'101;
    constexpr uint32 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec3(uint16, uint16)", result, expected);
  }

  static void Test_MortonCodes_Encode_3_uint16()
  {
    constexpr uint16 x = 5;
    constexpr uint16 y = 9;
    constexpr uint16 z = 1;

    constexpr uint32 expected = 1'095;
    constexpr uint32 result = Encode(x, y, z);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint16, uint16, uint16)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec3_uint16()
  {
    constexpr uint16 x = 5;
    constexpr uint16 y = 9;
    constexpr uint16 z = 1;
    constexpr vec3_t<uint16> v(x, y, z);

    constexpr uint32 expected = 1'095;
    constexpr uint32 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec3(uint16, uint16, uint16)", result, expected);
  }

  static void Test_MortonCodes_Encode_4_uint16()
  {
    constexpr uint16 x = 0b1'111'111'111'111'111;
    constexpr uint16 y = 0b1'111'111'111'111'111;
    constexpr uint16 z = 0b0'000'000'000'000'000;
    constexpr uint16 w = 0b0'000'000'000'000'000;

    constexpr uint64 expected =
      0b0'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011;
    constexpr uint64 result = Encode(x, y, z, w);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint16, uint16, uint16, uint16)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec4_uint16()
  {
    constexpr uint16 x = 0b1'111'111'111'111'111;
    constexpr uint16 y = 0b1'111'111'111'111'111;
    constexpr uint16 z = 0b0'000'000'000'000'000;
    constexpr uint16 w = 0b0'000'000'000'000'000;
    constexpr vec4_t<uint16> v(x, y, z, w);

    constexpr uint64 expected =
      0b0'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011;
    constexpr uint64 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec4(uint16, uint16, uint16, uint16)", result, expected);
  }

  static void Test_MortonCodes_Decode_uint32()
  {
    constexpr uint32 v = 0b01'010'101'010'101'010'101'010'101'010'101;

    constexpr uint16 x = 0b1'111'111'111'111'111;
    constexpr uint16 y = 0b0'000'000'000'000'000;

    constexpr vec2_t<uint16> expected(x, y);
    constexpr auto result = Decode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Decode uint32", result, expected);
  }

#pragma endregion uint16

#pragma region int16

  static void Test_MortonCodes_Encode_2_int16()
  {
    constexpr int16 x = 0b1'111'111'111'111'111;
    constexpr int16 y = 0b0'000'000'000'000'000;

    constexpr int32 expected = 0b01'010'101'010'101'010'101'010'101'010'101;
    constexpr int32 result = Encode(x, y);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (int16, int16)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec2_int16()
  {
    constexpr int16 x = 0b1'111'111'111'111'111;
    constexpr int16 y = 0b0'000'000'000'000'000;

    constexpr vec2_t<int16> v(x, y);

    constexpr int32 expected = 0b01'010'101'010'101'010'101'010'101'010'101;
    constexpr int32 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec3(int16, int16)", result, expected);
  }

  static void Test_MortonCodes_Encode_3_int16()
  {
    constexpr int16 x = 5;
    constexpr int16 y = 9;
    constexpr int16 z = 1;

    constexpr int64 expected = 1'095;
    constexpr int64 result = Encode(x, y, z);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (int16, int16, int16)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec3_int16()
  {
    constexpr int16 x = 5;
    constexpr int16 y = 9;
    constexpr int16 z = 1;
    constexpr vec3_t<int16> v(x, y, z);

    constexpr int32 expected = 1'095;
    constexpr int32 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec3(int16, int16, int16)", result, expected);
  }

  static void Test_MortonCodes_Encode_4_int16()
  {
    constexpr int16 x = 0b1'111'111'111'111'111;
    constexpr int16 y = 0b1'111'111'111'111'111;
    constexpr int16 z = 0b0'000'000'000'000'000;
    constexpr int16 w = 0b0'000'000'000'000'000;

    constexpr int64 expected =
      0b0'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011;
    constexpr int64 result = Encode(x, y, z, w);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (int16, int16, int16, int16)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec4_int16()
  {
    constexpr int16 x = 0b1'111'111'111'111'111;
    constexpr int16 y = 0b1'111'111'111'111'111;
    constexpr int16 z = 0b0'000'000'000'000'000;
    constexpr int16 w = 0b0'000'000'000'000'000;
    constexpr vec4_t<int16> v(x, y, z, w);

    constexpr int64 expected =
      0b0'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011;
    constexpr int64 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec4(int16, int16, int16, int16)", result, expected);
  }

#pragma endregion int16

#pragma region uint32

  static void Test_MortonCodes_Encode_2_uint32()
  {
    constexpr uint32 x = 0b11'111'111'111'111'111'111'111'111'111'111;
    constexpr uint32 y = 0b00'000'000'000'000'000'000'000'000'000'000;

    constexpr uint64 expected =
      0b0'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101;
    constexpr uint64 result = Encode(x, y);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint32, uint32)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec2_uint32()
  {
    constexpr uint32 x = 0b11'111'111'111'111'111'111'111'111'111'111;
    constexpr uint32 y = 0b00'000'000'000'000'000'000'000'000'000'000;
    constexpr vec2_t<uint32> v(x, y);

    constexpr uint64 expected =
      0b0'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101;
    constexpr uint64 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec2(uint32, uint32)", result, expected);
  }

  static void Test_MortonCodes_Encode_3_uint32()
  {
    constexpr uint32 x = 5;
    constexpr uint32 y = 9;
    constexpr uint32 z = 1;

    constexpr uint64 expected = 1'095;
    constexpr uint64 result = Encode(x, y, z);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint32, uint32, uint32)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec3_uint32()
  {
    constexpr uint32 x = 5;
    constexpr uint32 y = 9;
    constexpr uint32 z = 1;
    constexpr vec3_t<uint32> v(x, y, z);

    constexpr uint64 expected = 1'095;
    constexpr uint64 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec3(uint32, uint32, uint32)", result, expected);
  }

  static void Test_MortonCodes_Decode_uint64()
  {
    constexpr uint64 v =
      0b0'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101;

    constexpr uint32 x = 0b11'111'111'111'111'111'111'111'111'111'111;
    constexpr uint32 y = 0b00'000'000'000'000'000'000'000'000'000'000;
    constexpr vec2_t<uint32> expected(x, y);

    constexpr auto result = Decode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Decode uint64", result, expected);
  }

#pragma endregion uint32

#pragma region int32

  static void Test_MortonCodes_Encode_2_int32()
  {
    constexpr int32 x = 0b11'111'111'111'111'111'111'111'111'111'111;
    constexpr int32 y = 0b00'000'000'000'000'000'000'000'000'000'000;

    constexpr int64 expected =
      0b0'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101;
    constexpr int64 result = Encode(x, y);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (int32, int32)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec2_int32()
  {
    constexpr int32 x = 0b11'111'111'111'111'111'111'111'111'111'111;
    constexpr int32 y = 0b00'000'000'000'000'000'000'000'000'000'000;
    constexpr vec2_t<int32> v(x, y);

    constexpr int64 expected =
      0b0'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101;
    constexpr int64 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec2(int32, int32)", result, expected);
  }

  static void Test_MortonCodes_Encode_3_int32()
  {
    constexpr int32 x = 5;
    constexpr int32 y = 9;
    constexpr int32 z = 1;

    constexpr int64 expected = 1'095;
    constexpr int64 result = Encode(x, y, z);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (int32, int32, int32)", result, expected);
  }

  static void Test_MortonCodes_Encode_Vec3_int32()
  {
    constexpr int32 x = 5;
    constexpr int32 y = 9;
    constexpr int32 z = 1;
    constexpr vec3_t<int32> v(x, y, z);

    constexpr int64 expected = 1'095;
    constexpr int64 result = Encode(v);

    KRYS_EXPECT_EQUAL("MortonCodes Encode Vec3(int32, int32, int32)", result, expected);
  }

#pragma endregion int32
}
