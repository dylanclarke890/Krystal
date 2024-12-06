#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"
#include "MTL/Matrices/Ext/Determinant.hpp"

namespace Krys::MTL
{
  /// @brief Computes the inverse of `m`.
  /// @tparam TComponent The underlying floating point type of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @param m The input matrix.
  /// @return The inverse of `m`.
  template <IsFloatingPointT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr auto
    Inverse(const matrix_t<TComponent, RL, CL> &m) noexcept -> matrix_t<TComponent, RL, CL>
  {
    if constexpr (RL == 2 && CL == 2)
    {
      TComponent oneOverDeterminant = TComponent(1) / (m[0].x * m[1].y - m[1].x * m[0].y);
      return matrix_t<TComponent, 2, 2>(+m[1].y * oneOverDeterminant, -m[0].y * oneOverDeterminant,
                                        -m[1].x * oneOverDeterminant, +m[0].x * oneOverDeterminant);
    }
    else if constexpr (RL == 3 && CL == 3)
    {
      TComponent oneOverDeterminant = TComponent(1) / (m[0].x * m[1].y - m[1].x * m[0].y);
      return matrix_t<TComponent, 3, 3>(m[0] / oneOverDeterminant, m[1] / oneOverDeterminant,
                                        m[2] / oneOverDeterminant);
    }
    else if constexpr (RL == 4 && CL == 4)
    {
      TComponent oneOverDeterminant = TComponent(1) / (m[0].x * m[1].y - m[1].x * m[0].y);
      return matrix_t<TComponent, 4, 4>(m[0] / oneOverDeterminant, m[1] / oneOverDeterminant,
                                        m[2] / oneOverDeterminant, m[3] / oneOverDeterminant);
    }
    else
      static_assert(false, "'Inverse' is only supported for square matrices.");
  }
}