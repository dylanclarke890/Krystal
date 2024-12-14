#pragma once

#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Common/Abs.hpp"
#include "MTL/Power/Pow.hpp"
#include "MTL/Vectors/Ext/Abs.hpp"
#include "MTL/Vectors/Ext/Algorithms.hpp"
#include "MTL/Vectors/Ext/Geometric.hpp"
#include "MTL/Vectors/Vec3.hpp"

namespace Krys::MTL::Norm
{
  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr TComponent L1(const vec3_t<TComponent> &a, const vec3_t<TComponent> &b) noexcept
  {
    return MTL::Abs(b.x - a.x) + MTL::Abs(b.y - a.y) + MTL::Abs(b.z - a.z);
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr TComponent L1(const vec3_t<TComponent> &v) noexcept
  {
    return MTL::Abs(v.x) + MTL::Abs(v.y) + MTL::Abs(v.z);
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr TComponent L2(const vec3_t<TComponent> &a, const vec3_t<TComponent> &b) noexcept
  {
    return MTL::Length(b - a);
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr TComponent L2(const vec3_t<TComponent> &v) noexcept
  {
    return MTL::Length(v);
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr TComponent Lx(const vec3_t<TComponent> &a, const vec3_t<TComponent> &b,
                                     uint depth) noexcept
  {
    TComponent tDepth = TComponent(depth);
    return MTL::Pow(MTL::Pow(MTL::Abs(b.x - a.x), tDepth) + MTL::Pow(MTL::Abs(b.y - a.y), tDepth)
                      + MTL::Pow(MTL::Abs(b.z - a.z), tDepth),
                    TComponent(1) / tDepth);
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr TComponent Lx(const vec3_t<TComponent> &v, uint depth) noexcept
  {
    TComponent tDepth = TComponent(depth);
    TComponent powX = MTL::Pow(MTL::Abs(v.x), tDepth);
    TComponent powY = MTL::Pow(MTL::Abs(v.y), tDepth);
    TComponent powZ = MTL::Pow(MTL::Abs(v.z), tDepth);

    return MTL::Pow(powX + powY + powZ, TComponent(1) / tDepth);
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr TComponent LMax(const vec3_t<TComponent> &a, const vec3_t<TComponent> &b) noexcept
  {
    return MTL::MaxOf(MTL::Abs(b - a));
  }

  template <IsArithmeticT TComponent>
  NO_DISCARD constexpr TComponent LMax(const vec3_t<TComponent> &v) noexcept
  {
    return MTL::MaxOf(MTL::Abs(v));
  }
}