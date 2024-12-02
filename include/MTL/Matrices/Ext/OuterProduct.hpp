#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"

namespace Krys::MTL
{
  /// @brief Computes the outer product of `m`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @param m The input matrix.
  /// @return The outer product of `m`.
  template <IsArithmeticT TComponent, vec_length_t CL, vec_length_t RL>
  NO_DISCARD constexpr auto OuterProduct(const matrix_t<TComponent, CL, RL> &m) noexcept
  {
    if constexpr (CL == 2 && RL == 2)
      return matrix_t<TComponent, 2, 2>();
    else if constexpr (CL == 3 && RL == 3)
      return matrix_t<TComponent, 3, 3>();
    else if constexpr (CL == 4 && RL == 4)
      return matrix_t<TComponent, 4, 4>();
    else
      static_assert(false, "Unsupported number of cols/rows.");
  }
}
