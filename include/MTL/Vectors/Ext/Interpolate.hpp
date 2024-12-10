#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Clamp.hpp"
#include "MTL/Vectors/Base.hpp"
#include "MTL/Vectors/Ext/Clamp.hpp"

namespace Krys::MTL
{
  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Lerp(const vector_t<TComponent, L> &x,
                                                    const vector_t<TComponent, L> &y,
                                                    const vector_t<TComponent, L> &t) noexcept
  {
    vector_t<TComponent, L> weight = Clamp(t, TComponent(0), TComponent(1));
    return (x * (TComponent(1) - weight)) + (y * weight);
  }

  template <IsArithmeticT TComponent, vec_length_t L>
  NO_DISCARD constexpr vector_t<TComponent, L> Lerp(const vector_t<TComponent, L> &x,
                                                    const vector_t<TComponent, L> &y, TComponent t) noexcept
  {
    t = Clamp(t, TComponent(0), TComponent(1));
    return (x * (TComponent(1) - t)) + (y * t);
  }
}