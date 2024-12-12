#include "MTL/Common/MortonCodes.hpp"
#include "Core/Debug/Expect.hpp"

namespace Krys::Tests
{
  using namespace Krys::MTL::Morton;

  static void Test_MortonCodes_Encode_2_uint8()
  {
    constexpr uint8 x = 0b11'111'111;
    constexpr uint8 y = 0b00'000'000;

    constexpr uint16 expected = 0b0'101'010'101'010'101;
    constexpr uint16 result = Encode(x, y);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint8, uint8)", result, expected);
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

  static void Test_MortonCodes_Encode_2_uint16()
  {
    constexpr uint16 x = 0b1'111'111'111'111'111;
    constexpr uint16 y = 0b0'000'000'000'000'000;

    constexpr uint32 expected = 0b01'010'101'010'101'010'101'010'101'010'101;
    constexpr uint32 result = Encode(x, y);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint16, uint16)", result, expected);
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

  static void Test_MortonCodes_Encode_4_uint16()
  {
    constexpr uint16 x = 0b1'111'111'111'111'111;
    constexpr uint16 y = 0b1'111'111'111'111'111;
    constexpr uint16 z = 0b0'000'000'000'000'000;
    constexpr uint16 w = 0b0'000'000'000'000'000;

    constexpr uint64 expected =
      0b0'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011'001'100'110'011;
    constexpr uint64 result = Encode(x, y, z, w);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint8, uint8, uint8, uint8)", result, expected);
  }

  static void Test_MortonCodes_Encode_2_uint32()
  {
    constexpr uint32 x = 0b11'111'111'111'111'111'111'111'111'111'111;
    constexpr uint32 y = 0b00'000'000'000'000'000'000'000'000'000'000;

    constexpr uint64 expected =
      0b0'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101'010'101;
    constexpr uint64 result = Encode(x, y);

    KRYS_EXPECT_EQUAL("MortonCodes Encode (uint32, uint32)", result, expected);
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
}
