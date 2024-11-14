#pragma once

#include "Base/Concepts.hpp"
#include "Base/Defines.hpp"
#include "Base/Types.hpp"
#include "Core/Maths/Vectors/Base.hpp"
#include "Core/Maths/Vectors/Vec1.hpp"
#include "Core/Maths/Vectors/Vec2.hpp"
#include "Core/Maths/Vectors/Vec3.hpp"
#include "Core/Maths/Vectors/Vec4.hpp"

namespace Krys
{
  template <IsArithmeticT TComponent>
  using vec1_t = MTL::Vector<TComponent, 1>;
  using Vec1 = vec1_t<float>;
  using Vec1b = vec1_t<bool>;
  using Vec1f = vec1_t<float>;
  using Vec1d = vec1_t<double>;
  using Vec1i = vec1_t<int>;
  using Vec1u = vec1_t<uint>;
  using Vec1c = vec1_t<char>;
  using Vec1uc = vec1_t<uchar>;
  using Vec1s = vec1_t<short>;
  using Vec1us = vec1_t<ushort>;
  using Vec1l = vec1_t<long>;
  using Vec1ul = vec1_t<ulong>;
  using Vec1ll = vec1_t<long long>;
  using Vec1ull = vec1_t<unsigned long long>;

  template <IsArithmeticT TComponent>
  using vec2_t = MTL::Vector<TComponent, 2>;
  using Vec2 = vec2_t<float>;
  using Vec2b = vec2_t<bool>;
  using Vec2f = vec2_t<float>;
  using Vec2d = vec2_t<double>;
  using Vec2i = vec2_t<int>;
  using Vec2u = vec2_t<uint>;
  using Vec2c = vec2_t<char>;
  using Vec2uc = vec2_t<uchar>;
  using Vec2s = vec2_t<short>;
  using Vec2us = vec2_t<ushort>;
  using Vec2l = vec2_t<long>;
  using Vec2ul = vec2_t<ulong>;
  using Vec2ll = vec2_t<long long>;
  using Vec2ull = vec2_t<unsigned long long>;

  template <IsArithmeticT TComponent>
  using vec3_t = MTL::Vector<TComponent, 3>;
  using Vec3 = vec3_t<float>;
  using Vec3b = vec3_t<bool>;
  using Vec3f = vec3_t<float>;
  using Vec3d = vec3_t<double>;
  using Vec3i = vec3_t<int>;
  using Vec3u = vec3_t<uint>;
  using Vec3c = vec3_t<char>;
  using Vec3uc = vec3_t<uchar>;
  using Vec3s = vec3_t<short>;
  using Vec3us = vec3_t<ushort>;
  using Vec3l = vec3_t<long>;
  using Vec3ul = vec3_t<ulong>;
  using Vec3ll = vec3_t<long long>;
  using Vec3ull = vec3_t<unsigned long long>;

  template <IsArithmeticT TComponent>
  using vec4_t = MTL::Vector<TComponent, 4>;
  using Vec4 = vec4_t<float>;
  using Vec4b = vec4_t<bool>;
  using Vec4f = vec4_t<float>;
  using Vec4d = vec4_t<double>;
  using Vec4i = vec4_t<int>;
  using Vec4u = vec4_t<uint>;
  using Vec4c = vec4_t<char>;
  using Vec4uc = vec4_t<uchar>;
  using Vec4s = vec4_t<short>;
  using Vec4us = vec4_t<ushort>;
  using Vec4l = vec4_t<long>;
  using Vec4ul = vec4_t<ulong>;
  using Vec4ll = vec4_t<long long>;
  using Vec4ull = vec4_t<unsigned long long>;

#ifdef KRYS_ENABLE_TESTS
  #include "Core/Maths/StaticTests.hpp"
#endif
}