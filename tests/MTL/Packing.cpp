#include "MTL/Packing.hpp"
#include "Base/Types.hpp"
#include "Core/Debug/Expect.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::Tests
{
  static void Test_2x8To16()
  {
    {
      constexpr uint8 a = 1;
      constexpr uint8 b = 1;
      constexpr vec2_t<uint8> vec(a, b);
      constexpr uint16 result = MTL::Pack2x8To16(a, b);

      KRYS_EXPECT_EQUAL("Pack2x8To16", result, uint16(257));
      KRYS_EXPECT_EQUAL("Pack2x8To16", result, MTL::Pack2x8To16(vec));
      KRYS_EXPECT_EQUAL("Unpack16toVec2x8", MTL::Unpack16To2x8(result), vec);
    }

    {
      constexpr int8 a = 1;
      constexpr int8 b = 1;
      constexpr vec2_t<int8> vec(a, b);
      constexpr int16 result = MTL::Pack2x8To16(a, b);

      KRYS_EXPECT_EQUAL("Pack2x8To16", result, int16(257));
      KRYS_EXPECT_EQUAL("Pack2x8To16", result, MTL::Pack2x8To16(vec));
      KRYS_EXPECT_EQUAL("Unpack16toVec2x8", MTL::Unpack16To2x8(result), vec);
    }
  }

  static void Test_4x8To32()
  {
    {
      constexpr uint8 a = 1;
      constexpr uint8 b = 1;
      constexpr uint8 c = 1;
      constexpr uint8 d = 1;
      constexpr vec4_t<uint8> vec(a, b, c, d);
      constexpr uint32 result = MTL::Pack4x8To32(a, b, c, d);

      KRYS_EXPECT_EQUAL("Pack4x8To32", result, uint32(16'843'009));
      KRYS_EXPECT_EQUAL("Pack4x8To32", result, MTL::Pack4x8To32(vec));
      KRYS_EXPECT_EQUAL("Unpack32To4x8", MTL::Unpack32To4x8(result), vec);
    }

    {
      constexpr int8 a = 1;
      constexpr int8 b = 1;
      constexpr int8 c = 1;
      constexpr int8 d = 1;
      constexpr vec4_t<int8> vec(a, b, c, d);
      constexpr int32 result = MTL::Pack4x8To32(a, b, c, d);

      KRYS_EXPECT_EQUAL("Pack4x8To32", result, int32(16'843'009));
      KRYS_EXPECT_EQUAL("Pack4x8To32", result, MTL::Pack4x8To32(vec));
      KRYS_EXPECT_EQUAL("Unpack32To4x8", MTL::Unpack32To4x8(result), vec);
    }
  }

  static void Test_2x16To32()
  {
    {
      constexpr uint16 a = 1;
      constexpr uint16 b = 1;
      constexpr vec2_t<uint16> vec(a, b);
      constexpr uint32 result = MTL::Pack2x16To32(a, b);

      KRYS_EXPECT_EQUAL("Pack2x16To32", result, uint32(65'537));
      KRYS_EXPECT_EQUAL("Pack2x16To32", result, MTL::Pack2x16To32(vec));
      KRYS_EXPECT_EQUAL("Unpack32To2x16", MTL::Unpack32To2x16(result), vec);
    }

    {
      constexpr int16 a = 1;
      constexpr int16 b = 1;
      constexpr vec2_t<int16> vec(a, b);
      constexpr int32 result = MTL::Pack2x16To32(a, b);

      KRYS_EXPECT_EQUAL("Pack2x16To32", result, int32(65'537));
      KRYS_EXPECT_EQUAL("Pack2x16To32", result, MTL::Pack2x16To32(vec));
      KRYS_EXPECT_EQUAL("Unpack32To2x16", MTL::Unpack32To2x16(result), vec);
    }
  }

  static void Test_4x16To64()
  {
    {
      constexpr uint16 a = 1;
      constexpr uint16 b = 1;
      constexpr uint16 c = 1;
      constexpr uint16 d = 1;
      constexpr vec4_t<uint16> vec(a, b, c, d);
      constexpr uint64 result = MTL::Pack4x16To64(a, b, c, d);

      KRYS_EXPECT_EQUAL("Pack4x16To64", result, uint64(281'479'271'743'489));
      KRYS_EXPECT_EQUAL("Pack4x16To64", result, MTL::Pack4x16To64(vec));
      KRYS_EXPECT_EQUAL("Unpack64To4x16", MTL::Unpack64To4x16(result), vec);
    }

    {
      constexpr int16 a = 1;
      constexpr int16 b = 1;
      constexpr int16 c = 1;
      constexpr int16 d = 1;
      constexpr vec4_t<int16> vec(a, b, c, d);
      constexpr int64 result = MTL::Pack4x16To64(a, b, c, d);

      KRYS_EXPECT_EQUAL("Pack4x16To64", result, int64(281'479'271'743'489));
      KRYS_EXPECT_EQUAL("Pack4x16To64", result, MTL::Pack4x16To64(vec));
      KRYS_EXPECT_EQUAL("Unpack64To4x16", MTL::Unpack64To4x16(result), vec);
    }
  }

  static void Test_2x32To64()
  {
    {
      constexpr uint32 a = 1;
      constexpr uint32 b = 1;
      constexpr vec2_t<uint32> vec(a, b);
      constexpr uint64 result = MTL::Pack2x32To64(a, b);

      KRYS_EXPECT_EQUAL("Pack2x32To64", result, uint64(4'294'967'297));
      KRYS_EXPECT_EQUAL("Pack2x32To64", result, MTL::Pack2x32To64(vec));
      KRYS_EXPECT_EQUAL("Unpack64To2x32", MTL::Unpack64To2x32(result), vec);
    }

    {
      constexpr int32 a = 1;
      constexpr int32 b = 1;
      constexpr vec2_t<int32> vec(a, b);
      constexpr int64 result = MTL::Pack2x32To64(a, b);

      KRYS_EXPECT_EQUAL("Pack2x32To64", result, int64(4'294'967'297));
      KRYS_EXPECT_EQUAL("Pack2x32To64", result, MTL::Pack2x32To64(vec));
      KRYS_EXPECT_EQUAL("Unpack64To2x32", MTL::Unpack64To2x32(result), vec);
    }
  }

  static void Test_NormFloatTo8()
  {
    KRYS_EXPECT_EQUAL("NormFloatTo8", MTL::PackNormFloatToInt8(0.5f), 64);
    KRYS_EXPECT_NEAR("Unpack8ToNormFloat", MTL::UnpackInt8ToNormFloat(64), 0.5f, 0.004f);

    KRYS_EXPECT_EQUAL("NormFloatTo8", MTL::PackNormFloatToUint8(0.5f), 128);
    KRYS_EXPECT_NEAR("Unpack8ToNormFloat", MTL::UnpackUint8ToNormFloat(128), 0.5f, 0.004f);
  }

  static void Test_NormFloatTo16()
  {
    KRYS_EXPECT_EQUAL("NormFloatTo16", MTL::PackNormFloatToInt16(0.5f), 16'384);
    KRYS_EXPECT_NEAR("Unpack16ToNormFloat", MTL::UnpackInt16ToNormFloat(16'384), 0.5f, 0.00002f);

    KRYS_EXPECT_EQUAL("NormFloatTo16", MTL::PackNormFloatToUint16(0.5f), 32'768);
    KRYS_EXPECT_NEAR("Unpack8ToNormFloat", MTL::UnpackUint16ToNormFloat(32'768), 0.5f, 0.00002f);
  }
}