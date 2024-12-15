#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "Base/Types.hpp"
#include "MTL/Common/Bits.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Algorithms.hpp"

namespace Krys::MTL::Bits
{
  template <IsUnsignedT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Mask(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    return MTL::MapEach(m, [](TComponent val) -> TComponent { return MTL::Bits::Mask(val); });
  }

  template <IsUnsignedT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Set(const matrix_t<TComponent, RL, CL> &m, int first, int count) noexcept
  {
    return MapEach(m, [&](TComponent x) { return Set(x, first, count); });
  }

  template <IsUnsignedT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Unset(const matrix_t<TComponent, RL, CL> &m, int first, int count) noexcept
  {
    return MapEach(m, [&](TComponent x) { return Unset(x, first, count); });
  }

  template <IsUnsignedT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto Count(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    return MapEach(m, [](TComponent x) { return Count(x); });
  }

  template <IsUnsignedT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto RotateRight(const matrix_t<TComponent, RL, CL> &m, int count) noexcept
  {
    return MapEach(m, [&](TComponent x) { return RotateRight(x, count); });
  }

  template <IsUnsignedT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto RotateLeft(const matrix_t<TComponent, RL, CL> &m, int count) noexcept
  {
    return MapEach(m, [&](TComponent x) { return RotateLeft(x, count); });
  }
}