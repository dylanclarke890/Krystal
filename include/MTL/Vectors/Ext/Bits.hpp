#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Common/Bits.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"

namespace Krys::MTL::Bits
{
  template <IsUnsignedT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Mask(const vector_t<TComponent, L> &v) noexcept
  {
    return MTL::MapEach(v, [](TComponent val) -> TComponent { return MTL::Bits::Mask(val); });
  }

  template <IsUnsignedT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Set(const vector_t<TComponent, L> &v, int first, int count) noexcept
  {
    return MapEach(v, [&](TComponent x) { return Set(x, first, count); });
  }

  template <IsUnsignedT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto Unset(const vector_t<TComponent, L> &v, int first, int count) noexcept
  {
    return MapEach(v, [&](TComponent x) { return Unset(x, first, count); });
  }

  template <IsUnsignedT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto RotateRight(const vector_t<TComponent, L> &v, int count) noexcept
  {
    return MapEach(v, [&](TComponent x) { return RotateRight(x, count); });
  }

  template <IsUnsignedT TComponent, vec_length_t L>
  NO_DISCARD constexpr auto RotateLeft(const vector_t<TComponent, L> &v, int count) noexcept
  {
    return MapEach(v, [&](TComponent x) { return RotateLeft(x, count); });
  }
}