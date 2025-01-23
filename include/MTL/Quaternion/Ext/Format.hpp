#pragma once

#include "Base/Concepts.hpp"
#include "MTL/Quaternion/Quat.hpp"

#include <format>

namespace std
{
  template <Krys::IsArithmeticT TComponent>
  struct formatter<Krys::MTL::quaternion_t<TComponent>>
  {
    constexpr auto parse(format_parse_context &ctx)
    {
      return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const Krys::MTL::quaternion_t<TComponent> &quat, FormatContext &ctx)
    {
      return format_to(ctx.out(), "Q(w: {}, x: {}, y: {}, z: {})", quat.w, quat.x, quat.y, quat.z);
    }
  };
}