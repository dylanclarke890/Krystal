#pragma once

#include "Base/Concepts.hpp"
#include <MTL/Vectors/Base.hpp>

#include <format>

/// @brief Provides a custom formatter for MTL vectors
/// Unfortunately this currently able to be used at compile time.
namespace std
{
  template <Krys::IsArithmeticT T, Krys::MTL::vec_length_t N>
  struct formatter<Krys::MTL::vector_t<T, N>>
  {
    constexpr auto parse(format_parse_context &ctx)
    {
      return ctx.begin();
    }

    template <typename FormatContext>
    constexpr auto format(const Krys::MTL::vector_t<T, N> &v, FormatContext &ctx)
    {
      if constexpr (N == 1)
        return format_to(ctx.out(), "({})", v.x);
      else if constexpr (N == 2)
        return format_to(ctx.out(), "({}, {})", v.x, v.y);
      else if constexpr (N == 3)
        return format_to(ctx.out(), "({}, {}, {})", v.x, v.y, v.z);
      else if constexpr (N == 4)
        return format_to(ctx.out(), "({}, {}, {}, {})", v.x, v.y, v.z, v.w);
      else
        static_assert(N > 0 && N < 5, "Only vectors of length 1, 2, 3, or 4 are supported");
    }
  };
}