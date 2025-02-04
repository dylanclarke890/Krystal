#include "MTL/Common/Bits.hpp"
#include "Base/Types.hpp"
#include "tests/__utils__/Expect.hpp"

namespace Krys::Tests
{
  static void Test_Bits_Mask()
  {
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask<uint8>(0), 0);
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask<uint8>(8), 0b11'111'111);
    KRYS_EXPECT_EQUAL("Mask", MTL::Bits::Mask<uint8>(3), 0b00'000'111);
  }

  static void Test_Bits_Set()
  {
    KRYS_EXPECT_EQUAL("Set", MTL::Bits::Set<uint8>(0b00'000'000, 3, 2), 0b00'011'000);
  }

  static void Test_Bits_Unset()
  {
    KRYS_EXPECT_EQUAL("Unset", MTL::Bits::Unset<uint8>(0b00'011'000, 3, 2), 0b00'000'000);
  }

  static void Test_Bits_Count()
  {
    KRYS_EXPECT_EQUAL("Count", MTL::Bits::Count<uint8>(0b00'011'000), 2);
    KRYS_EXPECT_EQUAL("Count", MTL::Bits::Count<uint8>(0b11'111'111), 8);
  }

  static void Test_Bits_RotateLeft()
  {
    KRYS_EXPECT_EQUAL("RotateLeft", MTL::Bits::RotateLeft<uint8>(0b10'000'000U, 1), 0b00'000'001U);
  }

  static void Test_Bits_RotateRight()
  {
    KRYS_EXPECT_EQUAL("RotateRight", MTL::Bits::RotateRight<uint8>(0b10'000'000U, 1), 0b01'000'000U);
  }
}