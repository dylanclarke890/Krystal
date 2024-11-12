#pragma once

#include "Base/Types.hpp"
#include "Core/Maths/Vectors/Vec1.hpp"
#include "Core/Maths/Vectors/Vec2.hpp"
#include "Core/Maths/Vectors/Vec3.hpp"
#include "Core/Maths/Vectors/Vec4.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using vec1_t = Krys::Maths::Vector<TComponent, 1>;
  using Vec1 = vec1_t<float>;
  using Vec1f = vec1_t<float>;
  using Vec1i = vec1_t<int>;
  using Vec1u = vec1_t<uint>;
  using Vec1d = vec1_t<double>;
  using Vec1c = vec1_t<char>;
  using Vec1uc = vec1_t<uchar>;
  using Vec1s = vec1_t<short>;
  using Vec1us = vec1_t<ushort>;
  using Vec1l = vec1_t<long>;
  using Vec1ul = vec1_t<ulong>;
  using Vec1ll = vec1_t<long long>;
  using Vec1ull = vec1_t<unsigned long long>;
  using Vec1b = vec1_t<bool>;

  template <IsArithmeticT TComponent>
  using vec2_t = Krys::Maths::Vector<TComponent, 2>;
  using Vec2 = vec2_t<float>;
  using Vec2f = vec2_t<float>;
  using Vec2i = vec2_t<int>;
  using Vec2u = vec2_t<uint>;
  using Vec2d = vec2_t<double>;
  using Vec2c = vec2_t<char>;
  using Vec2uc = vec2_t<uchar>;
  using Vec2s = vec2_t<short>;
  using Vec2us = vec2_t<ushort>;
  using Vec2l = vec2_t<long>;
  using Vec2ul = vec2_t<ulong>;
  using Vec2ll = vec2_t<long long>;
  using Vec2ull = vec2_t<unsigned long long>;
  using Vec2b = vec2_t<bool>;

  template <IsArithmeticT TComponent>
  using vec3_t = Krys::Maths::Vector<TComponent, 3>;
  using Vec3 = vec3_t<float>;
  using Vec3f = vec3_t<float>;
  using Vec3i = vec3_t<int>;
  using Vec3u = vec3_t<uint>;
  using Vec3d = vec3_t<double>;
  using Vec3c = vec3_t<char>;
  using Vec3uc = vec3_t<uchar>;
  using Vec3s = vec3_t<short>;
  using Vec3us = vec3_t<ushort>;
  using Vec3l = vec3_t<long>;
  using Vec3ul = vec3_t<ulong>;
  using Vec3ll = vec3_t<long long>;
  using Vec3ull = vec3_t<unsigned long long>;
  using Vec3b = vec3_t<bool>;

  template <IsArithmeticT TComponent>
  using vec4_t = Krys::Maths::Vector<TComponent, 4>;
  using Vec4 = vec4_t<float>;
  using Vec4f = vec4_t<float>;
  using Vec4i = vec4_t<int>;
  using Vec4u = vec4_t<uint>;
  using Vec4d = vec4_t<double>;
  using Vec4c = vec4_t<char>;
  using Vec4uc = vec4_t<uchar>;
  using Vec4s = vec4_t<short>;
  using Vec4us = vec4_t<ushort>;
  using Vec4l = vec4_t<long>;
  using Vec4ul = vec4_t<ulong>;
  using Vec4ll = vec4_t<long long>;
  using Vec4ull = vec4_t<unsigned long long>;
  using Vec4b = vec4_t<bool>;

  static_assert(IVector<Vec1, float>, "'Vec1' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1f, float>, "'Vec1f' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1i, int>, "'Vec1i' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1u, uint>, "'Vec1u' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1d, double>, "'Vec1d' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1c, char>, "'Vec1c' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1uc, uchar>, "'Vec1uc' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1s, short>, "'Vec1s' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1us, ushort>, "'Vec1us' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1l, long>, "'Vec1l' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1ul, ulong>, "'Vec1ul' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1ll, long long>, "'Vec1ll' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1ull, unsigned long long>, "'Vec1ull' does not satisfy 'IVector'.");
  static_assert(IVector<Vec1b, bool>, "'Vec1b' does not satisfy 'IVector'.");

  static_assert(IVector<Vec2, float>, "'Vec2' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2f, float>, "'Vec2f' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2i, int>, "'Vec2i' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2u, uint>, "'Vec2u' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2d, double>, "'Vec2d' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2c, char>, "'Vec2c' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2uc, uchar>, "'Vec2uc' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2s, short>, "'Vec2s' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2us, ushort>, "'Vec2us' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2l, long>, "'Vec2l' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2ul, ulong>, "'Vec2ul' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2ll, long long>, "'Vec2ll' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2ull, unsigned long long>, "'Vec2ull' does not satisfy 'IVector'.");
  static_assert(IVector<Vec2b, bool>, "'Vec2b' does not satisfy 'IVector'.");

  static_assert(IVector<Vec3, float>, "'Vec3' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3f, float>, "'Vec3f' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3i, int>, "'Vec3i' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3u, uint>, "'Vec3u' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3d, double>, "'Vec3d' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3c, char>, "'Vec3c' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3uc, uchar>, "'Vec3uc' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3s, short>, "'Vec3s' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3us, ushort>, "'Vec3us' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3l, long>, "'Vec3l' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3ul, ulong>, "'Vec3ul' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3ll, long long>, "'Vec3ll' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3ull, unsigned long long>, "'Vec3ull' does not satisfy 'IVector'.");
  static_assert(IVector<Vec3b, bool>, "'Vec3b' does not satisfy 'IVector'.");

  static_assert(IVector<Vec4, float>, "'Vec4' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4f, float>, "'Vec4f' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4i, int>, "'Vec4i' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4u, uint>, "'Vec4u' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4d, double>, "'Vec4d' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4c, char>, "'Vec4c' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4uc, uchar>, "'Vec4uc' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4s, short>, "'Vec4s' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4us, ushort>, "'Vec4us' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4l, long>, "'Vec4l' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4ul, ulong>, "'Vec4ul' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4ll, long long>, "'Vec4ll' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4ull, unsigned long long>, "'Vec4ull' does not satisfy 'IVector'.");
  static_assert(IVector<Vec4b, bool>, "'Vec4b' does not satisfy 'IVector'.");
}