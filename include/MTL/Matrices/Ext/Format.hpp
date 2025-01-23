#pragma once

#include "Base/Concepts.hpp"
#include <MTL/Matrices/Base.hpp>

#include <format>

/// @brief Provides a custom formatter for MTL matrices
/// Unfortunately this currently able to be used at compile time.
namespace std
{
  template <Krys::IsArithmeticT T, Krys::MTL::vec_length_t R, Krys::MTL::vec_length_t C>
  struct formatter<Krys::MTL::matrix_t<T, R, C>>
  {
    constexpr auto parse(format_parse_context &ctx)
    {
      return ctx.begin();
    }

    template <typename FormatContext>
    constexpr auto format(const Krys::MTL::matrix_t<T, R, C> &m, FormatContext &ctx)
    {
      if constexpr (R == 2 && C == 2)
        return format_to(ctx.out(), "[{}, {}]\n[{}, {}]", m[0][0], m[0][1], m[1][0], m[1][1]);
      else if constexpr (R == 2 && C == 3)
        return format_to(ctx.out(), "[{}, {}, {}]\n[{}, {}, {}]", m[0][0], m[0][1], m[0][2], m[1][0], m[1][1],
                         m[1][2]);
      else if constexpr (R == 2 && C == 4)
        return format_to(ctx.out(), "[{}, {}, {}, {}]\n[{}, {}, {}, {}]", m[0][0], m[0][1], m[0][2], m[0][3],
                         m[1][0], m[1][1], m[1][2], m[1][3]);
      else if constexpr (R == 3 && C == 2)
        return format_to(ctx.out(), "[{}, {}]\n[{}, {}]\n[{}, {}]", m[0][0], m[0][1], m[1][0], m[1][1],
                         m[2][0], m[2][1]);
      else if constexpr (R == 3 && C == 3)
        return format_to(ctx.out(), "[{}, {}, {}]\n[{}, {}, {}]\n[{}, {}, {}]", m[0][0], m[0][1], m[0][2],
                         m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);
      else if constexpr (R == 3 && C == 4)
        return format_to(ctx.out(), "[{}, {}, {}, {}]\n[{}, {}, {}, {}]\n[{}, {}, {}, {}]", m[0][0], m[0][1],
                         m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0], m[2][1], m[2][2],
                         m[2][3]);
      else if constexpr (R == 4 && C == 2)
        return format_to(ctx.out(), "[{}, {}]\n[{}, {}]\n[{}, {}]\n[{}, {}]", m[0][0], m[0][1], m[1][0],
                         m[1][1], m[2][0], m[2][1], m[3][0], m[3][1]);
      else if constexpr (R == 4 && C == 3)
        return format_to(ctx.out(), "[{}, {}, {}]\n[{}, {}, {}]\n[{}, {}, {}]\n[{}, {}, {}]", m[0][0],
                         m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0],
                         m[3][1], m[3][2]);
      else if constexpr (R == 4 && C == 4)
        return format_to(ctx.out(), "[{}, {}, {}, {}]\n[{}, {}, {}, {}]\n[{}, {}, {}, {}]\n[{}, {}, {}, {}]",
                         m[0][0], m[0][1], m[0][2], m[0][3], m[1][0], m[1][1], m[1][2], m[1][3], m[2][0],
                         m[2][1], m[2][2], m[2][3], m[3][0], m[3][1], m[3][2], m[3][3]);
      else
        static_assert(R > 1 && R < 5 && C > 1 && C < 5,
                      "Only matrices ranging from 2x2 to 4x4 are supported.");
    }
  };
}