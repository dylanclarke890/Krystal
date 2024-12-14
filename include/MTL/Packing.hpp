#pragma once

#include "Base/Attributes.hpp"
#include "Base/Types.hpp"
#include "MTL/Common/Clamp.hpp"
#include "MTL/Common/MinMax.hpp"
#include "MTL/Common/Rounding.hpp"
#include "MTL/Vectors/Vec2.hpp"
#include "MTL/Vectors/Vec3.hpp"
#include "MTL/Vectors/Vec4.hpp"

namespace Krys::MTL
{
#pragma region Pack2x8To16

  NO_DISCARD constexpr uint16 Pack2x8To16(uint8 a, uint8 b) noexcept
  {
    return (static_cast<uint16>(a) << 8) | static_cast<uint16>(b);
  }

  NO_DISCARD constexpr uint16 Pack2x8To16(const vec2_t<uint8> &v) noexcept
  {
    return Pack2x8To16(v.x, v.y);
  }

  NO_DISCARD constexpr vec2_t<uint8> Unpack16To2x8(uint16 value) noexcept
  {
    uint8 a = static_cast<uint8>((value >> 8) & 0xFF);
    uint8 b = static_cast<uint8>(value & 0xFF);
    return {a, b};
  }

  NO_DISCARD constexpr int16 Pack2x8To16(int8 a, int8 b) noexcept
  {
    return (static_cast<int16>(a) << 8) | static_cast<int16>(b);
  }

  NO_DISCARD constexpr int16 Pack2x8To16(const vec2_t<int8> &v) noexcept
  {
    return Pack2x8To16(v.x, v.y);
  }

  NO_DISCARD constexpr vec2_t<int8> Unpack16To2x8(int16 value) noexcept
  {
    int8 a = static_cast<int8>((value >> 8) & 0xFF);
    int8 b = static_cast<int8>(value & 0xFF);
    return {a, b};
  }

#pragma endregion Pack2x8To16

#pragma region Pack4x8To32

  NO_DISCARD constexpr uint32 Pack4x8To32(uint8 a, uint8 b, uint8 c, uint8 d) noexcept
  {
    return (static_cast<uint32>(a) << 24) | (static_cast<uint32>(b) << 16) | (static_cast<uint32>(c) << 8)
           | static_cast<uint32>(d);
  }

  NO_DISCARD constexpr uint32 Pack4x8To32(const vec4_t<uint8> &v) noexcept
  {
    return Pack4x8To32(v.x, v.y, v.z, v.w);
  }

  NO_DISCARD constexpr vec4_t<uint8> Unpack32To4x8(uint32 value) noexcept
  {
    uint8 a = static_cast<uint8>((value >> 24) & 0xFF);
    uint8 b = static_cast<uint8>((value >> 16) & 0xFF);
    uint8 c = static_cast<uint8>((value >> 8) & 0xFF);
    uint8 d = static_cast<uint8>(value & 0xFF);
    return {a, b, c, d};
  }

  NO_DISCARD constexpr int32 Pack4x8To32(int8 a, int8 b, int8 c, int8 d) noexcept
  {
    return (static_cast<int32>(a) << 24) | (static_cast<int32>(b) << 16) | (static_cast<int32>(c) << 8)
           | static_cast<int32>(d);
  }

  NO_DISCARD constexpr int32 Pack4x8To32(const vec4_t<int8> &v) noexcept
  {
    return Pack4x8To32(v.x, v.y, v.z, v.w);
  }

  NO_DISCARD constexpr vec4_t<int8> Unpack32To4x8(int32 value) noexcept
  {
    int8 a = static_cast<int8>((value >> 24) & 0xFF);
    int8 b = static_cast<int8>((value >> 16) & 0xFF);
    int8 c = static_cast<int8>((value >> 8) & 0xFF);
    int8 d = static_cast<int8>(value & 0xFF);
    return {a, b, c, d};
  }

#pragma endregion Pack4x8To32

#pragma region Pack2x16To32

  NO_DISCARD constexpr uint32 Pack2x16To32(uint16 a, uint16 b) noexcept
  {
    return (static_cast<uint32>(a) << 16) | static_cast<uint32>(b);
  }

  NO_DISCARD constexpr uint32 Pack2x16To32(const vec2_t<uint16> &v) noexcept
  {
    return Pack2x16To32(v.x, v.y);
  }

  NO_DISCARD constexpr vec2_t<uint16> Unpack32To2x16(uint32 value) noexcept
  {
    uint16 a = static_cast<uint16>((value >> 16) & 0xFFFF);
    uint16 b = static_cast<uint16>(value & 0xFFFF);
    return {a, b};
  }

  NO_DISCARD constexpr int32 Pack2x16To32(int16 a, int16 b) noexcept
  {
    return (static_cast<int32>(a) << 16) | static_cast<int32>(b);
  }

  NO_DISCARD constexpr int32 Pack2x16To32(const vec2_t<int16> &v) noexcept
  {
    return Pack2x16To32(v.x, v.y);
  }

  NO_DISCARD constexpr vec2_t<int16> Unpack32To2x16(int32 value) noexcept
  {
    int16 a = static_cast<int16>((value >> 16) & 0xFFFF);
    int16 b = static_cast<int16>(value & 0xFFFF);
    return {a, b};
  }

#pragma endregion Pack2x16To32

#pragma region Pack4x16To64

  NO_DISCARD constexpr uint64 Pack4x16To64(uint16 a, uint16 b, uint16 c, uint16 d) noexcept
  {
    return (static_cast<uint64>(a) << 48) | (static_cast<uint64>(b) << 32) | (static_cast<uint64>(c) << 16)
           | static_cast<uint64>(d);
  }

  NO_DISCARD constexpr uint64 Pack4x16To64(const vec4_t<uint16> &v) noexcept
  {
    return Pack4x16To64(v.x, v.y, v.z, v.w);
  }

  NO_DISCARD constexpr vec4_t<uint16> Unpack64To4x16(uint64 value) noexcept
  {
    uint16 a = static_cast<uint16>((value >> 48) & 0xFF'FF'FF'FF);
    uint16 b = static_cast<uint16>((value >> 32) & 0xFF'FF'FF'FF);
    uint16 c = static_cast<uint16>((value >> 16) & 0xFF'FF'FF'FF);
    uint16 d = static_cast<uint16>(value & 0xFF);
    return {a, b, c, d};
  }

  NO_DISCARD constexpr int64 Pack4x16To64(int16 a, int16 b, int16 c, int16 d) noexcept
  {
    return (static_cast<int64>(a) << 48) | (static_cast<int64>(b) << 32) | (static_cast<int64>(c) << 16)
           | static_cast<int64>(d);
  }

  NO_DISCARD constexpr int64 Pack4x16To64(const vec4_t<int16> &v) noexcept
  {
    return Pack4x16To64(v.x, v.y, v.z, v.w);
  }

  NO_DISCARD constexpr vec4_t<int16> Unpack64To4x16(int64 value) noexcept
  {
    int16 a = static_cast<int16>((value >> 48) & 0xFF'FF'FF'FF);
    int16 b = static_cast<int16>((value >> 32) & 0xFF'FF'FF'FF);
    int16 c = static_cast<int16>((value >> 16) & 0xFF'FF'FF'FF);
    int16 d = static_cast<int16>(value & 0xFF);
    return {a, b, c, d};
  }

#pragma endregion Pack4x16To64

#pragma region Pack2x32To64

  NO_DISCARD constexpr uint64 Pack2x32To64(uint32 a, uint32 b) noexcept
  {
    return (static_cast<uint64>(a) << 32) | static_cast<uint64>(b);
  }

  NO_DISCARD constexpr uint64 Pack2x32To64(const vec2_t<uint32> &v) noexcept
  {
    return Pack2x32To64(v.x, v.y);
  }

  NO_DISCARD constexpr vec2_t<uint32> Unpack64To2x32(uint64 value) noexcept
  {
    uint32 a = static_cast<uint32>((value >> 32) & 0xFF'FF'FF'FF);
    uint32 b = static_cast<uint32>(value & 0xFF'FF'FF'FF);
    return {a, b};
  }

  NO_DISCARD constexpr int64 Pack2x32To64(int32 a, int32 b) noexcept
  {
    return (static_cast<int64>(a) << 32) | static_cast<int64>(b);
  }

  NO_DISCARD constexpr int64 Pack2x32To64(const vec2_t<int32> &v) noexcept
  {
    return Pack2x32To64(v.x, v.y);
  }

  NO_DISCARD constexpr vec2_t<int32> Unpack64To2x32(int64 value) noexcept
  {
    int32 a = static_cast<int32>((value >> 32) & 0xFF'FF'FF'FF);
    int32 b = static_cast<int32>(value & 0xFF'FF'FF'FF);
    return {a, b};
  }

#pragma endregion Pack32x2To64

#pragma region PackNormFloatTo8

  NO_DISCARD constexpr int8 PackNormFloatToInt8(float value) noexcept
  {
    return static_cast<int8>(MTL::Round(MTL::Clamp(value, -1.0f, 1.0f) * 127.0f));
  }

  NO_DISCARD constexpr float UnpackInt8ToNormFloat(int8 value) noexcept
  {
    return static_cast<float>(value) / 127.0f;
  }

  NO_DISCARD constexpr uint8 PackNormFloatToUint8(float value) noexcept
  {
    return static_cast<uint8>(MTL::Round(MTL::Clamp(value, 0.0f, 1.0f) * 255.0f));
  }

  NO_DISCARD constexpr float UnpackUint8ToNormFloat(uint8 value) noexcept
  {
    return static_cast<float>(value) / 255.0f;
  }

#pragma endregion PackNormFloatTo8

#pragma region PackNormFloatTo16

  NO_DISCARD constexpr int16 PackNormFloatToInt16(float value) noexcept
  {
    return static_cast<int16>(MTL::Round(MTL::Clamp(value, -1.0f, 1.0f) * 32767.0f));
  }

  NO_DISCARD constexpr float UnpackInt16ToNormFloat(int16 value) noexcept
  {
    return static_cast<float>(value) / 32767.0f;
  }

  NO_DISCARD constexpr uint16 PackNormFloatToUint16(float value) noexcept
  {
    return static_cast<uint16>(MTL::Round(MTL::Clamp(value, 0.0f, 1.0f) * 65535.0f));
  }

  NO_DISCARD constexpr float UnpackUint16ToNormFloat(uint16 value) noexcept
  {
    return static_cast<float>(value) / 65535.0f;
  }

#pragma endregion PackNormFloatTo16
}
