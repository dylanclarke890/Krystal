#include "Base/Attributes.hpp"
#include "Base/Concepts.hpp"
#include "MTL/Matrices/Base.hpp"

namespace Krys::MTL
{
  /// @brief Computes the determinant of `m`.
  /// @tparam TComponent The underlying arithmetic type of the input matrix.
  /// @tparam RL The row length of the input matrix.
  /// @tparam CL The column length of the input matrix.
  /// @param m The input matrix.
  /// @return The determinant of `m`.
  template <IsArithmeticT TComponent, vec_length_t RL, vec_length_t CL>
  NO_DISCARD constexpr TComponent Determinant(const matrix_t<TComponent, RL, CL> &m) noexcept
  {
    KRYS_STATIC_ASSERT_SQUARE_MATRIX(RL, CL);

    if constexpr (RL == 2 && CL == 2)
    {
      return m[0].x * m[1].y - m[0].y * m[1].x;
    }
    else if constexpr (RL == 3 && CL == 3)
    {
      return m[0].x * (m[1].y * m[2].z - m[2].y * m[1].z) - m[1].x * (m[0].y * m[2].z - m[2].y * m[0].z)
             + m[2].x * (m[0].y * m[1].z - m[0].z * m[1].y);
    }
    else if constexpr (RL == 4 && CL == 4)
    {
      return m[0].x
               * Determinant(matrix_t<TComponent, 3, 3> {
                 {m[1].y, m[1].z, m[1].w}, {m[2].y, m[2].z, m[2].w}, {m[3].y, m[3].z, m[3].w}})
             - m[1].x
                 * Determinant(matrix_t<TComponent, 3, 3> {
                   {m[0].y, m[0].z, m[0].w}, {m[2].y, m[2].z, m[2].w}, {m[3].y, m[3].z, m[3].w}})
             + m[2].x
                 * Determinant(matrix_t<TComponent, 3, 3> {
                   {m[0].y, m[0].z, m[0].w}, {m[1].y, m[1].z, m[1].w}, {m[3].y, m[3].z, m[3].w}})
             - m[3].x
                 * Determinant(matrix_t<TComponent, 3, 3> {
                   {m[0].y, m[0].z, m[0].w}, {m[1].y, m[1].z, m[1].w}, {m[2].y, m[2].z, m[2].w}});
    }
  }
}