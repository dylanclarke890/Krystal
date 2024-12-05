#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"

namespace Krys::MTL
{
  /// @brief Computes the transpose of `m`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param m The input matrix.
  /// @return The transpose of `m`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto
    Transpose(const matrix_t<TComponent, CL, RL> &m) noexcept -> matrix_t<TComponent, CL, RL>::transpose_t
  {
    static_assert(CL <= 4 && RL <= 4, "Unsupported number of cols/rows.");
    using transpose_t = matrix_t<TComponent, CL, RL>::transpose_t;
    using col_t = transpose_t::column_t;

    if constexpr (CL == 2 && RL == 2)
    {
      return transpose_t(col_t {m[0].x, m[1].x}, col_t {m[0].y, m[1].y});
    }
    else if constexpr (CL == 2 && RL == 3)
    {
      return transpose_t(col_t {m[0].x, m[1].x, m[2].x}, col_t {m[0].y, m[1].y, m[2].y});
    }
    else if constexpr (CL == 2 && RL == 4)
    {
      return transpose_t(col_t {m[0].x, m[1].x, m[2].x, m[3].x}, col_t {m[0].y, m[1].y, m[2].y, m[3].y});
    }
    else if constexpr (CL == 3 && RL == 2)
    {
      return transpose_t(col_t {m[0].x, m[1].x}, col_t {m[0].y, m[1].y}, col_t {m[0].z, m[1].z});
    }
    else if constexpr (CL == 3 && RL == 3)
    {
      return transpose_t(col_t {m[0].x, m[1].x, m[2].x}, col_t {m[0].y, m[1].y, m[2].y},
                         col_t {m[0].z, m[1].z, m[2].z});
    }
    else if constexpr (CL == 3 && RL == 4)
    {
      return transpose_t(col_t {m[0].x, m[1].x, m[2].x, m[3].x}, col_t {m[0].y, m[1].y, m[2].y, m[3].y},
                         col_t {m[0].z, m[1].z, m[2].z, m[3].z});
    }
    else if constexpr (CL == 4 && RL == 2)
    {
      return transpose_t(col_t {m[0].x, m[1].x}, col_t {m[0].y, m[1].y}, col_t {m[0].z, m[1].z},col_t {m[0].w, m[1].w});
    }
    else if constexpr (CL == 4 && RL == 3)
    {
      return transpose_t(col_t {m[0].x, m[1].x, m[2].x}, col_t {m[0].y, m[1].y, m[2].y},
                         col_t {m[0].z, m[1].z, m[2].z}, col_t {m[0].w, m[1].w, m[2].w});
    }
    else if constexpr (CL == 4 && RL == 4)
    {
      return transpose_t(col_t {m[0].x, m[1].x, m[2].x, m[3].x}, col_t {m[0].y, m[1].y, m[2].y, m[3].y},
                         col_t {m[0].z, m[1].z, m[2].z, m[3].z}, col_t {m[0].w, m[1].w, m[2].w, m[3].w});
    }
  }
}
