#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"

namespace Krys::MTL
{
  /// @brief Computes the outer product of `m`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @param m The input matrix.
  /// @return The outer product of `m`.
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto OuterProduct(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    KRYS_STATIC_ASSERT_MATRIX_SIZE(RL, CL);
    if constexpr (CL == 2 && RL == 2)
      return matrix_t<TComponent, 2, 2>();
    else if constexpr (CL == 3 && RL == 3)
      return matrix_t<TComponent, 3, 3>();
    else if constexpr (CL == 4 && RL == 4)
      return matrix_t<TComponent, 4, 4>();
  }
}
