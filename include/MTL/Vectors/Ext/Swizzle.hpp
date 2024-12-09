#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Vectors/Base.hpp"

namespace Krys::MTL
{
#define KRYS_SWIZZLE_BOUNDS_CHECK(lo, hi) static_assert(L >= lo && L <= hi, "Invalid vector length.");

#pragma region Two Components

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> xx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(1, 4);
    return vector_t<TComponent, 2>(v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> xy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 2>(v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> xz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 2>(v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> xw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 2>(v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> yx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 2>(v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> yy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 2>(v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> yz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 2>(v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> yw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 2>(v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> zx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 2>(v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> zy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 2>(v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> zz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 2>(v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> zw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 2>(v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> wx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 2>(v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> wy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 2>(v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> wz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 2>(v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 2> ww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 2>(v.w, v.w);
  }

#pragma endregion Two Components

#pragma region Three Components

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(1, 4);
    return vector_t<TComponent, 3>(v.x, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 3>(v.x, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.x, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.x, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 3>(v.x, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 3>(v.x, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.x, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.x, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.x, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.x, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.x, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.x, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.x, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.x, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.x, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> xww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.x, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 3>(v.y, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 3>(v.y, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.y, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.y, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 3>(v.y, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 3>(v.y, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.y, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.y, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.y, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.y, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.y, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.y, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> ywx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.y, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> ywy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.y, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> ywz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.y, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> yww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.y, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.z, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.z, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.z, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.z, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.z, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.z, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.z, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.z, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.z, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.z, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 3>(v.z, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.z, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.z, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.z, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.z, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> zww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.z, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> wwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 3> www(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 3>(v.w, v.w, v.w);
  }

#pragma endregion Three Components

#pragma region Four Components

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(1, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xxww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.x, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xywx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xywy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xywz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xyww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.y, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xzww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.z, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> xwww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.x, v.w, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yxww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.x, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(2, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yywx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yywy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yywz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yyww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.y, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> yzww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.z, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> ywww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.y, v.w, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zxww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.x, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zywx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zywy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zywz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zyww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.y, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(3, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zzww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.z, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> zwww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.z, v.w, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wxww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.x, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wywx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wywy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wywz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wyww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.y, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wzww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.z, v.w, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwxx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.x, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwxy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.x, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwxz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.x, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwxw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.x, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwyx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.y, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwyy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.y, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwyz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.y, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwyw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.y, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwzx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.z, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwzy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.z, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwzz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.z, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwzw(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.z, v.w);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwwx(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.w, v.x);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwwy(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.w, v.y);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwwz(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.w, v.z);
  }

  template <typename TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, 4> wwww(const vector_t<TComponent, L> &v) noexcept
  {
    KRYS_SWIZZLE_BOUNDS_CHECK(4, 4);
    return vector_t<TComponent, 4>(v.w, v.w, v.w, v.w);
  }

#pragma endregion Four Components
}